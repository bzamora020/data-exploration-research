#ifndef SHOOTINGDATA_H
#define SHOOTINGDATA_H

#include "placeData.h"
#include "race.h"
#include "gender.h"

using namespace std;

class shootingData : public placeData
{
public:
    shootingData(string inS, int inAge, string inRace, string inGender, string inMI, string inFleeing) : placeData{inS, 7}, raceCounts(inRace), genderCounts(inGender)
    {
        age = 0;
        countedMI = 0;
        countedAge = 0;
        mentalI = 0;
        fleeingCases = 0;
        triedFleeing = 0;


        if (inFleeing.compare("Not fleeing") == 0)
        {
            fleeingCases++;
        }

        if (inFleeing.compare("unknown") != 0 && inFleeing.compare("Not fleeing") != 0)
        {
            triedFleeing++;
            fleeingCases++;
        }


        if (inMI.compare("True") == 0)
        {
            mentalI++;
            countedMI++;
        }
        if (inMI.compare("False") == 0)
        {
            countedMI++;
        }

        if (inAge > 0)
        {
            age = inAge;
            countedAge++;
        }
    }

    shootingData(string inS) : placeData{inS, 7}, raceCounts(""), genderCounts("")
    {
        countedAge = 0;
        mentalI = 0;
        age = 0;
        fleeingCases = 0;
        triedFleeing = 0;
        countedMI = 0;
    }

    // These return percentage of police shootings by race

    double getPerAsians() const { return 100.0f * (double)(raceCounts.getNumAsians()) / raceCounts.getRaceCount(); }
    double getPerAfricanAme() const { return 100.0f * (double)(raceCounts.getNumAfricanAme()) / raceCounts.getRaceCount(); }
    double getPerWhite() const { return 100.0f * (double)(raceCounts.getNumWhite()) / raceCounts.getRaceCount(); }
    double getPerNativeAme() const { return 100.0f * (double)(raceCounts.getNumNative()) / raceCounts.getRaceCount(); }
    double getPerHispanics() const { return 100.0f * (double)(raceCounts.getNumHispanics()) / raceCounts.getRaceCount(); }
    double getPerOther() const { return 100.0f * (double)(raceCounts.getnumOther()) / raceCounts.getRaceCount(); }

    //Getters in percentage for gender
    double getPerWomen() const { return 100.0f * (double)(genderCounts.getNumWomen()) / genderCounts.getCountedGender(); }
    double getPerMen() const { return 100.0f * (double)(genderCounts.getNumMen()) / genderCounts.getCountedGender(); }

    //Getter for percentage of mentall illness reported
    double getPerMI() const { return 100.0f * (double)(mentalI) / countedMI; }

    //Getter in case the individual tried fleeing
    double getPerFleeing() const { return 100.0f * (double)(triedFleeing) / fleeingCases; }

    // Getter to obtain the average age
    double getAverageAge() const { return (age) / countedAge; }

    //counters getters
    int getCountedAge() { return countedAge; }
    int getFleeingCases() { return fleeingCases; }
    int getCountedMI() { return countedMI; }

    int getMentalI() { return mentalI; }
    int getTriedFleeing() { return triedFleeing; }
    int getAge() { return age; }
    race getRaceData() { return raceCounts; }
    gender getGenderData() { return genderCounts;}

    string getState() { return this->getName(); }

    void accept(class Visitor &v) override;

protected:
    // Counted cases per category
    int countedAge;
    int fleeingCases;
    int countedMI;

    // Numbers per categories
    int mentalI;
    int triedFleeing;
    int age;
    race raceCounts;
    gender genderCounts;

};

#endif