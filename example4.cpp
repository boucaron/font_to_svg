// main.cpp font_to_svg - public domain

#include "font_to_svg.hpp"

int main( int argc, char * argv[] )
{
  if (argc!=3) {
    std::cerr << "usage: " << argv[0] << " file.ttf myMessage\n";
    exit( 1 );
  }

  std::string myMessage = argv[2];
  double offsetX = 0.0, offsetY = 0.0;
  for(unsigned int i = 0 ; i < myMessage.size() ; i++ ) {
    char utf8 = myMessage.at(i);
    std::stringstream s;
    s << (int)utf8;    //Not really UTF-8 just a hack
    std::string unicodeChar = s.str();
    // std::cout << " unicodeChar = " << unicodeChar << std::endl;
    font2svg::glyph g( argv[1], unicodeChar.c_str(), offsetX, offsetY);
    if ( i == 0 ) {
      std::cout << g.svgheader();
    }
    /*	    << g.svgborder()
	    << g.svgtransform()
	    << g.axes()
	    << g.typography_box()
	    << g.points()
	    << g.pointlines() */
    /* std::cout << g.svgtransform(); */
    std::cout << g.outline();
      /* 
	 << g.labelpts() */

    //offsetX += g.bbwidth;
    if ( g.gWidth <= 0 ) {
      offsetX += 200; //Static shift
    }
    else {
      offsetX += g.gWidth * 1.1;
    }

      if ( i == myMessage.size() - 1 ) { 
	std::cout << g.svgfooter();
      }
	  
    g.free();
  }
	
  return 0;
}
