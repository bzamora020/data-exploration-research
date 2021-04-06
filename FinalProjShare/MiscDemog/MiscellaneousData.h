#ifndef MISCELLANEOUS_DATA_H
#define MISCELLANEOUS_DATA_H

class miscellaneousData {
    public:

        miscellaneousData(double inFemale, double inForeign, double inSameHouse,
                          double inCommute, double inLandArea, double inOtherLang,
                          double inVets, int inBuildingPermits, int inShipments) : popFemale(inFemale), popForeign(inForeign),
                          popSameHouse(inSameHouse), meanCommuting(inCommute), landArea(inLandArea), popOtherLanguage(inOtherLang),
                          popVeterans(inVets), buildingPermits(inBuildingPermits), manufacturerShipments(inShipments) {}
        
        miscellaneousData() : popFemale(0.0), popForeign(0.0), popSameHouse(0.0), meanCommuting(0.0), landArea(0.0), popOtherLanguage(0.0), popVeterans(0.0),
                              buildingPermits(0), manufacturerShipments(0) {};

        miscellaneousData& operator+=(miscellaneousData m){
            popFemale += m.getPopFemaleCount();//should be counts; ie for rest; might use for aggregation
            popForeign += m.getPopForeignCount();
            popSameHouse += m.getPopSameHouseCount();
            meanCommuting += m.getMeanCommute(); 
            landArea += m.getLandArea();
            popOtherLanguage += m.getPopOtherLangCount();
            popVeterans += m.getVeterans();
            buildingPermits += m.getBuildingPerm();
            manufacturerShipments += m.getManufacturerShipments();

            return *this;
        }

        miscellaneousData& operator=(miscellaneousData m){
            popFemale = m.getPopFemaleCount();//should be counts; ie for rest; might use for aggregation
            popForeign = m.getPopForeignCount();
            popSameHouse = m.getPopSameHouseCount();
            meanCommuting = m.getMeanCommute(); 
            landArea = m.getLandArea();
            popOtherLanguage = m.getPopOtherLangCount();
            popVeterans = m.getVeterans();
            buildingPermits = m.getBuildingPerm();
            manufacturerShipments = m.getManufacturerShipments();

            return *this;
        }
        
        double getPopFemaleCount() const { return popFemale; }
        double getPopForeignCount() const { return popForeign; }
        double getPopSameHouseCount() const { return popSameHouse; }
        double getMeanCommute() const { return meanCommuting; }
        double getLandArea() const { return landArea;}
        double getPopOtherLangCount() const { return popOtherLanguage; }
        int getVeterans() const { return popVeterans; }
        int getBuildingPerm() const { return buildingPermits; }
        int getManufacturerShipments() const { return manufacturerShipments; }

    private:
        //counts like other private demog data
        double popFemale;
        double popForeign;
        double popSameHouse;
        double meanCommuting;  //mean travel time to work
        double landArea;
        double popOtherLanguage;
        int popVeterans;
        int buildingPermits;
        int manufacturerShipments;
};

#endif