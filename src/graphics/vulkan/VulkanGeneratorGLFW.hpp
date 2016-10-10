#ifndef VulkanGeneratorGLFW_hpp
#define VulkanGeneratorGLFW_hpp


#include "GraphicsGenerator.hpp"


namespace graphics
{


class GraphicsHandler;


class VulkanGeneratorGLFW : public GraphicsGenerator
{

public:

  VulkanGeneratorGLFW( );

  virtual
  ~VulkanGeneratorGLFW( );

  virtual
  GraphicsHandler &generateHandler (
                                    std::string  title  = "Vulkan Window",
                                    unsigned int width  = DEFAULT_VIEW_WIDTH,
                                    unsigned int height = DEFAULT_VIEW_HEIGHT
                                    );

  virtual
  void checkEvents ( );


private:

  bool _initGLFW ( );

  void _terminateGLFW ( );

  bool glfwInitialized_;

};


} // namespace graphics


#endif // VulkanGeneratorGLFW_hpp
