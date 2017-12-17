#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <string>

std::string convert_int_to_string(const int& nb) {

	std::ostringstream buff;
	buff << nb;

	return buff.str();
}

std::string convert_double_to_string(const double& nb) {

	std::ostringstream buff;
	buff << nb;

	return buff.str();
}

std::vector< std::vector< double > > read_values(std::string file_name) {

	std::ifstream file(file_name);

	if( !file.good() ) {

		std::cerr << "File " << file_name << " has not been well opened " << std::endl;

		return { {} };
	}

	std::string temp;

	file >> temp;

	int nb_values;

	file >> nb_values;
	std::cout << "Nb_values = " << nb_values << std::endl;

	std::vector< std::vector< double > > measured_values(nb_values, std::vector< double >(2, 0));

	file >> temp;
	std::cout << "Coordinate 1 = " << temp << std::endl;
	file >> temp;
	std::cout << "Coordinate 2 = " << temp << std::endl;

	for( int i = 0; i < nb_values; ++i ) {

		double X_value;
		double Y_value;

		file >> X_value;
		file >> Y_value;
		std::cout << "X" << i << " = " << X_value << " ; Y" << i << " = " << Y_value << std::endl;

		measured_values[i][0] = X_value;
		measured_values[i][1] = Y_value;

	}

	return measured_values;
}

int main( int argc, char* argv[] ) {

	std::string file_name;
//	std::cout << "values_file_name = ";
//	std::cin >> file_name;
    file_name = "measured_values.txt";
    std::cout << "file = " << file_name << std::endl;
	std::vector< std::vector< double > > values = read_values(file_name);

	int nb_points = values.size();

	int polynomial_order;
	std::cout << "polynomial order = ";
	std::cin >> polynomial_order;

	assert( polynomial_order == 1 || polynomial_order == 2 );

	std::vector< std::vector< double > > X_values(nb_points, std::vector< double >(polynomial_order + 1, 1));
	std::vector< std::vector< double > > Y_values(nb_points, std::vector< double >(1, 1));

	double a;
	double b;
	double c;

	if( polynomial_order == 1 ) {

		for( int i = 0; i < nb_points; ++i ) {
			X_values[i][0] = values[i][0];
			Y_values[i][0] = values[i][1];
		}

		Matrix A = Matrix(X_values);
		Matrix B = Matrix(Y_values);
		Matrix X = Matrix::solve(A, B);

		a = X.get_value(0, 0);
		b = X.get_value(1, 0);
		c = 0;

		std::cout << "y = ax + b" << std::endl;
		std::cout << "a = " << a << std::endl;
		std::cout << "b = " << b << std::endl;
	}
	else {

		for( int i = 0; i < nb_points; ++i ) {
			X_values[i][0] = values[i][0] * values[i][0];
			X_values[i][1] = values[i][0];
			Y_values[i][0] = values[i][1];
		}

		Matrix A = Matrix(X_values);
		Matrix B = Matrix(Y_values);
		Matrix X = Matrix::solve(A, B);

		a = X.get_value(0, 0);
		b = X.get_value(1, 0);
		c = X.get_value(2, 0);

		std::cout << "y = ax^2 + bx + c" << std::endl;
		std::cout << "a = " << a << std::endl;
		std::cout << "b = " << b << std::endl;
		std::cout << "c = " << c << std::endl;
	}

	std::string commande = "python graphics.py " +
		file_name + " " +
		convert_int_to_string(polynomial_order) + " " +
		convert_double_to_string(a) + " " +
		convert_double_to_string(b) + " " +
		convert_double_to_string(c);

    std::cout << commande << std::endl;

	printf("start python\n");
	system(commande.c_str());
	printf("python finished\n");

	return 0;
}
