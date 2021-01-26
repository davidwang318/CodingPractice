/**

// Function-pointer declaration

return-type (* function-ptr-name) (parameter-list)

//Example

double (*fp) (int, int)
double f (int, int)
fp = f; //assign function f to fp function-pointer

**/

#include <iostream>

int arithmetic( int, int, int (*)(int, int) );

int add(int n1, int n2) { return n1 + n2; };
int sub(int n1, int n2) { return n1 - n2; };

int arithmetic( int n1, int n2, int (*operation) (int, int)) {
	return (*operation) (n1, n2);
}

int main() {
	int number1 = 5, number2 = 6;

	std::cout << arithmetic(number1, number2, add) << std::endl;
	std::cout << arithmetic(number1, number2, sub) << std::endl;
}