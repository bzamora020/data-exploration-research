#include "comboShootingData.h"
#include <sstream>
#include <string>

void comboShootingData::addShootingtoRegion(shootingData *CD)
{
  countedAge += CD->getCountedAge();

  armedCounts += CD->getArmedData();

  age += CD->getAge();
  genderCounts += CD->getGenderData();
  raceCounts += CD->getRaceData();
  bodyCamCounts += CD->getBodyCamData();
  fleeingCounts += CD->getFleeingData();
  mentalCounts += CD->getMIData();
  cases++;
}