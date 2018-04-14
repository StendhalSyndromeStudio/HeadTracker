#include "bytearrayconversion.h"

QByteArray ByteArrayConversion::reverse( QByteArray array ) {
    QByteArray bytes;
    foreach ( quint8 b, array ) {
        bytes.prepend( b );
    }
    return bytes;
}

float ByteArrayConversion::bytesToFloat( QByteArray array ) {
    float result;
    QByteArray reversedBytes = reverse(array);
    QDataStream ds(&reversedBytes, QIODevice::ReadOnly);
    ds.setFloatingPointPrecision(QDataStream::SinglePrecision);
    ds >> result;
    return result;
}
