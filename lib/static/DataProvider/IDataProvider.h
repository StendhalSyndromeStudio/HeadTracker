#ifndef IDATAPROVIDER_H
#define IDATAPROVIDER_H

#include <QByteArray>
#include <QObject>
/**
 * @brief описание интерфейса получения данных
 * от различных источников COM порт, Ethernet и т.д.
 */
class IDataProvider {
protected:
    IDataProvider( ) { }
public:
    virtual ~IDataProvider( ){ }
public:
    /**
    * @brief устанавливаем файл настроек
    * @param settingsDest - путь до файла настроек
    * описывает настройки интерфейса получения данных
    * и маску пакета
    */
    virtual void setSettings( const char *settingsDest ) = 0;
    virtual bool isDataAvailable( ) = 0;
    virtual const QByteArray &data( ) = 0;
public slots:
    virtual void start( ) = 0;
    virtual void stop( ) = 0;
};

#endif // IDATAPROVIDER_H
