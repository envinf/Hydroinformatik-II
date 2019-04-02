#include "dialog.h"
#include "plotter.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>

#include <string>
using namespace std;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
  //1 elements
  QLabel* labelHeader = new QLabel(tr("Here we can set text ..."));
  pushButtonIC = new QPushButton(tr("Initial conditions"));
  pushButtonIC->setToolTip("This is to specify initial conditions for the PDE");
  pushButtonBC = new QPushButton(tr("Boundary conditions"));
  pushButtonBC->setEnabled(false);
  pushButtonMAT = new QPushButton(tr("Material conditions"));
  pushButtonMAT->setEnabled(false);
  pushButtonRUN = new QPushButton(tr("Run simulation"));
  pushButtonRUN->setEnabled(false);
  pushButtonSHO = new QPushButton(tr("Show results"));
  pushButtonSHO->setEnabled(false);
  pushButtonALL = new QPushButton(tr("Run all"));
  pushButtonALL->setEnabled(true);
  pushButtonALL->setStyleSheet("background-color: yellow");
  QLabel *label_title = new QLabel();
  label_title->setAlignment(Qt::AlignCenter);
  label_title->setPixmap(QPixmap("../bhywi-08-03_title.png"));
  QLabel *label_ogs = new QLabel();
  label_ogs->setAlignment(Qt::AlignCenter);
  label_ogs->setPixmap(QPixmap("../ogs_teaching_150.png"));
   //2 connect
  connect(pushButtonIC,SIGNAL(clicked()),this,SLOT(on_pushButtonIC_clicked()));
  connect(pushButtonBC,SIGNAL(clicked()),this,SLOT(on_pushButtonBC_clicked()));
  connect(pushButtonMAT,SIGNAL(clicked()),this,SLOT(on_pushButtonMAT_clicked()));
  //connect(pushButtonRUN,SIGNAL(clicked()),this,SLOT(on_pushButtonRUN_clicked()));
  connect(pushButtonRUN,SIGNAL(clicked()),this,SLOT(RunTimeLoop()));
  connect(pushButtonSHO,SIGNAL(clicked()),this,SLOT(on_pushButtonSHO_clicked()));
  connect(pushButtonALL,SIGNAL(clicked()),this,SLOT(on_pushButtonALL_clicked()));
  //3 layout
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(label_title);
//  mainLayout->addWidget(labelHeader);
  mainLayout->addWidget(pushButtonIC);
  mainLayout->addWidget(pushButtonBC);
  mainLayout->addWidget(pushButtonMAT);
  mainLayout->addWidget(pushButtonRUN);
  mainLayout->addWidget(pushButtonALL);
  //mainLayout->addWidget(pushButtonSHO);
  mainLayout->addWidget(label_ogs);
  mainLayout->addStretch();
  setLayout(mainLayout);
  //4 memory
  out_file.open("out.txt");
  nj = 101;
  nt = 100;
  u_new.resize(nj);
  u_old.resize(nj);
}

Dialog::~Dialog()
{
}

void Dialog::on_pushButtonIC_clicked()
{
  // 2 Anfangsbedingungen
  for(int x=0;x<nj;x++)
  {
    u_old[x] = 0.;
  }
  pushButtonIC->setStyleSheet("background-color: green");
  pushButtonBC->setEnabled(true);
  //QMessageBox msgBox;
  //msgBox.setText("Anfangsbedingungen werden gesetzt");
  //msgBox.exec();
}

void Dialog::on_pushButtonBC_clicked()
{
  // 3 Randbedingungen
  double u_bc_l = 3.;
  double u_bc_r = -1.;
  u_new[0] = u_old[0] = u_bc_l;
  u_new[nj-1] = u_old[nj-1] = u_bc_r;
  pushButtonBC->setStyleSheet("background-color: green");
  pushButtonMAT->setEnabled(true);
}

void Dialog::on_pushButtonMAT_clicked()
{
  // 1 Datenstrukturen
  double alpha = 1.;
  //dt = 1.;
  dx = 1./(nj-1);
  // 4 Formel
  //dt = 0.50 * dx*dx / alpha * 1.; // Zeitschrittsteuerung
  dt = 1.0 * dx*dx / alpha * 1.; // Zeitschrittsteuerung
  Ne = alpha * dt / (dx*dx);
  pushButtonMAT->setStyleSheet("background-color: green");
  pushButtonRUN->setEnabled(true);
}

void Dialog::on_pushButtonRUN_clicked()
{
  for(int x=1;x<nj-1;x++)
  {
    u_new[x] = u_old[x] + Ne * (u_old[x-1] - 2*u_old[x] + u_old[x+1]);
  }
  // 5 Ergebnisse schreiben HW#4
/*
  out_file << "dt = " << dt << endl;
  out_file << "Ne = " << Ne << endl;
  for(int x=0;x<n;x++)
  {
    out_file << x << ": " << u_new[x] << endl;
  }
  out_file.close();
*/
  pushButtonRUN->setStyleSheet("background-color: green");
  pushButtonSHO->setEnabled(true);
}

void Dialog::on_pushButtonSHO_clicked()
{
  Plotter *plotter = new Plotter;
  plotter->setWindowTitle(QObject::tr("My Function Plotter"));
  QVector<QPointF> points0;
  double x;
  for (int i=0;i<nj;++i)
  {
    x = dx*i;
    points0.append(QPointF(x,u_new[i]));
    out_file << x << ": " << u_new[i] << endl;
  }
  plotter->setCurveData(0, points0);
  PlotSettings settings;
  settings.minX = 0.0;
  settings.maxX = 1.0;
  settings.minY = 0.0;
  settings.maxY = 1.0;
  plotter->setPlotSettings(settings);
  plotter->show();
  pushButtonSHO->setStyleSheet("background-color: green");
}

void Dialog::RunTimeLoop()
{
  Plotter *plotter = new Plotter;
  plotter->setWindowTitle(QObject::tr("My Function Plotter"));
  PlotSettings settings;
  settings.minX = 0.0;
  settings.maxX = 1.0;
  settings.minY = -1.0;
  settings.maxY = 3.0;
  plotter->setPlotSettings(settings);
  double x;
  for(int t=0;t<nt;t++)
  {
    QVector<QPointF> points0;
    points0.append(QPointF(0,u_new[0]));
    for(int i=1;i<nj-1;i++)
    {
      u_new[i] = u_old[i] + Ne * (u_old[i-1] - 2*u_old[i] + u_old[i+1]);
      x = dx*i;
      points0.append(QPointF(x,u_new[i]));
    }
    x = dx*(nj-1);
    points0.append(QPointF(x,u_new[nj-1]));
    plotter->setCurveData(t, points0);
    plotter->show();
    // Daten speichern
    for(int i=1;i<nj-1;i++)
    {
      u_old[i] = u_new[i];
    }
  }
}

void Dialog::on_pushButtonALL_clicked()
{
  on_pushButtonIC_clicked();
  on_pushButtonBC_clicked();
  on_pushButtonMAT_clicked();
  RunTimeLoop();
}

/*
    QMessageBox msgBox;
  msgBox.setText("Ergebnisse geschrieben");
  msgBox.exec();
*/
