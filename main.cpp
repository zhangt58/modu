/*
This is the auxiliary program of laser-beam interaction in a magnetic element.
simple tracking through a dispersive chicane
Author: Tong ZHANG
e-mail: tzhang@sinap.ac.cn
Created Time: 23:18, Sep. 21th, 2011
Usage: main namelist
	 main: the compiled executable program
 namelist: file contains parameter setup, see namelist.example
*/

#include <iostream>
#include <fstream>
#include <map>
#include "chicane.h"
#include "transport.h"
#include "readinput.h"
#include "methods.h"

using namespace std;

int main(int argc, char *argv[])
{
	map<string, string> var;
	Chicane 	param_chi;
	scanPanel   param_scan; 	// scanPanel type
	auxParam 	param_auxp; 	// parameters should be set when scan feature enabled
	ifstream file;
	file.open(argv[1]);
	getfield(file, var);
	set_Chicane	 (param_chi , var);
	set_scanPanel(param_scan, var); // set scanPanel
	set_auxParam (param_auxp, var);

	if(param_chi.get_print())
	{
		param_scan.printall();    // print scanPanel
		param_auxp.printall(); 	  // print auxParam
		param_chi.printall ();    // print chicane setup
	}

	// initialize file streams
	ifstream infile; //data infile
	ofstream outfile; //data outfile
	set_filestream  (infile, outfile, var);
	check_filestream(infile, outfile);

	double *t0, *gam0, *x0, *y0, *betax0, *betay0; // initialize 6 1D arrays to dipct 6D phase space
	readdata(infile, param_chi, t0, gam0, x0, y0, betax0, betay0); // read initial phase space

	if(param_scan.get_sflag())
	{
		performScan(outfile, param_scan, param_chi, param_auxp, var, t0, gam0, x0, y0, betax0, betay0);
	}
	else
	{
		passChicane(param_chi, t0, gam0, x0, y0, betax0, betay0);
		dumpout(outfile, param_chi, t0, gam0, x0, y0, betax0, betay0);

		post_process sliceAnalysis;
		sliceAnalysis.set_nbins   (param_auxp.get_nbins  ());
		sliceAnalysis.set_pCharge (param_auxp.get_pCharge());
		sliceAnalysis.set_dataSize(param_chi.get_npart());
		sliceAnalysis.set_data(t0);

		unsigned int nbins = sliceAnalysis.get_nbins();
		double *histc_x1 = new double [nbins];
		double *histc_x2 = new double [nbins];
		double *histc_y  = new double [nbins];
		

		double peakcurrent = sliceAnalysis.get_peakCurrent();
		double bunching    = sliceAnalysis.get_bunching(param_auxp.get_nharm(), param_auxp.get_xlamds());

		histc_x1 = sliceAnalysis.get_histc_x1();
		histc_x2 = sliceAnalysis.get_histc_x2();
		histc_y  = sliceAnalysis.get_histc_y ();

		double   delt = sliceAnalysis.get_binWidth();
		unsigned totN = sliceAnalysis.get_dataSize();
		double   totC = sliceAnalysis.get_pCharge();
		double   coef = totC/totN/delt;

		ofstream histfile;
		histfile.open((var.find("currentfilename")->second).c_str());
		histfile.precision(16);
		histfile.width(24);
		histfile << std::left;

		cout << "Peak Current: "    << peakcurrent << " Amp" << endl;
		cout << "Bunching factor: " << bunching    << endl;

		histfile << "#Peak Current: "    << peakcurrent << " Amp" << endl;
		histfile << "#Bunching factor: " << bunching    << endl;
		histfile << "#Total Charge: " 	 << totC 		<< "C"    << endl;
		histfile << "#Total Particle: "  << totN 		<< endl;
		histfile << "#slice width: " 	 << delt 		<< "sec"  << endl;

		histfile << std::scientific;
		for(unsigned int i = 0; i< nbins; i++)
		{
			histfile << histc_x1[i] << " " << histc_x2[i] << " " << histc_y[i] << " " << histc_y[i]*coef << "\n";
		}
		histfile.close();
	}

	unset_filestream(infile, outfile); // close file streams

	return 0;
}
