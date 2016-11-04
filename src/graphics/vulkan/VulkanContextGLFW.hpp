#ifndef VulkanContextGLFW_hpp
#define VulkanContextGLFW_hpp


#include <string>
#include <functional>
#include <vulkan/vulkan.h>

#include "GraphicsContext.hpp"
#include "VDeleter.hpp"


struct GLFWwindow;
typedef GLFWwindow GLFWwindow;


namespace graphics
{


///
/// \brief The VulkanContextGLFW class
///
class VulkanContextGLFW : public GraphicsContext
{

public:

  VulkanContextGLFW(
                    const std::string title,
                    const int         width,
                    const int         height
                    );

  ~VulkanContextGLFW( );


  //////////////////////////////////////////////////
  /// \brief updateWindow
  //////////////////////////////////////////////////
  virtual
  void updateWindow ( ) final;

  //////////////////////////////////////////////////
  /// \brief checkWindowShouldClose
  /// \return
  //////////////////////////////////////////////////
  virtual
  bool checkWindowShouldClose ( ) final;

  //////////////////////////////////////////////////
  /// \brief makeWindowCurrent
  //////////////////////////////////////////////////
  virtual
  void makeWindowCurrent( ) final;


private:

  //////////////////////////////////////////////////
  /// \brief _initWindow
  /// \param title
  /// \param width
  /// \param height
  //////////////////////////////////////////////////
  void _initWindow (
                    const std::string title,
                    const int         width,
                    const int         height
                    );

  //////////////////////////////////////////////////
  /// \brief _initVulkan
  /// \param title
  //////////////////////////////////////////////////
  void _initVulkan ( const std::string &title );

  //////////////////////////////////////////////////
  /// \brief _createVulkanInstance
  /// \param title
  //////////////////////////////////////////////////
  void _createVulkanInstance ( const std::string &title );

  //////////////////////////////////////////////////
  /// \brief _setUpVulkanDebugCallback
  //////////////////////////////////////////////////
  void _setUpVulkanDebugCallback ( );

  //////////////////////////////////////////////////
  /// \brief _createVulkanSurface
  //////////////////////////////////////////////////
  void _createVulkanSurface ( );

  //////////////////////////////////////////////////
  /// \brief _setUpVulkanPhysicalDevice
  //////////////////////////////////////////////////
  void _setUpVulkanPhysicalDevice ( );

  //////////////////////////////////////////////////
  /// \brief _createVulkanLogicalDevice
  //////////////////////////////////////////////////
  void _createVulkanLogicalDevice ( );


  //
  // member vars
  //
  GLFWwindow *pWindow_;

  VDeleter< VkInstance > instance_ {
    vkDestroyInstance
  };

  VDeleter< VkDebugReportCallbackEXT > callback_ {
    instance_, DestroyDebugReportCallbackEXT
  };

  VDeleter< VkSurfaceKHR > surface_ {
    instance_, vkDestroySurfaceKHR
  };

  VkPhysicalDevice physicalDevice_;

  VDeleter< VkDevice > device_ {
    vkDestroyDevice
  };

  VkQueue graphicsQueue_;
  VkQueue presentQueue_;

};


} // namespace graphics


#endif // VulkanContextGLFW_hpp
