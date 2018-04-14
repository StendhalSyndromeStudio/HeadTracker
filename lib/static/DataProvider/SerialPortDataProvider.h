#ifndef COMPORTDATAPROVIDER_H
#define COMPORTDATAPROVIDER_H

#include <QDebug>
#include <QObject>
#include <QTimer>
#include <QSerialPortInfo>
#include "IDataProvider.h"

#include <QtXml>
#include <QtSerialPort/QSerialPort>
/**
 * @brief Поставщик данных для трекинга - COM порт
 */
class SerialPortDataProvider : public QObject, public IDataProvider {
    Q_OBJECT
    public:
        SerialPortDataProvider( QObject *parent = nullptr );
        ~SerialPortDataProvider( );
        void setSettings( const char *settingsDest ) override;
        bool isDataAvailable( ) override;
        const QByteArray &data( ) override;
    public slots:
        void start( ) override;
        void stop( ) override;
    private:
        QSerialPort  _serialPort;
        QTimer       _timer;
        QByteArray   _readData;
        QByteArray   _resultData;

        int _packetSize{ 0 };
        int _codeCharDelimiter{ 0 };

        void getSettings( QDomElement setting );
    private slots:
        void handleReadyRead( );
        void handleTimeout( );
        void handleError( QSerialPort::SerialPortError error );
};

#endif // COMPORTDATAPROVIDER_H
