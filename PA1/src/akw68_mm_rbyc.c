#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BILLION 1000000000L
#define NUM_TRIALS 5

int main(int argc, char **argv)
{
  int n;
  if (argc != 2)
  {
    printf("Usage: rbyc n\nAborting...\n");
    exit(0);
  }
  n = atoi(argv[1]);
  int i, j, k;
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

  // Perform Multiplication (Record time)
  int a;
  for (a = 0; a < NUM_TRIALS; a++)
  {
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (i = 0; i < n; i++)
    {
      for (j = 0; j < n; j++)
      {
        for (k = 0; k < n; k++)
        {
          res[i][j] += M1[i][k] * M2[k][j];
        }
      }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    time[a] = BILLION * (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
    time[a] = time[a] / BILLION;
    printf("n = %d trial %d   %f\n", n, a, time[a]);
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
  if (n == 128)
  {
    file = fopen("rbyc_res.txt", "w");
  }
  else
  {
    file = fopen("rbyc_res.txt", "a");
  }
  fprintf(file, "%f\n", finaltime);
  fclose(file);
}
