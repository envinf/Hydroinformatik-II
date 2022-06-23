#include "dialog.h"
#include "plotter.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>

//ToDo2014
#include <cmath>

#include <string>
using namespace std;

extern void Gauss(double *matrix, double *vecb, double *vecx, int g);

#define PI 3.14159265358979323846

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
  pushButtonRUN = new QPushButton(tr("Run time step"));
  pushButtonRUN1 = new QPushButton(tr("Run simulation"));
  pushButtonRUN2 = new QPushButton(tr("Continue simulation"));
  //pushButtonRUN->setEnabled(false);
  QLabel *label_title = new QLabel();
  label_title->setAlignment(Qt::AlignCenter);
  label_title->setPixmap(QPixmap("../bhywi-08-04_title.png"));
  QLabel *label_ogs = new QLabel();
  label_ogs->setAlignment(Qt::AlignCenter);
  label_ogs->setPixmap(QPixmap("../ogs_teaching_150.png"));
  //connect
  connect(pushButtonIC,SIGNAL(clicked()),this,SLOT(on_pushButtonIC_clicked()));
  connect(pushButtonBC,SIGNAL(clicked()),this,SLOT(on_pushButtonBC_clicked()));
  connect(pushButtonMAT,SIGNAL(clicked()),this,SLOT(on_pushButtonMAT_clicked()));
  connect(pushButtonRUN,SIGNAL(clicked()),this,SLOT(RunTimeStep()));
  connect(pushButtonRUN1,SIGNAL(clicked()),this,SLOT(RunTimeLoop()));
  connect(pushButtonRUN2,SIGNAL(clicked()),this,SLOT(ContinueTimeLoop()));
  //layout
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(label_title);
  mainLayout->addWidget(labelHeader);
  mainLayout->addWidget(pushButtonIC);
  mainLayout->addWidget(pushButtonBC);
  mainLayout->addWidget(pushButtonMAT);
  mainLayout->addWidget(pushButtonRUN);
  mainLayout->addWidget(pushButtonRUN1);
  mainLayout->addWidget(pushButtonRUN2);
  mainLayout->addWidget(label_ogs);
  mainLayout->addStretch();
  setLayout(mainLayout);
  //memory
  out_file.open("out.txt");
  n = 101;
  u_new.resize(n);
  u_old.resize(n);
  matrix = new double[n*n];
  vecb = new double[n];
  vecx = new double[n];
  nt = 10;
  nexttimestep = false;
  u_bc_l=-2;
  u_bc_r=3;
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
  u_new[0] = u_old[0] = u_bc_l;
  u_new[n-1] = u_old[n-1] = u_bc_r;
  pushButtonBC->setStyleSheet("background-color: green");
  pushButtonMAT->setEnabled(true);
}

void Dialog::on_pushButtonMAT_clicked()
{
  // 1 Datenstrukturen
  double alpha = 1.;
  //dt = 0.01;
  dx = 1./(n-1);
  // 4 Formel
  dt = 0.5 * dx*dx / alpha ; // Zeitschrittsteuerung
  //dt = 0.0001;
  Ne = alpha * dt / (dx*dx);
  pushButtonMAT->setStyleSheet("background-color: green");
  pushButtonRUN->setEnabled(true);
}

void Dialog::RunTimeStep()
{
  if(!nexttimestep)
  {
    on_pushButtonIC_clicked();
    on_pushButtonBC_clicked();
    on_pushButtonMAT_clicked();
  }
  nexttimestep = true;
  Plotter *plotter = new Plotter;
  plotter->setWindowTitle(QObject::tr("My Function Plotter"));
  PlotSettings settings;
  settings.minX = 0.0;
  settings.maxX = 1.0;
  settings.minY = u_bc_l;
  settings.maxY = u_bc_r;
  plotter->setPlotSettings(settings);
  double x;
    QVector<QPointF> points0;
    points0.append(QPointF(0,u_new[0]));
    AssembleEquationSystem();
    Gauss(matrix,vecb,vecx,n);
    for(int i=0;i<n;i++)
    {
      u_new[i] = vecx[i];
      x = dx*i;
      points0.append(QPointF(x,u_new[i]));
    }
    plotter->setCurveData(9, points0);
    plotter->show();
    // Daten speichern
    for(int i=1;i<n-1;i++)
    {
      u_old[i] = u_new[i];
    }
}

