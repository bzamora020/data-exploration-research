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

  numBlackFleeing += CD->getCountBlackFleeing();
  numNativeFleeing += CD->getCountNativeFleeing();
  numWhiteFleeing += CD->getCountWhiteFleeing();
  numHispanicFleeing += CD->getCountHispanicFleeing();
  numBlackMI += CD->getCountBlackMI();
  numNativeMI += CD->getCountNativeMI();
  numWhiteMI += CD->getCountWhiteMI();
  numHispanicMI += CD->getCountHispanicMI();
  numBlackBodyCamOn += CD->getCountBlackBodyCamOn();
  numNativeBodyCamOn += CD->getCountNativeBodyCamOn();
  numWhiteBodyCamOn += CD->getCountWhiteBodyCamOn();
  numHispanicBodyCamOn += CD->getCountHispanicBodyCamOn();
  numBlackArmed += CD->getCountBlackArmed();
  numNativeArmed += CD->getCountNativeArmed();
  numWhiteArmed += CD->getCountWhiteArmed();
  numHispanicArmed += CD->getCountHispanicArmed();
  
  
  cases++;
}