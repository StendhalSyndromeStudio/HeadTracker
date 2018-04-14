#include "stm32.h"

STM32::STM32()
{
    _acc[ 0 ] = 0;
    _acc[ 1 ] = 0;
    _acc[ 2 ] = 0;

    _gyr[ 0 ] = 0;
    _gyr[ 1 ] = 0;
    _gyr[ 2 ] = 0;

    _mag[ 0 ] = 0;
    _mag[ 1 ] = 0;
    _mag[ 2 ] = 0;
}

double STM32::Acc( int i )
{
    return _acc[ i ];
}

double STM32::Gyr( int i )
{
    return _gyr[ i ];
}

double STM32::Mag( int i )
{
    return _mag[ i ];
}

void STM32::Acc( int i, double value )
{
    _acc[ i ] = value;
}

void STM32::Gyr( int i, double value )
{
    _gyr[ i ] = value;
}

void STM32::Mag( int i, double value )
{
    _mag[ i ] = value;
}

int STM32::TempGyr( )
{
    return _tempGyr;
}

double STM32::TempAcc( )
{
    return _tempAcc;
}

double STM32::DeltaTime( )
{
    return _deltaTime;
}

void STM32::TempGyr( int value )
{
    _tempGyr = value;
}

void STM32::TempAcc(double value )
{
    _tempAcc = value;
}

void STM32::DeltaTime(double value )
{
    _deltaTime = value;
}
