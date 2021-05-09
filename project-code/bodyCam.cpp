#include "bodyCam.h"

bodyCam &bodyCam::operator+=(const bodyCam &b)
{
    bodyCamCount += b.bodyCamCount;
    hadBodyCamOff += b.hadBodyCamOff;
    hadBodyCamOn += b.hadBodyCamOn;
    return *(this);
    
};
