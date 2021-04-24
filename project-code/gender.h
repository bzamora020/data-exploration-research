#ifndef GENDER_H
#define GENDER_H

#include <iostream>
#include <string>

using namespace std;

class gender {
public:
  gender(string inGender) : strGender(inGender) {
    numMen = 0;
    numWomen = 0;
    countedGender = 0;

    if (inGender.compare("M") == 0) {
      numMen++;
      countedGender++;
    }

    if (inGender.compare("F") == 0) {
      numWomen++;
      countedGender++;
    }
  }

  int getCountedGender() const { return countedGender; }
  int getNumMen() const { return numMen; }
  int getNumWomen() const { return numWomen; }

  string getGender() const { return strGender; }

  gender &operator+=(const gender &g);

private:
  string strGender;
  int countedGender;
  int numMen;
  int numWomen;
};

#endif