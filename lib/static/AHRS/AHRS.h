#ifndef AHRS_H
#define AHRS_H

#include <QQuaternion>
/**
 * @brief Класс получения угла поворота по данным акселерометра и гироскопа.
 * Для расчета используется фильтр Махоуни
 */
class AHRS {

public:
    AHRS( ) = delete;
    /**
     * @brief Получаем угол поворота в виде кватерниона
     * @param gX значение гироскопа по оси X
     * @param gY значение гироскопа по оси Y
     * @param gZ значение гироскопа по оси Z
     * @param aX значение акселерометра по оси X
     * @param aY значение акселерометра по оси Y
     * @param aZ значение акселерометра по оси Z
     * @return угол поворота
     */
    static QQuaternion rotation( float gX, float gY, float gZ, float aX, float aY, float aZ );

    static void sampleFreq( float value );
    static float sampleFreq( );
private:
    static volatile float _scalar;
    static volatile float _x;
    static volatile float _y;
    static volatile float _z;

    static volatile float _sampleFreq;
    static volatile float _twoKp;
    static volatile float _twoKi;

    static volatile float _integralFBx;
    static volatile float _integralFBy;
    static volatile float _integralFBz;
    /**
     * @brief алгоритм быстрой инверсии квадратного корня
     * как в Quake 3 от Кармака
     * @param x
     * @return
     */
    static float invSqrt( float x );

};

#endif // AHRS_H
