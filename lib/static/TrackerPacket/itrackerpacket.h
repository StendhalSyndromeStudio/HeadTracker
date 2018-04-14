#ifndef ITRACKERPACKET_H
#define ITRACKERPACKET_H

#include <QtCore>
#include <QVector3D>
/**
 * @brief Интерфейс описывающий класс
 * преобразующий массив байт полученный от провайдера данных
 * в Vector3 акселерометра, гироскопа, магнитометра
 */
class ITrackerPacket
{
    public:
        /**
         * @brief Данные акселерометра
         * @return Vector3
         */
        QVector3D Acc( ) {
            return _acc;
        }
        /**
         * @brief Данные гироскопа
         * @return Vector3
         */
        QVector3D Gyr( ) {
            return _gyr;
        }
        /**
         * @brief Данные магнитометра
         * @return Vector3
         */
        QVector3D Mag( ) {
            return _mag;
        }

        float dTime( ) {
            return _dTime;
        }

        QString ToString( );

    protected:
        QVector3D _acc;
        QVector3D _gyr;
        QVector3D _mag;
        float _dTime;
        virtual void fromBytes( QByteArray bytes ) = 0;
};

#endif // ITRACKERPACKET_H
