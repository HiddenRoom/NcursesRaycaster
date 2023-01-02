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

int main(void)
{
  int i, j;
  int input;

  unsigned char **map = malloc(sizeof(unsigned char *) * MAP_X_SIZE);

  /* ncurses boilerplate up here to use LINES and COLS later */
  initscr();
  raw();
  noecho();
  curs_set(0);

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

  for(i = 12; i < 16; i++)
  {
    for(j = 12; j < 16; j++)
    {
      map[i][j] = 1;
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


  do
  {
    clear();
    drawCamView(map, MAP_X_SIZE, MAP_Y_SIZE, cameraX, cameraY, rays, dummyArray, stdscr, COLS, LINES);
    //mvwprintw(stdscr, LINES - 8, 4, "X: %lf\nY: %lf\nMain view angle: %lf\n", cameraX, cameraY, rays[(int)(COLS / 2)]);
    refresh();
    input = getch();
    handleUserInput(map, rays, COLS, &cameraX, &cameraY, MAP_X_SIZE, MAP_Y_SIZE, input);
  } while(input != 'q');

  curs_set(1);
  endwin();

  free(dummyArray);
  free(rays);

  return 0;
}
