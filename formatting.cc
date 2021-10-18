#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
  int
    val = 12345;

  // output using just enough space    
  cout << '[' << val << ']' << endl;
  // output with extra space... data is right-justified
  cout << '[' << setw(8) << val << ']' << endl;
  // setw only works with the next item, not all that follow
  cout << '[' << val << ']' << endl;
  
  // text also works this way
  cout << '[' << setw(8) << "hello" << ']' << endl;
  // use left to left-justify
  cout << '[' << setw(8) << left << "hello" << ']' << endl;
  // left affects everything after it
  cout << '[' << setw(8) << val << ']' << endl;

  // show pi to 6 significant digits
  cout << M_PI << endl;
  // show it to 10 sig figs
  cout << setprecision(10) << M_PI << endl;
  // setprecision affects everything after it
  cout << M_E << endl;
  // output to 25 sig figs
  cout << setprecision(25) << 10*M_PI << endl;
  // setprecision only affects floating point
  cout << val << endl;
  
  // fixed now counts decimal places
  cout << fixed << setprecision(8) << M_PI << endl;
  // fixed can have some unintended consequences...
  cout << 6.022e23 << endl;
  cout << -6.67e-11 << endl;

  return 0;
}

