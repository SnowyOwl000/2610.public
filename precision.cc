#include <iostream>
#include <iomanip>

using namespace std;

int main() {
  float
    fPi = 3.141592653589793238462643383279;
  double
    dPi = 3.141592653589793238462643383279;
  long double
    lPi = 3.141592653589793238462643383279L;
  float
    nParticles = 1e90;
    
  cout << setprecision(25);
  
  cout << "float: " << fPi << endl;
  cout << "double: " << dPi << endl;
  cout << "long double: " << lPi << endl;
  
  cout << "Size of double: " << sizeof(double) << endl;
  cout << "Size of long double: " << sizeof(long double) << endl;
  
  cout << "particles: " << nParticles << endl;
  
  return 0;
}

