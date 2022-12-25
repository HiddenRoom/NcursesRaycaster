#include "include/renderMath.h"

#include <math.h>
 
double rayCollisonDist(unsigned char **map, int mapXSize, int mapYSize, double cameraX, double cameraY, double rayAngle)
{
  const double cameraXInit = cameraX;
  const double cameraYInit = cameraY;

  double horiXOffset, horiYOffset, horiHypo;
  double vertXOffset, vertYOffset, vertHypo;

  while((cameraX < mapXSize && cameraY < mapYSize) && !(map[(int)floor(cameraX)][(int)floor(cameraY)]))
  {
    horiXOffset = 1.0 - (cameraX - floor(cameraX));
    horiYOffset = tan((M_PI / 2.0) - rayAngle) * horiXOffset;
    horiHypo = sqrt(horiXOffset * horiXOffset + horiYOffset * horiYOffset);

    vertYOffset = 1.0 - (cameraY - floor(cameraY));
    vertXOffset = tan((M_PI / 2.0) - rayAngle) * vertYOffset;
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

  return sqrt(pow(fabs(cameraXInit - cameraX), 2.0) + pow(fabs(cameraYInit - cameraY), 2.0));
}
