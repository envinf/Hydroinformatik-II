#include <QApplication>
#include <QLabel>
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QLabel *label = new QLabel("<h1><i>Hello<!i>""<font color=red>Qt!</font></h1>");
  label->show();
  return app.exec();
}

