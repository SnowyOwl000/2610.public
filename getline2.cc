#include <iostream>

using namespace std;

int main() {
  string
    name;
  int
    number;

  cout << "Enter jersey number: ";
  cin >> number;
      
  cout << "Enter name: ";
  getline(cin,name);
  
  cout << "Name [" << name << ']' << endl;
  cout << "Number: " << number << endl;
  
  return 0;
}

