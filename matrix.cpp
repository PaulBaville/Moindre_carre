#include "matrix.h"

Matrix::Matrix() {
	std::vector< std::vector< double > > values = { { 1 } };
	values_ = values;
}

Matrix::Matrix(std::vector< std::vector< double > > values) :
	values_(values) {
}

Matrix::~Matrix() {
}

const int Matrix::get_nb_lin() const {

	return values_.size();
}

const int Matrix::get_nb_col() const {

	int nb_col = values_[0].size();

	return nb_col;
}

const double Matrix::get_value(int i, int j) const {

	return values_[i][j];
}

Matrix Matrix::operator=(const Matrix& M) {

	if (this == &M) {
		return *this;
	}

	values_ = M.values_;

	return *this;
}

void Matrix::operator*(const double& nb) {

	for (int i = 0; i < get_nb_lin(); ++i) {
		for (int j = 0; j < get_nb_col(); ++j) {
			values_[i][j] *= nb;
		}
	}
}

void Matrix::operator+(const Matrix& M) {

	assert(get_nb_lin() == M.get_nb_lin() &&
		   get_nb_col() == M.get_nb_col());

	for (int i = 0; i < get_nb_lin(); ++i) {
		for (int j = 0; j < get_nb_col(); ++j) {
			values_[i][j] += M.values_[i][j];
		}
	}
}

void Matrix::prod_mat(const Matrix& M) {

	assert(M.get_nb_lin() == get_nb_col());

	int nb_lin = get_nb_lin();
	int nb_col = M.get_nb_col();

	std::vector< std::vector< double > > temp_values(get_nb_lin(), std::vector< double >(M.get_nb_col(), 0));

	for (int i = 0; i < nb_lin; ++i) {
		for (int j = 0; j < nb_col; ++j) {
			for (int k = 0; k < get_nb_col(); ++k) {
				temp_values[i][j] += values_[i][k] * M.values_[k][j];
			}
		}
	}

	values_ = temp_values;
}

void Matrix::transpose() {

	int nb_lin = get_nb_lin();
	int nb_col = get_nb_col();

	int new_nb_lin = nb_col;
	int new_nb_col = nb_lin;

	std::vector< std::vector< double > > temp_values(new_nb_lin, std::vector< double >(new_nb_col, 0));

	for (int i = 0; i < new_nb_lin; ++i) {
		for (int j = 0; j < new_nb_col; ++j) {
			temp_values[i][j] = values_[j][i];
		}
	}

	values_ = temp_values;
}

void Matrix::co_mat() {

	assert(get_nb_lin() == get_nb_col() &&
		  (get_nb_lin() == 2 || get_nb_lin() == 3));

	std::vector< std::vector< double > > temp_values(get_nb_lin(), std::vector< double >(get_nb_col(), 0));

	if (get_nb_lin() == 2) {

		temp_values[0][0] = values_[1][1];
		temp_values[0][1] = -values_[1][0];
		temp_values[1][0] = -values_[0][1];
		temp_values[1][1] = values_[0][0];

		values_ = temp_values;

	}
	else if (get_nb_lin() == 3) {

		temp_values[0][0] =  (values_[1][1] * values_[2][2] - values_[1][2] * values_[2][1]);
		temp_values[0][1] = -(values_[0][1] * values_[2][2] - values_[0][2] * values_[2][1]);
		temp_values[0][2] =  (values_[0][1] * values_[1][2] - values_[0][2] * values_[1][1]);
		temp_values[1][0] = -(values_[1][0] * values_[2][2] - values_[1][2] * values_[0][2]);
		temp_values[1][1] =  (values_[0][0] * values_[2][2] - values_[0][2] * values_[2][0]);
		temp_values[1][2] = -(values_[0][0] * values_[1][2] - values_[0][2] * values_[1][0]);
		temp_values[2][0] =  (values_[0][1] * values_[1][2] - values_[1][1] * values_[0][2]);
		temp_values[2][1] = -(values_[0][0] * values_[1][2] - values_[1][0] * values_[0][2]);
		temp_values[2][2] =  (values_[0][0] * values_[1][1] - values_[1][0] * values_[0][1]);

		values_ = temp_values;
	}

}

double Matrix::det() {

	assert(get_nb_lin() == get_nb_col() &&
		  (get_nb_lin() == 2 || get_nb_lin() == 3));

	if (get_nb_lin() == 2) {

		double detM = values_[0][0] * values_[1][1] - values_[1][0] * values_[0][1];

		return detM;

	}
	else if (get_nb_lin() == 3) {

		double detM = values_[0][0] * values_[1][1] * values_[2][2] +
					  values_[0][1] * values_[1][2] * values_[2][0] +
					  values_[1][0] * values_[2][1] * values_[0][2] -
					  values_[0][2] * values_[1][1] * values_[2][0] -
					  values_[1][0] * values_[0][1] * values_[2][2] -
					  values_[0][0] * values_[2][1] * values_[1][2];
		return detM;

	}
}

Matrix Matrix::solve(Matrix& A, const Matrix& B) {

	Matrix Aa = A;
	A.transpose();
	Matrix At = A;
	Matrix Ata = At;
	At.prod_mat(Aa);
	Matrix M = At;
	Matrix Mm = M;
	M.co_mat();
	Matrix coM = M;
	coM.transpose();
	Matrix coMt = coM;
	double detM = Mm.det();
	coMt*(1 / detM);
	Matrix invM = coMt;
	Ata.prod_mat(B);
	Matrix Y = Ata;
	invM.prod_mat(Y);
	Matrix X = invM;
	return X;
}
