#include "IOHandler.hpp"

#include <iostream>
#include <csignal>
#include <random>
#include "SubtractiveTerrainConfig.hpp"


#ifdef USE_DIRECT_X_12
#include "DX12Wrapper.hpp"
#else
#include "VulkanGlfwWrapper.hpp"
#include "TerrainCallback.hpp"
#endif



namespace srt
{


namespace
{

bool signalCaught( false );

///
/// \brief signalHandler
/// \param signum
///
void
signalHandler( int signum )
{

  std::cout << "Caught signal" << std::endl;

  signalCaught = ( signum == SIGINT );

}



}


/////////////////////////////////////////////
/// \brief Renderer::Renderer
///
/// \author Logan Barnes
/////////////////////////////////////////////
IOHandler::IOHandler(
                     World &world,
                     bool   printInfo
                     )
  :
  world_          ( world )
  , exitRequested_( false )
  , upCallback_   ( new TerrainCallback( ) )
{

  signal ( SIGINT, signalHandler );

  if ( printInfo )
  {

    std::cout << "Press 'CTRL + C' or 'ESC' to exit" << std::endl;

  }

  try
  {

    upGraphics_ =
      std::unique_ptr< graphics::VulkanGlfwWrapper >( new graphics::VulkanGlfwWrapper( ) );

    graphics::VulkanGlfwWrapper &graphics = *upGraphics_;

    graphics.setCallback( upCallback_.get( ) );

    graphics.createNewWindow( "Subtractive Terrain", 1024, 720 );

    graphics.createRenderPass( );

    graphics.createGraphicsPipeline(
                                    SHADER_PATH + "screenSpace/vert.spv",
                                    SHADER_PATH + "terrain/frag.spv"
                                    );

    graphics.createFrameBuffer( );

    graphics.createCommandPool( );

    graphics.createCommandBuffers( );

    graphics.createSemaphores( );

  }
  catch ( const std::exception &e )
  {

    std::cerr << "IOHandler graphics init failed: " << e.what( ) << std::endl;

  }

}



/////////////////////////////////////////////
/// \brief Renderer::~Renderer
///
/// \author Logan Barnes
/////////////////////////////////////////////
IOHandler::~IOHandler( )
{}



/////////////////////////////////////////////
/// \brief Renderer::render
/// \param alpha
///
/// \author Logan Barnes
/////////////////////////////////////////////
void
IOHandler::showWorld( const double )
{

  /// \todo: render stuff

  upGraphics_->drawFrame( );

} // IOHandler::showWorld



/////////////////////////////////////////////
/// \brief IOHandler::updateIO
///
/// \author Logan Barnes
/////////////////////////////////////////////
void
IOHandler::updateIO( )
{

  upGraphics_->checkInputEvents( );

  exitRequested_ |= signalCaught;

  //
  // check windows for exit requests
  //
  exitRequested_ |= upGraphics_->checkWindowShouldClose( );


}



/////////////////////////////////////////////
/// \brief IOHandler::onLoopExit
///
/// \author Logan Barnes
/////////////////////////////////////////////
void
IOHandler::onLoopExit( )
{

  upGraphics_->syncDevice( );

}



} // namespace srt
