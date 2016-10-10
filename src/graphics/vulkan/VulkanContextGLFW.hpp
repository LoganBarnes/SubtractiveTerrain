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

  virtual
  ~VulkanContextGLFW( );


  virtual
  void updateWindow ( );

  virtual
  bool checkWindowShouldClose ( );

  virtual
  void makeWindowCurrent ( );


private:

  void _initWindow (
                    const std::string title,
                    const int         width,
                    const int         height
                    );

  void _initVulkan ( const std::string &title );

  void _createVulkanInstance ( const std::string &title );

  void _setUpVulkanDebugCallback ( );

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


};


} // namespace graphics


#endif // VulkanContextGLFW_hpp
