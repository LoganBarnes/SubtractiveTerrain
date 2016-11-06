#ifndef VulkanContextGLFW_hpp
#define VulkanContextGLFW_hpp


#include <string>
#include <functional>
#include <vector>
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
  void makeWindowCurrent ( ) final;

  virtual
  void createRenderPass ( ) final;

  ///
  /// \brief createGraphicsPipeline
  /// \param vertexFile
  /// \param fragmentFile
  ///
  virtual
  void createGraphicsPipeline (
                               const std::string &vertFile,
                               const std::string &fragFile
                               ) final;


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
  void _initVulkan (
                    const std::string &title,
                    const int          width,
                    const int          height
                    );

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

  //////////////////////////////////////////////////
  /// \brief _createSwapChain
  /// \param width
  /// \param height
  //////////////////////////////////////////////////
  void _createSwapChain (
                         const int width,
                         const int height
                         );

  //////////////////////////////////////////////////
  /// \brief _createImageViews
  //////////////////////////////////////////////////
  void _createImageViews ( );


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

  VDeleter< VkSwapchainKHR > swapChain_ {
    device_, vkDestroySwapchainKHR
  };

  std::vector< VkImage > swapChainImages_;
  VkFormat swapChainImageFormat_;
  VkExtent2D swapChainExtent_;

  VkQueue graphicsQueue_;
  VkQueue presentQueue_;

  std::vector< VDeleter< VkImageView > > swapChainImageViews_;

  VDeleter< VkShaderModule > vertShaderModule_ {
    device_, vkDestroyShaderModule
  };

  VDeleter< VkShaderModule > fragShaderModule_ {
    device_, vkDestroyShaderModule
  };

  VDeleter< VkRenderPass > renderPass_ {
    device_, vkDestroyRenderPass
  };

  VDeleter< VkPipelineLayout > pipelineLayout_ {
    device_, vkDestroyPipelineLayout
  };

  VDeleter< VkPipeline > graphicsPipeline_ {
    device_, vkDestroyPipeline
  };

};


} // namespace graphics


#endif // VulkanContextGLFW_hpp
