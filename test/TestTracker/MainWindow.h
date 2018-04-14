#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "SerialPortDataProvider.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow( QWidget *parent = nullptr );
    ~MainWindow( );
private:
    Ui::MainWindow *ui;
    SerialPortDataProvider _dataProvider;
    QTimer _tmrUpdate;
private slots:
    void onUpdate( );
};

#endif // MAINWINDOW_H
