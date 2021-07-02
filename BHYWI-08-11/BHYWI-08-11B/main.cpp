#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QTime>
#include "dialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
/*
  //...........................................................
  QPixmap pixmap ("../E9.jpg");
  QSplashScreen splash(pixmap);
  splash.show();
  splash.showMessage(QObject::tr("Übung E9 wird geladen..."), Qt::black);
  QTime dieTime = QTime::currentTime().addSecs(3); while( QTime::currentTime() < dieTime )  \
                  QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
                  // Warte-Funktion (http://lists.trolltech.com/qt-interest/2007-01/thread00133-0.html)
*/
  //...........................................................
  Dialog w;
  //splash.finish(&w); //test
  w.setWindowTitle("Newton Simulator");
  w.setFixedWidth(300);
  w.show();

  return a.exec();
}

