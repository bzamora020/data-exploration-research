#ifndef SHOOTINGDATA_H
#define SHOOTINGDATA_H

#include "placeData.h"
#include "race.h"
#include "gender.h"
#include "armed.h"
#include "bodyCam.h"

using namespace std;

class shootingData : public placeData
{
public:
    shootingData(string inS, int inAge, string inRace, string inGender, string inMI, string inFleeing, string inBodyCam, string inArmed) : placeData{inS, 7}, raceCounts(inRace), genderCounts(inGender), numberOfCases(1), age(inAge), armedCounts(inArmed), bodyCamCounts(inBodyCam)
    {
        countedMI = 0;
        countedAge = 0;
        mentalI = 0;
        fleeingCases = 0;
        triedFleeing = 0;
        notFleeing = 0;

        if ((inFleeing.compare("Foot") == 0) || (inFleeing.compare("Car") == 0) || (inFleeing.compare("Other") == 0))
        {
            triedFleeing++;
            fleeingCases++;
        }
        else
        {
            fleeingCases++;
            notFleeing++;
        }

        if (inMI.compare("True") == 0)
        {
            mentalI++;
            countedMI++;
        }
        else
        {
            countedMI++;
        }

        if (inAge > 0)
        {
            age = inAge;
            countedAge++;
        }
    }

    shootingData(string inS) : placeData{inS, 7}, raceCounts(""), genderCounts(""), armedCounts(""), bodyCamCounts("")
    {
        countedAge = 0;
        mentalI = 0;
        age = 0;
        fleeingCases = 0;
        triedFleeing = 0;
        countedMI = 0;
    }

    // These return percentage of police shootings by race

    // Adding base case if no cases at all then return = 0
    double getPerAsians() const
    {
        if (raceCounts.getRaceCount() == 0)
        {
            return 0;
        }
        else
            return (100.0f * (double)(raceCounts.getNumAsians()) / raceCounts.getRaceCount());
    }

    double getPerAfricanAme() const
    {
        if (raceCounts.getRaceCount() == 0)
        {
            return 0;
        }
        return (100.0f * (double)(raceCounts.getNumAfricanAme()) / raceCounts.getRaceCount());
    }

    double getPerWhite() const
    {
        if (raceCounts.getRaceCount() == 0)
        {
            return 0;
        }
        return (100.0f * (double)(raceCounts.getNumWhite()) / raceCounts.getRaceCount());
    }

    double getPerNativeAme() const
    {
        if (raceCounts.getRaceCount() == 0)
        {
            return 0;
        }
        return (100.0f * (double)(raceCounts.getNumNative()) / raceCounts.getRaceCount());
    }

    double getPerHispanics() const
    {
        if (raceCounts.getRaceCount() == 0)
        {
            return 0;
        }
        return (100.0f * (double)(raceCounts.getNumHispanics()) / raceCounts.getRaceCount());
    }

    double getPerOther() const
    {
        if (raceCounts.getRaceCount() == 0)
        {
            return 0;
        }
        return (100.0f * (double)(raceCounts.getnumOther()) / raceCounts.getRaceCount());
    }

    //Getters in percentage for gender
    double getPerWomen() const
    {
        if (genderCounts.getCountedGender() == 0)
        {
            return 0;
        }
        return (100.0f * (double)(genderCounts.getNumMen()) / genderCounts.getCountedGender());
    }
    double getPerMen() const
    {
        if (genderCounts.getCountedGender() == 0)
        {
            return 0;
        }
        return (100.0f * (double)(genderCounts.getNumMen()) / genderCounts.getCountedGender());
    }

    //Getter for percentage of mentall illness reported
    double getPerMentalI() const
    {
        if (countedMI == 0)
        {
            return 0;
        }
        return (100.0f * (double)(mentalI) / countedMI);
    }

    //Getter in case the individual tried fleeing
    double getPerFleeing() const
    {
        if (fleeingCases == 0)
        {
            return 0;
        }
        return (100.0f * (double)(triedFleeing) / fleeingCases);
    }

    double getPerNotFleeing() const
    {
        if (fleeingCases == 0)
        {
            return 0;
        }
        return (100.0f * (double)(notFleeing) / fleeingCases);
    }

    //Getters for body cams

    double getPerBodyCamOn() const
    {
        if (bodyCamCounts.getBodyCamCount() == 0)
        {
            return 0;
        }
        return (100.0f * (double)(bodyCamCounts.getBodyCamOn()) / bodyCamCounts.getBodyCamCount());
    }

    double getPerBodyCamOff() const
    {
        if (bodyCamCounts.getBodyCamCount() == 0)
        {
            return 0;
        }
        return (100.0f * (double)(bodyCamCounts.getBodyCamOff()) / bodyCamCounts.getBodyCamCount());
    }

    //Getters for armed counts

    double getPerArmedUnknown() const
    {

        return (100.0f * (double)(numberOfCases - armedCounts.getWasArmed()) / armedCounts.getArmedCount());
    }
    double getPerArmed() const
    {
        if (armedCounts.getWasArmed() == 0)
        {
            return 0;
        }
        return (100.0f * (double)(armedCounts.getWasArmed()) / armedCounts.getArmedCount());
    }
    double getPerArmedGun() const
    {
        if (armedCounts.getArmedGun() == 0)
        {
            return 0;
        }
        return (100.0f * (double)(armedCounts.getArmedGun()) / armedCounts.getArmedCount());
    }

    // Getter to obtain the average age
    double getAverageAge() const
    {
        if (countedAge == 0)
        {
            return 0;
        }
        else
            return ((age) / countedAge);
    }

    //counters getters
    int getCountedAge() { return countedAge; }
    int getFleeingCases() { return fleeingCases; }
    int getCountedMI() { return countedMI; }

    int getMentalI() { return mentalI; }
    int getTriedFleeing() { return triedFleeing; }
    int getNotTriedFleeing() { return notFleeing; }

    int getAge() { return age; }
    armed getArmedData() { return armedCounts; }
    race getRaceData() { return raceCounts; }
    gender getGenderData() { return genderCounts; }
    bodyCam getBodyCamData() { return bodyCamCounts; }

    int getNumberOfCases() { return numberOfCases; }

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
    int notFleeing;

    int age;
    int numberOfCases;
    bodyCam bodyCamCounts;
    armed armedCounts;
    race raceCounts;
    gender genderCounts;
};

#endif