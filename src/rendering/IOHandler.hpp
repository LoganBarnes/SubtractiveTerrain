#ifndef IoHandler_hpp
#define IoHandler_hpp


#include <memory>
#include <vector>
#include <functional>


namespace graphics
{

class GraphicsGenerator;
class GraphicsHandler;

}



namespace srt
{


class World;


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
  virtual
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
  /// \brief isExitRequested
  /// \return true if the user requested to exit the program
  ///////////////////////////////////////////////////////////////
  bool
  isExitRequested( ) { return exitRequested_; }


protected:

  World &world_;
  bool exitRequested_;

  std::unique_ptr< graphics::GraphicsGenerator > upGraphicsGen_;

  std::vector< std::reference_wrapper< graphics::GraphicsHandler > > graphicses_;

};


} // namespace srt


#endif // IoHandler_hpp
