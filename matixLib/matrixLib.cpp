#include "Matrix.h"

int main()
{
	int a[16] = {1,-1,2,4,0,1,0,3,5,7,-2,0,2,0,-1,4};
	My::Matrix first(4,4);
	for (int j = 0; j < first.getHeight(); j++)
	{
		for (int i = 0; i < first.getWidth(); i++)
		{
			first.setAt(a[4*j+i], i, j);
		}
	}
	printf("%.2f",first.det());
	
}
