#include <stdlib.h>
#include <stddef.h>

struct Matrix2D {
    double **data;
    size_t rows;
    size_t columns;
};

struct Matrix3D {
    double ***data;
    size_t layers;
    size_t rows;
    size_t columns;
};

struct Matrix2D *new_2DMatrix(size_t rows, size_t columns) {
    struct Matrix2D *matrix = (struct Matrix2D *)malloc(sizeof(struct Matrix2D));
    if (matrix == NULL)
        return NULL;
    matrix->data = (double **)malloc(rows * sizeof(double *));
    if (matrix->data == NULL) {
        free(matrix);
        return NULL;
    }
    for (size_t i = 0; i < rows; i++) {
        matrix->data[i] = (double *)malloc(columns * sizeof(double));
        if (matrix->data[i] == NULL) {
            free(matrix->data);
            free(matrix);
            return NULL;
        }
    }
    matrix->rows = rows;
    matrix->columns = columns;
    return matrix;
}

void free_2DMatrix(struct Matrix2D *matrix) {
    if (matrix == NULL)
        return;
    for (size_t i = 0; i < matrix->rows; i++)
        free(matrix->data[i]);
    free(matrix->data);
    free(matrix);
}

struct Matrix3D *new_3DMatrix(size_t layers, size_t rows, size_t columns) {
    struct Matrix3D *matrix = (struct Matrix3D *)malloc(sizeof(struct Matrix3D));
    if (matrix == NULL)
        return NULL;
    matrix->data = (double ***)malloc(layers * sizeof(double **));
    if (matrix->data == NULL) {
        free(matrix);
        return NULL;
    }
    for (size_t i = 0; i < layers; i++) {
        matrix->data[i] = (double **)malloc(rows * sizeof(double *));
        if (matrix->data[i] == NULL) {
            free(matrix->data);
            free(matrix);
            return NULL;
        }
        for (size_t j = 0; j < rows; j++) {
            matrix->data[i][j] = (double *)malloc(columns * sizeof(double));
            if (matrix->data[i][j] == NULL) {
                free(matrix->data[i]);
                free(matrix->data);
                free(matrix);
                return NULL;
            }
        }
    }
    matrix->layers = layers;
    matrix->rows = rows;
    matrix->columns = columns;
    return matrix;
}

void free_3DMatrix(struct Matrix3D *matrix) {
    if (matrix == NULL)
        return;
    for (size_t i = 0; i < matrix->layers; i++)
        for (size_t j = 0; j < matrix->rows; j++)
            free(matrix->data[i][j]);
    for (size_t i = 0; i < matrix->layers; i++)
        free(matrix->data[i]);
    free(matrix->data);
    free(matrix);
}
