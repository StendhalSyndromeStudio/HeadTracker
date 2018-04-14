#ifndef FACTORACCMAG_H
#define FACTORACCMAG_H

class FactorAccMag {
    private:
        double _min;
        double _max;
        double _mean;
        double _factor;

    public:
        double Min( ) { return _min; }
        double Max( ) { return _max; }
        double Mean( ) { return _mean; }
        double Factor( ) { return _factor; }

        FactorAccMag( double min, double max, double scale ) {
            _min = min;
            _max = max;
            _mean = ( _max + _min ) * 0.5;
            _factor = scale / ( _max - _min );
        }
};

#endif // FACTORACCMAG_H
