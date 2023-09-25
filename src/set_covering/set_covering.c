#include "set_covering.h"

struct set_covering {
    int n;                       // Número de esquinas
    int m;                       // Número de pontos de interesse
    int r;                       // Raio de cobertura
    DistanceType distance_type;  // Tipo de distância
    Point **locations;           // Pontos de coleta
    Point **points;              // Pontos de interesse
    int *solution;               // Solução (id dos vértices) = Conjunto de esquinas
    int solution_size;           // Tamanho da solução
    int** x;                     // Matriz de decisão
};


SetCovering* set_covering_create(int n, int m, int r, Point **locations, Point **points, DistanceType distance_type) {
    SetCovering *set_covering = (SetCovering *) malloc(sizeof(SetCovering));
    set_covering->n = n;
    set_covering->m = m;
    set_covering->r = r;
    set_covering->distance_type = distance_type;
    set_covering->locations = locations;
    set_covering->points = points;
    set_covering->solution = (int *) malloc(sizeof(int) * n);
    set_covering->solution_size = 0;
    set_covering->x = (int **) malloc(sizeof(int *) * n);
    for(int i = 0; i < n; i++) {
        set_covering->x[i] = (int *) malloc(sizeof(int) * m);
        for(int j = 0; j < m; j++) {
            set_covering->x[i][j] = 0;
        }
    }
    return set_covering;    
}

// Complexity: O(n * m)
void calculate_x(SetCovering *set_covering) {
    for(int i = 0; i < set_covering->n; i++) {
        for(int j = 0; j < set_covering->m; j++) {
            Point *location = set_covering->locations[i];
            Point *point = set_covering->points[j];
            if(point_in_range(location, point, set_covering->r, set_covering->distance_type)) {
                set_covering->x[i][j] = 1;
            }
        }
    }
}

void print_x(SetCovering *set_covering) {
    for(int i = 0; i < set_covering->n; i++) {
        for(int j = 0; j < set_covering->m; j++) {
            printf("%d ", set_covering->x[i][j]);
        }
        printf("\n");
    }
}

// Brute force
void set_covering_solve(SetCovering *set_covering) {
    calculate_x(set_covering);
    print_x(set_covering);
    
    int *solution = set_covering->solution;
    int solution_size = 0;
    for(int i = 0; i < set_covering->n; i++) {
        for(int j = 0; j < set_covering->m; j++) {
            if(set_covering->x[i][j] == 1) {
                solution[solution_size++] = i;
                break;
            }
        }
    }
    set_covering->solution_size = solution_size;

    /*
        
    for(int i = 0; i < set_covering->m; i++) {
        int min = 999999;
        int selected = -1;

        for(int j = 0; j < set_covering->n; j++) {
            if(set_covering->x[j][i] == 1) {
                int count = 0;
                for(int k = 0; k < set_covering->m; k++) {
                    if(set_covering->x[j][k] == 1) {
                        count++;
                    }
                }
                if(count < min) {
                    min = count;
                    selected = j;
                }
            }
        }
        if(selected != -1) {
            set_covering->solution[set_covering->solution_size++] = selected;
        }
    }
    */
}

void set_covering_destroy(SetCovering *set_covering) {
    for(int i = 0; i < set_covering->n; i++) {
        free(set_covering->x[i]);
    }
    free(set_covering->x);
    free(set_covering->solution);
    free(set_covering);
}
int* set_covering_get_solution(SetCovering *set_covering){
    return set_covering->solution;
}

int set_covering_get_solution_size(SetCovering *set_covering)  {
    return set_covering->solution_size;
}
