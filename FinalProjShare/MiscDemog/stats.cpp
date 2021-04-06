#include "stats.h"
#include <vector> 
#include <numeric>
#include <algorithm>
#include <cmath>
#include <iostream> 

using namespace std;

double stats::computeMean(vector<double> theNums){

	double sum = std::accumulate(theNums.begin(), theNums.end(), 0.0);
	return sum / theNums.size();
}

//pass in counts
double stats::computePopMean(vector<double> theNums, int totPop){

	double sum = std::accumulate(theNums.begin(), theNums.end(), 0.0);
	return sum / totPop;
}


//pass in percentages
double stats::computeStdDevPop(std::vector<double> theNums, double theMean) {

	//convert to percentage
	double m = theMean*100;
	double accum = 0.0;
	std::for_each (std::begin(theNums), std::end(theNums), 
					[&](const double d) { accum += (d - m) * (d - m); }	
				  );

	return sqrt(accum / theNums.size());
}

double stats::computeStdDevSample(vector<double> theNums) {

	double m = stats::computeMean(theNums);
	double accum = 0.0;
	std::for_each (std::begin(theNums), std::end(theNums), 
					[&](const double d) { accum += (d - m) * (d - m); }	
				  );

	return sqrt(accum / (theNums.size()-1));

}


//https://www.statisticshowto.com/probability-and-statistics/correlation-coefficient-formula/
//This is the Pearson correlation coefficient
double stats::computeCorCoeff(std::vector<double> inX, std::vector <double> inY) {

	double sumX = std::accumulate(inX.begin(), inX.end(), 0.0);
	double sumY = std::accumulate(inY.begin(), inY.end(), 0.0);

	double iP = std::inner_product(inX.begin(), inX.end(), inY.begin(), 0);

	double sumSqX = std::inner_product(inX.begin(), inX.end(), inX.begin(), 0);
	double sumSqY = std::inner_product(inY.begin(), inY.end(), inY.begin(), 0);

	double n = inX.size();
	double corr = (n* iP - sumX*sumY)/
					sqrt((n*sumSqX - sumX*sumX)*(n*sumSqY - sumY*sumY));
	return corr;
}

//https://www.r-tutor.com/elementary-statistics/numerical-measures/covariance
double stats::computeCoVar(std::vector<double> inX, std::vector <double> inY, double mX, double mY) {
	//make a vector to put in differences
	vector<double> diff(inX.size(), 0.0);
	//fill with differences
    std::transform(inX.begin(), inX.end(),
    				inY.begin(), diff.begin(),  
                   [&](double xi, double yi) {return (xi - mX)*(yi - mY); } );

    //return the sum scaled by n
	return (1.0/inX.size())*std::accumulate(diff.begin(), diff.end(), 0.0);
}

//http://www.r-tutor.com/elementary-statistics/numerical-measures/correlation-coefficient
//working on passing in percentages
double stats::computeCorCoeffPop(std::vector<double> inX, std::vector <double> inY, double mX, double mY) {

	//convert to percent
	double mXp = mX*100;
	double mYp = mY*100;

	//compute the standard deviations
	double stdDevX = computeStdDevPop(inX, mX);
	double stdDevY= computeStdDevPop(inY, mY);

	//compute the covariance
	double covar = computeCoVar(inX, inY, mXp, mYp);

	double corr = covar/(stdDevX*stdDevY);

	//cout << "stdDX: " << stdDevX << " stdDy: " << stdDevY << " cov " << covar << endl;
	return corr;
}

double stats::computeCorCoeffSample(std::vector<double> inX, std::vector <double> inY) {

	double mX = computeMean(inX);
	double mY = computeMean(inY);
	//compute the standard deviations
	double stdDevX = computeStdDevSample(inX);
	double stdDevY= computeStdDevSample(inY);

	//compute the covariance
	double covar = computeCoVar(inX, inY, mX, mY);

	double corr = covar/(stdDevX*stdDevY);

	//cout << "stdDX: " << stdDevX << " stdDy: " << stdDevY << " cov " << covar << endl;
	return corr;
}

double stats::computeChiSqGoodFit(vector<double> obs, vector <double> exp) {

	//over-writes observed data
    std::transform(obs.begin(), obs.end(),
    				exp.begin(), obs.begin(),  
                   [](double o, double e) {return ((o-e)*(o-e))/e; });

	//accumulate
	double ChiSq = std::accumulate(obs.begin(), obs.end(), 0.0);

	return ChiSq;
}


