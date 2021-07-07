#include "swap.h"
void swap(int a, int b) {
	int temp = b;
	b = a;
	a = temp;
	std::cout << "a is " << a << "b is" << b << std::endl;
}