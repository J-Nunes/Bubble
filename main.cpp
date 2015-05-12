#include "DynamicArray.h"
#include <random>
#include <time.h>
#include <iostream>

using namespace std;

int main()
{
	srand(time(NULL));

	unsigned int counter;
	DynamicArray<int> a;
	
	for (unsigned int i = 0; i < 10000; i++)
		a.pushBack(rand());

	counter = a.bubble();

	cout << counter;
	getchar();
	return 0;
}