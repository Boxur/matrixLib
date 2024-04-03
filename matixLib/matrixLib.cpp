#include "Matrix.h"

int main()
{
	int a[16] = {3,4,6,8};
	My::Matrix first(2,2);
	for (int j = 0; j < first.getHeight(); j++)
	{
		for (int i = 0; i < first.getWidth(); i++)
		{
			first.setAt(a[2*j+i], i, j);
		}
	}
	std::cout << first.det();
	
}
