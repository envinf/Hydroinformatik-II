#include <QApplication>
#include "plotter.h"
#include <cmath>
#define PI 3.14159265358979323846

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  //
  int numPoints = 100;
  double x,y,alpha=1.,t=10.;
  //
  QVector<QPointF> points0;
  // y = sin(pi*x) * exp(-alpha*t^2)
  for (int i = 0; i < numPoints+1; ++i)
  {
    x = double(i)/double(numPoints);
    y = sin(PI*x) * exp(-alpha*t*t);
    points0.append(QPointF(i,y));
  }
  //
  Plotter plotter;
  plotter.setWindowTitle(QObject::tr("Function Plotter"));
  plotter.setCurveData(0, points0);
  PlotSettings settings;
  settings.minX = 0.0;
  settings.maxX = 100.0;
  settings.minY = 0.0;
  settings.maxY = 1.0;
  plotter.setPlotSettings(settings);
  plotter.show();
  return app.exec();
}

//HW3 Umschreiben für double x
//HW4 vernünftige Werte für a und b setzen
