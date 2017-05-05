#ifndef TerrainIOHandler_hpp
#define TerrainIOHandler_hpp


#include "shared/core/VulkanIOHandler.hpp"


namespace shs
{

class World;

}


namespace srt
{


/////////////////////////////////////////////
/// \brief The TerrainIOHandler class
///
/// \author Logan Barnes
/////////////////////////////////////////////
class TerrainIOHandler : public shs::VulkanIOHandler
{

public:

  ///////////////////////////////////////////////////////////////
  /// \brief Renderer
  ///////////////////////////////////////////////////////////////
  explicit
  TerrainIOHandler( shs::World &world );


  ///////////////////////////////////////////////////////////////
  /// \brief ~Renderer
  ///////////////////////////////////////////////////////////////
  ~TerrainIOHandler( );


protected:


private:

  virtual
  void onRender( const double alpha ) final;


};


} // namespace srt


#endif // TerrainIOHandler_hpp
