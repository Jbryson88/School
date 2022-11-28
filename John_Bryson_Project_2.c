// John Bryson
// Project#2 Matrix Multiplication
// Due 10/16/2022
// CS 3513

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define M 3
#define K 2
#define N 3

int A[M][K] = { {1, 4}, {2, 5}, {3, 6} };
int B[K][N] = { {8, 7, 6}, {5, 4, 3} };

int C[M][N];

struct v
{
  int i;			/* row */
  int j;			/* column */
};

void *runner (void *param);	/* the thread */

int
main (int argc, char *argv[])
{
  int i, j, count = 0;
  pthread_t workers[M * N];	/* the thread identifier */
  pthread_attr_t attr;		/* set of thread attributes */
  /* get the default attributes */
  pthread_attr_init (&attr);
  struct v *data = (struct v *) malloc (sizeof (struct v));
  for (i = 0; i < M; i++)
    for (j = 0; j < N; j++)
      {
	data->i = i;
	data->j = j;
	/* create the thread */
	pthread_create (&workers[count++], &attr, runner, data);
      }
  for (i = 0; i < M * N; i++)
    pthread_join (workers[i], NULL);
  for (i = 0; i < M; i++)
    {
      for (j = 0; j < N; j++)
	printf ("%d ", C[i][j]);
      printf (" ");
    }
}

/* The thread will begin control in this function */
void *
runner (void *param)
{
  struct v *data = param;	/* the structure that holds our data */
  int n, sum = 0;
  /* row multiplied by column */
  for (n = 0; n < K; n++)
    sum += A[data->i][n] * B[n][data->j];
  /* assign the sum to its coordinate */
  C[data->i][data->j] = sum;
  /* terminate the thread */
  pthread_exit (0);
}
