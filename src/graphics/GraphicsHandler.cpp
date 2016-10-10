#include "GraphicsHandler.hpp"

#include "GraphicsContext.hpp"


namespace graphics
{



///
/// \brief GraphicsHandler::GraphicsHandler
/// \param width
/// \param height
///
GraphicsHandler::GraphicsHandler(
                                 std::unique_ptr< GraphicsContext > &upContext,
                                 const int                           width,
                                 const int                           height
                                 )
  :
  upContext_   ( std::move( upContext ) )
  , viewWidth_ ( width )
  , viewHeight_( height )
{}



///
/// \brief GraphicsHandler::~GraphicsHandler
///
GraphicsHandler::~GraphicsHandler( )
{

  //
  // todo: delete OpenGL buffers
  //

  //
  // window will be deleted by ~GraphicsContext
  // when upContext goes out of scope
  //

}



///
/// \brief GraphicsHandler::clearViewport
/// \param width
/// \param height
///
void
GraphicsHandler::clearViewport( )
{

//  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

}



///
/// \brief GraphicsHandler::makeContextCurrent
///
void
GraphicsHandler::makeContextCurrent( )
{

  upContext_->makeWindowCurrent( );

}



///
/// \brief GraphicsHandler::updateWindow
///
void
GraphicsHandler::updateWindow( )
{

  upContext_->updateWindow( );

}



///
/// \brief GraphicsHandler::checkWindowShouldClose
/// \return
///
bool
GraphicsHandler::checkWindowShouldClose( )
{

  return upContext_->checkWindowShouldClose( );

}



} // namespace graphics
