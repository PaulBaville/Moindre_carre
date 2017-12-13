#ifndef MATRIX_H_
#define MATRIX_H_

#include <assert.h>
#include <iostream>
#include <vector>

class Matrix {

public:

	Matrix();
	Matrix(std::vector< std::vector< double > > values);
	~Matrix();

	const int get_nb_lin() const;
	const int get_nb_col() const;
	const double get_value(int i, int j) const;

	Matrix operator=(const Matrix& M);
	void operator*(const double& nb);
	void operator+(const Matrix& M);

	void prod_mat(const Matrix& M);
	void transpose();
	void co_mat();

	double det();

	static Matrix solve(Matrix& A, const Matrix& B);

private:

	std::vector< std::vector< double > > values_;

};


#endif /* MATRIX_H_ */
