#include "TerrainIOHandler.hpp"

#include "shared/graphics/VulkanGlfwWrapper.hpp"
#include "SubtractiveTerrainConfig.hpp"


namespace srt
{



/////////////////////////////////////////////
/// \brief Renderer::Renderer
///
/// \author Logan Barnes
/////////////////////////////////////////////
TerrainIOHandler::TerrainIOHandler( shs::World &world )
  : shs::VulkanIOHandler( world, true )
{}



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
TerrainIOHandler::onRender( const double )
{
  upVulkanWrapper_->drawFrame( );
} // TerrainIOHandler::onRender



} // namespace srt
