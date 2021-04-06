#include "rating.h"

/* 
A class to represent a rating system that uses both words and numbers
(see CORGIS hospital data for an example)
Rating.Overall  Integer     Overall rating between 1 and 5 stars, with 5 stars being the highest rating; -1 represents no rating.
Rating.Mortality    String  Above, Same, Below, or Unknown comparison to national hospital mortality
Rating.Safety   String  Above, Same, Below, or Unknown comparison to national hospital safety 
*/
string rating::getRating() const{
//    cout << num_rating << endl;
    if(num_rating >= 0 && num_rating <= 0.5){
        return "Below";
    }
    else if(num_rating > 0.5 && num_rating <= 1.5){
        return "Same";
    }
    else if (num_rating > 1.5 && num_rating <= 2.5){
        return "Above";
    }
    else{
        return "None";
    }
}
std::ostream& operator<<(std::ostream &out, const rating &r) {
    if(r.str_rating == "num"){
        out << r.num_rating;
    }
    else{
        out << r.getRating();
        out << " num " << r.num_rating << endl;
    }
    return out;
}
