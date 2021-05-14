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
  //2-Berechnung und //3-Ausgabe
  //y = sin(pi*x) * exp(-alpha*t^2)
  for (int i = 0; i < numPoints+1; ++i)
  {
    x = double(i)/double(numPoints);
    y=sin(PI*x) * exp(-alpha*PI*PI*t);
    out_file << x << "," << y << std::endl;
  }
}