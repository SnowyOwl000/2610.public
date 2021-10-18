#include <iostream>

using namespace std;

int main() {
  string
    name;
  int
    number;

  cout << "Enter jersey number: ";
  cin >> number;
  
  // add this line in between >> input and getline input
  // ignore next 8 characters or until \n reached
  // whichever comes first
  cin.ignore(8,'\n');
      
  cout << "Enter name: ";
  getline(cin,name);
  
  cout << "Name [" << name << ']' << endl;
  cout << "Number: " << number << endl;
  
  return 0;
}

