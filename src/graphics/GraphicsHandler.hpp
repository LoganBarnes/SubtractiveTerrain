#ifndef GraphicsHandler_hpp
#define GraphicsHandler_hpp

#include <memory>


namespace graphics
{


class GraphicsContext;


class GraphicsHandler
{

public:

  GraphicsHandler(
                  std::unique_ptr< GraphicsContext > &upContext,
                  const int                           width,
                  const int                           height
                  );

  virtual
  ~GraphicsHandler( );

  //
  // GL calls
  //
  void clearViewport ( );


  //
  // context calls
  //
  void makeContextCurrent ( );
  void updateWindow ( );
  bool checkWindowShouldClose ( );


private:

  std::unique_ptr< GraphicsContext > upContext_;

  int viewWidth_, viewHeight_;


};


} // namespace graphics


#endif // GraphicsHandler_hpp
