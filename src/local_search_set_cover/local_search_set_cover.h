#ifndef _LOCAL_SEARCH_SET_COVER_H_
#define _LOCAL_SEARCH_SET_COVER_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_ITERATIONS 100


bool all_covered(int **A, int m, int n, int coverage[]);

int evaluate_coverage(int **A, int m, int n, int coverage[]);

int evaluate_without_element(int **A, int m, int n, int coverage[], int index);

int* generate_neighbor(int **A, int m, int n, int *current_solution, int index);

int* find_minimal_coverage(int **A, int m, int n);


#endif // _LOCAL_SEARCH_SET_COVER_H_