#include <iostream>
#include "BMP.h"
#include <cmath>

int plotEllipsePoints(int x, int y, int offsetx, int offsety, BMP& bmpNew){
    std::cout << x << "," << y << "\n";
    //Different colors to show how rasterized
    bmpNew.set_pixel(x+offsetx, y+offsety, 255, 50, 100, 0);
    bmpNew.set_pixel(x+offsetx, -y+offsety, 255, 100, 255, 0);
    bmpNew.set_pixel(-x+offsetx, y+offsety, 100, 255, 255, 0);
    bmpNew.set_pixel(-x+offsetx, -y+offsety, 255, 255, 100, 0);
    return 0;
}

int nextEllipsePoint(int x, int radx, int rady){
  int y = rady*sqrt((pow(radx,2)-(pow(x,2)))/(pow(radx,2)));
  if (y < 0){
    std::cout << "Out of bounds" << "\n";
    return 0;
  }
  return y;
}

int plotExtraPoints(BMP& bmpNew){
  //Added to top as supplement 
  for (int i = 763; i <= 773; i++){
    bmpNew.set_pixel(i,768, 255, 255, 255, 0);
  }
  return 0; 
}

int rasterizeEllipse(int radx, int rady, int cy, int cx){    
  int h = rady*2; 
  int w = radx*2; 
  BMP bmpNew(w+10,h+10,false);
  bmpNew.fill_region(0, 0, w+10, h+10, 0, 0, 0, 0);

  int x = 0; 
  int y = 0; 

  while(x<=radx){
    if (x < 0 || x > (radx*2)+10 || y < 0 || y > (rady*2)+10){
      std::cout << "Out of bounds" << "\n";
      return 0; 
    }
    plotEllipsePoints(x,y,cx,cy,bmpNew);
    x++;  
    y=nextEllipsePoint(x,radx, rady);
    if (y == 0){
      std::cout << "Not Ellipse Point" << "\n";
    }
  }
  plotExtraPoints(bmpNew);
  bmpNew.write("output.bmp");  
  return 0; 
}

int main() {
    std::cout << "Running";
    rasterizeEllipse(768,384,384,768);
    std::cout << "Done"; 
}


