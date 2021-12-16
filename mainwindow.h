#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>
#include <QList>
#include <QDateTime>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


//CAMERA

class QVBoxLayout;
class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void readSerial();
    void on_szukaj_button_clicked();

    void on_polacz_button_clicked();

    void on_rozlacz_button_clicked();

    void on_camera_0_check_stateChanged(int arg1);

    void on_camera_1_check_stateChanged(int arg1);

    void on_camera_2_check_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QList<QSerialPortInfo> dev;
    void add_monitor_log(QString mess);
    QSerialPort *arduino; //wskaźnik na obiekt QSerialPort
    static const quint16 arduino_uno_vendro_id=9025;
    static const quint16 arduino_uno_product_id=67;
    QByteArray serialData;
    QString serialBuffer;


    // CAMERA 1
    QCamera *m_Camera1;
    QCameraViewfinder *m_CameraViewfinder1;
    QCameraImageCapture *m_CameraImageCapture1;
    QVBoxLayout *m_layout1;
    // CAMERA 2
    QCamera *m_Camera2;
    QCameraViewfinder *m_CameraViewfinder2;
    QCameraImageCapture *m_CameraImageCapture2;
    QVBoxLayout *m_layout2;

    // CAMERA 3
    QCamera *m_Camera3;
    QCameraViewfinder *m_CameraViewfinder3;
    QCameraImageCapture *m_CameraImageCapture3;
    QVBoxLayout *m_layout3;
    bool checkCameraAvailability();


};
#endif // MAINWINDOW_H
