#include "GraphicsGenerator.hpp"

#include <algorithm>
#include "GraphicsHandler.hpp"


namespace graphics
{


///
/// \brief GraphicsGenerator::~GraphicsGenerator
///
GraphicsGenerator::~GraphicsGenerator( )
{}



///
/// \brief GraphicsGeneratorGLFW::removeHandler
/// \param handler
///
void
GraphicsGenerator::removeHandler( GraphicsHandler &handler )
{

  GraphicsHandler *pHandler = &handler;

  auto iter = std::remove_if(
                             handlers_.begin( ),
                             handlers_.end( ),
                             [ & ]( std::unique_ptr< GraphicsHandler > &handle )
                             { return handle.get( ) == pHandler; }
                             );

  handlers_.erase( iter );

}



///
/// \brief GraphicsGenerator::getNumHandlers
/// \return
///
unsigned int
GraphicsGenerator::getNumHandlers( )
{

  return handlers_.size( );

}



} // namespace graphics
