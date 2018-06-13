#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow){
  ui->setupUi(this);
  socket = new QTcpSocket(this);

  // Slider timing

  connect(ui->Start,
          SIGNAL(clicked(bool)),
          this,
          SLOT(onTimer()));

  connect(ui->Stop,
          SIGNAL(clicked(bool)),
          this,
          SLOT(offTimer()));

  connect(ui->sliderTiming,
          SIGNAL(valueChanged(int)),
          this,
          SLOT(setTimer(int)));

  connect(ui->SliderMax,
          SIGNAL(valueChanged(int)),
          this,
          SLOT(limitesup(int)));

  connect(ui->SliderMin,
          SIGNAL(valueChanged(int)),
          this,
          SLOT(limiteinf(int)));

  connect(ui->Connect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(conectar()));

  connect(ui->Disconnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(desconectar()));

  connect(ui->serverIP,
          SIGNAL(textChanged(QString)),
          this,
          SLOT(updateIP(QString)));

  ip_address = "127.0.0.1";

  time=1;

  sup=10;

  inf=1;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    sendInfo();
}

void MainWindow::conectar(){
  socket->connectToHost(ip_address,1234);
  if(socket->waitForConnected(3000)){
      QStringList list("Connected");
      ui->listWidget->addItems(list);
    qDebug() << "Connected";
//      ui->labelConnect->setText("Connected to "+ip_address);
  }
  else{
//      QStringList list("Connection error");
//      ui->listWidget->addItems(list);
    qDebug() <<"Connection error";
  }
}

void MainWindow::desconectar()
{
    socket->disconnectFromHost();
    if(socket->waitForConnected(3000)){
      qDebug() << "Connected to "+ip_address;
       QStringList list("Connected to "+ip_address);
       ui->listWidget->addItems(list);
    }
    else{
        QStringList list("Disconnected");
        ui->listWidget->addItems(list);
      qDebug() << "Disconnected";
    }
}

void MainWindow::updateIP(QString _IP)
{
    ip_address=QString (_IP);
}

void MainWindow::sendInfo(){
  QDateTime datetime;
  QString str;
  qint64 msecdate;

  if(socket->state()== QAbstractSocket::ConnectedState){

    msecdate = QDateTime::currentDateTime().toMSecsSinceEpoch();
    str = "set "+ QString::number(msecdate) + " " + QString::number((float)inf+((float)qrand()/(float)RAND_MAX)*(float)(sup-inf))+"\r\n";
    QStringList list(str);
    ui->listWidget->addItems(list);
    ui->listWidget->scrollToBottom();
      qDebug() << str;
      qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
      if(socket->waitForBytesWritten(3000)){
        qDebug() << "wrote";
      }
  }
}

void MainWindow::limiteinf(int _min){
    if (sup <= _min)
        ui->SliderMax->setValue(_min);
    inf=_min;
}

void MainWindow::limiteSup(int _max){
    if (inf >= _max)
        ui->SliderMin->setValue(_max);
    sup=_max;
}

void MainWindow::onTimer(){
    if(timer.size()==0){
       timer.push_back(startTimer(1000*time));
    }
    else{
        killTimer(timer[0]);
        timer[0]=startTimer(1000*time);
    }
}

void MainWindow::offTimer(){
    killTimer(timer[0]);
    timer.clear();
}

void MainWindow::setTimer(int _t){
    time = _t;
    if(timer.size()){
        onTimer();
    }
}

MainWindow::~MainWindow(){
  delete socket;
  delete ui;
}
