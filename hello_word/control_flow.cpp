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
		}// while ѭ����������� 
		//��ס��ӡ�ļ������һ��ֵ�ĸ��� 
		std::cout << currVal << " occurs " << cnt << " times" << std::endl;
	}//������ if ������������ 
	return 0;
}