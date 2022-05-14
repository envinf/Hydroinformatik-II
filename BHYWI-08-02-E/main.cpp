#include <QApplication>
#include "plotter.h"
#include <cmath>
#define PI 3.14159265358979323846

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  //
  int numPoints = 100;
  double x,y,alpha=1.,t;
  //
  QVector<QPointF> points0;
  QVector<QPointF> points1;
  QVector<QPointF> points2;
  // y = sin(pi*x) * exp(-alpha*t^2)
  for (int i = 0; i < numPoints+1; ++i)
  {
    x = double(i)/double(numPoints);
    t = 0.001;
    y = sin(PI*x) * exp(-alpha*t*t);
    points0.append(QPointF(x,y));
    t = 0.5;
    y = sin(PI*x) * exp(-alpha*t*t);
    points1.append(QPointF(x,y));
    t = 5.;
    y = sin(PI*x) * exp(-alpha*t*t);
    points2.append(QPointF(x,y));
  }
  //
  Plotter plotter;
  plotter.setWindowTitle(QObject::tr("BHYWI-08-02-E: Function Plotter"));
  plotter.setCurveData(2, points0);
  plotter.setCurveData(1, points1);
  plotter.setCurveData(0, points2);
  PlotSettings settings;
  settings.minX = 0.0;
  settings.maxX = 1.0;
  settings.minY = 0.0;
  settings.maxY = 1.0;
  plotter.setPlotSettings(settings);
  plotter.show();
  return app.exec();
}

//HW1 Weiter Kurve plotten (t=0.01)
//HW3 Umschreiben für double x
//HW4 vernünftige Werte für a und b setzen
