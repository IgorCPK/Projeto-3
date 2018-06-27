#include "plotter.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <cmath>
#define e 2.718281828459045235360287


Plotter::Plotter(QWidget *parent) : QWidget(parent)
{ qDebug() << "oi";
    x0 =0;
    VarX = 0;
    PrimPrint = true;
}

void Plotter::paintEvent(QPaintEvent *event){
    qDebug() << "event" ;
    QPainter painter(this);
    QBrush brush;
    QPen pen;


    brush.setColor(QColor(255,255,255));
    brush.setStyle(Qt::SolidPattern);
    pen.setColor(QColor(211,211,211));
    pen.setWidth(2);
    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawRect(0,0,width(),height());


    pen.setColor(QColor(211,211,211));
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);
    painter.setPen(pen);

    for(int i=0; i<width(); i= i+20){
        painter.drawLine(i,0,i,height());
    }

    for(int i=0; i<height(); i= i+20){
        painter.drawLine(0,i,width(),i);
    }


    pen.setColor(QColor(0,0,255));
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);


    double x2,y1,y2;
    if (PrimPrint){
        x0 =0;
        y1 = height();
    }else{
        qDebug() << "x0: " <<  (TimeList[0]/TimeList[29])*width();

        x0  = (TimeList[0]/TimeList[29])*width() ;
        y1 = height() - ValueList[0];
    }

    int size = TimeList.size();

    qDebug() << size;
    for(int i=1; i< size  ; i++){

        x2=  (TimeList[i]/TimeList[29])*width()  ;
        y2= height() - ValueList[i];
        //  qDebug() << "TimeList: " << TimeList[i] << " ValueList: " << ValueList[i];
        painter.drawLine(x0,y1,x2,y2);
        //painter.drawPoint(x0,y1);
        //painter.drawLine(0,0,300,300);
        x0 = x2;
        y1 = y2;
        qDebug() <<  "X: " << x0 << " Y1: " << y1;

    }


    TimeList.clear();
    ValueList.clear();




}

void Plotter::draw( std::vector<qint64> _TimeList, std::vector<int>_ValueList){
    double normTimeList [30];

    qDebug() << "draw Time: : " << _TimeList[0] << " draw Value: " << _ValueList[0];
    double x = _TimeList[0];
    if(x0 + _TimeList[0]*20 >= width() ){
        PrimPrint = true;
        x0 = 0;
    }


    if (PrimPrint)
        VarX = _TimeList[0];



    for(int i =0 ; i <30 ; i++){
        double x = _TimeList[i];
        //   qDebug() << "x: " << ( x- VarX )/1000 ; // 1 milliseconds/1000 = 1 microsec

        TimeList.push_back( (x -VarX )/1000 );
        // 1/ (1 + (e/3.5)^x)) adaptação feita para variar melhor entre 0 e 10, deixando o menor valor de  y = 0.5
        //   qDebug() << " função: " << (1 / (1 +  std::pow(e/3.5,_ValueList[i] )  ) ) * height() ;
        // qDebug() << "altura: " << height();
        ValueList.push_back(height()*0.05 + 4*_ValueList[i] );
    }
    PrimPrint = false;


    repaint();

}
