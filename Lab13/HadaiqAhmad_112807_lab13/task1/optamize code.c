#include <iostream>
//#include <math.h>  strength reduction
using namespace std;
int main() {

	int x;
	//int x = 3;  constant propagation

	//int y = 3 + 3; constant folding

	int y = 6;

	//int z = pow(y, 2); strength reduction

	int z = y*y;

	//int a = pow(y, 2);  strength reduction

	//z = y; subexpression elimination

	cout << "Result is " << z << endl;

	//int a = b + z; dead code

	return 0;

}