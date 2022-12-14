#include "include/renderMath.h"
#include "include/renderFrontend.h"

#include <ncurses.h>
#include <math.h>

#define WALL_HEIGHT(winYSize, rayCollisonDist) ((double)winYSize * (4 / rayCollisonDist))
#define SMALL_STEP 0.2
#define PALETTE_SIZE 5

/* raysTmp used to avoid repeated dynamic mem alloc */
void drawCamView(unsigned char **map, int mapXSize, int mapYSize, double cameraX, double cameraY, const double *rays, double *raysTmp, WINDOW *win, int winXSize, int winYSize) /* rays size should be winXSize */
{
  int i, j;

  int screenRayOffset;

  const char charPalette[PALETTE_SIZE] = { '$', '@', 'B', '8', '&' };

  for(i = 0; i < winXSize; i++)
  {
    raysTmp[i] = rayCollisonDist(map, mapXSize, mapYSize, cameraX, cameraY, rays[i]);
    screenRayOffset = (int)((winYSize - WALL_HEIGHT(winYSize, raysTmp[i])) / 2); /* amount leftover at top and bottom of drawn intersection */

    for(j = screenRayOffset; j < winYSize - screenRayOffset; j++)
    {
      mvwprintw(win, j, i, "%c", charPalette[(int)((PALETTE_SIZE + 1) * (atan(4.0 / (mapXSize + mapYSize) * WALL_HEIGHT(winYSize, raysTmp[i])) / M_PI_2) - 1)]);
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

void handleUserInput(unsigned char **map, double *rays, int rayNum, double *cameraX, double *cameraY, int mapXSize, int mapYSize, int input)
{
  int i;

  double deltaX, deltaY;

  if(input == 'w' || input == 's')
  {
    switch(input)
    {
      case 'w' :
        deltaX = SMALL_STEP * cos(rays[(int)(rayNum / 2)]);
        deltaY = SMALL_STEP * sin(rays[(int)(rayNum / 2)]);
        break;
      case 's' :
        deltaX = -(SMALL_STEP * cos(rays[(int)(rayNum / 2)]));
        deltaY = -(SMALL_STEP * sin(rays[(int)(rayNum / 2)]));
        break;
    }
    
    *cameraX += deltaX;
    *cameraY += deltaY;

    if(*cameraX < 0.0 || *cameraX > (double)mapXSize 
       || *cameraY < 0.0 || *cameraY > (double)mapYSize
       || map[(int)floor(*cameraX)][(int)floor(*cameraY)])
    {
      *cameraX -= deltaX;
      *cameraY -= deltaY;
    }
  }
  else
  {
    switch(input)
    {
      case 'a' :
        for(i = 0; i < rayNum; i++)
          _addClampedToUnitCircle(rays + i, -SMALL_STEP / 2);
        break;
      case 'd' :
        for(i = 0; i < rayNum; i++)
          _addClampedToUnitCircle(rays + i, SMALL_STEP / 2);
        break;
    }
  }
}
