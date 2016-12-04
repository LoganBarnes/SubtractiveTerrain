#ifndef TerrainIOHandler_hpp
#define TerrainIOHandler_hpp


#include "io/VulkanIOHandler.hpp"


namespace shared
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
class TerrainIOHandler : public shared::VulkanIOHandler
{

public:

  ///////////////////////////////////////////////////////////////
  /// \brief Renderer
  ///////////////////////////////////////////////////////////////
  TerrainIOHandler( shared::World &world );


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
