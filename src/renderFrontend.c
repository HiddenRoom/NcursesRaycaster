#include "include/renderMath.h"
#include "include/renderFrontend.h"

#include <ncurses.h>
#include <math.h>

#define WALL_HEIGHT(winYSize, rayCollisonDist) ((int)((double)winYSize * (4 / rayCollisonDist)))
#define SMALL_STEP 0.2

/* raysTmp used to avoid repeated dynamic mem alloc */
void drawCamView(unsigned char **map, int mapXSize, int mapYSize, double cameraX, double cameraY, const double *rays, double *raysTmp, WINDOW *win, int winXSize, int winYSize) /* rays size should be winXSize */
{
  int i, j;

  int screenRayOffset;

  for(i = 0; i < winXSize; i++)
  {
    raysTmp[i] = rayCollisonDist(map, mapXSize, mapYSize, cameraX, cameraY, rays[i]);
    screenRayOffset = (int)((winYSize - WALL_HEIGHT(winYSize, raysTmp[i])) / 2); /* amount leftover at top and bottom of drawn intersection */

    for(j = screenRayOffset; j < winYSize - screenRayOffset; j++)
    {
      mvwprintw(win, j, i, "X");
    }
  }
}

void _addClampedToUnitCircle(double *val, double toAdd)
{
  if(*val + toAdd > 2 * M_PI)
    *val = (*val + toAdd) - 2 * M_PI;
  else if(*val + toAdd < 0)
    *val = 2 * M_PI + (*val + toAdd);
  else
    *val += toAdd;
}

void handleUserInput(double *rays, int rayNum, double *cameraX, double *cameraY, int mapXSize, int mapYSize, int input)
{
  int i;

  switch(input)
  {
    case 'w' :
      *cameraY += SMALL_STEP * sin(rays[(int)(rayNum / 2)]);
      *cameraX += SMALL_STEP * cos(rays[(int)(rayNum / 2)]);
      break;
    case 's' :
      *cameraY -= SMALL_STEP * sin(rays[(int)(rayNum / 2)]);
      *cameraX -= SMALL_STEP * cos(rays[(int)(rayNum / 2)]);
      break;
    case 'a' :
      for(i = 0; i < rayNum; i++)
        _addClampedToUnitCircle(rays + i, -SMALL_STEP / 2);
      break;
    case 'd' :
      for(i = 0; i < rayNum; i++)
        _addClampedToUnitCircle(rays + i, SMALL_STEP / 2);
      break;
  }

  if(*cameraX < 0.0)
    *cameraX += SMALL_STEP;
  else if(*cameraX > (double)mapXSize)
    *cameraX -= SMALL_STEP;

  if(*cameraY < 0.0)
    *cameraY += SMALL_STEP;
  else if(*cameraY > (double)mapYSize)
    *cameraY -= SMALL_STEP;
}
