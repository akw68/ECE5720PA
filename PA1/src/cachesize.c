#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BILLION 1000000000L
#define MAX_LENGTH 1 << 26
#define MIN_SIZE 1 << 10

//float *A = (float *)malloc(sizeof(float) * MAX_LENGTH);
int main(int argc, char **argv)
{
  int n, s, i, k;
  int s_ = 0;
  int n_ = 0;
  register float curr;
  struct timespec start, end;
  double time;
  double T[17][26];
  float *A = (float *)malloc(sizeof(float) * MAX_LENGTH);
  for (n = MIN_SIZE; n <= MAX_LENGTH; n = n << 1)
  {
    for (s = 1; s < n; s = s << 1)
    {
      //Start timer
      clock_gettime(CLOCK_MONOTONIC, &start);
      for (k = 0; k < s * 10; k++)
      {
        for (i = 0; i < n; i += s)
        {
          curr = A[i];
        }
      }
      clock_gettime(CLOCK_MONOTONIC, &end);
      time = BILLION * (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
      time = time / n / 10;
      T[n_][s_] = time;
      s_++;
      printf("n = %d i = %d s = %d   %f\n", n, i, s, time);
    }
    s_ = 0;
    n_++;
  }
  s_ = 0;
  n_++;
  
  int j;
  FILE *file;
  file = fopen("cache_res.csv", "w");
  for(i = 0; i < 17; i++)
  {
    for(j = 0; j < 26; j++)
    {
      fprintf(file, "%f, ", T[i][j]);
    }
    fprintf(file, "\n");
  }
  fclose(file);
}
