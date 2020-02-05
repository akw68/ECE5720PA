#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BILLION 1000000000L
#define MAX_LENGTH 1 << 26
#define MIN_SIZE 1 << 10

float *A = (float *)malloc(sizeof(float) * MAX_LENGTH);
int main(int argc, char **argv)
{
  int n, s, i, t;
  int s_ = 0;
  int n_ = 0;
  register float curr;
  struct timespec start, end;
  double time;
  double T[17][26];

  for (n = MIN_SIZE; n <= MAX_LENGTH; n << 1)
  {
    for (s = 1; s < n; s << 1)
    {
      //Start timer
      clock_gettime(CLOCK_MONOTONIC, &start);
      for (t = 0; t < 10; t++) //Repeat 10 times
      {
        for (i = 0; i < n; i += s)
        {
          curr = A[i];
        }
      }
      clock_gettime(CLOCK_MONOTONIC, &end);
      time = BILLION * (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
      time = time / BILLION / 10;
      T[n_][s_] = time;
      s_++;
    }
  }
  s_ = 0;
  n_++;
}