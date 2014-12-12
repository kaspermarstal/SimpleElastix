#ifndef __selxsimpletransformix_h_
#define __selxsimpletransformix_h_

// SimpleITK
#include "sitkSimpleElastix.h"
#include "sitkPixelIDTokens.h"
#include "sitkImage.h"
#include "sitkMemberFunctionFactory.h"

// SimpleTransformix
#include "transformixlib.h"

namespace itk { 
  namespace simple {

class SELX_EXPORT SimpleTransformix
{
  public:

    SimpleTransformix( void );
    ~SimpleTransformix( void );
    
    typedef SimpleTransformix Self;
    typedef itk::ParameterFileParser::ParameterMapType      ParameterMapType;
    typedef ParameterMapType::iterator                      ParameterMapIterator;
    typedef std::vector< ParameterMapType >                 ParameterMapListType;
    typedef ParameterMapListType::iterator                  ParameterMapListIterator;
    typedef std::string                                     ParameterKeyType;
    typedef itk::ParameterFileParser::ParameterValuesType   ParameterValuesType;
    typedef itk::ParameterFileParser                        ParameterFileParserType;
    typedef ParameterFileParserType::Pointer                ParameterFileParserPointer;
 
    // typedefs inherited from SimpleITK
    typedef BasicPixelIDTypeList PixelIDTypeList;

    // typedefs inherited from elastix library api
    typedef transformix::TRANSFORMIX libtransformix;

    /** To be wrapped by SWIG */ 

    const std::string GetName( void );

    // Images
    void SetInputImage( Image* fixedImage );

    // Warp images
    Image Execute( void );

    // Get result
    Image GetResultImage( void );

    // Output
    void SetOutputFolder( const std::string folder );
    void LogToDisk( bool );
    void LogToDiskOn( void );
    void LogToDiskOff( void );
    void LogToConsole( bool );
    void LogToConsoleOn( void );
    void LogToConsoleOff( void );

    void SetTransformParameterMapList( std::vector< std::map< std::string, std::vector< std::string > > > parameterMapList );
    void SetTransformParameterMap( std::map< std::string, std::vector< std::string > > parameterMap );
    std::vector< std::map< std::string, std::vector< std::string > > > GetTransformParameterMapList( void );

    ParameterMapType ParameterFileReader( const std::string filename );

  private:

    template< typename TResultImage >
    Image ExecuteInternal( void );

    // Addressor of this class for member function factory
    #ifndef SWIG
      template < class TMemberFunctionPointer >
      struct SimpleTransformixAddressor
      {
        typedef typename ::detail::FunctionTraits< TMemberFunctionPointer >::ClassType ObjectType;

        template< typename TResultImage >
        TMemberFunctionPointer operator() ( void ) const
        {
          return &ObjectType::template ExecuteInternal< TResultImage >;
        }
      };
    #endif

    // Functions to register SimpleElastix with SimpleITK member factory
    typedef Image ( Self::*MemberFunctionType )( void );
    std::auto_ptr< detail::MemberFunctionFactory< MemberFunctionType > > m_MemberFactory;

    // This class holds configuration and pointers to data that is passed to transformix API when run
    Image*                 m_InputImage;
    Image                  m_ResultImage;
    std::string            m_OutputFolder;
    bool                   m_LogToDisk;
    bool                   m_LogToConsole;
    ParameterMapListType   m_TransformParameterMaps;

};

// Procedural Interface 
SELX_EXPORT Image transformix( Image inputImage, std::map< std::string, std::vector< std::string > > parameterMap, bool logToConsole = false, bool logToDisk = false, std::string outputFolder = "" );
SELX_EXPORT Image transformix( Image fixedImage, SimpleTransformix::ParameterMapListType parameterMapList, bool logToConsole = false, bool logToDisk = false, std::string outputFolder = "" );


} // end namespace simple
} // end namespace itk

#endif // __selxsimpleelastix_h_