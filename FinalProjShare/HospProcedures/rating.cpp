#include "rating.h"

/*
A class to represent a rating system that uses both words and numbers
(see CORGIS hospital data for an example)
Rating.Overall  Integer     Overall rating between 1 and 5 stars, with 5 stars being the highest rating; -1 represents no rating.
Rating.Mortality    String  Above, Same, Below, or Unknown comparison to national hospital mortality
Rating.Safety   String  Above, Same, Below, or Unknown comparison to national hospital safety
*/

void rating::updateRating(){
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
      general = "Below";
    else if (overall <= 2.5)
      general = "Same";
    else
      general = "Above";
  }

}