void Dialog::RunTimeLoop()
{
  on_pushButtonIC_clicked();
  on_pushButtonBC_clicked();
  on_pushButtonMAT_clicked();
  Plotter *plotter = new Plotter;
  plotter->setWindowTitle(QObject::tr("My Function Plotter"));
  PlotSettings settings;
  settings.minX = 0.0;
  settings.maxX = 1.0;
  settings.minY = u_bc_l;
  settings.maxY = u_bc_r;
  plotter->setPlotSettings(settings);
  double x;
  for(int t=0;t<nt;t++)
  {
    QVector<QPointF> points0;
    points0.append(QPointF(0,u_new[0]));
    AssembleEquationSystem();
    Gauss(matrix,vecb,vecx,n);
    for(int i=0;i<n;i++)
    {
      u_new[i] = vecx[i];
      x = dx*i;
      points0.append(QPointF(x,u_new[i]));
    }
    plotter->setCurveData(t, points0);
    plotter->show();
    // Daten speichern
    for(int i=1;i<n-1;i++)
    {
      u_old[i] = u_new[i];
    }
  }
}

void Dialog::ContinueTimeLoop()
{
  Plotter *plotter = new Plotter;
  plotter->setWindowTitle(QObject::tr("My Function Plotter"));
  PlotSettings settings;
  settings.minX = 0.0;
  settings.maxX = 1.0;
  settings.minY = u_bc_l;
  settings.maxY = u_bc_r;
  plotter->setPlotSettings(settings);
  double x;
  for(int t=0;t<nt;t++)
  {
    QVector<QPointF> points0;
    points0.append(QPointF(0,u_new[0]));
    AssembleEquationSystem();
    Gauss(matrix,vecb,vecx,n);
    for(int i=0;i<n;i++)
    {
      u_new[i] = vecx[i];
      x = dx*i;
      points0.append(QPointF(x,u_new[i]));
    }
    plotter->setCurveData(t, points0);
    plotter->show();
    // Daten speichern
    for(int i=1;i<n-1;i++)
    {
      u_old[i] = u_new[i];
    }
  }
}

void Dialog::AssembleEquationSystem()
{
  int i,j;
  // Matrix entries
  for(i=0;i<n;i++)
  {
    vecb[i] = u_old[i];
    for(j=0;j<n;j++)
    {
      matrix[i*n+j] = 0.0;
      if(i==j)
        matrix[i*n+j] = 1. + 2.*Ne;
      else if(abs((i-j))==1)
        matrix[i*n+j] = - Ne;
    }
  }
  // Treat boundary conditions
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
    {
      if(i==0||i==n-1)
        matrix[i*n+j] = 0.0;
    }
  for(i=0;i<n;i++)
  {
    if(i!=0&&i!=n-1)
      continue;
    for(j=0;j<n;j++)
    {
       if(i==j)
         matrix[i*n+j] = 1.0;
       else
         matrix[i*n+j] = 0.0;
    }
  }
  // Matrix output
  for(i=0;i<n;i++)
  {
    for(j=0;j<n;j++)
    {
      out_file << matrix[i*n+j] << " ";
    }
    out_file << "b:" << vecb[i] << " ";
    out_file << endl;
  }
}

void Dialog::AnalyticalSolution()
{
/*
  for (int i = 0; i < numPoints+1; ++i)
  {
    x = double(i)/double(numPoints);
    t = 0.3;
    y = sin(PI*x) * exp(-alpha*t*t);
    points0.append(QPointF(x,y));
*/
}

/*
    QMessageBox msgBox;
  msgBox.setText("Ergebnisse geschrieben");
  msgBox.exec();
*/

void Dialog::on_pushButtonRUN_clicked()
{
  on_pushButtonIC_clicked();
  if(!nexttimestep) on_pushButtonBC_clicked();
  nexttimestep = true;
  on_pushButtonMAT_clicked();
  AssembleEquationSystem();
  Gauss(matrix,vecb,vecx,n);
  for(int i=0;i<n;i++)
  {
    u_new[i] = vecx[i];
  }
  // 5 Ergebnisse schreiben HW#4
  out_file << "dt = " << dt << endl;
  out_file << "Ne = " << Ne << endl;
  for(int i=0;i<n;i++)
  {
    out_file << i << ": " << vecx[i] << endl;
  }
  out_file.close();
  pushButtonRUN->setStyleSheet("background-color: green");
}

void Dialog::on_pushButtonSHO_clicked()
{
  Plotter *plotter = new Plotter;
  plotter->setWindowTitle(QObject::tr("My Function Plotter"));
  QVector<QPointF> points0;
  QVector<QPointF> points1;
  QVector<QPointF> points2;
  double x,u_ana,u_exp;
  double alpha=1;
  for (int i=0;i<n;++i)
  {
    x = dx*i;
    points0.append(QPointF(x,u_new[i]));
    out_file << x << ": " << u_new[i] << endl;
    u_ana = sin(PI*x) * exp(-alpha*dt*dt);
    points1.append(QPointF(x,u_ana));
  }
  plotter->setCurveData(0, points0);
  plotter->setCurveData(1, points1);
  plotter->setCurveData(2, points2);
  PlotSettings settings;
  settings.minX = 0.0;
  settings.maxX = 1.0;
  settings.minY = 0.0;
  settings.maxY = 2.0;
  plotter->setPlotSettings(settings);
  plotter->show();
}
