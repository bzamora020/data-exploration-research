#include "comboShootingData.h"
#include <sstream>
#include <string>

void comboShootingData::addShootingtoRegion(shootingData *CD) {
  countedAge += CD->getCountedAge();

  fleeingCases += CD->getFleeingCases();
  triedFleeing += CD->getTriedFleeing();
  notFleeing += CD->getNotTriedFleeing();

  bodyCamCount += CD->getCountedBodyCam();
  hadBodyCamOff += CD->getHadBodyCamOff();
  hadBodyCamOn += CD->getHadBodyCamOn();

  countedMI += CD->getCountedMI();
  mentalI += CD->getMentalI();
  age += CD->getAge();
  genderCounts += CD->getGenderData();
  raceCounts += CD->getRaceData();
  cases++;
}