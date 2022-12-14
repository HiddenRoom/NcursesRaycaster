#ifndef RENDER_FRONTEND
#define RENDER_FRONTEND

#include <ncurses.h>

int wallHeight(double rayCollisonDist);

void handleUserInput(unsigned char **map, double *rays, int rayNum, double *cameraX, double *cameraY, int mapXSize, int mapYSize, int input);

void drawCamView(unsigned char **map, int mapXSize, int mapYSize, double cameraX, double cameraY, const double *rays, double *raysTmp, WINDOW *win, int winXSize, int winYSize);

#endif
