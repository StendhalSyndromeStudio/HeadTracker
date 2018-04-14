#include "trackerpacketardurimu9dof.h"


TrackerPacketArdurImu9Dof::TrackerPacketArdurImu9Dof( QByteArray bytes ) {
    this->fromBytes( bytes );
}

void TrackerPacketArdurImu9Dof::fromBytes( QByteArray bytes ) {
    this->_acc.setX( ByteArrayConversion::bytesToFloat( bytes.mid( 0, 4 ) ) );
    this->_acc.setY( ByteArrayConversion::bytesToFloat( bytes.mid( 4, 4 ) ) );
    this->_acc.setZ( ByteArrayConversion::bytesToFloat( bytes.mid( 8, 4 ) ) );

    this->_gyr.setX( ByteArrayConversion::bytesToFloat( bytes.mid( 12, 4 ) ) );
    this->_gyr.setY( ByteArrayConversion::bytesToFloat( bytes.mid( 16, 4 ) ) );
    this->_gyr.setZ( ByteArrayConversion::bytesToFloat( bytes.mid( 20, 4 ) ) );

    this->_dTime = 1000 * ByteArrayConversion::bytesToFloat( bytes.mid( 24, 4 ) );
}
