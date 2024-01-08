#ifndef _LOCAL_SEARCH_SET_COVER_H_
#define _LOCAL_SEARCH_SET_COVER_H_
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../greedy_set_cover/greedy_set_cover.h"
#include "../utils/utils.h"

#define MAX_ITERATIONS 1e5
#define TS_FACTOR 0.5



int* local_search_set_cover(int **A, int m, int n);


#endif // _LOCAL_SEARCH_SET_COVER_H_