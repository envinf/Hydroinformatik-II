#include <QApplication>
#include <QLabel>
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  //  QLabel *label = new QLabel("<h1><i>Hello<!i>""<font color=red>Qt!</font></h1>");
  QLabel *label = new QLabel("<h1>Hallo Hydroinformatik II 2019. Wir nutzen GitHub für die Übungen</h1>");
  label->show();
  return app.exec();
}

