#include "include/renderMath.h"

#include <math.h>
 
double rayCollisonDist(char **map, double cameraX, double cameraY, double rayAngle)
{
  const double cameraXInit = cameraX;
  const cameraYIniti = cameraY;

  double horiXOffset, horiYOffset, horiHypo;
  double veriXOffset, vertYOffset, veriHypo;

  while(!(map[(int)cameraX][(int)cameraY]))
  {
    horiXOffset = 1.0f - (cameraX - (int)cameraX);
    horiYOffset = tan(rayAngle) * horiXOffset;
    horiHypo = sqrt(horiXOffset * horiXOffset + horiYOffset * horiYOffset);

    veriYOffset = 1.0f - (cameraY - (int)cameraY);
    veriXOffset = tan(rayAngle) * veriYOffset;
    veriHypo = sqrt(veriXOffset * veriXOffset + veriYOffset * veriYOffset);

    /* add code to update camera pos according to longer hypo */
  }
}
