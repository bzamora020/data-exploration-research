#ifndef RACIALDATA_H
#define RACIALDATA_H
class RacialData{
    public:
        RacialData(double n = 0, double a = 0, double b = 0, double hisp = 0, 
                    double haw = 0, double mix = 0, double w = 0, double ow = 0):
        native(n), asian(a), black(b), hispanic(hisp), hawaiian(haw), mixed(mix), white(w), onlyWhite(ow)
        {}
        double getNative() const{ return native; }
        double getAsian() const{ return asian; }
        double getBlack() const{ return black; }
        double getHispanic() const{ return hispanic; }
        double getHawaiian() const{ return hawaiian; }
        double getMixed() const{ return mixed; }
        double getWhite() const{ return white; }
        double getOnlyWhite() const{ return onlyWhite; }

        RacialData& operator+=(const RacialData& rd){
            native += rd.native;
            asian += rd.asian;
            black += rd.black;
            hispanic += rd.hispanic;
            hawaiian += rd.hawaiian;
            mixed += rd.mixed;
            white += rd.white;
            onlyWhite += rd.onlyWhite;
            return *this;
        }

        RacialData operator/(const double count){
            RacialData r{native/count, asian/count, black/count, hispanic/count, hawaiian/count,
                        mixed/count, white/count, onlyWhite/count};
            return r;
        }
    private:
        double native;
        double asian;
        double black;
        double hispanic;
        double hawaiian;
        double mixed;
        double white;
        double onlyWhite;
};
#endif
