#include "dialog.h"
#include "plotter.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>

#include <string>
using namespace std;
#include <cmath>

#define n 11

extern void Gauss(double *matrix, double *vecb, double *vecx, int g);

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
  //elements
  QLabel* labelHeader = new QLabel(tr("Here we can set text ..."));
  pushButtonIC = new QPushButton(tr("Initial conditions"));
  pushButtonIC->setEnabled(false);
  pushButtonIC->setToolTip("This is to specify initial conditions for the PDE");
  pushButtonBC = new QPushButton(tr("Boundary conditions"));
  pushButtonBC->setEnabled(false);
  pushButtonMAT = new QPushButton(tr("Material conditions"));
  pushButtonMAT->setEnabled(false);
  pushButtonRUN = new QPushButton(tr("Run simulation"));
  //pushButtonRUN->setEnabled(false);
  pushButtonSHO = new QPushButton(tr("Show results"));
  pushButtonSHO->setEnabled(false);
  QLabel *label_ogs = new QLabel();
  label_ogs->setAlignment(Qt::AlignCenter);
  label_ogs->setPixmap(QPixmap("../s1.png"));
  //connect
  connect(pushButtonIC,SIGNAL(clicked()),this,SLOT(on_pushButtonIC_clicked()));
  connect(pushButtonBC,SIGNAL(clicked()),this,SLOT(on_pushButtonBC_clicked()));
  connect(pushButtonMAT,SIGNAL(clicked()),this,SLOT(on_pushButtonMAT_clicked()));
  connect(pushButtonRUN,SIGNAL(clicked()),this,SLOT(on_pushButtonRUN_clicked()));
  connect(pushButtonSHO,SIGNAL(clicked()),this,SLOT(on_pushButtonSHO_clicked()));
  //layout
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(label_ogs);
  mainLayout->addWidget(labelHeader);
  mainLayout->addWidget(pushButtonIC);
  mainLayout->addWidget(pushButtonBC);
  mainLayout->addWidget(pushButtonMAT);
  mainLayout->addWidget(pushButtonRUN);
  mainLayout->addWidget(pushButtonSHO);
  mainLayout->addStretch();
  setLayout(mainLayout);
  //memory
  out_file.open("out.txt");
  //out_file.setf(ios::scientific);
  out_file.precision(3);
//OK  n = 11;
  u_new.resize(n);
  u_old.resize(n);
  matrix = new double[n*n];
  vecb = new double[n];
  vecx = new double[n];
}

Dialog::~Dialog()
{
  delete [] matrix;
  delete [] vecb;
  delete [] vecx;
}

void Dialog::on_pushButtonIC_clicked()
{
  // 2 Anfangsbedingungen
  for(int x=0;x<n;x++)
  {
    u_old[x] = 0.;
  }
  pushButtonIC->setStyleSheet("background-color: green");
  pushButtonBC->setEnabled(true);
}

void Dialog::on_pushButtonBC_clicked()
{
  // 3 Randbedingungen
  double u_bc_l = 1.;
  double u_bc_r = 1.;
  u_new[0] = u_old[0] = u_bc_l;
  u_new[10] = u_old[10] = u_bc_r;
  pushButtonBC->setStyleSheet("background-color: green");
  pushButtonMAT->setEnabled(true);
}

void Dialog::on_pushButtonMAT_clicked()
{
  // 1 Datenstrukturen
  double alpha = 1.;
  dt = 1.;
  dx = 0.1;
  // 4 Formel
  dt = 0.5 * dx*dx / alpha; // Zeitschrittsteuerung
  Ne = alpha * dt / (dx*dx);
  pushButtonMAT->setStyleSheet("background-color: green");
  pushButtonRUN->setEnabled(true);
}

