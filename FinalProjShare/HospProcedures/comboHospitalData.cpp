
#include "comboHospitalData.h"
#include <sstream>
#include <string>
#include <assert.h>


void comboHospitalData::addHospitaltoRegion(hospitalData* RA) {
  overall += RA->getOverallRate_rat();
  mortality += RA->getMortRate();
  readmission += RA->getReadRate();
  heart_attack_q += RA ->getHeart_attack_q();
  heart_attack_v += RA ->getHeart_attack_v();
  heart_failure_q += RA ->getHeart_failure_q();
  heart_failure_v += RA ->getHeart_attack_v();
  pneumonia_q += RA ->getPneumonia_q();
  count++;
}

std::ostream& operator<<(std::ostream &out, const comboHospitalData& SH) {
//  out << "Combined hopital Data at level: " << SH.getRegion() << endl;
  out << "Number of hospitals: " << SH.getNumH() << endl;
  out << "Overall rating: " << SH.getOverallRate() << endl;
  out << "Mortality rating: " << SH.getMortRate() << endl;
  out << "Readmission rating: " << SH.getReadRate();
  return out;
}
