#include "IOHandler.hpp"

#include <iostream>
#include <csignal>
#include <random>
#include "GraphicsHandler.hpp"


#ifdef USE_DIRECT_X_12
#include "DX12Generator.hpp"
typedef DX12Generator GraphicsGen;
#else
#include "VulkanGeneratorGLFW.hpp"
typedef graphics::VulkanGeneratorGLFW GraphicsGen;
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
{

  signal ( SIGINT, signalHandler );

  if ( printInfo )
  {

    std::cout << "Press 'CTRL + C' to exit" << std::endl;

  }

  try
  {

    upGraphicsGen_ = std::unique_ptr< graphics::GraphicsGenerator >( new GraphicsGen( ) );

    graphicses_.push_back( upGraphicsGen_->generateHandler( "Subtractive Terrain" ) );

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

  //
  // render to all windows
  //
  for ( graphics::GraphicsHandler & graphics : graphicses_ )
  {

    graphics.makeContextCurrent( );
    graphics.clearViewport( );

    /// \todo: render stuff

    graphics.updateWindow( );

  }

} // IOHandler::showWorld



/////////////////////////////////////////////
/// \brief IOHandler::updateIO
///
/// \author Logan Barnes
/////////////////////////////////////////////
void
IOHandler::updateIO( )
{

  upGraphicsGen_->checkEvents( );

  exitRequested_ |= signalCaught;

  //
  // check all windows for exit requests
  //
  for ( graphics::GraphicsHandler & graphics : graphicses_ )
  {

    exitRequested_ |= graphics.checkWindowShouldClose( );

  }

}



} // namespace srt
