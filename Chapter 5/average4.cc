#include <iostream>

using namespace std;

int main() {
  int
    sum=0,
    count=0,
    score;
  double
    average;

  while (true) {
    cout << "Enter score (-1 to quit): ";
    cin >> score;    

    if (score == -1)	// if sentinel is entered, stop loop
      break;

    sum += score;	// same as sum = sum + score
    
    count++;		// one more score
  }
  
  average = (double)sum / count;
  
  cout << "Average is " << average << endl;
  
  return 0;
}

