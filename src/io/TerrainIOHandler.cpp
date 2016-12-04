#include "TerrainIOHandler.hpp"

#include "graphics/vulkan/VulkanGlfwWrapper.hpp"
#include "SubtractiveTerrainConfig.hpp"


namespace srt
{



/////////////////////////////////////////////
/// \brief Renderer::Renderer
///
/// \author Logan Barnes
/////////////////////////////////////////////
TerrainIOHandler::TerrainIOHandler( shared::World &world )
  : shared::VulkanIOHandler( world, true )
{

  upVulkanWrapper_->createRenderPass( );

  upVulkanWrapper_->createGraphicsPipeline(
                                           SHADER_PATH + "screenSpace/vert.spv",
                                           SHADER_PATH + "terrain/frag.spv"
                                           );

  upVulkanWrapper_->createFrameBuffer( );

  upVulkanWrapper_->createCommandPool( );

  upVulkanWrapper_->createCommandBuffers( );

  upVulkanWrapper_->createSemaphores( );

}



/////////////////////////////////////////////
/// \brief Renderer::~Renderer
///
/// \author Logan Barnes
/////////////////////////////////////////////
TerrainIOHandler::~TerrainIOHandler( )
{}



/////////////////////////////////////////////
/// \brief Renderer::onRender
/// \param alpha
///
/// \author Logan Barnes
/////////////////////////////////////////////
void
TerrainIOHandler::onRender( const double alpha )
{

  upVulkanWrapper_->drawFrame( );

} // TerrainIOHandler::onRender



/////////////////////////////////////////////
/// \brief IOHandler::onLoopExit
///
/// \author Logan Barnes
/////////////////////////////////////////////
void
TerrainIOHandler::onLoopExit( )
{

  upVulkanWrapper_->syncDevice( );

}



} // namespace srt
