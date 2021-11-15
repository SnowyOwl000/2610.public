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
    cout << "Enter score (^D to quit): ";
    cin >> score;    

    if (!cin)	// this is true if user presses ^D
      break;

    sum += score;	// same as sum = sum + score
    
    count++;		// one more score
  }
  
  average = (double)sum / count;
  
  cout << "Average is " << average << endl;
  
  return 0;
}

