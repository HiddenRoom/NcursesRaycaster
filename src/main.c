#include <ncurses.h>
#include <math.h>
#include <stdlib.h>

#include "include/renderMath.h"
#include "include/renderFrontend.h"

#define TEST_ANGLE (M_PI / 3.0)
#define TEST_X 2.0
#define TEST_Y 2.0

#define MAP_X_SIZE 30
#define MAP_Y_SIZE 30

#define LINES 20
#define COLS 20

int main(void)
{
  int i, j;
  int input;

  unsigned char **map = malloc(sizeof(unsigned char *) * MAP_X_SIZE);

  /* set up map that is a box of dimensions MAP_X_SIZE x MAP_Y_SIZE */
  for(i = 0; i < MAP_X_SIZE; i++)
  {
    map[i] = malloc(sizeof(char) * MAP_Y_SIZE);
    for(j = 0; j < MAP_Y_SIZE; j++)
    {
      if(i == 0 || i == (MAP_X_SIZE - 1) || j == 0 || j == (MAP_Y_SIZE - 1))
      {
        map[i][j] = 1;
      }
      else
      {
        map[i][j] = 0;
      }
    }
  }

  double *rays = malloc(sizeof(double) * COLS);
  double *dummyArray = malloc(sizeof(double) * COLS);

  const double fov = 2.4;
  const double fovChunk = fov / COLS;
  
  double cameraX = TEST_X;
  double cameraY = TEST_Y;

  for(i = 0; i < COLS; i++)
    rays[i] = (i + 1) * fovChunk;

  /* ncurses boilerplate */
  initscr();
  raw();
  noecho();

  do
  {
    clear();
    drawCamView(map, MAP_X_SIZE, MAP_Y_SIZE, cameraX, cameraY, rays, dummyArray, stdscr, LINES, COLS);
    refresh();
    input = getch();
    handleUserInput(rays, COLS, &cameraX, &cameraY, MAP_X_SIZE, MAP_Y_SIZE, input);
  } while(input != 'q');

  endwin();

  free(dummyArray);
  free(rays);

  return 0;
}
