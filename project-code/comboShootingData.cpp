#include "comboShootingData.h"
#include <sstream>
#include <string>

void comboShootingData::addShootingtoRegion(shootingData *CD)
{
    countedAge += CD->getCountedAge();
    fleeingCases += CD->getFleeingCases();
    countedMI += CD->getCountedMI();
    mentalI += CD->getMentalI();
    triedFleeing += CD->getTriedFleeing();
    age += CD->getAge();
    genderCounts += CD->getGenderData();
    raceCounts += CD->getRaceData();
    cases++;
}