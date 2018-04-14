#include "ahrs.h"

#include <math.h>
#include <QtMath>

void AHRS::gyrCalibration( )
{
    if (_calibrationCount < _calibrationSize) {
        for (int i = 0; i < 3; i++) {
            _drift_gyr[ i ] = _driftGyr.at( i )->ApplyFilter( _sensorData.Gyr( i ) );
        }
        _calibrationCount++;
    }
    else {
        _isCalibrationGyr = false;
        qDebug() << "drift Gyr:" << _drift_gyr[0] << _drift_gyr[1] << _drift_gyr[2];
    }
}

void AHRS::setGyrCalibrationSettings( int tickCount )
{
    this->_calibrationCount = 0;
    this->_calibrationSize = tickCount;
    this->_isCalibrationGyr = true;
}

void AHRS::calculateAngle( )
{
    if ( _isStart )
    {
        for ( int i( 0 ); i < 3; i++ )
        {
            _filterAcc.at( i )->SetState( _sensorData.Acc( i ), 0.1f );
            _filterGyr.at( i )->SetState( _sensorData.Gyr( i ), 0.1f );
            //filter_Mag[i].SetState(sensor_data.mag[i], 0.1f);
        }
        _isStart = false;
        _drift_gyr[ 0 ] = 0; _drift_gyr[ 1 ] = 0; _drift_gyr[ 2 ] = 0; _calibrationCount = 0;
        _isCalibrationGyr = true;
    }

    if ( _isCalibrationGyr )
    {
        gyrCalibration( );
        return;
    }
    correctionData( );

    applyKalmanFilter( );

    calculateQuaternion( );
}

void AHRS::correctionData( )
{
    for ( int i( 0 ); i < 3; i++ )
    {

        if ( _cutOffAcc )
        {
            if ( _sensorData.Acc( i ) > _fctAcc.at( i )->Max( ) * ( 1 + this->DELTA_ACC( ) ) )
            {
                _sensorData.Acc( i, _fctAcc.at( i )->Max( ) * ( 1 + this->DELTA_ACC( ) ) );
            }
            else
            {
                if ( _sensorData.Acc( i ) < _fctAcc.at( i )->Min( ) * ( 1 + this->DELTA_ACC( ) ) )
                {
                    _sensorData.Acc( i, _fctAcc.at( i )->Min( ) * ( 1 + this->DELTA_ACC( ) ) );
                }
            }
        }
        _sensorData.Acc( i, ( _sensorData.Acc( i ) - _fctAcc.at( i )->Mean( ) ) * _fctAcc.at( i )->Factor( ) );
        if ( _sensorData.Gyr( i ) > _drift_gyr[ i ] - this->DELTA_GYR( ) && _sensorData.Gyr( i ) < _drift_gyr[i] + this->DELTA_GYR( ) )
        {
            _drift_gyr[ i ] = _driftGyr.at( i )->ApplyFilter( _sensorData.Gyr( i ) );
        }
        _sensorData.Gyr( i, _sensorData.Gyr( i ) - _drift_gyr[ i ] );
    }
    //qDebug( ) << "acc:" << _sensorData.Acc( 0 ) << " " << _sensorData.Acc( 1 ) << " " << _sensorData.Acc( 2 );
    //qDebug( ) << "gyr:" << _sensorData.Gyr( 0 ) << " " << _sensorData.Gyr( 1 ) << " " << _sensorData.Gyr( 2 );
}

void AHRS::applyKalmanFilter( )
{
    for (int i( 0 ); i < 3; i++)
    {
        _filterAcc.at( i )->ApplyFilter( _sensorData.Acc( i ) );
        _filterGyr.at( i)->ApplyFilter( _sensorData.Gyr( i ) );
        //filter_Mag[i].ApplyFilter(sensor_data.mag[i]);

        if ( qAbs( _filterGyr.at( i )->State( ) ) < this->CUTOFF_GYR( ) )
        {
            _filterGyr.at( i )->SetState( 0 );
        }
    }
   //qDebug() << "Acc:" << _filterAcc.at( 0 )->State() << " " << _filterAcc.at( 1 )->State() << " " << _filterAcc.at( 2 )->State();
   //qDebug() << "Gyr:" << _filterGyr.at( 0 )->State() << " " << _filterGyr.at( 1 )->State() << " " << _filterGyr.at( 2 )->State();
}

