#ifndef PROCQ_H
#define PROCQ_H

#include "rating.h"
using namespace std;
//only thing different are the constructors. basically same as rating, except the
//nomenclature is different. Also, this will ALWAYS use strings
class procedure_quality : public rating {
public:
  procedure_quality(string inProc) : rating(true) {
      general = inProc;
      count = 1;
      if (general == "Worse") {
        overall = 1.0;
      } else if (general == "Average") {
        overall = 2.0;
      } else if (general == "Better"){
        overall = 3.0;
      } else{
        overall = 0.0;
        isValid = false;
      }
      if (overall != 0.0){
        isValid = true;
      }
  }

  //used to initalize empty procedure ratings
  procedure_quality( bool useS ) : rating(useS) {}

  //slightly different than rating, just nomenclature
  void updateRating() {
    //check whether to do something or not.
    if ((!isValid) )
      return;

    if (count == 0){ //in case there were no valid ratings, and to avoid dividing by zero
      count++;
    }

    overall = overall/count;
    count = 1; //reset count -- WILL LOSE AVERAGING WEIGHT!!!

    if (useString){
        if (overall == 0.0)
          general = "None";
        else if (overall <= 1.5)
          general = "Worse";
        else if (overall <= 2.5)
          general = "Average";
        else
          general = "Better";
      }
    }
    /*
    Scale;
      1 - Worse
      2 - Average
      3 - Better
    */

};
#endif
