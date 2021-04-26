#include "rating.h"


const string rating::getRating() const {

	if (numericRating == 0)
			return "unknown";
	assert(numericRating >= 1.0);
	if (numericRating >= 1.0 && numericRating <= 1.5)
			return "below";
	else if (numericRating > 1.5 && numericRating <= 2.5)
			return "same";
	else if (numericRating > 2.5)
			return "above";
	
	return "error";
}
