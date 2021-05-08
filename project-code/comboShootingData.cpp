#include "comboShootingData.h"
#include <sstream>
#include <string>

void comboShootingData::addShootingtoRegion(shootingData *CD)
{
  countedAge += CD->getCountedAge();

  fleeingCases += CD->getFleeingCases();
  triedFleeing += CD->getTriedFleeing();
  notFleeing += CD->getNotTriedFleeing();

  bodyCamCount += CD->getCountedBodyCam();
  hadBodyCamOff += CD->getHadBodyCamOff();
  hadBodyCamOn += CD->getHadBodyCamOn();

  // armedCount += CD->getCountedArmed();
  // wasArmed += CD->getWasArmed();
  // notArmed += CD->getNotArmed();
  // armedGun += CD->getArmedWithGun();
  // armedUnknown += CD->getArmedUnknown();

  armedCounts += CD->getArmedData();

  countedMI += CD->getCountedMI();
  mentalI += CD->getMentalI();
  age += CD->getAge();
  genderCounts += CD->getGenderData();
  raceCounts += CD->getRaceData();
  cases++;
}