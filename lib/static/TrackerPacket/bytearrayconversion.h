#ifndef BYTEARRAYCONVERSION_H
#define BYTEARRAYCONVERSION_H

#include <QByteArray>
#include <QDataStream>

/**
 * @brief Класс расширяющий функционал
 * массива байт
 */
class ByteArrayConversion
{
    public:
        static QByteArray reverse( QByteArray array );
        static float bytesToFloat( QByteArray array );
};

#endif // BYTEARRAYCONVERSION_H
