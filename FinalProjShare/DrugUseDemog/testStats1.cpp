#include "stats.h"
#include "parse.h"
#include <iostream>
#include "tddFuncs.h"
using namespace std;

int main() {


  cout << "Testing stats" << endl;

  vector<double> x = vector<double>{43.0, 21, 25, 42, 57, 59}; 
  vector<double> y = vector<double>{99.0, 65, 79, 75, 87, 81}; 

  double meanX =  stats::computeMean(x); 
  double stdDevX = stats::computeStdDevSample(x);  
  double meanY =  stats::computeMean(y); 
  double stdDevY = stats::computeStdDevSample(y); 

  ASSERT_EQUALS(meanX, 41.167);
  //TODO fill in!!!
  ASSERT_EQUALS(stdDevX, 15.753);
  ASSERT_EQUALS(meanY, 81.0);
  ASSERT_EQUALS(stdDevY, 11.454);

  return 0;
}
