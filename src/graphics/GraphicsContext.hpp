#ifndef GraphicsContext_hpp
#define GraphicsContext_hpp


#include <string>


namespace graphics
{


///
/// \brief The GraphicsContext class
///
class GraphicsContext
{

public:

  ///
  /// \brief GraphicsContext
  /// \param title
  /// \param width
  /// \param height
  ///
  GraphicsContext(
                  const std::string,
                  const int,
                  const int
                  ) {}

  virtual
  ~GraphicsContext( ) {}


  virtual
  void updateWindow ( ) = 0;

  virtual
  bool checkWindowShouldClose ( ) = 0;

  virtual
  void makeWindowCurrent ( ) = 0;

  virtual
  void createRenderPass ( ) = 0;

  virtual
  void createGraphicsPipeline (
                               const std::string &vertFile,
                               const std::string &fragFile
                               ) = 0;


};


} // namespace graphics


#endif // GraphicsContext_hpp
