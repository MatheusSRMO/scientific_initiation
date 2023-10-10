#ifndef _LOCAL_SEARCH_SET_COVER_H_
#define _LOCAL_SEARCH_SET_COVER_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../greedy_set_cover/greedy_set_cover.h"

#define MAX_ITERATIONS 1e3


bool all_covered(int **A, int m, int n, int coverage[]);

int* find_minimal_coverage(int **A, int m, int n);


#endif // _LOCAL_SEARCH_SET_COVER_H_