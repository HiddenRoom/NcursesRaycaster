#include "include/renderMath.h"

#include <math.h>
#include <stdio.h>
 
double rayCollisonDist(unsigned char **map, int mapXSize, int mapYSize, double cameraX, double cameraY, double rayAngle)
{
  const double cameraXInit = cameraX;
  const double cameraYInit = cameraY;

  double horiXOffset, horiYOffset, horiHypo;
  double vertXOffset, vertYOffset, vertHypo;

  while((cameraX < mapXSize && cameraY < mapYSize) && !(map[(int)floor(cameraX)][(int)floor(cameraY)]))
  {
    horiXOffset = 1.0f - (cameraX - floor(cameraX));
    horiYOffset = tan(rayAngle) * horiXOffset;
    horiHypo = sqrt(horiXOffset * horiXOffset + horiYOffset * horiYOffset);

    vertYOffset = 1.0f - (cameraY - floor(cameraY));
    vertXOffset = tan(rayAngle) * vertYOffset;
    vertHypo = sqrt(vertXOffset * vertXOffset + vertYOffset * vertYOffset);

    if(horiHypo > vertHypo)
    {
      cameraX += horiXOffset;
      cameraY += horiYOffset;
    }
    else
    {
      cameraX += vertXOffset;
      cameraY += vertYOffset;
    }
  }
  
  printf("final x %lf final y %lf\n", cameraX, cameraY);

  return sqrt(pow(fabs(cameraXInit - cameraX), 2) + pow(fabs(cameraYInit - cameraY), 2));
}
