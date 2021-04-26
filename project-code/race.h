#ifndef RACE_H
#define RACE_H

#include <string>
#include <iostream>

using namespace std;

class race
{
public:
    race(string inRace) : strRace(inRace)
    {
        numAsians = 0;
        numNativeAmer = 0;
        numWhite = 0;
        numAfricanAme = 0;
        numHispanics = 0;
        numOther = 0;
        raceCount = 0;
        if (inRace.compare("A") == 0) // Asian, non-Hispanic
        {
            numAsians++;
            raceCount++;
        }
        if (inRace.compare("B") == 0) // Black, non-Hispanic
        {
            // cout << "oh 0.0" << endl;
            numAfricanAme++;
            raceCount++;
        }
        if (inRace.compare("W") == 0)
        {
            numWhite++;
            raceCount++;
        }
        if (inRace.compare("H") == 0)
        {
            // cout << "oh 0.0" << endl;

            numHispanics++;
            raceCount++;
        }
        if (inRace.compare("N") == 0)
        {
            numNativeAmer++;
            raceCount++;
        }
        if (inRace.compare("O") == 0)
        {
            numOther++;
            raceCount++;
        }
    }
    // GETTERS
    // Total number of counted cases with "known" race
    int getRaceCount() const { return raceCount; }

    // Number of counted cases by race
    int getNumAsians() const { return numAsians; }
    int getNumAfricanAme() const { return numAfricanAme; }
    int getNumWhite() const { return numWhite; }
    int getNumNative() const { return numNativeAmer; }
    int getNumHispanics() const { return numHispanics; }
    int getnumOther() const { return numOther; }
    string getRace() const { return strRace; };

    race &operator+=(const race &r);

private:
    // Total number of counted cases with "known" race
    int raceCount;
    // Total number of counted cases by race
    int numAsians;
    int numAfricanAme;
    int numWhite;
    int numNativeAmer;
    int numHispanics;
    int numOther;
    string strRace;
};

#endif