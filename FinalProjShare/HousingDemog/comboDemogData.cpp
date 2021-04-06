#include "comboDemogData.h"
#include "demogData.h"
#include <sstream>
#include <string>
#include <cassert>
#include <iomanip>

 //note this stores a running total until averageOut 
//just adds the current region info to the running total
void comboDemogData::addDemogtoRegion(demogData *CD) {
	popOver65 += CD->getpopOver65Count();
	popUnder18 += CD->getpopUnder18Count();
	popUnder5 += CD->getpopUnder5Count();
	bachelorDegreeUp += CD->getBAupCount();
	highSchoolUp += CD->getHSupCount() ;
    belowPoverty += CD->getBelowPovertyCount();
	population2014 += CD->getPop();
	numCounties++;
}

std::ostream& operator<<(std::ostream &out, const comboDemogData &SD) {
	out << SD.regionType << " Info: " << SD.region;
    out << "\nNumber of Counties: " << SD.numCounties;
    out << std::setprecision(2) << std::fixed;
    out << "\nPopulation info: \n(over 65): " << SD.getpopOver65() << "\% and total: ";
    out << SD.getpopOver65Count();
    out << "\n(under 18): " << SD.getpopUnder18() << "\% and total: ";
    out << SD.getpopUnder18Count();
    out << "\n(under 5): " << SD.getpopUnder5() << "\% and total: ";
    out << SD.getpopUnder5Count();
    out << "\nEducation info: \n(Bachelor or more): " << SD.getBAup() << "\% and total: ";
    out << SD.getBAupCount() ;
    out << "\n(high school or more): " << SD.getHSup() << "\% and total: ";
    out << SD.getHSupCount();
    out << "\npersons below poverty: " << SD.getBelowPoverty() << "\% and total: ";
    out << SD.getBelowPovertyCount();
    out << "\nTotal population: " << SD.population2014;
    return out;
}
