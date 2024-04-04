#include "Matrix.h"

My::Matrix::Matrix(int width, int height)
	:m_width(width),
	m_height(height) 
{
	m_values = new std::vector<std::vector<float>>(
		m_width, std::vector<float>(m_height)
	); 
}

float My::Matrix::getAt(int x, int y)
{
	if (!(0 <= x && x < m_width && 0 <= y && y < m_height))
	{
		std::string err = "no such place in the matrix " + std::to_string(x) + " " + std::to_string(y) + "\n";
		My::errorMsg((char*)err.data());
		return 0;
	}
	return (*m_values)[x][y];
}

bool My::Matrix::setAt(float val, int x, int y)
{
	if (!(0 <= x && x < m_width && 0 <= y && y < m_height))
	{
		std::string err = "no such place in the matrix " + std::to_string(x) + " " + std::to_string(y) + "\n";
		My::errorMsg((char*)err.data());
		return false;
	}
	(*m_values)[x][y] = val;
	return true;
}

//addition
My::Matrix My::Matrix::add(My::Matrix first, My::Matrix second)
{
	if(first.addTo(second))
		return first;
	return My::Matrix(0, 0);
}

My::Matrix My::Matrix::operator+(My::Matrix second)
{
	return My::Matrix::add(*this, second);
}

bool My::Matrix::addTo(My::Matrix matrix)
{
	if (this->getWidth() != matrix.getWidth())
	{
		std::string err = "the matricies have to have the same widths";
		My::errorMsg((char*)err.data());
		return false;
	}
	if (this->getHeight() != matrix.getHeight())
	{
		std::string err = "the matricies have to have the same heights";
		My::errorMsg((char*)err.data());
		return false;
	}
	for (int j = 0; j < this->getHeight(); j++)
	{
		for (int i = 0; i < this->getWidth(); i++)
		{
			this->setAt((this->getAt(i, j) + matrix.getAt(i, j)), i, j);
		}
	}
	return true;

}

bool My::Matrix::operator+=(My::Matrix matrix)
{
	return this->addTo(matrix);
}


//transposion
My::Matrix My::Matrix::transpose(My::Matrix matrix)
{
	My::Matrix ans(matrix.getHeight(), matrix.getWidth());
	for (int j = 0; j < ans.getHeight(); j++)
	{
		for (int i = 0; i < ans.getWidth(); i++) 
		{
			ans.setAt(matrix.getAt(j, i), i, j);
		}
	}
	return ans;
}

bool My::Matrix::transpose()
{
	*this = My::Matrix::transpose(*this);
	return true;
}

My::Matrix My::Matrix::operator~()
{
	return this->transpose(*this);
}

//multiplication by a scalar
My::Matrix My::Matrix::multiply(My::Matrix matrix, float val)
{

	if(matrix.multiplyBy(val))
		return matrix;
	return My::Matrix(0, 0);
}

My::Matrix My::Matrix::operator*(float val)
{
	return multiply(*this, val);
}

bool My::Matrix::multiplyBy(float val)
{
	for (int j = 0; j < m_height; j++)
	{
		for (int i = 0; i < m_width; i++)
		{
			(*m_values)[i][j] *= val;
		}
	}
	return true;
}

bool My::Matrix::operator*=(float val)
{
	return multiplyBy(val);
}

//multiplication by another matrix
My::Matrix My::Matrix::multiply(My::Matrix first, My::Matrix second)
{
	first *= second;
	return first;
}

My::Matrix My::Matrix::operator*(My::Matrix matrix)
{
	return My::Matrix::multiply(*this, matrix);
}

bool My::Matrix::multiplyBy(My::Matrix matrix)
{
	if (this->getWidth() != matrix.getHeight())
	{
		My::errorMsg((char*)"the width of this matrix has to be the same as the height on the other one");
		return false;
	}
	My::Matrix ans(matrix.getWidth(),this->getHeight());
	const int repeat = this->getWidth();
	for (int k = 0; k < ans.getHeight(); k++)
	{
		for (int j = 0; j < ans.getWidth(); j++)
		{
			float sum=0;
			for (int i = 0; i < repeat; i++)
			{
				sum += this->getAt(i, k) * matrix.getAt(j, i);
			}
			ans.setAt(sum, j, k);
		}
	}
	*this = ans;
	return true;
}

bool My::Matrix::operator*=(My::Matrix matrix)
{
	return multiplyBy(matrix);
}

//determinant
float My::Matrix::det(My::Matrix matrix)
{
	if (matrix.getWidth() != matrix.getHeight())
	{
		My::errorMsg((char*)"the matrix has to be square");
		return 0;
	}

	for (int  j = 0; j < matrix.getWidth(); j++)
	{
		for (int i = j+1; i < matrix.getWidth(); i++)
		{
			float mult = matrix.getAt(i, j) / matrix.getAt(j, j);
			for (int a = j; a < matrix.getHeight(); a++)
			{
				matrix.setAt(matrix.getAt(i, a) - mult * matrix.getAt(j, a),i,a);
			}
		}
	}
	float ans = 1;
	for (int i = 0; i < matrix.getWidth(); i++)
	{
		ans *= matrix.getAt(i, i);
	}
	return ans;
}

float My::Matrix::det()
{
	return this->det(*this);
}

//minors
My::Matrix My::Matrix::minor(My::Matrix& matrix, int x, int y)
{
	const int width = matrix.getWidth();
	const int height = matrix.getHeight();
	if (width != height)
	{
		My::errorMsg((char*)"Minors are only defined for square matrices");
		return matrix;
	}

	My::Matrix ans(width - 1, height - 1);

	char wasY = 0;
	char wasX = 0;
	for (int j = 0; j < height; j++)
	{
		wasX = 0;
		if (j == y)
		{
			wasY = 1;
			continue;
		}
		for (int i = 0; i < width; i++)
		{
			if (i == x)
			{
				wasX = 1;
				continue;
			}
			ans.setAt(matrix.getAt(i, j), i - wasX, j - wasY);
		}
	}
	return ans;


}

My::Matrix My::Matrix::minor(int x, int y)
{
	return My::Matrix::minor(*this, x, y);
}

//Matrix of Minors
My::Matrix My::Matrix::matrixOfMinors(My::Matrix& matrix)
{
	const int width = matrix.getWidth();
	const int height = matrix.getHeight();
	My::Matrix ans(width, height);
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			ans.setAt(My::Matrix::det(minor(matrix, i, j)), i, j);
		}
	}
	return ans;

}

My::Matrix My::Matrix::matrixOfMinors()
{
	return My::Matrix::matrixOfMinors(*this);
}

//matrix of cofactors
My::Matrix My::Matrix::matrixOfCofactor(My::Matrix& matrix)
{
	My::Matrix ans = My::Matrix::matrixOfMinors(matrix);
	for (int j = 0; j < ans.getHeight(); j++)
	{
		for (int i = 0; i < ans.getWidth(); i++)
		{
			if ((j + i) % 2 != 0)
				ans.setAt(-1 * ans.getAt(i, j), i, j);
		}
	}
	return ans;
}

My::Matrix My::Matrix::matrixOfCofactor()
{
	return My::Matrix::matrixOfCofactor(*this);
}

//Adjoint matrix
My::Matrix My::Matrix::adjoint(My::Matrix& matrix)
{
	return My::Matrix::transpose(matrix.matrixOfCofactor());
}

My::Matrix My::Matrix::adjoint()
{
	return My::Matrix::adjoint(*this);
}


