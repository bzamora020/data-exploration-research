#ifndef BODYCAM_H
#define BODYCAM_H

#include <string>

using namespace std;

class bodyCam
{
public:
    bodyCam(string inBodyCam)
    {
        bodyCamCount = 0;
        hadBodyCamOn = 0;
        hadBodyCamOff = 0;

        if (inBodyCam.compare("True") == 0)
        {

            hadBodyCamOn++;
            bodyCamCount++;
        }
        if (inBodyCam.compare("False") == 0)
        {

            hadBodyCamOff++;
            bodyCamCount++;
        }
    }

    int getBodyCamCount() const { return bodyCamCount; }
    int getBodyCamOff() const { return hadBodyCamOff; }
    int getBodyCamOn() const { return hadBodyCamOn; }

    bodyCam &operator+=(const bodyCam &b);

private:
    int bodyCamCount;
    int hadBodyCamOn;
    int hadBodyCamOff;
};

#endif