#include "rating.h"

/* 
A class to represent a rating system that uses both words and numbers
(see CORGIS hospital data for an example)
Rating.Overall  Integer     Overall rating between 1 and 5 stars, with 5 stars being the highest rating; -1 represents no rating.
Rating.Mortality    String  Above, Same, Below, or Unknown comparison to national hospital mortality
Rating.Safety   String  Above, Same, Below, or Unknown comparison to national hospital safety 
*/
const string rating::getRating() const {
	if (numRating > 1.5)
    return "Above";
  else if (numRating > 0.5)
    return "Same";
  else if (numRating >= 0)
    return "Below";
  else
    return "None";
}
