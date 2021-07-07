#include <iostream>
using namespace std;
#include "swap.h"
/*
	1.创建一个.h后缀名的头文件
	2.创建一个.cpp后缀名的源文件
	3.再头文件中写函数的声明
	4.再源文件中写函数的定义
	
*/

int main() {
	int a = 10;
	int b = 20;
	swap(a, b);
}