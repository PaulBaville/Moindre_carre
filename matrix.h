#ifndef MATRIX_H_
#define MATRIX_H_

#include <assert.h>
#include <iostream>
#include <vector>

class Matrix {

public:

	/**
 	 * \brief A constructor of matrix.
	 *
	 * @param values is a 2D vector containing matrix values.
 	 */
	Matrix(std::vector< std::vector< double > > values);

	/**
 	 * \brief Gets the row number of the matrix.
	 */
	const int get_nb_lin() const;
	
	/**
 	 * \brief Gets the column number of the matrix.
	 */
	const int get_nb_col() const;

	/**
 	 * \brief Gets the (i, j)th element of the matrix.
 	 *
 	 * @param i is the row number of the element
 	 * @param j is the column number of the element
	 */
	const double get_value( int i, int j ) const;

	/**
 	 * \brief New definition of the operator =
 	 *
 	 * @param \in M is a matrix
	 */
	Matrix operator=( const Matrix& M );

	/**
 	 * \brief New definition of the operator *
 	 * between a matrix and a scalar
 	 *
 	 * @param \in nb is a number
	 */
	void operator*( const double& nb );

	/**
 	 * \brief New definition of the operator +
 	 *
 	 * @param M is a matrix
	 */
	void operator+( const Matrix& M );

	/**
 	 * \brief Gets the product between two matrix.
 	 *
 	 * @param M is a matrix which has to have the
 	 * same number of row than the number of column
 	 * of the current matrix.
	 */
	void prod_mat( const Matrix& M );

	/**
 	 * \brief Gets the  transpose of the matrix.
 	 *
 	 * A[i, j] = A[j, i]
	 */
	void transpose();

	/**
 	 * \brief Gets the co-matrix of the matrix.
	 *
	 * The matrix has to be square
	 * Here we just process cases where shapes are 2*2 or 3*3
	 */
	void co_mat();

	/**
 	 * \brief Gets the determinant of the matrix.
	 *
 	 * The matrix has to be square
	 * Here we just process cases where shapes are 2*2 or 3*3
	 */
	double det();

	/**
 	 * \brief Gets the result X of the equation AX = B.
	 *
 	 * @param A is a matrix which contains absisses
 	 * @param B is a vector which contains ordonates
	 *
	 * The result is given by the equation :
	 *
	 * X = 1/det(AtA) * co(AtA).(AtB)
	 */
	static Matrix solve( Matrix& A, const Matrix& B );

private:

	std::vector< std::vector< double > > values_;

};


#endif /* MATRIX_H_ */
