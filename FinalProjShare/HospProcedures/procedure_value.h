#ifndef PROCV_H
#define PROCV_H

#include "rating.h"
using namespace std;
//only thing different are the constructors. basically same as rating, except the
//nomenclature is different. Also, this will ALWAYS use strings
class procedure_value : public rating {
public:
  procedure_value(string inProc) : rating(true) {
      general = inProc;
      count = 1;
      if (general == "Lower") {
        overall = 1.0;
      } else if (general == "Average") {
        overall = 2.0;
      } else if (general == "Higher"){
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
  procedure_value( bool useS ) : rating(useS) {}

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
          general = "Lower";
        else if (overall <= 2.5)
          general = "Average";
        else
          general = "Higher";
      }
    }
    /*
    Scale;
      1 - Lower
      2 - Average
      3 - Higher
    */

};
#endif
