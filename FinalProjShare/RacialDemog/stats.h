#ifndef STATS_H
#define STATS_H

#include <vector> 

class stats {
public:
	static double computeMean(std::vector<double> theNums);
	static double computePopMean(std::vector<double> theNums, int totPop);
	static double computeStdDevSample(std::vector<double> theNums);
	static double computeStdDevPop(std::vector<double> theNums, double theMean);
	//covariance
	static double computeCoVar(std::vector<double> inX, std::vector <double> inY, double mX, double mY);
	//Pearson
	static double computeCorCoeff(std::vector<double> inX, std::vector <double> inY);
	//population
	static double computeCorCoeffPop(std::vector<double> inX, std::vector <double> inY, double mX, double mY);
	//sample
	static double computeCorCoeffSample(std::vector<double> inX, std::vector <double> inY);
	static double computeChiSqGoodFit(std::vector<double> obs, std::vector <double> exp);
};
#endif