#pragma once
#include <iostream>

namespace My
{
	inline void errorMsg(char *msg)
	{
		printf("\033[0;31m");
		printf("%s", msg);
		printf("\033[0m");
	}

}