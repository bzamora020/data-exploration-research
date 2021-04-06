#ifndef COMBOSHOOTING_H
#define COMBOSHOOTING_H

#include <memory>
#include <string>
#include <iostream>
#include "shootingData.h"
#include "placeData.h"

class comboShootingData : public shootingData
{
public:
    comboShootingData(string inRegtype, string inS) : shootingData(inS), region(inRegtype), cases(0) {}

    void addShootingtoRegion(shootingData *inD);

    int getNumCases() { return cases; }
    string getRegionType() { return region; }

private:
    string region;
    int cases;
};

#endif