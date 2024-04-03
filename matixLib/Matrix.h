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

		float getAt(int x, int y);
		bool setAt(float value, int x, int y);

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
		static My::Matrix multiply(My::Matrix matrix, float val);
		My::Matrix operator*(float val);

		bool multiplyBy(float val);
		bool operator*= (float val);

		//multiplication by another matrix
		static My::Matrix multiply(My::Matrix first, My::Matrix second);
		My::Matrix operator*(My::Matrix second);
		bool multiplyBy(My::Matrix matrix);
		bool operator*=(My::Matrix matrix);

		//determinant
		static float det(My::Matrix matrix);
		float det();
		

	private:
		int m_width, m_height;
		std::vector<std::vector<float>> *m_values;
	};
}
