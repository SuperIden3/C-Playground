#include <stddef.h>

/**
 * Structure for a regular matrix, or a "two-dimensional tensor".
 */
struct Matrix2D {
    double **data;
    size_t rows;
    size_t columns;
};

/**
 * Structure for a 3D matrix, or a "three-dimensional tensor".
 */
struct Matrix3D {
    double ***data;
    size_t layers;
    size_t rows;
    size_t columns;
};

/**
 * Allocate and initialize a 2D matrix.
 * @param rows Number of rows.
 * @param columns Number of columns.
 * @return Pointer to the matrix.
 */
struct Matrix2D *new_matrix2D(size_t rows, size_t columns);

/**
 * Free a 2D matrix.
 * @param matrix Matrix to free.
 * @see new_matrix2D
 */
void free_matrix2D(struct Matrix2D *matrix);

/**
 * Allocate and initialize a 3D matrix.
 * @param layers Number of layers.
 * @param rows Number of rows.
 * @param columns Number of columns.
 * @return Pointer to the matrix.
 */
struct Matrix3D *new_matrix3D(size_t layers, size_t rows, size_t columns);

/**
 * Free a 3D matrix.
 * @param matrix Matrix to free.
 * @see new_matrix3D
 */
void free_matrix3D(struct Matrix3D *matrix);

