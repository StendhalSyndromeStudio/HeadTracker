#ifndef KALMANFILTER_H
#define KALMANFILTER_H


class KalmanFilter
{

    public:
        KalmanFilter( double q, double r, double f = 1, double h = 1 );

        double X0( ) { return _x0; }
        double P0( ) { return _p0; }

        double F( ) { return _f; }
        double Q( ) { return _q; }
        double H( ) { return _h; }
        double R( ) { return _r; }

        double State( ) { return _state; }
        double Covariance( ) { return _covariance; }

        double ApplyFilter( double data );

        void SetState( double state, double covariance );
        void SetState( double state );
    private:
        double _x0;
        double _p0;

        double _f;
        double _q;
        double _h;
        double _r;

        double _state;
        double _covariance;

        void Correct( double data );
};

#endif // KALMANFILTER_H
