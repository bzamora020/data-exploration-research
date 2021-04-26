#ifndef CITYSHOOTING_H
#define CITYSHOOTING_H

#include "shootingData.h"

#include <string>
#include <iostream>

using namespace std;

class cityShootingData : public shootingData
{
public:
    cityShootingData(string inState, string inCity, int inAge, string inRace, string inGender, string inMI, string inFleeing) : shootingData{inState, inAge, inRace, inGender, inMI, inFleeing}, cityName(inCity), hadMentalIllness(inMI)
    {
    }

    string getCity() { return cityName; }
    string getFleeingFactor() { return fleeing; }
    string getMentalIllnessFactor() { return hadMentalIllness; }

private:
    string cityName;
    string fleeing;
    string hadMentalIllness;
};

#endif