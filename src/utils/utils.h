#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

// Print vector, if size > MAX_LINE_LENGTH, print the first MAX_LINE_LENGTH elements and ...]
void print_vector(int *vector, int size);

#endif // _UTILS_H_