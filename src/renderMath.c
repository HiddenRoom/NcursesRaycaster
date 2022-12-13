#include "include/renderMath.h"

#include <math.h>
 
double rayCollisonDist(char **map, double cameraX, double cameraY, double rayAngle)
{
  const double cameraXInit = cameraX;
  const double cameraYInit = cameraY;

  double horiXOffset, horiYOffset, horiHypo;
  double veriXOffset, vertYOffset, veriHypo;

  while(!(map[floor(cameraX)][floor(cameraY)]))
  {
    horiXOffset = 1.0f - (cameraX - floor(cameraX));
    horiYOffset = tan(rayAngle) * horiXOffset;
    horiHypo = sqrt(horiXOffset * horiXOffset + horiYOffset * horiYOffset);

    veriYOffset = 1.0f - (cameraY - floor(cameraY));
    veriXOffset = tan(rayAngle) * veriYOffset;
    veriHypo = sqrt(veriXOffset * veriXOffset + veriYOffset * veriYOffset);

    if(horiHypo > veriHypo)
    {
      cameraX += horiXOffset;
      cameraY += horiYOffset;
    }
    else
    {
      cameraX += veriXOffset;
      cameraY += veriYOffset;
    }
  }

  return sqrt(cameraX * cameraX + cameraY * cameraY);
}
