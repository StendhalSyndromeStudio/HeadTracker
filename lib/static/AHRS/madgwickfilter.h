#ifndef MADGWICKFILTER_H
#define MADGWICKFILTER_H

#include <QQuaternion>

#define BETA_DEF 0.025
#define DELTA_TIME 0.0041f;

class MadgwickFilter
{
    private:
        double beta;
        double sensitivity_beta = 0.01;

        double q0 = 1.0, q1 = 0.0, q2 = 0.0, q3 = 0.0;
        double _q0 = 1.0, _q1 = 0.0, _q2 = 0.0, _q3 = 0.0;

        double qDot0, qDot1, qDot2, qDot3;
        double recipNorm;
        double q0q0, q1q1, q2q2, q3q3, df02, df13;
        double s0, s1, s2, s3;

        double _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2, _8q1, _8q2;

        double dq[4];

        void CorrectionQuaternion( );
    public:
        MadgwickFilter( QQuaternion uncalibratedQuat );
        MadgwickFilter( );
        void Reset( );      
        QQuaternion Quaternion( );
        void Update( double gx, double gy, double gz, double ax, double ay, double az, double deltaTimeGyr );
        void UpdateUpY( double gx, double gy, double gz, double ax, double ay, double az, double deltaTimeGyr );
};

#endif // MADGWICKFILTER_H
