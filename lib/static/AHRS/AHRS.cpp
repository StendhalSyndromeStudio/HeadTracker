#include "AHRS.h"
#include <math.h>

QQuaternion AHRS::rotation( float gX, float gY, float gZ, float aX, float aY, float aZ ) {
    float recipNorm;
    float halfvx, halfvy, halfvz;
    float halfex, halfey, halfez;
    float qa, qb, qc;

    if( !( ( aX == 0.0f ) && ( aY == 0.0f ) && ( aZ == 0.0f ) ) ) {
        recipNorm = invSqrt( aX * aX + aY * aY + aZ * aZ );
        aX *= recipNorm;
        aY *= recipNorm;
        aZ *= recipNorm;

        halfvx = _x * _z - _scalar * _y;
        halfvy = _scalar * _x + _y * _z;
        halfvz = _scalar * _scalar - 0.5f + _z * _z;

        halfex = ( aY * halfvz - aZ * halfvy );
        halfey = ( aZ * halfvx - aX * halfvz );
        halfez = ( aX * halfvy - aY * halfvx );

        if( _twoKi > 0.0f ) {
            _integralFBx += _twoKi * halfex * ( 1.0f / _sampleFreq );
            _integralFBy += _twoKi * halfey * ( 1.0f / _sampleFreq );
            _integralFBz += _twoKi * halfez * ( 1.0f / _sampleFreq );
            gX += _integralFBx;
            gY += _integralFBy;
            gZ += _integralFBz;
        }
        else {
            _integralFBx = 0.0f;
            _integralFBy = 0.0f;
            _integralFBz = 0.0f;
        }
        gX += _twoKp * halfex;
        gY += _twoKp * halfey;
        gZ += _twoKp * halfez;
    }
    gX *= ( 0.5f * ( 1.0f / _sampleFreq ) );
    gY *= ( 0.5f * ( 1.0f / _sampleFreq ) );
    gZ *= ( 0.5f * ( 1.0f / _sampleFreq ) );
    qa = _scalar;
    qb = _x;
    qc = _y;
    _scalar += ( -qb * gX - qc * gY - _z * gZ );
    _x += ( qa * gX + qc * gZ - _z * gY );
    _y += ( qa * gY - qb * gZ + _z * gX );
    _z += ( qa * gZ + qb * gY - qc * gX );


    recipNorm = invSqrt( _scalar * _scalar + _x * _x + _y * _y + _z * _z );
    _scalar *= recipNorm;
    _x *= recipNorm;
    _y *= recipNorm;
    _z *= recipNorm;

    return QQuaternion( _scalar, _x, _y, _z );
}

void AHRS::sampleFreq( float value ) {
    _sampleFreq = value;
}

float AHRS::sampleFreq( ) {
    return _sampleFreq;
}

float AHRS::invSqrt( float x ) {
    float halfx = 0.5f * x;
    float y = x;
    long i = *( long* )&y;
    i = 0x5f3759df - ( i >> 1 );
    y = *( float* )&i;
    y = y * ( 1.5f - ( halfx * y * y ) );
    return y;
}

volatile float AHRS::_scalar{ 1.0f };
volatile float AHRS::_x{ 0.0f };
volatile float AHRS::_y{ 0.0f };
volatile float AHRS::_z{ 0.0f };

volatile float AHRS::_sampleFreq{ 64.0f };
volatile float AHRS::_twoKp{ 2.0f * 0.5f };
volatile float AHRS::_twoKi{ 2.0f * 0.0f };

volatile float AHRS::_integralFBx{ 0.0f };
volatile float AHRS::_integralFBy{ 0.0f };
volatile float AHRS::_integralFBz{ 0.0f };
