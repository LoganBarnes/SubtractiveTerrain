#ifndef VulkanGlfwWrapper_hpp
#define VulkanGlfwWrapper_hpp


#include <string>
#include <functional>
#include <vector>
#include <vulkan/vulkan.h>

#include "VDeleter.hpp"


struct GLFWwindow;
typedef GLFWwindow GLFWwindow;


namespace graphics
{


///
/// \brief The VulkanGlfwWrapper class
///
class VulkanGlfwWrapper
{

public:

  ///////////////////////////////////////////////////////////////////////////////////
  //
  //  Initialization functions
  //
  ///////////////////////////////////////////////////////////////////////////////////

  VulkanGlfwWrapper( );

  ~VulkanGlfwWrapper( );


  virtual
  void createNewWindow(
                       const std::string &title,
                       const int          width,
                       const int          height
                       );


  virtual
  void createRenderPass ( );


  ///
  /// \brief createGraphicsPipeline
  /// \param vertexFile
  /// \param fragmentFile
  ///
  virtual
  void createGraphicsPipeline (
                               const std::string &vertFile,
                               const std::string &fragFile
                               );



  ///////////////////////////////////////////////////////////////////////////////////
  //
  //  Render loop functions
  //
  ///////////////////////////////////////////////////////////////////////////////////


  //////////////////////////////////////////////////
  /// \brief checkInputEvents
  //////////////////////////////////////////////////
  virtual
  void checkInputEvents ( );

  //////////////////////////////////////////////////
  /// \brief updateWindow
  //////////////////////////////////////////////////
  virtual
  void updateWindow ( );


  //////////////////////////////////////////////////
  /// \brief checkWindowShouldClose
  /// \return
  //////////////////////////////////////////////////
  virtual
  bool checkWindowShouldClose ( );


private:

  //////////////////////////////////////////////////
  /// \brief _initGlfw
  //////////////////////////////////////////////////
  bool _initGlfw( );


  //////////////////////////////////////////////////
  /// \brief _terminateGlfw
  //////////////////////////////////////////////////
  void _terminateGlfw( );


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
  virtual
  void _createVulkanInstance ( const std::string &title );

  //////////////////////////////////////////////////
  /// \brief _setUpVulkanDebugCallback
  //////////////////////////////////////////////////
  virtual
  void _setUpVulkanDebugCallback ( );

  //////////////////////////////////////////////////
  /// \brief _createVulkanSurface
  //////////////////////////////////////////////////
  virtual
  void _createVulkanSurface ( );

  //////////////////////////////////////////////////
  /// \brief _setUpVulkanPhysicalDevice
  //////////////////////////////////////////////////
  virtual
  void _setUpVulkanPhysicalDevice ( );

  //////////////////////////////////////////////////
  /// \brief _createVulkanLogicalDevice
  //////////////////////////////////////////////////
  virtual
  void _createVulkanLogicalDevice ( );

  //////////////////////////////////////////////////
  /// \brief _createSwapChain
  /// \param width
  /// \param height
  //////////////////////////////////////////////////
  virtual
  void _createSwapChain (
                         const int width,
                         const int height
                         );

  //////////////////////////////////////////////////
  /// \brief _createImageViews
  //////////////////////////////////////////////////
  virtual
  void _createImageViews ( );


  bool glfwInitialized_;


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


#endif // VulkanGlfwWrapper_hpp
