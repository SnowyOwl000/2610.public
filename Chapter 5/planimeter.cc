#include <iostream>

using namespace std;

int main() {
  int
    xFirst,yFirst,	// first point entered
    xCur,yCur,		// current point
    xPrev,yPrev;	// previous point
  double
    area;
    
  // get first point, save as current point
  
  cout << "Enter first point: ";
  cin >> xFirst >> yFirst;
  
  xCur = xFirst;
  yCur = yFirst;
  
  // loop until we return to first point
  
  while (true) {
    // move current point into previous point
    xPrev = xCur;
    yPrev = yCur;
    
    // get next point
    
    cout << "Enter next point: ";
    cin >> xCur >> yCur;
    
    // process
    
    area += xPrev * yCur - xCur * yPrev;
    
    // stop if current point is first point
    if (xCur == xFirst && yCur == yFirst)
      break;
  }
  
  // divide by 2 and display answer
  
  area /= 2;		// same as area = area / 2
  
  cout << "Area is " << area << endl;
  
  return 0;
}

