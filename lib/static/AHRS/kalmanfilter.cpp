#include "kalmanfilter.h"


KalmanFilter::KalmanFilter( double q, double r, double f, double h )
{
    _q = q;
    _r = r;
    _f = f;
    _h = h;
}

double KalmanFilter::ApplyFilter( double data )
{
    Correct( data );
    return _state;
}

void KalmanFilter::Correct( double data )
{
    _x0 = _f * _state;
    _p0 = _f * _covariance * _f + _q;

    double K = _h * _p0 / ( _h * _p0 * _h + _r );
    _state = _x0 + K * ( data - _h * _x0 );
    _covariance = ( 1 - K * _h ) * _p0;
}

void KalmanFilter::SetState( double state, double covariance )
{
    _state = state;
    _covariance = covariance;
}

void KalmanFilter::SetState( double state )
{
    _state = state;
}
