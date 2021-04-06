#include "tddFuncs.h"
#include <iostream>
#include <math.h>
using std::cout;
using std::endl;

#define epsilon 0.001

void assertEquals(std::string expected, 
		  std::string actual, 
		  std::string message) {
  if (expected==actual) {
    cout << "PASSED: " << message << endl;;
  } else {
    cout << "   FAILED: " << message << endl 
	 << "     Expected: " << expected << " Actual: " << actual << endl; 
  }
}

void assertEquals(int expected, 
		  int actual, 
		  std::string message) {
  if (expected==actual) {
    cout << "PASSED: " << message << endl;;
  } else {
    cout << "   FAILED: " << message << endl 
	 << "     Expected: " << expected << " Actual: " << actual << endl; 
  }
}

void assertEquals(double expected, 
      double actual, 
      std::string message) {
      if (fabs(expected-actual) < epsilon) {
        cout << "PASSED: " << message << endl;;
      } else {
        cout << "   FAILED: " << message << endl 
      << "     Expected: " << expected << " Actual: " << actual << endl; 
  }
}

void assertTrue(bool expression,
		  std::string message) {
  if (expression) {
    cout << "PASSED: " << message << endl;;
  } else {
    cout << "   FAILED: " << message << endl 
	 << "     Expected true, but was false " << endl;
  }
}

