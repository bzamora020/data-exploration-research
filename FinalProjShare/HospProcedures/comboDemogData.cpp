#include "comboDemogData.h"
#include "demogData.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <iomanip>


void comboDemogData::addDemogtoRegion(demogData* CD) {
  assert(getRegion().compare(CD->getRegion()) == 0); //might throw error.
  popOver65 += CD->getpopOver65Count();
  popUnder18 += CD->getpopUnder18Count();
  popUnder5 += CD->getpopUnder5Count();
  bachelorDegreeUp += CD->getBAupCount();
  highSchoolUp += CD->getHSupCount() ;
  belowPoverty += CD->getBelowPovertyCount();
  population2014 += CD->getPop();
  numDemog++;
}


/* print county demographic data */
std::ostream& operator<<(std::ostream &out, const comboDemogData &DD) {
  out << "Region Demographics Info: " << DD.getRegion() ;
  out << "\nPopulation info: \n(\% over 65): " << DD.getpopOver65();
  out <<  " Count: " << DD.getpopOver65Count();
  out << "\n(\% under 18): " << DD.getpopUnder18();
  out <<  " Count: " << DD.getpopUnder18Count();
  out << "\n(\% under 5): " << DD.getpopUnder5();
  out <<  " Count: " << DD.getpopUnder5Count();
  out << "\nEducation info: \n(\% Bachelor degree or more): " << DD.getBAup();
  out <<  " Count: " << DD.getBAupCount();
  out << "\n(\% high school or more): " << DD.getHSup();
  out <<  " Count: " << DD.getHSupCount();
  out << "\n\% below poverty: " << DD.getBelowPoverty();
  out <<  " Count: " << DD.getBelowPovertyCount();
  out << "\nTotal population: " << DD.population2014;
  return out;
}
