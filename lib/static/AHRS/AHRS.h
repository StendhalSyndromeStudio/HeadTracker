#ifndef AHRS_H
#define AHRS_H

#include <QtCore>
#include <QVector>
#include <QQuaternion>
#include <QVector3D>
#include <factoraccmag.h>
#include <stm32.h>
#include <floataverage.h>
#include <kalmanfilter.h>
#include <madgwickfilter.h>
#include <itrackerpacket.h>

class AHRS : public QObject
{
    Q_OBJECT
    private:
        QVector<FloatAverage *> _driftGyr;
        double _drift_gyr[ 3 ];
        QVector<FactorAccMag *> _fctAcc;
        bool _cutOffAcc;
        STM32 _sensorData;
        QVector<QString> _dataString;
        QVector<KalmanFilter *> _filterAcc;
        QVector<KalmanFilter *> _filterGyr;
        bool _isStart;
        MadgwickFilter _madgwickFilter;

        int _calibrationCount;
        int _calibrationSize;
        bool _isCalibrationGyr;

        void gyrCalibration( );

        void calculateAngle( );
        void correctionData( );
        void applyKalmanFilter( );
        void calculateQuaternion( );

        float    _scaleGyr;
        double   _scaleAcc;
        double   _scaleMag;
        double   _deltaGyr;
        double   _cutoffGyr;
        double   _deltaAcc;
        double   _magDeclination;
    public:
        float    SCALE_GYR( );
        double   SCALE_ACC( );
        double   SCALE_MAG( );
        double   DELTA_GYR( );
        double   CUTOFF_GYR( );
        double   DELTA_ACC( );
        double   RAD_TO_DEG( );
        double   DEG_TO_RAD( );
        double   MAG_DECLINATION( );

        void   SCALE_GYR( float value );
        void   SCALE_ACC( double value );
        void   SCALE_MAG( double value );
        void   DELTA_GYR( double value );
        void   CUTOFF_GYR( double value );
        void   DELTA_ACC( double value );
        void   MAG_DECLINATION( double value );

        AHRS( double q, double r );
        bool isReady( );
        QQuaternion Quaternion( );
        void setGyrCalibrationSettings( int tickCount );
        void SetCalibrationData( QVector3D accMin, QVector3D accMax, QVector3D deltaGyr, QVector3D magMin, QVector3D magMax );
        void Reset( );
     public slots:
        void SetSensorsData( ITrackerPacket *packet );
};

#endif // AHRS_H
