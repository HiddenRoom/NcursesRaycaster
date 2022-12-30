#ifndef RENDER_FRONTEND
#define RENDER_FRONTEND

#include <ncurses.h>

int wallHeight(double rayCollisonDist);

void handleUserInput(double *rays, int rayNum, double *cameraX, double *cameraY, int input);

void drawCamView(unsigned char **map, int mapXSize, int mapYSize, double cameraX, double cameraY, double rays[], WINDOW *win, int winYSize, int winXSize);

#endif
