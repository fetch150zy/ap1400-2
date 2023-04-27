/**
 * file hw1.h
 * fetch150zy (Mars_zhewei@outlook.com)
 * date 2023-04-26 
 * copyleft Copyleft (ɔ) 2023 
 */
#ifndef AP_HW1_H
#define AP_HW1_H

#include <vector>
#include <cstddef>

using Matrix = std::vector<std::vector<double>>;

namespace algebra
{
    /* Create a (n * m) matrix(all of zero) */
    Matrix zeros(size_t n, size_t m);

    /* Create a (n * m) matrix(all of one) */
    Matrix ones(size_t n, size_t m);

    /* Create a n * m matrix(all of elements between min -> max) */
    Matrix random(size_t n, size_t m, double min, double max);

    /* Show matrix */
    void show(const Matrix& matrix);

    /* Multiply: scalar number  */
    Matrix multiply(const Matrix& matrix, double c);

    /* Multiply: matrix */
    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2);

    /* Sum: scalar number */
    Matrix sum(const Matrix& matrix, double c);

    /* Sum: matrix */
    Matrix sum(const Matrix& matrix1, const Matrix& matrix2);
    
    /* Matrix transpose */
    Matrix transpose(const Matrix& matrix);

    /* Matrix minor */
    Matrix minor(const Matrix& matrix, size_t n, size_t m);

    /* Calculate the determinant */
    double determinant(const Matrix& matrix);

    /* Calculate matrix inversion */
    Matrix inverse(const Matrix& matrix);

    /* Merge two matrices */
    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis=0);

    /* Swap two rows */
    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2);

    /* R raw: scalar number */
    Matrix ero_multiply(const Matrix& matrix, size_t r, double c);

    /* R1 row scalar number adds to r2 row */
    Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2);

    /* Calculate upper triangular */
    Matrix upper_triangular(const Matrix& matrix);
    
} // namespace algebra


#endif //AP_HW1_H
