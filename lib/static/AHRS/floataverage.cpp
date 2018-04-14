#include "floataverage.h"


FloatAverage::FloatAverage()
{

}

FloatAverage::FloatAverage( int newSize )
{
    _windowSize = 10;
    _windowCurrent = 0;

    _windowSize = newSize;
    _average.resize( newSize );
}

double FloatAverage::Value( )
{
    return _value;
}

double FloatAverage::ApplyFilter( double value )
{
    double result = 0.0f;

    // записываем новое значение
    if ( _windowCurrent < _windowSize - 1 )
    {
        _average[ _windowCurrent ] = value;
        _windowCurrent++;
    }
    else
    {
        // сдвигаем вниз на 1 элемент
        for ( int i = 0; i < _windowSize - 1; i++ )
        {
            _average[ i ] = _average[ i + 1 ];
        }
        _average[ _windowSize - 1 ] = value;
    }

    // считаем среднее в окне
    for ( int i = 0; i < _windowCurrent; i++ )
    {
        result += _average[ i ];
    }
    result /= _windowCurrent;

    _value = result;

    return result;
}
