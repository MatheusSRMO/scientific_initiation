#include "point.h"

struct point {
    int id;
    double x;
    double y;
};

Point* point_create(int id, double x, double y) {
    Point* point = (Point *) malloc(sizeof(Point));
    point->id = id;
    point->x = x;
    point->y = y;
    return point;
}

void point_destroy(Point* point) {
    free(point);
}

int point_get_id(Point* point) {
    return point->id;
}

double point_get_x(Point* point) {
    return point->x;
}

double point_get_y(Point* point) {
    return point->y;
}

double point_eucledian_distance(Point* point1, Point* point2) {
    double x1 = point_get_x(point1);
    double y1 = point_get_y(point1);
    double x2 = point_get_x(point2);
    double y2 = point_get_y(point2);
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double point_manhattan_distance(Point* point1, Point* point2) {
    double x1 = point_get_x(point1);
    double y1 = point_get_y(point1);
    double x2 = point_get_x(point2);
    double y2 = point_get_y(point2);
    return fabs(x1 - x2) + fabs(y1 - y2);
}

double point_chebyshev_distance(Point* point1, Point* point2) {
    double x1 = point_get_x(point1);
    double y1 = point_get_y(point1);
    double x2 = point_get_x(point2);
    double y2 = point_get_y(point2);
    return fmax(fabs(x1 - x2), fabs(y1 - y2));
}

double point_geographical_distance(Point* point1, Point* point2) {
    double x1 = point_get_x(point1);
    double y1 = point_get_y(point1);
    double x2 = point_get_x(point2);
    double y2 = point_get_y(point2);
    double PI = 3.141592;
    double RRR = 6378.388;
    double q1 = cos(y1 - y2);
    double q2 = cos(x1 - x2);
    double q3 = cos(x1 + x2);
    return RRR * acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0;
}

double point_distance(Point* point1, Point* point2, DistanceType distance_type) {
    switch(distance_type) {
        case eucledian:
            return point_eucledian_distance(point1, point2);
        case manhattan:
            return point_manhattan_distance(point1, point2);
        case chebyshev:
            return point_chebyshev_distance(point1, point2);
        case geographical:
            return point_geographical_distance(point1, point2);
    }
    return 0;
}

void point_print(Point* point) {
    printf("%d %lf %lf\n", point->id, point->x, point->y);
}

void point_print_list(Point** point_list, int dimension) {
    for(int i = 0; i < dimension; i++) {
        point_print(point_list[i]);
    }
}

void point_print_list_with_distances(Point** point_list, int dimension, DistanceType distance_type) {
    for(int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            printf("%lf ", point_distance(point_list[i], point_list[j], distance_type));
        }
        printf("\n");
    }
}

void point_print_list_with_distances_to_file(Point** point_list, int dimension, DistanceType distance_type, char* file_name) {
    FILE* file = fopen(file_name, "w");
    for(int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            fprintf(file, "%lf ", point_distance(point_list[i], point_list[j], distance_type));
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

Point** point_list_create(int dimension) {
    Point** point_list = (Point **) malloc(sizeof(Point *) * dimension);
    for(int i = 0; i < dimension; i++) {
        point_list[i] = NULL;
    }
    return point_list;
}

Point* point_list_get_by_id(Point** point_list, int dimension, int id) {
    for(int i = 0; i < dimension; i++) {
        if(point_get_id(point_list[i]) == id) {
            return point_list[i];
        }
    }
    return NULL;
}

void point_list_destroy(Point** point_list, int dimension) {
    for(int i = 0; i < dimension; i++) {
        point_destroy(point_list[i]);
    }
    free(point_list);
}

void point_list_print(Point** point_list, int dimension) {
    for(int i = 0; i < dimension; i++) {
        point_print(point_list[i]);
    }
}

void point_list_print_with_distances(Point** point_list, int dimension, DistanceType distance_type) {
    for(int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            printf("%lf ", point_distance(point_list[i], point_list[j], distance_type));
        }
        printf("\n");
    }
}

void point_list_print_with_distances_to_file(Point** point_list, int dimension, DistanceType distance_type, char* file_name) {
    FILE* file = fopen(file_name, "w");
    for(int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            fprintf(file, "%lf ", point_distance(point_list[i], point_list[j], distance_type));
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

Point** point_list_from_file(char* file_name, int dimension) {
    FILE* file = fopen(file_name, "r");
    Point** point_list = point_list_create(dimension);
    int id;
    double x, y;
    for(int i = 0; i < dimension; i++) {
        fscanf(file, "%d %lf %lf", &id, &x, &y);
        point_list[i] = point_create(id, x, y);
    }
    fclose(file);
    return point_list;
}

void point_list_to_file(Point** point_list, int dimension, char* file_name) {
    FILE* file = fopen(file_name, "w");
    for(int i = 0; i < dimension; i++) {
        fprintf(file, "%d %lf %lf\n", point_list[i]->id, point_list[i]->x, point_list[i]->y);
    }
    fclose(file);
}

void point_list_to_file_with_distances(Point** point_list, int dimension, DistanceType distance_type, char* file_name) {
    FILE* file = fopen(file_name, "w");
    for(int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            fprintf(file, "%lf ", point_distance(point_list[i], point_list[j], distance_type));
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void point_list_to_file_with_distances_to_file(Point** point_list, int dimension, DistanceType distance_type, char* file_name) {
    FILE* file = fopen(file_name, "w");
    for(int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            fprintf(file, "%lf ", point_distance(point_list[i], point_list[j], distance_type));
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

int point_in_range(Point* point1, Point* point2, int range, DistanceType distance_type) {
    return point_distance(point1, point2, distance_type) <= range;
}

// Path: point/point.c