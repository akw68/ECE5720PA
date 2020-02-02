#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define BILLION 1000000000L

#include "ref.h"

typedef struct
{
  double **a, *b;
  int *c, n, p, pid;
} GM;

void *
pbksb(void *varg)
{
  GM *arg = varg;
  register int i, j, k, last;
  register double sum;
  int pid, n, p, *c, start1, start2, half, prev;
  double **a, *b;
  a = arg->a;
  b = arg->b;
  c = arg->c;
  n = arg->n;
  p = arg->p;
  pid = arg->pid;
  half = n >> 1;
  start1 = n - 1 - pid;
  prev = (half - 1) % p;                    //last thread at half way mark
  start2 = half - 1 - (prev - pid + p) % p; //starting point for each thread
  last = n;
  for (i = start1; i >= half; i -= p)
  {
    sum = b[i];
    for (j = n - 1; j >= last; j--)
    {
      sum -= a[i][j] * b[j];
    }
    for (j = last - 1; j > i; j--)
    {
      //printf("Core %d blocked by %d\n", pid, *c);
      //if(c[j]==0) printf("blocked by %d\n", j);
      while (*c == j)
        ;
      sum -= a[i][j] * b[j];
    }
    b[i] = sum / a[i][i];
    //printf("Computed b[%d]\n", *c);
    *c = *c - 1;
    last = i;
  }
  for (k = start2; k >= 0; k -= p)
  {
    //printf("%d\n", k);
    sum = b[k];
    for (j = n - 1; j >= last; j--)
    {
      sum -= a[k][j] * b[j];
    }
    for (j = last - 1; j > k; j--)
    {
      while (*c == j)
        ;
      sum -= a[k][j] * b[j];
    }
    b[k] = sum / a[k][k];
    *c = *c - 1;
    last = k;
  }
  // for(j = n - 1; j > end; j--)
  //     while(c[j] == 0);
  // for(i = end; i >= start; i--) {
  //     sum = b[i];
  //     for(j = n - 1; j > i; j--)
  //         sum -= a[i][j] * b[j];
  //     b[i] = sum / a[i][i];
  //     c[i] = 1;
  // }
  return NULL;
}

int main(int argc, char **argv)
{
  struct timespec start, end;
  int i, j, p, n, *c;
  double **a, *b, time, count = 1.0;
  if (argc != 3)
  {
    printf("Usage: pbksb n p\nAborting...\n");
    exit(0);
  }
  n = atoi(argv[1]);
  p = atoi(argv[2]);
  a = (double **)malloc(n * sizeof(double *));
  for (i = 0; i < n; i++)
  {
    a[i] = (double *)malloc(n * sizeof(double));
    for (j = i; j < n; j++)
    {
      a[i][j] = count;
      count++;
    }
  }
  b = (double *)malloc(n * sizeof(double));
  c = (int *)malloc(sizeof(int));
  *c = n - 1;
  for (i = 0; i < n; i++)
  {
    b[i] = count;
    count++;
  }
  //c[n-1]=1;
  clock_gettime(CLOCK_MONOTONIC, &start);
  pthread_t *threads = malloc(p * sizeof(threads));
  for (i = 0; i < p; i++)
  {
    GM *arg = malloc(sizeof(*arg));
    arg->a = a;
    arg->b = b;
    arg->c = c;
    arg->n = n;
    arg->p = p;
    arg->pid = i;
    pthread_create(&threads[i], NULL, pbksb, arg);
  }
  for (i = 0; i < p; i++)
    pthread_join(threads[i], NULL);
  clock_gettime(CLOCK_MONOTONIC, &end);
  free(threads);

  time = BILLION * (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
  time = time / BILLION;

  printf("PARALLEL IMPL|n=%d, p=%d| Elapsed time: %lf seconds\n", n, p, time);

  //   // Testing For Correctness
  // int mismatch = 0;
  // // Checking Module
  // for (i = 0; i < n; i++)
  // {
  //   if ((b[i] - ref[i] > 0.000001) || (ref[i] - b[i] > 0.000001))
  //     mismatch = 1;
  // }
  // // Printing Module
  // if (mismatch)
  // {
  //   printf("\033[1;31mTEST FAILED\033[0m\n");
  //   printf("ref = [ ");
  //   for (i = 0; i < n; i++)
  //   {
  //     printf("% 6.3f ", ref[i]);
  //   }
  //   printf("]\n");
  //   printf("ans = [ ");
  //   for (i = 0; i < n; i++)
  //   {
  //     if (b[i] - ref[i] > 0.000001 || ref[i] - b[i] > 0.000001)
  //       printf("\033[0;31m% 6.3f ", b[i]);
  //     else
  //       printf("\033[1;32m% 6.3f ", b[i]);
  //   }
  //   printf("\033[0m]\n\n");
  // }
  // else
  //   printf("\033[1;32mTEST PASSED\033[0m\n");

  // return 0;
}
