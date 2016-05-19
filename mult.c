#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <time.h>

/*taille des matrices A[M][P],B[P][N],C[M][N]*/

#define M 512
#define P 512
#define N 512

#define SEC2NANO 1000000000.0f


int A[M][P];
int B[P][N];
int C[M][N];

int nbr_thread;


/* fontion du thread*/
void *
work (void *p)
{
  int Id = (intptr_t) p;
  int row_d = (Id * M) / nbr_thread;
  int row_f = ((Id + 1) * M) / nbr_thread;
  int k, i, j;
  int m, job = 0;
  int sum;



  for (i = row_d; i < row_f; i++)
    {
      for (j = 0; j < N; j++)
	{
	  for (sum = 0, k = 0; k < P; k++)
	    {
	      sum += A[i][k] * B[k][j];
	    }

	  C[i][j] = sum;
	  job++;
	}
    }

  pthread_exit (NULL);

  return (NULL);
}


int
compute ()
{
  void *status;
  pthread_t *threadid;
  pthread_attr_t attr;
  pthread_attr_setscope (&attr, PTHREAD_SCOPE_SYSTEM);
  threadid = (pthread_t *) malloc (sizeof (pthread_t) * nbr_thread);

  int i, j;
/*construction de la matrice A*/
  for (i = 0; i < M; i++)
    for (j = 0; j < P; j++)
      A[i][j] = rand () % 10;

/*construction de la matrice B*/
  for (i = 0; i < P; i++)
    for (j = 0; j < N; j++)
      B[i][j] = rand () % 10;

  unsigned long long start, end;

/*creation des threads*/
  for (i = 0; i < nbr_thread; i++)
    {

      pthread_create (&*(threadid + 1), NULL, (void *(*)(void *)) work,
		      (void *) (intptr_t) i);

    }
/*Attendre les threads*/
  for (i = 0; i < nbr_thread; i++)
    {
      pthread_join (*(threadid + i), &status);
    }

  return 0;

}


int
main (int argc, char **argv)
{
  nbr_thread = atoi (argv[1]);

  struct timespec ts;
  struct timespec ts2;

  clock_gettime (CLOCK_MONOTONIC_RAW, &ts);
  double v1 = ts.tv_nsec;
  double v2 = ts.tv_sec;

  compute ();
  clock_gettime (CLOCK_MONOTONIC_RAW, &ts);
  v1 = ts2.tv_nsec - v1;
  v2 = ts2.tv_sec - v2;
  long long totaltime =
    ((ts2.tv_sec * SEC2NANO + ts2.tv_nsec) -
     (ts.tv_sec * SEC2NANO + ts.tv_nsec));

  printf ("%d ; %f\n", nbr_thread, totaltime / SEC2NANO);

  return 0;

}
