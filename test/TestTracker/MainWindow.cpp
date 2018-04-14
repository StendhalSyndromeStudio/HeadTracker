#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Converter.h"
#include "trackerpacketardurimu9dof.h"
#include "AHRS.h"
#include <QQuaternion>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect( &_tmrUpdate, SIGNAL( timeout( ) ),SLOT( onUpdate( ) ) );

    _dataProvider.setSettings( "D:/build/bin/config.xml" );
    _dataProvider.start( );
    _tmrUpdate.start( 10 );
}

MainWindow::~MainWindow( ) {
    delete ui;
}

void MainWindow::onUpdate( ) {
    QByteArray bytes{ _dataProvider.data( ) };
    TrackerPacketArdurImu9Dof *trackerPacket = new TrackerPacketArdurImu9Dof( bytes );
    ui->label->setText( QString::number( trackerPacket->Acc( ).x( ) ) );
    ui->label_2->setText( QString::number( trackerPacket->Acc( ).y( ) ) );
    ui->label_3->setText( QString::number( trackerPacket->Acc( ).z( ) ) );

    ui->label_4->setText( QString::number( trackerPacket->Gyr( ).x( ) ) );
    ui->label_5->setText( QString::number( trackerPacket->Gyr( ).y( ) ) );
    ui->label_6->setText( QString::number( trackerPacket->Gyr( ).z( ) ) );

    QQuaternion rotation = AHRS::rotation( trackerPacket->Gyr( ).x( ),
                    trackerPacket->Gyr( ).y( ),
                    trackerPacket->Gyr( ).z( ),
                    trackerPacket->Acc( ).x( ),
                    trackerPacket->Acc( ).y( ),
                    trackerPacket->Acc( ).z( ) );

//    ui->label->setText( QString::number( rotation.x( ) ) );
//    ui->label_2->setText( QString::number( rotation.y( ) ) );
//    ui->label_3->setText( QString::number( rotation.z( ) ) );

//    ui->label_4->setText( QString::number( rotation.scalar( ) ) );
}
