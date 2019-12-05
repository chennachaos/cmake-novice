#include <iostream>
#include "myadd.h"
#include "mymul.h"

using namespace std;

int main()
{
	cout << "CMake Example 2:" << endl;

    int a = 5;
    int b = 2;
    int c = 10;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;

    cout << "Addition       = " << myadd(a,myadd(b,c)) << endl; 
    cout << "Multiplication = " << mymul(a,mymul(b,c)) << endl; 

    return 0;
}