#ifndef FLOATAVERAGE_H
#define FLOATAVERAGE_H

#include <QVector>

class FloatAverage
{
    private:
        int _windowSize;
        int _windowCurrent;
        QVector<double> _average;
        double _value;
    public:
        FloatAverage( );
        FloatAverage( int newSize );
        double Value( );
        double ApplyFilter( double value );
};

#endif // FLOATAVERAGE_H
