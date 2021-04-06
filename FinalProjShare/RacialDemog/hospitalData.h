#ifndef HOSP_H
#define HOSP_H

#include <string>
#include <iostream>
#include <utility>
#include <memory>
#include "rating.h"

using namespace std;

/*
  class to represent hospital data
  from CORGIS
*/
#include <iostream>
#include "rating.h"
#include "placeData.h"

using namespace std;

class hospitalData: public placeData, public enable_shared_from_this<hospitalData> {
  public:
	 //constructor for starting code - make complete by adding rating
    hospitalData(string name, string county, string region, int oRate, rating mort, rating re) :
            placeData(name, county, region), overallRate(oRate), mortality(mort), readmit(re) {
    }
    hospitalData(string name, string county, string region): placeData(name, county, region){}
    double getOverallRate() const { return double(overallRate);}
    rating getMortality() const { return mortality;}
    rating getReadmit() const { return readmit;}

    void accept(class Visitor &v) override;
    friend std::ostream& operator<<(std::ostream &out, const hospitalData &HD);

protected:
    rating mortality{};
    rating readmit{};
    int overallRate = 0;
    // int overallRate = 0;
};

#endif
