#include "comboDemogData.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <iomanip>


void comboDemogData::addDemogtoRegion(shared_ptr<demogData> CD) {
	setpopOver65Count((double)getpopOver65Count() + CD->getpopOver65Count());
	setpopUnder18Count((double)getpopUnder18Count() + CD->getpopUnder18Count());
	setpopUnder5Count((double)getpopUnder5Count() + CD->getpopUnder5Count());
	setBAupCount((double)getBAupCount() + CD->getBAupCount());
	setHSupCount((double)getHSupCount() + CD->getHSupCount());
	setBelowPovertyCount((double)getBelowPovertyCount() + CD->getBelowPovertyCount());
	setPop((double)getPop() + CD->getPop());
	counties.push_back(CD);
}