#include <iostream>

using namespace std;

int main() {
  int
    sum=0,
    count=0,
    score,
    average;
    
  while (score != -1) {
    cout << "Enter score (-1 to quit): ";
    cin >> score;
    
    sum += score;	// same as sum = sum + score
    
    count++;		// one more score
  }
  
  average = sum / count;
  
  cout << "Average is " << average << endl;
  
  return 0;
}

