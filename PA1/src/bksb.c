#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BILLION 1000000000L

void
bksb(double **a, double *b, int n) {
    register int i, j, end;
    register double sum;
    end = n - 1;
    for(i = end; i >= 0; i--) {
        sum = b[i];
        for(j = end; j > i; j--)
            sum -= a[i][j] * b[j];
        b[i] = sum / a[i][i];
    }
}

int
main(int argc, char **argv) {
    struct timespec start, end;
    double time;
    int n, i, j;
    double **a, *b, count = 1.0;
    
    if(argc != 2) {
        printf("Usage: bksb n\nAborting...\n");
        exit(0);
    }
    n = atoi(argv[1]);
    a = (double **) malloc(n * sizeof(double *));
    for(i = 0; i < n; i++) {
        a[i] = (double *) malloc(n * sizeof(double));
        for(j = i; j < n; j++) {
            a[i][j] = count;
            count++;
        }
    }
    b = (double *) malloc(n * sizeof(double));
    for(i = 0; i < n; i++) {
        b[i] = count;
        count++;
    }
    // Printing the input matrices out:
    // printf("Input = [\n");
    // for (i = 0; i < n; i++){
    //   for (j = 0; j < n; j++){
    //     printf("%lf ", a[i][j]);
    //   }
    //   printf("\n");
    // }
    // printf("]\n");
    // printf("x = [\n");
    // for(i = 0; i < n; i++) {
    //     printf("%lf ", b[i]);
    // }
    // printf("\n");
    // printf("]\n");

    clock_gettime(CLOCK_MONOTONIC, &start);
    bksb(a, b, n);
    clock_gettime(CLOCK_MONOTONIC, &end);
    
    time =
    BILLION *(end.tv_sec - start.tv_sec) +(end.tv_nsec - start.tv_nsec);
    time = time / BILLION;
    
    printf("SERIAL IMPL|n=%d| Elapsed: %lf seconds\n", n,time);
    
    // Testing For Correctness by printing out Golden Model
    // for(i = 0; i < n; i++)
    //     printf("%lf ", b[i]);
    // printf("\n");
    // Print to ref file
    // FILE * fp = fopen("../src/ref.h", "w");
    // fprintf(fp, "double ref[] = {\n");
    // for(i = 0; i < n; i++)
    //     fprintf(fp, "%lf, ", b[i]);
    // fprintf(fp, "\n};\n\n");
    // fclose(fp);
    return 0;
}
