#include "VulkanContextGLFW.hpp"

#include <vector>
#include <iostream>

#define GLFW_INCLUDE_GL_3
#include "GLFW/glfw3.h"


namespace graphics
{


//
// Vulkan helper functions and variables for initialization
//
namespace
{

//
// requested error checking layers
//
const std::vector< const char* > validationLayers
{

  "VK_LAYER_LUNARG_standard_validation"

};

//
// only enable validation for debug builds
//
#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif


///
/// \brief checkValidationLayerSupport
///
///        Check for the availability of the requested
///        Vulkan validation layers
///
/// \return
///
bool
checkValidationLayerSupport( )
{

  uint32_t layerCount;

  vkEnumerateInstanceLayerProperties( &layerCount, nullptr );

  std::vector< VkLayerProperties > availableLayers( layerCount );
  vkEnumerateInstanceLayerProperties( &layerCount, availableLayers.data( ) );

  for ( const char *layerName : validationLayers )
  {

    bool layerFound = false;

    for ( const auto & layerProperties : availableLayers )
    {

      if ( strcmp( layerName, layerProperties.layerName ) == 0 )
      {

        layerFound = true;
        break;

      }

    }

    if ( !layerFound )
    {

      return false;

    }

  }

  return true;

} // checkValidationLayerSupport



///
/// \brief getRequiredExtensions
///
///        Get the required list of extensions based on
///        whether validation layers are enabled or not
///
/// \return
///
std::vector< const char* >
getRequiredExtensions( )
{

  std::vector< const char* > extensions;

  unsigned int glfwExtensionCount = 0;
  const char**glfwExtensions( glfwGetRequiredInstanceExtensions( &glfwExtensionCount ) );

  for ( unsigned int i = 0; i < glfwExtensionCount; i++ )
  {

    extensions.push_back( glfwExtensions[ i ] );

  }

  if ( enableValidationLayers )
  {

    extensions.push_back( VK_EXT_DEBUG_REPORT_EXTENSION_NAME );

  }

  return extensions;

} // getRequiredExtensions



///
/// \brief debugCallback
/// \param flags
/// \param objType
/// \param obj
/// \param location
/// \param code
/// \param layerPrefix
/// \param msg
/// \param userData
///
VKAPI_ATTR VkBool32 VKAPI_CALL
debugCallback(
              VkDebugReportFlagsEXT,
              VkDebugReportObjectTypeEXT,
              uint64_t,
              size_t,
              int32_t,
              const char*,
              const char *msg,
              void*
              )
{

  std::cerr << "Vulkan validation layer: " << msg << std::endl;

  return VK_FALSE;

}



}


VulkanContextGLFW::VulkanContextGLFW(
                                     const std::string title,
                                     const int         width,
                                     const int         height
                                     )
  :
  GraphicsContext( title, width, height )
{

  _initWindow( title, width, height );
  _initVulkan( title );

}



///
/// \brief VulkanContextGLFW::~VulkanContextGLFW
///
VulkanContextGLFW::~VulkanContextGLFW( )
{

  glfwDestroyWindow( pWindow_ );

}



///
/// \brief VulkanContextGLFW::showBuffer
///
void
VulkanContextGLFW::updateWindow( )
{

  glfwSwapBuffers( pWindow_ );

}



///
/// \brief VulkanContextGLFW::checkWindowShouldClose
///
bool
VulkanContextGLFW::checkWindowShouldClose( )
{

  return glfwWindowShouldClose( pWindow_ ) != 0;

}



///
/// \brief VulkanContextGLFW::makeWindowCurrent
///
void
VulkanContextGLFW::makeWindowCurrent( )
{

  // glfwMakeContextCurrent( pWindow_ );

}



///
/// \brief VulkanContextGLFW::_initWindow
/// \param title
/// \param width
/// \param height
///
void
VulkanContextGLFW::_initWindow(
                               const std::string title,
                               const int         width,
                               const int         height
                               )
{


  //
  // no title means no visibility
  //
  if ( title.length( ) )
  {

    glfwWindowHint( GLFW_VISIBLE, GL_TRUE );

  }
  else
  {

    glfwWindowHint( GLFW_VISIBLE, GL_FALSE );

  }

  pWindow_ = glfwCreateWindow(
                              width,
                              height,
                              title.c_str( ),
                              nullptr,
                              nullptr
                              );

  if ( !pWindow_ )
  {

    throw( std::runtime_error( "GLFW window creation failed" ) );

  }

  /* Make the window's context current */
  makeWindowCurrent( );

  glfwSwapInterval( 0 );

  /* set default callback functions */
//  glfwSetWindowSizeCallback ( pWindow_, CallbackSingleton::windowSizeCallback  );
//  glfwSetWindowFocusCallback( pWindow_, CallbackSingleton::windowFocusCallback );

//  glfwSetMouseButtonCallback( pWindow_, CallbackSingleton::mouseButtonCallback    );
//  glfwSetKeyCallback        ( pWindow_, CallbackSingleton::keyCallback            );
//  glfwSetCursorPosCallback  ( pWindow_, CallbackSingleton::cursorPositionCallback );
//  glfwSetScrollCallback     ( pWindow_, CallbackSingleton::scrollCallback         );

} // GraphicsContext::_initWindow



///
/// \brief VulkanContextGLFW::_initVulkan
///
void
VulkanContextGLFW::_initVulkan( const std::string &title )
{

  //
  // get number of available extentions
  //
  uint32_t extensionCount = 0;

  vkEnumerateInstanceExtensionProperties( nullptr, &extensionCount, nullptr );

  //
  // get names of available extentions
  //
  std::vector< VkExtensionProperties > extensions( extensionCount );
  vkEnumerateInstanceExtensionProperties( nullptr, &extensionCount, extensions.data( ) );

  std::cout << "Available Vulkan extensions:" << std::endl;

  //
  // print available extentions
  //
  for ( const auto & extension : extensions )
  {

    std::cout << "\t" << extension.extensionName << std::endl;

  }

  //
  // create instance
  //
  _createVulkanInstance( title );

  //
  // setup any debugging
  //
  _setUpVulkanDebugCallback( );

} // VulkanContextGLFW::_initVulkan



/////////////////////////////////////////////////////////////////
/// \brief VulkanContextGLFW::_createVulkanInstance
/// \param title
///
/// \author Logan Barnes
/////////////////////////////////////////////////////////////////
void
VulkanContextGLFW::_createVulkanInstance( const std::string &title )
{

  //
  // check for existing validation layers if requested
  //
  if ( enableValidationLayers && !checkValidationLayerSupport( ) )
  {

    throw std::runtime_error( "Vulkan validation layers requested but not available" );

  }

  //
  // optional but useful struct
  //
  VkApplicationInfo appInfo = {};

  appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName   = title.c_str( );
  appInfo.applicationVersion = VK_MAKE_VERSION( 1, 0, 0 );
  appInfo.pEngineName        = "No Engine";
  appInfo.engineVersion      = VK_MAKE_VERSION( 1, 0, 0 );
  appInfo.apiVersion         = VK_API_VERSION_1_0;

  //
  // creation info
  //
  VkInstanceCreateInfo createInfo = {};

  createInfo.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;

  auto extensions                    = getRequiredExtensions( );
  createInfo.enabledExtensionCount   = extensions.size( );
  createInfo.ppEnabledExtensionNames = extensions.data( );

  //
  // specify level of validation
  //
  if ( enableValidationLayers )
  {

    createInfo.enabledLayerCount   = validationLayers.size( );
    createInfo.ppEnabledLayerNames = validationLayers.data( );

  }
  else
  {

    createInfo.enabledLayerCount = 0;

  }

  //
  // try to create the Vulkan instance
  //
  if ( vkCreateInstance( &createInfo, nullptr, instance_.replace( ) ) != VK_SUCCESS )
  {

    throw std::runtime_error( "Failed to create Vulkan instance" );

  }

} // VulkanContextGLFW::_createVulkanInstance



/////////////////////////////////////////////////////////////////
/// \brief VulkanContextGLFW::_setUpVulkanDebugCallback
///
/// \author Logan Barnes
/////////////////////////////////////////////////////////////////
void
VulkanContextGLFW::_setUpVulkanDebugCallback( )
{

  if ( !enableValidationLayers )
  {

    return;

  }

  VkDebugReportCallbackCreateInfoEXT createInfo = {};
  createInfo.sType       = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
  createInfo.flags       = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
  createInfo.pfnCallback = debugCallback;

  if ( CreateDebugReportCallbackEXT(
                                    instance_,
                                    &createInfo,
                                    nullptr,
                                    callback_.replace( )
                                    )
      != VK_SUCCESS )
  {

    throw std::runtime_error( "Failed to set up Vulkan debug callback" );

  }

} // VulkanContextGLFW::_setUpVulkanDebugCallback



} // namespace graphics
