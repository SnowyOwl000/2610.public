#include <iostream>

using namespace std;

int main() {
  int
    val = 2147483647,
    f = 1;
    
  cout << val << endl;
  
  val++;	// add 1 to val
  
  cout << val << endl;
  
  for (int i=1;i<=40;i++) {
    f *= i;	// multiply f * i, result goes back into f
    cout << i << '\t' << f << endl;
  }
  
  return 0;
}

