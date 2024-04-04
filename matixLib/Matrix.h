#pragma once
#include <vector>
#include <string>

#include "error.h"

namespace My
{
	class Matrix
	{
	public:
		Matrix(int width, int height);

		int getWidth() {return m_width;}
		int getHeight() {return m_height;}

		double getAt(int x, int y);
		bool setAt(double value, int x, int y);

		////copy constructor
		//Matrix(My::Matrix& matrix);

		//deep copy
		My::Matrix& operator=(const My::Matrix& matrix);

		//addition
		static My::Matrix add(My::Matrix first, My::Matrix second);
		My::Matrix operator+( My::Matrix second);

		bool addTo(My::Matrix second);
		bool operator+=(My::Matrix second);

		//transposition
		static My::Matrix transpose(My::Matrix);
		My::Matrix operator~();
		bool transpose();

		//multiplication by a scalar
		static My::Matrix multiply(My::Matrix matrix, double val);
		My::Matrix operator*(double val);

		bool multiplyBy(double val);
		bool operator*= (double val);

		//multiplication by another matrix
		static My::Matrix multiply(My::Matrix first, My::Matrix second);
		My::Matrix operator*(My::Matrix second);
		bool multiplyBy(My::Matrix matrix);
		bool operator*=(My::Matrix matrix);

		//determinant
		static double det(My::Matrix matrix);
		double det();

		//minors
		static My::Matrix minor(My::Matrix& matrix, int x, int y);
		My::Matrix minor(int x, int y);

		//Matrix of minors
		static My::Matrix matrixOfMinors(My::Matrix& matrix);
		My::Matrix matrixOfMinors();

		//matrix of cofactors
		static My::Matrix matrixOfCofactor(My::Matrix& matrix);
		My::Matrix matrixOfCofactor();

		//Adjoint matrix
		static My::Matrix adjoint(My::Matrix matrix);
		My::Matrix adjoint();

		//Inverse matrix
		static My::Matrix inverse(My::Matrix& matrix);
		My::Matrix inverse();

		

	private:
		int m_width, m_height;
		std::vector<std::vector<double>> m_values;
	};
}

inline std::ostream& operator<<(std::ostream& stream, My::Matrix matrix)
{
	for (int j = 0; j < matrix.getHeight(); j++)
	{
		for (int i = 0; i < matrix.getWidth(); i++)
		{
			stream << matrix.getAt(i, j)<<" ";
		}
		stream<<"\n";
	}
	return stream;
}

