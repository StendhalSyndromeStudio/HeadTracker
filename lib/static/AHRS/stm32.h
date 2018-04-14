#ifndef STM32_H
#define STM32_H


class STM32
{
    private:
        double _acc[ 3 ];
        double _gyr[ 3 ];
        double _mag[ 3 ];

        int _tempGyr;
        double _tempAcc;
        double _deltaTime;
    public:
        STM32( );
        double Acc( int i );
        double Gyr( int i );
        double Mag( int i );

        void Acc( int i, double value );
        void Gyr( int i, double value );
        void Mag( int i, double value );

        int TempGyr( );
        double TempAcc( );
        double DeltaTime( );

        void TempGyr( int value );
        void TempAcc( double value );
        void DeltaTime( double value );
};

#endif // STM32_H
