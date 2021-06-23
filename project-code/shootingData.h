#ifndef SHOOTINGDATA_H
#define SHOOTINGDATA_H

#include "placeData.h"
#include "race.h"
#include "gender.h"
#include "armed.h"
#include "bodyCam.h"
#include "fleeing.h"
#include "mental.h"

using namespace std;

class shootingData : public placeData
{
public:
    shootingData(string inS, int inAge, string inRace, string inGender, string inMI, string inFleeing, string inBodyCam, string inArmed) : placeData{inS, 7}, raceCounts(inRace), genderCounts(inGender), numberOfCases(1), age(inAge), armedCounts(inArmed), bodyCamCounts(inBodyCam), fleeingCounts(inFleeing), mentalCounts(inMI)
    {
        countedAge = 0;
        numBlackFleeing = 0;
        numBlackMI = 0;
        numBlackBodyCamOn = 0;
        numNativeFleeing = 0;
        numNativeMI = 0;
        numNativeBodyCamOn = 0;
        numBlackArmed = 0;
        numNativeArmed = 0;

        if (inAge > 0)
        {
            age = inAge;
            countedAge++;
        }
        if((inRace.compare("B") == 0)){
            if((inFleeing.compare("Foot") == 0) || (inFleeing.compare("Car") == 0) || (inFleeing.compare("Other") == 0)){
                numBlackFleeing++;
            }
            if(inMI.compare("True") == 0){
                numBlackMI++;
            }
            if(inBodyCam.compare("True") == 0){
                numBlackBodyCamOn++;
            }
            if((inArmed.compare("") != 0) && (inArmed.compare("undetermined") != 0) && (inArmed.compare("unarmed") != 0)){
                numBlackArmed++;
            }

        }
        if((inRace.compare("N") == 0)){
            if((inFleeing.compare("Foot") == 0) || (inFleeing.compare("Car") == 0) || (inFleeing.compare("Other") == 0)){
                numNativeFleeing++;
            }
            if(inMI.compare("True") == 0){
                numNativeMI++;
            }
            if(inBodyCam.compare("True") == 0){
                numNativeBodyCamOn++;
            }
            if((inArmed.compare("") != 0) && (inArmed.compare("undetermined") != 0) && (inArmed.compare("unarmed") != 0)){
                numNativeArmed++;
            }
        }
    }

    shootingData(string inS) : placeData{inS, 7}, raceCounts(""), genderCounts(""), armedCounts(""), bodyCamCounts(""), fleeingCounts(""), mentalCounts("")
    {
        countedAge = 0;
        age = 0;
    }
    // Race specific counts of different tags for police shootings
    int getCountBlackFleeing() const
    {
        return numBlackFleeing;
    }
    int getCountBlackMI() const
    {
        return numBlackMI;
    }
    int getCountBlackBodyCamOn() const
    {
        return numBlackBodyCamOn;
    }
    int getCountBlackArmed() const
    {
        return numBlackArmed;
    }
    int getCountNativeFleeing() const
    {
        return numNativeFleeing;
    }
    int getCountNativeMI() const
    {
        return numNativeMI;
    }
    int getCountNativeBodyCamOn() const
    {
        return numNativeBodyCamOn;
    }
    int getCountNativeArmed() const
    {
        return numNativeArmed;
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
        if (mentalCounts.getCountedMI() == 0)
        {
            return 0;
        }
        return (100.0f * (double)(mentalCounts.getMentalI()) / mentalCounts.getCountedMI());
    }

    //Getter in case the individual tried fleeing
    double getPerFleeing() const
    {
        if (fleeingCounts.getFleeingCases() == 0)
        {
            return 0;
        }
        return (100.0f * (double)(fleeingCounts.getNotTriedFleeing()) / fleeingCounts.getFleeingCases());
    }

    double getPerNotFleeing() const
    {
        if (fleeingCounts.getFleeingCases() == 0)
        {
            return 0;
        }
        return (100.0f * (double)(fleeingCounts.getNotTriedFleeing()) / fleeingCounts.getFleeingCases());
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
    int getAge() { return age; }
    armed getArmedData() { return armedCounts; }
    race getRaceData() { return raceCounts; }
    gender getGenderData() { return genderCounts; }
    bodyCam getBodyCamData() { return bodyCamCounts; }
    fleeing getFleeingData() { return fleeingCounts; }
    mental getMIData() { return mentalCounts; }

    int getNumberOfCases() { return numberOfCases; }

    string getState() { return this->getName(); }

    void accept(class Visitor &v) override;

protected:
    // Counted cases per category
    int countedAge;

    // Numbers per categories

    int age;
    int numberOfCases;

    int numBlackFleeing;
    int numNativeFleeing;
    int numBlackMI;
    int numNativeMI;
    int numBlackBodyCamOn;
    int numNativeBodyCamOn;
    int numBlackArmed;
    int numNativeArmed;

    mental mentalCounts;
    fleeing fleeingCounts;
    bodyCam bodyCamCounts;
    armed armedCounts;
    race raceCounts;
    gender genderCounts;
};

#endif