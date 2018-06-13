#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QTimerEvent>
#include <vector>


namespace Ui {

class MainWindow;

}
/**
 * @brief Esta classe gera a janela do produtor de arquivos
 *
 */
class MainWindow : public QMainWindow
{
  Q_OBJECT
    int inf,sup,time;
    std::vector <int>timer;
    QString ip_address;
public:
  explicit MainWindow(QWidget *parent = 0);
  void timerEvent(QTimerEvent *event);
  ~MainWindow();
  /**
   * @brief Este método envia os dados.
   */
  void sendInfo();
public slots:
  /**
   * @brief Este método conecta com o IP desejado
   */

  void conectar();

  /**
   * @brief Este método desconecta do IP.
   */

  void desconectar();

  /**
   * @brief Este método Atualiza o IP
   */

  void updateIP(QString _IP);

  /**
   * @brief Este método altera o limite inferior de dados enviados
   */

  void limiteinf(int _min);

  /**
   * @brief Este método altera o limite superior de dados enviados
   */

  void limiteSup(int _max);

  /**
   * @brief Este método liga o timer
   */

  void onTimer();

  /**
   * @brief Este método desliga o timer
   */

  void offTimer();

  /**
   * @brief Este método configura o timer
   */

  void setTimer(int _t);

private slots:

private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
};

#endif // MAINWINDOW_H
