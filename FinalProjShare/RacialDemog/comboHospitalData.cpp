#include "comboHospitalData.h"
#include <sstream>

using namespace std;


std::ostream& operator<<(std::ostream &out, comboHospitalData &CH){
    out << "Combined hospital data at level: ";
    out << CH.getRegion()<< " in " << CH.getState() << endl;
    out << "includes num hospitals: "<< CH.getNumH() << endl;
    out <<  "Overall rating (out of 5): " << CH.getOverallRate() << endl;
    out <<  "mortality rating: " << CH.getMortality() << endl;
    out <<  "readmit rating: " << CH.getReadmit() << endl;
    return out;
}