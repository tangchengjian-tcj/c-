#include <iostream>
using namespace std;
int a()
{
	int sum = 0, value = 0;
	int currVal = 0, val = 0;
	while (std::cin >> value)
		sum += value; 
	std::cout << "Sum is: " << sum << std::endl; 
	if (std::cin >> currVal) {
		int cnt = 1;  
		while (std::cin >> val) { 
			if (val == currVal) 
				++cnt;  
			else {  
				std::cout << currVal << " occurs " << cnt << " times" << std::endl;
				currVal = val;
				cnt = 1;  
				break;
			}
		}// while 循环在这里结束 
		//记住打印文件中最后一个值的个数 
		std::cout << currVal << " occurs " << cnt << " times" << std::endl;
	}//最外层的 if 语句在这里结束 
	return 0;
}