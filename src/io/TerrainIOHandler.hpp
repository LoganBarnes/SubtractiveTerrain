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
  TerrainIOHandler( shs::World &world );


  ///////////////////////////////////////////////////////////////
  /// \brief ~Renderer
  ///////////////////////////////////////////////////////////////
  virtual
  ~TerrainIOHandler( );


  ///////////////////////////////////////////////////////////////
  /// \brief onLoopExit
  ///
  ///        Allows for any synchronization or clean up that
  ///        needs to be completed before destruction
  ///
  ///////////////////////////////////////////////////////////////
  virtual
  void onLoopExit ( ) final;



protected:


private:

  virtual
  void onRender( const double alpha ) final;


};


} // namespace srt


#endif // TerrainIOHandler_hpp
