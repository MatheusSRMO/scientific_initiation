#ifndef _LINEAR_PROGRAMING_H_
#define _LINEAR_PROGRAMING_H_

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    LP_SUCCESS, // Sucesso
    LP_ERROR,   // Erro
} LPStatus;

typedef enum {
    LP_MIN, // Minimizar
    LP_MAX, // Maximizar
} LPObjective;

typedef enum {
    LP_EQUAL,         // Igual
    LP_LESS_EQUAL,    // Maior ou igual
    LP_GREATER_EQUAL, // Menor ou igual
} LPConstraint;

typedef struct {
    int n;                     // number of variables
    int m;                     // number of constraints
    int *c;                 // objective function
    int *b;                 // right hand side
    int **A;                // constraint matrix
    int *solution;          // solution
    int solution_size;         // size of solution
    LPObjective objective;     // objective type
    LPConstraint constraints; // constraints type
} LinearPrograming;


LinearPrograming *linear_programing_create(int n, int m, LPObjective objective, LPConstraint constraints);


void linear_programing_set_objective(LinearPrograming *lp, int *c);

void linear_programing_set_right_hand_side(LinearPrograming *lp, int *b);

void linear_programing_set_constraint_matrix(LinearPrograming *lp, int **A);

void linear_programing_destroy(LinearPrograming *lp);

LPStatus lp_solve(LinearPrograming *lp);

void linear_programing_get_solution(LinearPrograming *lp, int *solution);

#endif // _LINEAR_PROGRAMING_H_