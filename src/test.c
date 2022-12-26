#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "include/renderMath.h"

#define TEST_ANGLE (M_PI * 0.25)
#define TEST_X 1.0
#define TEST_Y 1.0

#define MAP_X_SIZE 5
#define MAP_Y_SIZE 6

int main(void)
{
  int i, j;

  unsigned char **map = malloc(sizeof(char *) * MAP_X_SIZE);

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

  printf("rayCollisonDist returned %lf with cameraX %lf, CameraY %lf, rayAngle %lf, and map\n\n", rayCollisonDist(map, MAP_X_SIZE, MAP_Y_SIZE, TEST_X, TEST_Y, TEST_ANGLE), TEST_X, TEST_Y, TEST_ANGLE);
  for(i = 0; i < MAP_X_SIZE; i++)
  {
    printf("\n");
    for(j = 0; j < MAP_Y_SIZE; j++)
    {
      if(map[i][j])
      {
        printf("X");
      }
      else
      {
        printf("O");
      }
    }
  }

  printf("\n");

  for(i = 0; i < MAP_X_SIZE; i++)
  {
    free(map[i]);
  }

  free(map);

  return 0;
}
