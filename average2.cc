#include <iostream>

using namespace std;

int main() {
  int
    sum=0,
    count=0,
    score,
    average;

  // loop priming
  
  cout << "Enter score (-1 to quit): ";
  cin >> score;    
    
  while (score != -1) {
    sum += score;	// same as sum = sum + score
    
    count++;		// one more score

    cout << "Enter score (-1 to quit): ";
    cin >> score;    
  }
  
  average = sum / count;
  
  cout << "Average is " << average << endl;
  
  return 0;
}

