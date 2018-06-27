#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <QDateTime>
#include <vector>

class Plotter : public QWidget{
    Q_OBJECT
private:
    std::vector< double >TimeList;
    std::vector< double >ValueList;
    double VarX;
    double x0;
    bool PrimPrint;

public:
    //!Construtor do Plotter
    explicit Plotter(QWidget *parent = nullptr);
    //!Atualiza a região de Plotagem
    void paintEvent(QPaintEvent *event);
    //!Plotar o gráfico a partir do que se coleta do servidor
    void draw(  std::vector<qint64 > _timeList, std::vector<int>_valueList);
signals:

public slots:
};

#endif // Plotter_H
