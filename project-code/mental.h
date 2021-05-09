#ifndef MENTAL_H
#define MENTAL_H


#include <string>
class mental
{

public:
    mental(std::string inMI)
    {
        countedMI = 0;
        mentalI = 0;

        if (inMI.compare("True") == 0)
        {
            mentalI++;
            countedMI++;
        }
        else
        {
            countedMI++;
        }
    }

    int getCountedMI() const { return countedMI; }
    int getMentalI() const { return mentalI; }

    mental &operator+=(const mental &m);

private:
    int mentalI;
    int countedMI;
};

#endif