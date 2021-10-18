#include <iostream>

using namespace std;

int main() {
  string
    name,
    lastName;
    
  cout << "Enter your name: ";
  cin >> name >> lastName;
  
  cout << "Your name is [" << name << ']' << endl;
  cout << "Last name is [" << lastName << ']' << endl;
  
  return 0;
}

