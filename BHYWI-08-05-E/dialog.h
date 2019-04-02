#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog> //modified
#include <vector>
#include <fstream>
using namespace std;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

private:
  double dx;
  vector<double> u_new, u_old;
  int n;
  ofstream out_file;
  double Ne;
  double dt;
  QPushButton* pushButtonIC;
  QPushButton* pushButtonBC;
  QPushButton* pushButtonMAT;
  QPushButton* pushButtonRUN;
  QPushButton* pushButtonSHO;
  double* matrix;
  double* vecb;
  double* vecx;
  double* bottom_elevation;

private slots:
    void on_pushButtonIC_clicked();
    void on_pushButtonSHO_clicked();
    void on_pushButtonRUN_clicked();
    void on_pushButtonBC_clicked();
    void on_pushButtonMAT_clicked();
};

#endif // DIALOG_H
