#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QCameraInfo>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->arduino=new QSerialPort;  //arduino
    serialBuffer="";

        const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
         m_Camera1=new QCamera(cameras[0]);
         m_Camera2=new QCamera(cameras[1]);
         m_Camera3=new QCamera(cameras[2]);

    m_CameraViewfinder1=new QCameraViewfinder(this);
    m_CameraImageCapture1 = new QCameraImageCapture(m_Camera1,this);
    m_layout1=new QVBoxLayout;

    m_Camera1->setViewfinder(m_CameraViewfinder1);
    m_layout1->addWidget(m_CameraViewfinder1);
    m_layout1->setMargin(0);
    ui->camera0_place->setLayout(m_layout1);

    m_CameraViewfinder2=new QCameraViewfinder(this);
    m_CameraImageCapture2 = new QCameraImageCapture(m_Camera2,this);
    m_layout2=new QVBoxLayout;

    m_Camera2->setViewfinder(m_CameraViewfinder2);
    m_layout2->addWidget(m_CameraViewfinder2);
    m_layout2->setMargin(0);
    ui->camera1_place->setLayout(m_layout2);

    m_CameraViewfinder3=new QCameraViewfinder(this);
    m_CameraImageCapture3 = new QCameraImageCapture(m_Camera3,this);
    m_layout3=new QVBoxLayout;

    m_Camera3->setViewfinder(m_CameraViewfinder3);
    m_layout3->addWidget(m_CameraViewfinder3);
    m_layout3->setMargin(0);
    ui->camera2_place->setLayout(m_layout3);



   }




//bool MainWindow::checkCameraAvailability()
//{
//    if (QCameraInfo::availableCameras().count() > 0)
//        return true;
//    else
//        return false;
//}

MainWindow::~MainWindow()
{
    delete ui;
    if(this->arduino->isOpen())this->arduino->close();
    delete arduino;
}

void MainWindow::readSerial()
{
        serialData =arduino->readAll();
        float napiecie=serialData.toFloat();
        serialBuffer += QString::fromStdString(serialData.toStdString());

        //qDebug()<<serialBuffer;
        qDebug()<<"napiecie"<<napiecie;
        serialBuffer="";

        ui->lcdNumber_VOLTAGE->display(napiecie);
   // qDebug()<<"zmienna_napiecie: "<<napiecie

}


void MainWindow::on_szukaj_button_clicked()
{
   this->add_monitor_log("Szukam urządzeń");
    dev = QSerialPortInfo::availablePorts();
    ui->box_wybierz_urzadzenie->clear();
    for(int i = 0; i < dev.count(); i++) {
        this->add_monitor_log("Znalazłem urządzenie: " + dev.at(i).portName() + " " + dev.at(i).description());
      ui->box_wybierz_urzadzenie->addItem(dev.at(i).portName() + "\t" + dev.at(i).description());
    }

}

void MainWindow::add_monitor_log(QString mess) {
    QString curDT=QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
 ui->log_monitor->append(curDT + "\t" + mess);
}

void MainWindow::on_polacz_button_clicked()
{

    if(ui->box_wybierz_urzadzenie->count() == 0) {      // jezeli nie ma zadnych urzadzen to nie ma sie z czym laczyc.
      this->add_monitor_log("Nie wykryto żadnych urządzeń! Sprawdź połączenie i ustawienia portu szeregowego.");
      return;
    }

    QString portName = ui->box_wybierz_urzadzenie->currentText().split("\t").first(); // nazwa wybranego portu z comboboxa w postaci stringa
    this->arduino->setPortName(portName);   // wybieramy odpowiedni port w urzadzeniu.

    qDebug()<<portName;

    if(!arduino->isOpen()) {    // jezeli port jest juz otwarty, to nie ma sensu otwierac go jeszcze raz


        // OTWÓRZ I SKONFIGURUJ PORT:
    if(arduino->open(QSerialPort::ReadWrite)) {
      this->arduino->setBaudRate(QSerialPort::Baud115200); // boudrate
      this->arduino->setDataBits(QSerialPort::Data8);   // liczba bitow danych (8)
      this->arduino->setParity(QSerialPort::NoParity); // bez kontroli parzystosci.
      this->arduino->setStopBits(QSerialPort::OneStop);
      this->arduino->setFlowControl(QSerialPort::NoFlowControl); // bez kontroli przeplywu
      this->add_monitor_log("Port szeregowy pomyślnie otwarty.");
       QObject::connect(arduino,SIGNAL(readyRead()),this,SLOT(readSerial()));
    }
    else {this->add_monitor_log("Otwarcie portu szeregowego nie powiodło się."); }
    }
    else { this->add_monitor_log("Port już jest otwarty!");
          return;
    }
}



void MainWindow::on_rozlacz_button_clicked()
{
    if(this->arduino->isOpen()){
        this->arduino->close();
        this->add_monitor_log("Zamknięto połączenie.");
        ui->lcdNumber_VOLTAGE->display(0);
    }
    else{
        this->add_monitor_log("Port nie jest otwarty!");
        return;
    }
}


void MainWindow::on_camera_0_check_stateChanged(int arg1){
    if(arg1==2) {

        //qDebug()<<m_Camera1->availability();
       // if(m_Camera1->availability()==0) {
          //  this->add_monitor_log("KAMERA NR 0 NIE JEST DOSTĘPNA!");
       // }

       // else {
            ui->camera_0_check->setText("ON");
            m_Camera1->start();
       // }

    }
    else {
        ui->camera_0_check->setText("OFF");
        m_Camera1->stop();

    }
}

void MainWindow::on_camera_1_check_stateChanged(int arg1){
    if(arg1==2) {

       // if(m_Camera2->availability()==0) {
           // this->add_monitor_log("KAMERA NR 1 NIE JEST DOSTĘPNA!");
       // }
       // else {
        ui->camera_1_check->setText("ON");
        m_Camera2->start();
 //   }
}
    else {
        ui->camera_1_check->setText("OFF");
        m_Camera2->stop();

    }
}

void MainWindow::on_camera_2_check_stateChanged(int arg1){
    if(arg1==2) {

       // if(m_Camera3->availability()==0) {
         //   this->add_monitor_log("KAMERA NR 2 NIE JEST DOSTĘPNA!");
       // }
      //  else {
            m_Camera3->start();
            ui->camera_2_check->setText("ON");
      //       }
    }
    else {
        ui->camera_2_check->setText("OFF");
        m_Camera3->stop();

    }
}



void MainWindow::on_pushButton_2_clicked()
{
    if(this->arduino->isOpen()){
    this->arduino->write("l");
    }
    else{
        this->add_monitor_log("Port nie jest otwarty!");
        return;
    }
}


void MainWindow::on_pushButtonIncrease_clicked()
{
    if(this->arduino->isOpen()){
    this->arduino->write("p");
    }
    else{
        this->add_monitor_log("Port nie jest otwarty!");
        return;
    }
}

