#include "demogData.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <iomanip>
#include "comboDemogData.h"
#include "visitor.h"

//note this stores a running total until averageOut
//just adds the current demog info to the running total
void comboDemogData::addDemog(shared_ptr<demogData> demog) {
	popOver65+=demog->getpopOver65Count();
	popUnder18+=demog->getpopUnder18Count();
	popUnder5+=demog->getpopUnder5Count();
	eduOverBachelor+=demog->getBAupCount();
	eduOverHS+=demog->getHSupCount();
	belowPoverty+=demog->getBelowPovertyCount();
	numCounties++;
	population2014+=demog->getPop();
	ed.add(demog->getED());
}

std::ostream& comboDemogData::print(std::ostream &out) const{
	out << std::setprecision(2) << std::fixed;
	out << "Region Info: "<<this->region;
	out << "\nNumber of Counties: " << this->getNumCounties();
	out << "\nPopulation info:";
	out << "\n(over 65): "<<this->getpopOver65()<<"% and total: "<< this->getpopOver65Count();
	out << "\n(under 18): "<<this->getpopUnder18()<<"% and total: "<<this->getpopUnder18Count();
	out << "\n(under 5): "<<this->getpopUnder5()<<"% and total: "<<this->getpopUnder5Count();
	out << "\nEducation info:";
	out << "\n(Bachelor or more): "<<this->getBAup()<<"% and total: "<<this->getBAupCount();
	out << "\n(high school or more): "<<this->getHSup()<<"% and total: "<<this->getHSupCount();
	out << "\npersons below poverty: "<<this->getBelowPoverty()<<"% and total: "<<this->getBelowPovertyCount();
	out << "\nTotal population: "<<this->getPop();
	return out;
}
/*
std::ostream& operator<<(std::ostream &out, const comboDemogData&SD) {
	out << std::setprecision(2) << std::fixed;
	out << "Region Info: "<<SD.region;
	out << "\nNumber of Counties: " << SD.getNumCounties();
	out << "\nPopulation info:";
	out << "\n(over 65): "<<SD.getProportionOver65()<<"% and total: "<< SD.getpopOver65();
	out << "\n(under 18): "<<SD.getProportionUnder18()<<"% and total: "<<SD.getpopUnder18();
	out << "\n(under 5): "<<SD.getProportionUnder5()<<"% and total: "<<SD.getpopUnder5();
	out << "\nEducation info:";
	out << "\n(Bachelor or more): "<<SD.getProportionBAup()<<"% and total: "<<SD.getBAup();
	out << "\n(high school or more): "<<SD.getProportionHSup()<<"% and total: "<<SD.getHSup();
	out << "\npersons below poverty: "<<SD.getProportionBelowPoverty()<<"% and total: "<<SD.getBelowPoverty();
	out << "\nTotal population: "<<SD.getPop();
	return out;
}
*/
