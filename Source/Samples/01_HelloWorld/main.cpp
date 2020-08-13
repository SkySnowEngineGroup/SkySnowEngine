#include <stdlib.h>
#include <iostream>
#include "TestAddFile.h"
int main()
{
	printf("Hello World!\n");

	TestAddFile* td = new TestAddFile();

	delete td;
	system("pause");
	return 0;
}