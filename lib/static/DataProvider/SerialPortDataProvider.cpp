#include "SerialPortDataProvider.h"

void SerialPortDataProvider::getSettings( QDomElement setting ) {
    bool ok = false;
    QDomNode domNode = setting.firstChild( );
    while ( !domNode.isNull( ) ) {
        if ( domNode.isElement( ) ) {
            QDomElement domElement = domNode.toElement( );
            if ( !domElement.isNull( ) ) {
                if ( domElement.tagName( ) == "portName" ) {
                    _serialPort.setPortName( domElement.attribute( "value" ) );
                }
                if ( domElement.tagName( ) == "baudRate" ) {
                    _serialPort.setBaudRate( domElement.attribute( "value" ).toInt( &ok, 10 ) );
                    if ( !ok ) {
                        qDebug( ) << "error on convert " << domElement.attribute( "value" ) << " to int";
                    }
                }
                if ( domElement.tagName( ) == "lenght" ) {
                    _packetSize = domElement.attribute( "value" ).toInt( &ok, 10 );
                    if ( !ok ) {
                        qDebug( ) << "error on convert " << domElement.attribute( "value" ) << " to int";
                    }
                }
                if ( domElement.tagName( ) == "delimeterCharCode" ) {
                    _codeCharDelimiter = domElement.attribute( "value" ).toInt( &ok, 10 );
                    if ( !ok ) {
                        qDebug( ) << "error on convert " << domElement.attribute( "value" ) << " to int";
                    }
                }
                getSettings( domElement );
            }
        }
        domNode = domNode.nextSibling( );
    }
}

SerialPortDataProvider::SerialPortDataProvider( QObject *parent ) : QObject{ parent } {
    connect( &_serialPort, &QSerialPort::readyRead, this, &SerialPortDataProvider::handleReadyRead );
    connect( &_serialPort, static_cast < void ( QSerialPort::* )( QSerialPort::SerialPortError ) > ( &QSerialPort::error ),
            this, &SerialPortDataProvider::handleError );
    connect( &_timer, &QTimer::timeout, this, &SerialPortDataProvider::handleTimeout );
}

SerialPortDataProvider::~SerialPortDataProvider( ) {

}

void SerialPortDataProvider::handleReadyRead( ) {
    _readData.append( _serialPort.readAll( ) );
    if ( !_timer.isActive( ) )
        _timer.start( 10 );
}

void SerialPortDataProvider::handleTimeout( ) {
    if ( _readData.isEmpty( ) ) {
        qDebug( ) << QObject::tr( "No data was currently available for reading from port %1" ).arg( _serialPort.portName( ) );
    } else {
        QList<QByteArray> list = _readData.split( char( _codeCharDelimiter ) );

        foreach ( QByteArray bytes, list ) {
            if ( bytes.length( ) != _packetSize ) {
//                qDebug( ) << bytes.length( ) << "!=" << _packetSize;
                continue;
            }
            _resultData = bytes;
//            qDebug( ) << bytes.toHex( );

        }
    }
}

void SerialPortDataProvider::handleError( QSerialPort::SerialPortError error ) {
    if ( error == QSerialPort::ReadError ) {
        qDebug( ) << QObject::tr( "An I/O error occurred while reading the data from port %1, error: %2" ).arg( _serialPort.portName( ) ).arg( _serialPort.errorString( ) );
    }
}

void SerialPortDataProvider::start( ) {
    if ( !_serialPort.open( QIODevice::ReadOnly ) ) {
        qDebug( ) << "Error on open:" << _serialPort.portName( ) << " " << _serialPort.errorString( );
        return;
    }
}

void SerialPortDataProvider::stop( ) {

}

bool SerialPortDataProvider::isDataAvailable( ) {
    return false;
}

const QByteArray &SerialPortDataProvider::data( ) {
    return _resultData;
}

void SerialPortDataProvider::setSettings( const char *settingsDest ) {
    QDomDocument domDoc;
    QFile        file( settingsDest );
    if ( file.open( QIODevice::ReadOnly ) ) {
        if ( domDoc.setContent( &file ) ) {
            QDomElement domElement = domDoc.documentElement( );
            getSettings( domElement );

            QSerialPortInfo serialPortInfo( _serialPort.portName( ) );

            qDebug( ) << "*** Serial Port Info ***" ;
            qDebug( ) << "Name:" << _serialPort.portName( );
            qDebug( ) << "Speed:" << _serialPort.baudRate( );
            qDebug( ) << "ProductIdentifier:" << serialPortInfo.productIdentifier( );
            qDebug( ) << "SerialNumber:" << serialPortInfo.serialNumber( );
            qDebug( ) << "*************************" ;

            file.close();
        }
    }
    else
        qDebug() << "file " << settingsDest << " not found";
}
