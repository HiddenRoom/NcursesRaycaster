#include "include/renderMath.h"
#include "include/renderFrontend.h"

#include <ncurses.h>
#include <math.h>

#define WALL_HEIGHT(winYSize, rayCollisonDist) (int)((double)winYSize * (4 / rayCollisonDist))

void drawCamView(unsigned char **map, int mapXSize, int mapYSize, double cameraX, double cameraY, double rays[], WINDOW *win, int winYSize, int winXSize) /* rays size should be winXSize */
{
  int i, j;

  int screenRayOffset;

  for(i = 0; i < winXSize; i++)
  {
    rays[i] = rayCollisonDist(map, mapXSize, mapYSize, cameraX, cameraY, rays[i]);
    screenRayOffset = (int)((winYSize - WALL_HEIGHT(winYSize, rays[i])) / 2); /* amount leftover at top and bottom of drawn intersection */

    for(j = screenRayOffset; j < winYSize - screenRayOffset; j++)
    {
      mvwprintw(win, j, i, "█");
    }
  }
}

void addClamped(double *val, double toAdd)
{
  if(*val + toAdd > 2 * M_PI)
    *val = (*val + toAdd) - 2 * M_PI;
  else if(*val + toAdd < 0)
    *val = 2 * M_PI + (*val + toAdd);
  else
    *val += toAdd;
}

void handleUserInput(double *rays, int rayNum, double *cameraX, double *cameraY, int input)
{
  int i;

  switch(input)
  {
    case 'w' :
      *cameraY += 0.2;
      break;
    case 'a' :
      *cameraX -= 0.2;
      break;
    case 's' :
      *cameraX += 0.2;
      break;
    case 'd' :
      *cameraY -= 0.2;
      break;
    case 'h' :
      for(i = 0; i < rayNum; i++)
        addClamped(rays + i, 0.1);
      break;
    case 'l' :
      for(i = 0; i < rayNum; i++)
        addClamped(rays + i, -0.1);
      break;
  }
}
