#include <vector>
#include <cmath>
#include <fstream>
using namespace std;
	
int main(int argc, char *argv[])
{
	// Datenstrukturen (dynamnisch)
	int n=11;
    vector<double> u_new, u_old;
	u_new.resize(n);
    u_old.resize(n);
	ofstream out_file;
	out_file.open("out.txt");
	ofstream out_python;
	out_python.open("out.csv");
    //out_file.setf(ios::scientific);
    out_file.precision(3);
    // Geometrie
	double x[n];
    for(int i=0;i<n;i++)
      x[i] = -100. + i*10.;
	double bottom_elevation[n];
    for(int i=0;i<n;i++)
      bottom_elevation[i] = 0.04 - i*0.004;
    // Anfangsbedingungen
    for(int x=0;x<n;x++)
    {
      u_old[x] = 0.25;
    }
    // Randbedingungen
    u_old[10] = 0.1; // Wasserstand flußabwärts [m]
    u_new[10] = 0.1; // Wasserstand flußabwärts [m]
    // Parameter (konstant)
	double discharge = 0.05; // Volumenfließrate [m3/s]
    double gravity = 9.81; // [m/s2]
    double friction_law_exponent = 0.5; // Chezy, Manning-Strickler [-]
    double error_tolerance = 1e-3; // [m]
    double bed_slope = 0.0004; // [m/m]
    double bottom_width = 1.; // [m]
    double m = 1.; //
    double friction_coefficient = 10.; //
    // Parameter (variabel)
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
//HA: Schreiben sie alle variablen Parameter in das File out_file
    // Berechnungsgrößen
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
    // Berechnung (1. Iteration des Newton-Verfahrens)
    // Ausgabe der Ergebnisse
      // File 
	out_file << "Water depth (new):\t\t";
    for(int i=0;i<n;i++)
    {
      out_file << "\t" << u_new[i] << " ";
    }
    out_file << endl;
      // für Python plot
    for(int i=0;i<n;i++)
    {
      out_python << x[i] << "," << u_new[i] << endl;
    }
    out_python.close();
}