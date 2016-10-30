#include "VulkanContextGLFW.hpp"

#include <vector>
#include <iostream>
#include <set>

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
const std::vector< const char* > validationLayers =
{

  "VK_LAYER_LUNARG_standard_validation"

};

//
// requested GPU extensions
//
const std::vector< const char* > deviceExtensions =
{

  VK_KHR_SWAPCHAIN_EXTENSION_NAME

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



bool
checkDeviceExtensionSupport( VkPhysicalDevice device )
{

  uint32_t extensionCount;

  vkEnumerateDeviceExtensionProperties( device, nullptr, &extensionCount, nullptr );

  std::vector< VkExtensionProperties > availableExtensions( extensionCount );
  vkEnumerateDeviceExtensionProperties( device, nullptr, &extensionCount, availableExtensions.data( ) );

  std::set< std::string > requiredExtensions( deviceExtensions.begin(), deviceExtensions.end( ) );

  for ( const auto & extension : availableExtensions )
  {

    requiredExtensions.erase( extension.extensionName );

  }

  return requiredExtensions.empty( );

}



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



///
/// \brief The QueueFamilyIndices struct
///
struct QueueFamilyIndices
{

  int graphicsFamily_ = -1;
  int presentFamily_  = -1;

  bool
  isComplete( )
  {

    return graphicsFamily_ >= 0 && presentFamily_ >= 0;

  }


};



///
/// \brief findQueueFamilies
/// \param device
/// \return
///
QueueFamilyIndices
findQueueFamilies(
                  VkPhysicalDevice device,
                  VkSurfaceKHR     surface
                  )
{

  QueueFamilyIndices indices;

  uint32_t queueFamilyCount = 0;

  vkGetPhysicalDeviceQueueFamilyProperties( device, &queueFamilyCount, nullptr );

  std::vector< VkQueueFamilyProperties > queueFamilies( queueFamilyCount );
  vkGetPhysicalDeviceQueueFamilyProperties( device, &queueFamilyCount, queueFamilies.data( ) );


  int i = 0;

  for ( const auto & queueFamily : queueFamilies )
  {

    if ( queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT )
    {

      indices.graphicsFamily_ = i;

    }

    VkBool32 presentSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR( device, i, surface, &presentSupport );

    if ( queueFamily.queueCount > 0 && presentSupport )
    {

      indices.presentFamily_ = i;

    }

    if ( indices.isComplete( ) )
    {

      break;

    }

    ++i;

  }

  return indices;

} // findQueueFamilies



///
/// \brief isDeviceSuitable
/// \param device
/// \return
///
bool
isDeviceSuitable(
                 VkPhysicalDevice device,
                 VkSurfaceKHR     surface
                 )
{

  QueueFamilyIndices indices = findQueueFamilies( device, surface );

  bool extensionsSupported = checkDeviceExtensionSupport( device );

  return indices.isComplete( ) && extensionsSupported;

}



} // namespace


VulkanContextGLFW::VulkanContextGLFW(
                                     const std::string title,
                                     const int         width,
                                     const int         height
                                     )
  :
  GraphicsContext( title, width, height )
  , physicalDevice_( VK_NULL_HANDLE )
{

  _initWindow( title, width, height ); // GLFW init
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

  //
  // surface for rendering?
  //
  _createVulkanSurface( );

  //
  // select GPU(s)
  //
  _setUpVulkanPhysicalDevice( );

  //
  // create device to interface with GPU
  //
  _createVulkanLogicalDevice( );

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



/////////////////////////////////////////////////////////////////
/// \brief VulkanContextGLFW::_createVulkanSurface
///
/// \author Logan Barnes
/////////////////////////////////////////////////////////////////
void
VulkanContextGLFW::_createVulkanSurface( )
{

  if ( glfwCreateWindowSurface( instance_, pWindow_, nullptr, surface_.replace( ) ) != VK_SUCCESS )
  {

    throw std::runtime_error( "Failed to create window surface" );

  }

}



/////////////////////////////////////////////////////////////////
/// \brief VulkanContextGLFW::_setUpVulkanPhysicalDevice
///
/// \author Logan Barnes
/////////////////////////////////////////////////////////////////
void
VulkanContextGLFW::_setUpVulkanPhysicalDevice( )
{

  uint32_t deviceCount = 0;

  vkEnumeratePhysicalDevices( instance_, &deviceCount, nullptr );

  if ( deviceCount == 0 )
  {

    throw std::runtime_error( "Failed to find GPUs with Vulkan support" );

  }

  std::vector< VkPhysicalDevice > devices( deviceCount );
  vkEnumeratePhysicalDevices( instance_, &deviceCount, devices.data( ) );

  for ( const auto & device : devices )
  {

    ///\todo add device checking, scoring, and selection options.
    ///      Using first vulkan capable device for now
    if ( isDeviceSuitable( device, surface_ ) )
    {

      physicalDevice_ = device;
      break;

    }

  }

  if ( physicalDevice_ == VK_NULL_HANDLE )
  {

    throw std::runtime_error( "Failed to find a suitable GPU" );

  }

} // VulkanContextGLFW::_setUpVulkanPhysicalDevice



/////////////////////////////////////////////////////////////////
/// \brief VulkanContextGLFW::_createVulkanLogicalDevice
///
/// \author Logan Barnes
/////////////////////////////////////////////////////////////////
void
VulkanContextGLFW::_createVulkanLogicalDevice( )
{

  QueueFamilyIndices indices = findQueueFamilies( physicalDevice_, surface_ );

  std::vector< VkDeviceQueueCreateInfo > queueCreateInfos;
  std::set< int > uniqueQueueFamilies = { indices.graphicsFamily_, indices.presentFamily_ };

  float queuePriority = 1.0f;

  for ( int queueFamily : uniqueQueueFamilies )
  {

    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queueFamily;
    queueCreateInfo.queueCount       = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;
    queueCreateInfos.push_back( queueCreateInfo );

  }

  VkPhysicalDeviceFeatures deviceFeatures = {};

  VkDeviceCreateInfo createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

  createInfo.pQueueCreateInfos    = queueCreateInfos.data( );
  createInfo.queueCreateInfoCount = static_cast< uint32_t >( queueCreateInfos.size( ) );

  createInfo.pEnabledFeatures = &deviceFeatures;

  createInfo.enabledExtensionCount = 0;

  if ( enableValidationLayers )
  {

    createInfo.enabledLayerCount   = validationLayers.size( );
    createInfo.ppEnabledLayerNames = validationLayers.data( );

  }
  else
  {

    createInfo.enabledLayerCount = 0;

  }

  if ( vkCreateDevice( physicalDevice_, &createInfo, nullptr, device_.replace( ) ) != VK_SUCCESS )
  {

    throw std::runtime_error( "Failed to create logical device" );

  }

  vkGetDeviceQueue( device_, indices.graphicsFamily_, 0, &graphicsQueue_ );
  vkGetDeviceQueue( device_, indices.presentFamily_,  0, &presentQueue_  );

} // VulkanContextGLFW::_createVulkanLogicalDevice



} // namespace graphics
