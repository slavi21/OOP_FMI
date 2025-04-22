#include <iostream>

int main()
{
	int a = 3, b = 7;
	int* ptrA = &a;
	int* ptrB = &b;

    std::cout<< ptrA << " "<< &a << std::endl;
    std::cout<< ptrB << " "<< &b << std::endl;

	std::cout << a << " " << b << std::endl;
	std::cout << *ptrA << " " << *ptrB << std::endl;

	int x = *ptrA;
	*ptrA = *ptrB;
	*ptrB = x;

	std::cout << *ptrA << " " << ptrB << std::endl;
	std::cout << a << " " << b << std::endl;
}