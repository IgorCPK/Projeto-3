#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //!Construtor da classe
    explicit MainWindow(QWidget *parent = 0);
    //!Destrutor da classe
    ~MainWindow();



public slots:
    //!Recebe os dados enviados ao servidor.
    void getData();
    //!Manipula os eventos de tempo.
    void timerEvent(QTimerEvent *e);
    //!Inicia a comunicação com o servidor.
    void tcpConnect();
    //!Finaliza a comunicação com servidor.
    void tcpDisconnect();
    //!Inicia o processo de aquisição de dados.
    void start();
    //!Finaliza o processo de aquisição de dados.
    void stop();
    //!Atualiza a lista de ips produtores de dados
    void update();
    //!Conecta-se ao ip selecionado
    void updateLineEditIP();

private slots:
    //!Fecha o Programa
    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    int timer;
};

#endif // MAINWINDOW_H
