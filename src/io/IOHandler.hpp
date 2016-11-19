#ifndef IoHandler_hpp
#define IoHandler_hpp


#include <memory>
#include <vector>
#include <functional>


namespace graphics
{

//class GraphicsGenerator;
//class GraphicsHandler;
class VulkanGlfwWrapper;

}



namespace srt
{


class World;
class TerrainCallback;


/////////////////////////////////////////////
/// \brief The IOHandler class
///
/// \author Logan Barnes
/////////////////////////////////////////////
class IOHandler
{

public:

  ///////////////////////////////////////////////////////////////
  /// \brief Renderer
  ///////////////////////////////////////////////////////////////
  IOHandler(
            World &world,
            bool   printInfo = true
            );


  ///////////////////////////////////////////////////////////////
  /// \brief ~Renderer
  ///////////////////////////////////////////////////////////////
  ~IOHandler( );


  ///////////////////////////////////////////////////////////////
  /// \brief render
  /// \param alpha
  ///////////////////////////////////////////////////////////////
  virtual
  void showWorld ( const double alpha );


  ///////////////////////////////////////////////////////////////
  /// \brief updateIO
  ///
  ///        Checks for keystrokes or mouse movement (or
  ///        alternate controllers) and updates output text,
  ///        images, or buffer swaps not handled by showWorld()
  ///
  ///////////////////////////////////////////////////////////////
  virtual
  void updateIO ( );


  ///////////////////////////////////////////////////////////////
  /// \brief onLoopExit
  ///
  ///        Allows for any synchronization or clean up that
  ///        needs to be completed before destruction
  ///
  ///////////////////////////////////////////////////////////////
  virtual
  void onLoopExit ( );


  ///////////////////////////////////////////////////////////////
  /// \brief isExitRequested
  /// \return true if the user requested to exit the program
  ///////////////////////////////////////////////////////////////
  bool
  isExitRequested( ) { return exitRequested_; }


protected:

  World &world_;
  bool exitRequested_;

  std::unique_ptr< graphics::VulkanGlfwWrapper > upGraphics_;
  std::unique_ptr< TerrainCallback >             upCallback_;

};


} // namespace srt


#endif // IoHandler_hpp
