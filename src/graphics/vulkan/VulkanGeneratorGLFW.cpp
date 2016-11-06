#include "VulkanGeneratorGLFW.hpp"

#include <iostream>
#include <sstream>

#define GLFW_INCLUDE_GL_3
#include "GLFW/glfw3.h"

#include "VulkanContextGLFW.hpp"
#include "GraphicsHandler.hpp"
//#include "CallbackSingleton.hpp"


namespace graphics
{


///
/// \brief VulkanGeneratorGLFW::VulkanGeneratorGLFW
///
VulkanGeneratorGLFW::VulkanGeneratorGLFW( )
  :
  GraphicsGenerator ( )
  , glfwInitialized_( false )
{

  if ( !_initGLFW( ) )
  {

    throw std::runtime_error( "GLFW init failed" );

  }

}



///
/// \brief VulkanGeneratorGLFW::~VulkanGeneratorGLFW
///
VulkanGeneratorGLFW::~VulkanGeneratorGLFW( )
{

  //
  // must delete handlers first because they have all
  // the window contexts
  //
  handlers_.clear( );

  _terminateGLFW( );

}



///
/// \brief VulkanGeneratorGLFW::generateHandler
/// \param title
/// \return
///
GraphicsHandler&
VulkanGeneratorGLFW::generateHandler(
                                     std::string  title,
                                     unsigned int width,
                                     unsigned int height
                                     )
{

  try
  {

    int iwidth  = static_cast< int >( width );
    int iheight = static_cast< int >( height );

    std::unique_ptr< GraphicsContext > context( new VulkanContextGLFW(
                                                                      title,
                                                                      iwidth,
                                                                      iheight
                                                                      ) );

    std::unique_ptr< GraphicsHandler > handler( new GraphicsHandler(
                                                                    context,
                                                                    static_cast< int >( iwidth ),
                                                                    static_cast< int >( iheight )
                                                                    ) );

    handlers_.push_back( std::move( handler ) );

  }
  catch ( const std::exception &e )
  {

    std::stringstream msg;
    msg << "Vulklan graphics handler init failed: " << e.what( );
    throw( std::runtime_error( msg.str( ) ) );

  }

  return *handlers_.back( );

} // VulkanGeneratorGLFW::generateHandler



///
/// \brief VulkanGeneratorGLFW::checkEvents
///
void
VulkanGeneratorGLFW::checkEvents( )
{

  glfwPollEvents( );

}



///
/// \brief VulkanGeneratorGLFW::_initGLFW
/// \return
///
bool
VulkanGeneratorGLFW::_initGLFW( )
{

  //
  // set error callback before anything else to get
  // error messages from future calls
  //
//  glfwSetErrorCallback( CallbackSingleton::errorCallback );

  //
  // If we aren't already initialized then try
  // to initialized GLFW.
  //
  if ( !glfwInitialized_ && !glfwInit( ) )
  {

    //
    // init failed
    //
    return false;

  }

  std::cout << "Initialized GLFW Version: ";
  std::cout << glfwGetVersionString( ) << std::endl;


  glfwInitialized_ = true;

  //
  // using vulkan so we don't need OpenGL
  //
  glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );

  //
  // temporary until we handle resizing
  //
  glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE );

  return true;

} // VulkanGeneratorGLFW::_initGLFW



///
/// \brief VulkanGeneratorGLFW::_terminateGLFW
///
void
VulkanGeneratorGLFW::_terminateGLFW( )
{

  if ( glfwInitialized_ )
  {

    glfwTerminate( );
    glfwInitialized_ = false;
    //
    // ready to be initialized again if necessary
    //
    std::cout << "Terminated GLFW" << std::endl;

  }

}



} // namespace graphics
