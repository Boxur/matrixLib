#include "Matrix.h"

int main()
{
	int a[16] = {8,4,3,-5,6,-2,7,9,-8};
	My::Matrix first(3,3);
	for (int j = 0; j < first.getHeight(); j++)
	{
		for (int i = 0; i < first.getWidth(); i++)
		{
			first.setAt(a[3*j+i], i, j);
		}
	}
	std::cout <<first.matrixOfCofactor();
	
}
