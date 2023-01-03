#include "include/renderMath.h"

#include <math.h>
 
double rayCollisonDist(unsigned char **map, int mapXSize, int mapYSize, double cameraX, double cameraY, double rayAngle)
{
  const double cameraXInit = cameraX;
  const double cameraYInit = cameraY;

  double horiXOffset, horiYOffset, horiHypo;
  double vertXOffset, vertYOffset, vertHypo;

  double xMultiplier;
  double yMultiplier;

  double (*xRound)(double);
  double (*yRound)(double);

  /* initialize multipliers for ray travel direction based on angle */
  if(rayAngle < M_PI / 2.0)
  {
    xMultiplier = 1.0;
    yMultiplier = 1.0;
    xRound = floor;
    yRound = floor;
  }
  else if(rayAngle < M_PI)
  {
    xMultiplier = -1.0;
    yMultiplier = 1.0;
    xRound = ceil;
    yRound = floor;
  }
  else if(rayAngle < 3.0 * M_PI / 2.0)
  {
    xMultiplier = -1.0;
    yMultiplier = -1.0;
    xRound = ceil;
    yRound = ceil;
  }
  else if(rayAngle < 2.0 * M_PI) /* no else at the end for increased clarity */
  {
    xMultiplier = 1.0;
    yMultiplier = -1.0;
    xRound = floor;
    yRound = ceil;
  }

  /* while camera is within map bounds and has not hit a wall 
   * camera + mult * 0.00001 is to catch literal edge cases */
  while((cameraX < mapXSize  && cameraX >= 0.0 && cameraY < mapYSize && cameraY >= 0.0) 
        && !(map[(int)(floor(cameraX + xMultiplier * 0.00001))][(int)floor(cameraY + yMultiplier * 0.00001)]))
  {
    horiXOffset = 1.0 - xMultiplier * (cameraX - xRound(cameraX));
    horiYOffset = tan(rayAngle) * horiXOffset;
    horiHypo = sqrt(horiXOffset * horiXOffset + horiYOffset * horiYOffset);

    vertYOffset = 1.0 - yMultiplier * (cameraY - yRound(cameraY));
    vertXOffset = tan((M_PI / 2.0) - rayAngle) * vertYOffset;
    vertHypo = sqrt(vertXOffset * vertXOffset + vertYOffset * vertYOffset);

    if(horiHypo < vertHypo)
    {
      cameraX += horiXOffset * xMultiplier;
      cameraY += horiYOffset * xMultiplier;
    }
    else
    {
      cameraX += vertXOffset * yMultiplier;
      cameraY += vertYOffset * yMultiplier;
    }
  }

  return sqrt(pow(fabs(cameraXInit - cameraX), 2.0) + pow(fabs(cameraYInit - cameraY), 2.0));
}
