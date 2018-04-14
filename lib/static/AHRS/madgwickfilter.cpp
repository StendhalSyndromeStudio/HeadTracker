#include "madgwickfilter.h"

#include <QtCore>
#include <qmath.h>

void MadgwickFilter::CorrectionQuaternion()
{
    if ( qAbs( q0 - _q0 ) < dq[0] && qAbs( q1 - _q1 ) < dq[1] && qAbs( q2 - _q2 ) < dq[2]
        && qAbs( q3 - _q3 ) < dq[3] )
    {
        q0 = _q0;
        q1 = _q1;
        q2 = _q2;
        q3 = _q3;
    }
    else
    {
        _q0 = q0;
        _q1 = q1;
        _q2 = q2;
        _q3 = q3;
    }
}

MadgwickFilter::MadgwickFilter( QQuaternion uncalibratedQuat )
{
    q0 = uncalibratedQuat.scalar( );
    q1 = uncalibratedQuat.x( );
    q2 = uncalibratedQuat.y( );
    q3 = uncalibratedQuat.z( );
}

MadgwickFilter::MadgwickFilter()
{
    q0 = 1;
    q1 = 0;
    q2 = 0;
    q3 = 0;
}

void MadgwickFilter::Reset()
{
    q0 = 1;
    q1 = q2 = q3 = 0;
}

QQuaternion MadgwickFilter::Quaternion()
{
   QQuaternion result( q0, q1, q2, q3 );
   //qDebug() << " w:" << q0 << " x:" << q1 << " y:" << q2 << " z:" << q3;
   return result;
}

void MadgwickFilter::Update( double gx, double gy, double gz, double ax, double ay, double az, double deltaTimeGyr )
{
    qDot0 = 0.5f * ( -q1 * gx - q2 * gy - q3 * gz );
    qDot1 = 0.5f * ( q0 * gx + q2 * gz - q3 * gy );
    qDot2 = 0.5f * ( q0 * gy - q1 * gz + q3 * gx );
    qDot3 = 0.5f * ( q0 * gz + q1 * gy - q2 * gx );

    if ( !( ( ax == 0.0f ) && ( ay == 0.0f ) && ( az == 0.0f ) ) )
    {
        recipNorm = 1 / qSqrt( ( double )( ax * ax + ay * ay + az * az ) );
        ax *= recipNorm;
        ay *= recipNorm;
        az *= recipNorm;

        _2q0 = 2.0f * q0;
        _2q1 = 2.0f * q1;
        _2q2 = 2.0f * q2;
        _2q3 = 2.0f * q3;
        _4q0 = 4.0f * q0;
        _4q1 = 4.0f * q1;
        _4q2 = 4.0f * q2;
        _8q1 = 8.0f * q1;
        _8q2 = 8.0f * q2;
        q0q0 = q0 * q0;
        q1q1 = q1 * q1;
        q2q2 = q2 * q2;
        q3q3 = q3 * q3;

        s0 = _4q0 * q2q2 + _2q2 * ax + _4q0 * q1q1 - _2q1 * ay;
        s1 = _4q1 * q3q3 - _2q3 * ax + 4.0f * q0q0 * q1 - _2q0 * ay - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * az;
        s2 = 4.0f * q0q0 * q2 + _2q0 * ax + _4q2 * q3q3 - _2q3 * ay - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * az;
        s3 = 4.0f * q1q1 * q3 - _2q1 * ax + 4.0f * q2q2 * q3 - _2q2 * ay;
        recipNorm = 1 / qSqrt( s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3 );
        s0 *= recipNorm;
        s1 *= recipNorm;
        s2 *= recipNorm;
        s3 *= recipNorm;

        qDot0 -= beta * s0;
        qDot1 -= beta * s1;
        qDot2 -= beta * s2;
        qDot3 -= beta * s3;
    }

    q0 += qDot0 * deltaTimeGyr;
    q1 += qDot1 * deltaTimeGyr;
    q2 += qDot2 * deltaTimeGyr;
    q3 += qDot3 * deltaTimeGyr;

    recipNorm = 1 / qSqrt( q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3 );
    q0 *= recipNorm;
    q1 *= recipNorm;
    q2 *= recipNorm;
    q3 *= recipNorm;
}

void MadgwickFilter::UpdateUpY(double gx, double gy, double gz, double ax, double ay, double az, double deltaTimeGyr)
{
    //qDebug() << gx << gy << gz << ax << ay << az << deltaTimeGyr;
    qDot0 = 0.5f * ( -q1 * gx - q2 * gy - q3 * gz );
    qDot1 = 0.5f * ( q0 * gx + q2 * gz - q3 * gy );
    qDot2 = 0.5f * ( q0 * gy - q1 * gz + q3 * gx );
    qDot3 = 0.5f * ( q0 * gz + q1 * gy - q2 * gx );

    if ( !( ( ax == 0.0f ) && ( ay == 0.0f ) && ( az == 0.0f ) ) )
    {
        recipNorm = 1.0f / qSqrt( ax * ax + ay * ay + az * az );
        ax *= recipNorm;
        ay *= recipNorm;
        az *= recipNorm;

        q0q0 = q0 * q0;
        q1q1 = q1 * q1;
        q2q2 = q2 * q2;
        q3q3 = q3 * q3;
        df02 = 4 * ( q1q1 + q3q3 );
        df13 = 4 * ( q0q0 + 2 * q1q1 + q2q2 + 2 * q3q3 - 1 + ay );

        s0 = df02 * q0 + 2 * ( q1 * az - q3 * ax );
        s1 = df13 * q1 + 2 * ( q0 * az - q2 * ax );
        s2 = df02 * q2 - 2 * ( q1 * ax + q3 * az );
        s3 = df13 * q3 - 2 * ( q0 * ax + q2 * az );

        recipNorm = 1 / qSqrt( s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3 );
        s0 *= recipNorm;
        s1 *= recipNorm;
        s2 *= recipNorm;
        s3 *= recipNorm;

        qDot0 -= beta * s0;
        qDot1 -= beta * s1;
        qDot2 -= beta * s2;
        qDot3 -= beta * s3;
    }

    q0 += qDot0 * deltaTimeGyr;
    q1 += qDot1 * deltaTimeGyr;
    q2 += qDot2 * deltaTimeGyr;
    q3 += qDot3 * deltaTimeGyr;

    recipNorm = 1 / qSqrt( q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3 );
    q0 *= recipNorm;
    q1 *= recipNorm;
    q2 *= recipNorm;
    q3 *= recipNorm;
    //qDebug() << q0 << q1 << q2 << q3;
}