void Dialog::on_pushButtonRUN_clicked()
{
  // Anfangsbedingungen
  double x[n];
  for(int i=0;i<n;i++)
    x[i] = -100. + i*10.;
  for(int i=0;i<n;i++)
    bottom_elevation[i] = 0.04 - i*0.004;
  u_old[0]=0.244918436659073; //-100
  u_old[1]=0.243;             //-90
  u_old[2]=0.242293545352681; //-80
  u_old[3]=0.241;             //-70
  u_old[4]=0.240216955447788; //-60
  u_old[5]=0.235;             //-50
  u_old[6]=0.225684124843115; //-40
  u_old[7]=0.223;             //-30
  u_old[8]=0.220898136369048; //-20
  u_old[9]=0.201434531839821; //-10
  u_old[10]=0.1;              //0
  for(int x=0;x<n;x++)
  {
    u_old[x] = 0.25;
  }
  // Randbedingungen
  u_old[10] = 0.1; // Wasserstand flußabwärts [m]
  u_new[10] = 0.1; // Wasserstand flußabwärts [m]
  // Parameter
  double discharge = 0.05; // Volumenfließrate [m3/s]
  double gravity = 9.81; // [m/s2]
  double friction_law_exponent = 0.5; // Chezy, Manning-Strickler [-]
  double error_tolerance = 1e-3; // [m]
  double bed_slope = 0.0004; // [m/m]
  double bottom_width = 1.; // [m]
  double m = 1.; //
  double friction_coefficient = 10.; //
  // Nichtlineare Iteration
  // Diskretisierung
  double wetted_cross_section[n];
  double water_level_elevation[n];
  double flow_velocity[n];
  double Froude_number[n];
  double wetted_perimeter[n];
  double hydraulic_radius[n];
  double friction_slope[n];
  for(int i=0;i<n;i++)
  {
    wetted_perimeter[i] = bottom_width + 2.*sqrt(1.+m*m)*u_old[i];
    wetted_cross_section[i] = (bottom_width + m*u_old[i])*u_old[i];
    hydraulic_radius[i] = wetted_cross_section[i] / wetted_perimeter[i];
    water_level_elevation[i] = bottom_elevation[i] + u_old[i];
    flow_velocity[i] = discharge/wetted_cross_section[i];
    Froude_number[i] = flow_velocity[i]/(sqrt(gravity*wetted_cross_section[i]\
                       /sqrt(bottom_width*bottom_width+4.*m*wetted_cross_section[i])));
    friction_slope[i] = pow(flow_velocity[i]/(friction_coefficient*pow(hydraulic_radius[i],friction_law_exponent)),2);
  }
  // Test output
  out_file << "Water depth (old):\t\t";
  for(int i=0;i<n;i++)
  {
    out_file << "\t" << u_old[i] << " ";
  }
  out_file << endl;
  out_file << "Wetted perimeter:\t\t";
  for(int i=0;i<n;i++)
  {
    out_file << "\t" << wetted_perimeter[i] << " ";
  }
  out_file << endl;
  out_file << "Wetted cross section:\t";
  for(int i=0;i<n;i++)
  {
    out_file << "\t" << wetted_cross_section[i] << " ";
  }
  out_file << endl;
  out_file << "Hydraulic radius:\t\t";
  for(int i=0;i<n;i++)
  {
    out_file << "\t" << hydraulic_radius[i] << " ";
  }
  out_file << endl;
  out_file << "Water level elevation:\t";
  for(int i=0;i<n;i++)
  {
    out_file << "\t" << water_level_elevation[i] << " ";
  }
  out_file << endl;
  out_file << "Flow velocity:\t\t";
  for(int i=0;i<n;i++)
  {
    out_file << "\t" << flow_velocity[i] << " ";
  }
  out_file << endl;
  out_file << "Froude number:\t\t";
  for(int i=0;i<n;i++)
  {
    out_file << "\t" << Froude_number[i] << " ";
  }
  out_file << endl;
  out_file << "Friction slope:\t\t";
  for(int i=0;i<n;i++)
  {
    out_file << "\t" << friction_slope[i] << " ";
  }
  out_file << endl;
  //
  double N,N1,N2,N3,D,D1,D2,D21,D22;
  for(int i=0;i<n-1;i++)
  {
    N1 = pow(discharge,2)/pow(wetted_cross_section[i+1],2) + gravity*u_old[i+1];
    N2 = pow(discharge,2)/pow(wetted_cross_section[i],2) + gravity*u_old[i];
    N3 = gravity*(bed_slope - (friction_slope[i+1]+friction_slope[i])/2.)*(x[i+1]-x[i]);
    N = N1 - N2 - N3;
    D1 = pow(discharge,2)/pow(wetted_cross_section[i],3) * (bottom_width+2.*m*u_old[i]) - gravity;
    D21 = friction_law_exponent*2.*(sqrt(1+m*m))/wetted_perimeter[i];
    D22 = (1.+friction_law_exponent)/wetted_cross_section[i] * (bottom_width+2.*m*u_old[i]);
    D2 = gravity*friction_slope[i]*(D21-D22)*(x[i+1]-x[i]);
    D = D1 + D2;
    u_new[i] = u_old[i] - N/D;
  }
  out_file << "Water depth (new):\t\t";
  for(int i=0;i<n;i++)
  {
    out_file << "\t" << u_new[i] << " ";
  }
  out_file << endl;
  //
  pushButtonRUN->setStyleSheet("background-color: green");
  pushButtonSHO->setEnabled(true);
}

void Dialog::on_pushButtonSHO_clicked()
{
  Plotter *plotter = new Plotter;
  plotter->setWindowTitle(QObject::tr("My Function Plotter"));
  QVector<QPointF> points0;
  QVector<QPointF> points1;
  double x;
  for (int i=0;i<n;++i)
  {
    x = -100. + 10.*i;
    points0.append(QPointF(x,u_old[i]));
    points1.append(QPointF(x,u_new[i]));
  }
  plotter->setCurveData(0, points0);
  plotter->setCurveData(1, points1);
  PlotSettings settings;
  settings.minX = -100.0;
  settings.maxX = 0.0;
  settings.minY = 0.0;
  settings.maxY = 0.4;
  plotter->setPlotSettings(settings);
  plotter->show();
  pushButtonSHO->setStyleSheet("background-color: green");
}

