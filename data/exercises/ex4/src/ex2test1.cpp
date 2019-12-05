#include <iostream>
#include "myadd.h"
#include "mymul.h"

#include "mpi.h"

using namespace std;

int main()
{
	cout << "CMake Example 2:" << endl;

    int a = 5;
    int b = 2;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    cout << "Addition       = " << myadd(a,b) << endl; 
    cout << "Multiplication = " << mymul(a,b) << endl; 

    return 0;
}
