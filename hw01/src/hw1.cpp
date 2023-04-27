/**
 * file hw1.cpp
 * fetch150zy (Mars_zhewei@outlook.com)
 * date 2023-04-26 
 * copyleft Copyleft (ɔ) 2023 
 */
#include "hw1.h"
#include <algorithm>    // std::fill
#include <random>       // for random
#include <iomanip>      // for show matrix
#include <iostream>
#include <cmath>

namespace algebra
{
    /* Create a (n * m) matrix(all of zero) */
    Matrix zeros(size_t n, size_t m)
    {
        if (n < 0 || m < 0)
            throw std::logic_error("n and m can't be negative");
        Matrix matrix(n, std::vector<double>(m));
        for (auto &row: matrix)
            std::fill(row.begin(), row.end(), 0.0);
        return matrix;
    }

    /* Create a (n * m) matrix(all of one) */
    Matrix ones(size_t n, size_t m)
    {
        if (n < 0 || m < 0)
            throw std::logic_error("n and m can't be negative");
        Matrix matrix(n, std::vector<double>(m));
        for (auto &row: matrix)
            std::fill(row.begin(), row.end(), 1.0);
        return matrix;
    }

    /* Create a (n * m) matrix(all of elements between min -> max) */
    Matrix random(size_t n, size_t m, double min, double max)
    {
        if (n < 0 || m < 0)
            throw std::logic_error("n and m can't be negative");
        if (min > max)
            throw std::logic_error("min must less than max");
        std::random_device r;
        std::default_random_engine e(r());
        std::uniform_real_distribution<double> uniform_dist(min, max);
        Matrix matrix(n, std::vector<double>(m));
        for (auto &row: matrix)
            for (auto &x: row)
                x = uniform_dist(e);
        return matrix;
    }

    /* Show matrix */
    void show(const Matrix& matrix)
    {
        if (matrix.empty())
            std::cout << "[ ]\n";
        for (auto &row: matrix) {
            for (auto x: row)
                std::cout << std::setw(10) << std::setiosflags(std::ios::right)
                    << std::fixed << std::setprecision(3) << x;
            std::cout << '\n';
        }
    }

    /* Multiply: scalar number  */
    Matrix multiply(const Matrix& matrix, double c)
    {
        if (matrix.empty())
            return {};
        Matrix matrix_(matrix);
        for (auto &row: matrix_)
            for (auto &x: row)
                x *= c;
        return matrix_;
    }

