#ifndef EMPLOYMENTDATA_H_
#define EMPLOYMENTDATA_H_
class employmentData{
public:
	//stores decimal value of percent
	employmentData(double inAIndian, double inAsian,double inBlack,double inHispanic,double inHawaiian,
			int inTotal, double inWomen){
		this->aIndian=inAIndian*inTotal;
		this->asian=inAsian*inTotal;
		this->black=inBlack*inTotal;
		this->hispanic=inHispanic*inTotal;
		this->nHawaiian=inHawaiian*inTotal;
		this->total=inTotal;
		this->women=inWomen*inTotal;
	}
	employmentData(){
		this->aIndian=0;
		this->asian=0;
		this->black=0;
		this->hispanic=0;
		this->nHawaiian=0;
		this->total=0;
		this->women=0;
	}
	void addIndian(double in){ aIndian+=in;}
	void addAsian(double in){ asian+=in;}
	void addBlack(double in){ black+=in;}
	void addHispanic(double in){ hispanic+=in;}
	void addHawaiian(double in){ nHawaiian+=in;}
	void addTotal(int in){ total+=in;}
	void addWomen(double in){ women+=in;}

	void add(employmentData in){
		aIndian+=in.getIndian();
		asian+=in.getAsian();
		black+=in.getBlack();
		hispanic+=in.getHispanic();
		nHawaiian+=in.getHawaiian();
		total+=in.getTotal();
		women+=in.getWomen();
	}
	/*
	double getIndianTotal(){return aIndian*(total);}
	double getAsianTotal(){return asian*total;}
	double getBlackTotal(){return black*total;}
	double getHispanicTotal(){return hispanic*total;}
	double getHawaiianTotal(){return nHawaiian*total;}
	double getWomenTotal(){return women*total;}
	 */
	double getIndianDecimal(){return aIndian/total;}
	double getAsianDecimal(){return asian/total;}
	double getBlackDecimal(){return black/total;}
	double getHispanicDecimal(){return hispanic/total;}
	double getHawaiianDecimal(){return nHawaiian/total;}
	double getWomenDecimal(){return women/total;}
	//returns flat value
	double getIndian(){return aIndian;}
	double getAsian(){return asian;}
	double getBlack(){return black;}
	double getHispanic(){return hispanic;}
	double getHawaiian(){return nHawaiian;}
	int getTotal(){return total;}
	double getWomen(){return women;}

private:
	double aIndian;
	double asian;
	double black;
	double hispanic;
	double nHawaiian;
	int total;
	double women;
};




#endif /* EMPLOYMENTDATA_H_ */
