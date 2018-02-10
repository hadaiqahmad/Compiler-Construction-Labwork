/* Test Type Casting (TestTypeCast.cpp) */
#include <iostream>
#include <iomanip>
using namespace std;
 
int main() {
   // Print floating-point number in fixed format with 1 decimal place
   cout << fixed << setprecision(1);
 
   // Test explicit type casting
   int i1 = 4, i2 = 8;
   cout << i1 / i2 << endl;           // 0
   cout << (double)i1 / i2 << endl;   // 0.5
   cout << i1 / (double)i2 << endl;   // 0.5
   cout << (double)(i1 / i2) << endl; // 0.0
 
   double d1 = 5.5, d2 = 6.6;
   cout << (int)d1 / i2 << endl;      // 0
   cout << (int)(d1 / i2) << endl;    // 0
 
   // Test implict type casting
   d1 = i1;             // int implicitly casts to double
   cout << d1 << endl;  // 4.0
   i2 = d2;             // double truncates to int! (Warning?)
   cout << i2 << endl;  // 6
}