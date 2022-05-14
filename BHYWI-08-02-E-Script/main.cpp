#include <cmath>
#include <fstream>
#define PI 3.14159265358979323846

int main(int argc, char *argv[])
{
  //1-Definitionen
  int numPoints = 1000;
  double x,y,alpha=1.,t=0.01;
  std::ofstream out_file;
  out_file.open("out.csv");
  //2-Berechnung
  //y = sin(pi*x) * exp(-alpha*t^2)
  for (int i = 0; i < numPoints+1; ++i)
  {
    x = double(i)/double(numPoints);
    //y=sin(PI*x) * exp(-alpha*t*t);
    //y=sin(sqrt(PI*alpha)*x) * exp(-PI*t);
    //y=sin(PI/sqrt(alpha)*x) * exp(-PI*PI*t);
    y=sin(PI*x) * exp(-alpha*PI*PI*t);
    out_file << x << "," << y << std::endl;
  }
  //3-Ausgabe
}
//HW1 Lösung: y=sin(sqrt(pi*alpha)*x) * exp(-pi*t) plotten
//HW2 Lösung: y=sin(pi/sqrt(alpha)*x) * exp(-pi*pi*t) plotten
//HW3 Lösung: y=sin(pi*x) * exp(-alpha*pi*pi*t) plotten
//HW4 Lösungen vergleichen
//HW5 Verschiedene Zeiten (aus Eingabedatei) lesen und rechnen