    /* Multiply: matrix */
    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2)
    {
        if (matrix1.empty() && matrix2.empty())
            return {};
        if (matrix1.empty() || matrix2.empty())
            throw std::logic_error("one of matrices is empty");
        auto n1 = matrix1.size(), m1 = matrix1[0].size();
        auto n2 = matrix2.size(), m2 = matrix2[0].size();
        if (m1 != n2)
            throw std::logic_error("m1 should be equs n2");
        Matrix matrix_(n1, std::vector<double>(m2));
        for (auto &row: matrix_)
            std::fill(row.begin(), row.end(), 0.0);
        for (int i = 0; i < n1; ++i) {
            for (int j = 0; j < m2; ++j) {
                for (int k = 0; k < m1; ++k) {
                    matrix_[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
        return matrix_;
    }

    /* Sum: scalar number */
    Matrix sum(const Matrix& matrix, double c)
    {
        if (matrix.empty())
            return {};
        Matrix matrix_(matrix);
        for (auto &row: matrix_)
            for (auto &x: row)
                x += c;
        return matrix_;
    }

    /* Sum: matrix */
    Matrix sum(const Matrix& matrix1, const Matrix& matrix2)
    {
        if (matrix1.empty() && matrix2.empty())
            return {};
        if (matrix1.empty() || matrix2.empty())
            throw std::logic_error("one of matrices is empty");
        auto n1 = matrix1.size(), m1 = matrix1[0].size();
        auto n2 = matrix1.size(), m2 = matrix1[0].size();
        if (n1 != n2 || m1 != m2)
            throw std::logic_error("two matrices should be same shape");
        Matrix matrix_(n1, std::vector<double>(m1));
        for (int i = 0; i < n1; ++i)
            for (int j = 0; j < m1; ++j)
                matrix_[i][j] = matrix1[i][j] + matrix2[i][j];
        return matrix_;
    }
    
    /* Matrix transpose */
    Matrix transpose(const Matrix& matrix)
    {
        if (matrix.empty())
            return {};
        auto n = matrix.size(), m = matrix[0].size();
        Matrix matrix_(m, std::vector<double>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                matrix_[j][i] = matrix[i][j];
        return matrix_;
    }

    /* Matrix minor */
    Matrix minor(const Matrix& matrix, size_t n, size_t m)
    {
        if (matrix.empty())
            return {};
        auto rown = matrix.size(), coln = matrix[0].size();
        if (n >= rown || m >= coln || n < 0 || m < 0)
            throw std::logic_error("n or m is out of range");
        Matrix matrix_(rown - 1, std::vector<double>(coln - 1));
        for (int i = 0, j = 0; i < rown, j < rown - 1; ++i) {
            if (i == n)
                continue;
            for (int x = 0, y = 0; x < coln, y < coln - 1; ++x) {
                if (x == m)
                    continue;
                matrix_[j][y++] = matrix[i][x];
            }
            ++j;
        }
        return matrix_;
    }

    /* Calculate the determinant */
    double determinant(const Matrix& matrix)
    {
        if (matrix.empty())
            return 1.0;
        auto n = matrix.size(), m = matrix[0].size();
        if (n != m)
            throw std::logic_error("n should equal m");
        double res = 0.0;
        for (int j = 0; j < m; ++j) {
            res += matrix[0][j] * std::pow(-1, j) *
                    determinant(minor(matrix, 0, j));
        }
        return res;
    }

    /* Division: scalar number */
    static Matrix divide(const Matrix& matrix, double c)
    {
        if (matrix.empty())
            return {};
        constexpr double esp = 1e-10;
        if (c > -esp && c < esp)
            throw std::logic_error("c should not be 0");
        Matrix matrix_(matrix);
        for (auto &row: matrix_)
            for (auto &x: row)
                x /= c;
        return matrix_;
    }

    /* Adjoint matrix */
    static Matrix adjoint(const Matrix& matrix)
    {
        if (matrix.empty())
            return {};
        auto n = matrix.size(), m = matrix[0].size();
        if (n != m)
            throw std::logic_error("n should equal m");
        Matrix matrix_(n, std::vector<double>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                matrix_[j][i] = std::pow(-1, i + j) *
                        determinant(minor(matrix, i, j));
            }
        }
        return matrix_;
    }

    /* Calculate matrix inversion */
    Matrix inverse(const Matrix& matrix)
    {
        if (matrix.empty())
            return {};
        if (matrix.size() != matrix[0].size())
            throw std::logic_error("n should equal m");
        if (determinant(matrix) == 0)
            throw std::logic_error("should not be singular matrix");
        return divide(adjoint(matrix), determinant(matrix));
    }

    /* Merge two matrices */
    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis)
    {
        if (matrix1.empty() && matrix2.empty())
            return {};
        if (matrix1.empty() || matrix2.empty())
            throw std::logic_error("one of matrix is empty");
        auto n1 = matrix1.size(), m1 = matrix1[0].size();
        auto n2 = matrix2.size(), m2 = matrix2[0].size();
        if (axis == 0) {
            if (m1 != m2)
                throw std::logic_error("m1 should equal m2");
            Matrix matrix_(n1 + n2);
            std::copy(matrix1.begin(), matrix1.end(), matrix_.begin());
            std::copy(matrix2.begin(), matrix2.end(), matrix_.begin() + n1);
            return matrix_;
        } else if (axis == 1) {
            if (n1 != n2)
                throw std::logic_error("n1 should equal n2");
            Matrix matrix_(n1);
            std::copy(matrix1.begin(), matrix1.end(), matrix_.begin());
            for (int i = 0; i < n1; ++i)
                for (int j = 0; j < m2; ++j)
                    matrix_[i].push_back((matrix2[i][j]));
            return matrix_;
        } else {
            throw std::logic_error("axis should be 0 or 1");
        }
    }

    /* Swap two rows */
    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2)
    {
        if (matrix.empty())
            return {};
        auto n = matrix.size();
        if (r1 >= n || r2 >= n || r1 < 0 || r2 < 0)
            throw std::logic_error("r1 or r2 is out of range");
        Matrix matrix_(n);
        std::copy(matrix.begin(), matrix.end(), matrix_.begin());
        std::iter_swap(matrix_.begin() + r1, matrix_.begin() + r2);
        return matrix_;
    }

    /* R raw: scalar number */
    Matrix ero_multiply(const Matrix& matrix, size_t r, double c)
    {
        if (matrix.empty())
            return {};
        auto n = matrix.size();
        if (r >= n || r < 0)
            throw std::logic_error("r is out of range");
        Matrix matrix_(n);
        std::copy(matrix.begin(), matrix.end(), matrix_.begin());
        std::transform(matrix_[r].begin(), matrix_[r].end(), 
                matrix_[r].begin(), [c](double x){ return x * c; });
        return matrix_;
    }

    /* R1 row scalar number adds to r2 row */
    Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2)
    {
        if (matrix.empty())
            return {};
        auto n = matrix.size();
        if (r1 >= n || r2 >= n || r1 < 0 || r2 < 0)
            throw std::logic_error("r1 or r2 is out of range");
        Matrix matrix_(n);
        std::copy(matrix.begin(), matrix.end(), matrix_.begin());
        std::transform(matrix_[r1].begin(), matrix_[r1].end(),
                matrix_[r2].begin(),
                matrix_[r2].begin(), [c](double x, double y){ return y + x * c; });
        return matrix_;
    }

    /* Calculate upper triangular */
    Matrix upper_triangular(const Matrix& matrix)
    {
        if (matrix.empty())
            return {};
        auto n = matrix.size(), m = matrix[0].size();
        if (n != m)
            throw std::logic_error("matrix should be square");
        Matrix matrix_(matrix);
        for (int j = 0; j < m; ++j) {
            double diagonal_elem = matrix_[j][j];
            for (int i = j + 1; i < n; ++i) {
                double elem = matrix_[i][j];
                matrix_ = ero_sum(matrix_, j, - elem / diagonal_elem, i);
            }
        }
        return matrix_;
    }

} // namespace algebra
