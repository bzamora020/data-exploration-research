#ifndef GENDER_H
#define GENDER_H

#include <string>
#include <iostream>

using namespace std;

class gender
{
public:
    gender(string inGender) : strGender(inGender)
    {
        numMen = 0;
        numWomen = 0;
        countedGender = 0;

        if (inGender.compare("Male") == 0)
        {
            numMen++;
            countedGender++;
        }

        if (inGender.compare("Female") == 0)
        {
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