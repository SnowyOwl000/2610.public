#include <iostream>

using namespace std;

int main() {
  string
    first,last;
    
  cout << "Enter first name: ";
  getline(cin,first);
  
  cout << "Enter last name: ";
  getline(cin,last);
  
  cout << "First name [" << first << ']' << endl;
  cout << "Last name [" << last << ']' << endl;
  
  return 0;
}

