#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BILLION 1000000000L
#define NUM_TRIALS 5

int main(int argc, char **argv)
{
  int n, b;
  if (argc != 3)
  {
    printf("Usage: tile n b\nAborting...\n");
    exit(0);
  }
  n = atoi(argv[1]);
  b = atoi(argv[2]);
  if (n % b != 0)
  {
    printf("Usage: n MUST be divisible by b\nAborting...\n");
    exit(0);
  }
  int i, j, k, l, m, p;
  float *M1[n];
  float *M2[n];
  float *res[n];

  struct timespec start, end;
  double time[NUM_TRIALS];

  srand48(1);
  for (i = 0; i < n; i++)
  {
    M1[i] = (float *)malloc(sizeof(float) * n);
    M2[i] = (float *)malloc(sizeof(float) * n);
    res[i] = (float *)malloc(sizeof(float) * n);
    for (j = 0; j < n; j++)
    {
      M1[i][j] = drand48();
      M2[i][j] = drand48();
      res[i][j] = 0;
    }
  }

  int a;
  // Perform Multiplication (Record time)
  for (a = 0; a < NUM_TRIALS; a++)
  {
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (i = 0; i < n; i += b)
    {
      for (j = 0; j < n; j += b)
      {
        for (k = 0; k < n; k += b)
        {
          for (l = 0; l < b; l++)
          {
            for (m = 0; m < b; m++)
            {
              for (p = 0; p < b; p++)
              {
                res[i + l][j + m] += M1[i + l][k + p] * M2[k + p][j + m];
              }
            }
          }
        }
      }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    time[a] = BILLION * (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
    time[a] = time[a] / BILLION;
  }
  // Average values over all trials

  double finaltime;
  for (a = 0; a < NUM_TRIALS; a++)
  {
    finaltime += time[a];
  }
  finaltime /= NUM_TRIALS;
  printf("FINAL RESULT: %f\n", finaltime);
  FILE *file;
  if (n == 128 && b == 2)
  {
    file = fopen("tile_res.txt", "w");
  }
  else
  {
    file = fopen("tile_res.txt", "a");
  }
  fprintf(file, "%f\n", finaltime);
  fclose(file);
}