void AHRS::calculateQuaternion( )
{
    _madgwickFilter.UpdateUpY( _filterGyr.at( 0 )->State( ) * this->DEG_TO_RAD( ),
                               _filterGyr.at( 1 )->State( ) * this->DEG_TO_RAD( ),
                               _filterGyr.at( 2 )->State( ) * this->DEG_TO_RAD( ),
                               _filterAcc.at( 0 )->State( ),
                               _filterAcc.at( 1 )->State( ),
                              -_filterAcc.at( 2 )->State( ),
                               _sensorData.DeltaTime( ) );
}

float AHRS::SCALE_GYR( )
{
    return _scaleGyr;
}

double AHRS::SCALE_ACC( )
{
    return _scaleAcc;
}

double AHRS::SCALE_MAG( )
{
    return _scaleMag;
}

double AHRS::DELTA_GYR( )
{
    return _deltaGyr;
}

double AHRS::CUTOFF_GYR( )
{
    return _cutoffGyr;
}

double AHRS::DELTA_ACC( )
{
    return _deltaAcc;
}

double AHRS::RAD_TO_DEG( )
{
    return 180 / M_PI;
}

double AHRS::DEG_TO_RAD( )
{
    return M_PI / 180;
}

double AHRS::MAG_DECLINATION( )
{
    return _magDeclination;
}

void AHRS::SCALE_GYR(float value)
{
    _scaleGyr = value;
}

void AHRS::SCALE_ACC(double value)
{
    _scaleAcc = value;
}

void AHRS::SCALE_MAG(double value)
{
    _scaleMag = value;
}

void AHRS::DELTA_GYR(double value)
{
    _deltaGyr = value;
}

void AHRS::CUTOFF_GYR(double value)
{
    _cutoffGyr = value;
}

void AHRS::DELTA_ACC(double value)
{
    _deltaAcc = value;
}

void AHRS::MAG_DECLINATION(double value)
{
    _magDeclination = value;
}

AHRS::AHRS(double q, double r)
{
    _isStart = true;

    _scaleGyr = 1;
    _scaleAcc = 2040;
    _scaleMag = 2600;
    _deltaGyr = 0.75;
    _cutoffGyr = 0.75;
    _deltaAcc = 0.1;
    _magDeclination = 10.5;

    for ( int i( 0 ); i < 3; i++ ) {
        _driftGyr.append( new FloatAverage( 10 ) );
        _filterAcc.append( new KalmanFilter( q, r, 1, 1 ) );
        _filterGyr.append( new KalmanFilter( q, r, 1, 1 ) );
    }
}

bool AHRS::isReady()
{
    return !this->_isCalibrationGyr;
}

QQuaternion AHRS::Quaternion()
{
    return _madgwickFilter.Quaternion( );
}

void AHRS::SetCalibrationData( QVector3D accMin, QVector3D accMax, QVector3D deltaGyr, QVector3D magMin, QVector3D magMax )
{
    Q_UNUSED( magMin );
    Q_UNUSED( magMax );
    _fctAcc.append( new FactorAccMag( accMin.x( ), accMax.x( ), this->SCALE_ACC( ) ) );
    _fctAcc.append( new FactorAccMag( accMin.y( ), accMax.y( ), this->SCALE_ACC( ) ) );
    _fctAcc.append( new FactorAccMag( accMin.z( ), accMax.z( ), this->SCALE_ACC( ) ) );
    _drift_gyr[ 0 ] = deltaGyr.x( );
    _drift_gyr[ 1 ] = deltaGyr.y( );
    _drift_gyr[ 2 ] = deltaGyr.z( );

    //this->calculateAngle( );
}

void AHRS::Reset( )
{
    _madgwickFilter.Reset( );
}

void AHRS::SetSensorsData( ITrackerPacket *packet )
{
    _sensorData.Acc( 0, packet->Acc( ).x( ) );
    _sensorData.Acc( 1, packet->Acc( ).y( ) );
    _sensorData.Acc( 2, packet->Acc( ).z( ) );

    _sensorData.Gyr( 0, packet->Gyr( ).x( ) );
    _sensorData.Gyr( 1, packet->Gyr( ).y( ) );
    _sensorData.Gyr( 2, packet->Gyr( ).z( ) );

//    _sensorData.TempAcc( );
    //sensor_data.delta_time = data.dTime * 0.001f;
    _sensorData.DeltaTime( packet->dTime( ) * 0.001f );
    calculateAngle( );
}
