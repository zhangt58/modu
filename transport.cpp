#include "chicane.h"
#include "readinput.h"
#include "transport.h"
#include "methods.h"
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>

double func_mean(double *a, int size)
{
    double s=0;
    for(int i=0; i<size; i++)s+=*(a+i);
    return s/double(size);
}

void readdata(std::ifstream &infile, Chicane &param_chi, double* &t0, double* &gam0, double* &x0, double* &y0, double* &betax0, double* &betay0)
{
	unsigned int npart = param_chi.get_npart();
	double *ptrt0      = new double[npart];
	double *ptrgam0    = new double[npart];
	double *ptrx0      = new double[npart];
	double *ptry0      = new double[npart];
	double *ptrbetax0  = new double[npart];
	double *ptrbetay0  = new double[npart];
	for(unsigned int i = 0; i< npart; i++)
	{
		infile >> ptrt0[i];
		infile >> ptrgam0[i];
		infile >> ptrx0[i];
		infile >> ptry0[i];
		infile >> ptrbetax0[i];
		infile >> ptrbetay0[i];
	}
	infile.close();
	t0   	= ptrt0;
	gam0 	= ptrgam0;
	x0   	= ptrx0;
	y0   	= ptry0;
	betax0  = ptrbetax0;
	betay0  = ptrbetay0;
}

void passChicane(Chicane &param_chi, double* &t0, double* &gam0, double* &x0, double* &y0, double* &betax0,double* &betay0)
{
	unsigned int npart = param_chi.get_npart();
	double gam0_avg=func_mean(gam0, npart);
	double r56 = param_chi.r56(gam0_avg);
//	std::cout << "R56: " << r56 << "m" << std::endl;
	for(unsigned int i = 0; i< npart; i++ )
	{
		param_chi.disperse(t0[i],gam0[i],x0[i],y0[i],betax0[i],betay0[i],r56,gam0_avg);
	}
}

void dumpout(std::ofstream &outfile, Chicane &param_chi, double *t0, double *gam0, double *x0, double *y0, double *betax0, double *betay0)
{
	unsigned int npart = param_chi.get_npart();
	outfile << std::left;
	outfile << std::scientific;
	outfile.precision(16);
	outfile.width(20);
	for(unsigned int i=0;i<npart;i++)
		outfile << t0[i] << "\t" << gam0[i] << "\t" << x0[i] << "\t" << y0[i] << "\t" << betax0[i] << "\t" << betay0[i] << std::endl;
}

void performScan(std::ofstream &outfile, scanPanel &param_scan, Chicane &param_chi, auxParam &param_auxp, std::map <std::string, std::string> &var, double *t0, double *gam0, double *x0, double *y0, double *betax0, double *betay0)
{
	std::string scanparam  = param_scan.get_sparam();
	double      scanbegin  = param_scan.get_sbegin();
	double      scanstep   = param_scan.get_sstep ();
	double      scanend    = param_scan.get_send  ();
	int 		scanecho   = param_scan.get_secho ();
	int 		nharm  	   = param_auxp.get_nharm ();
	double 		xlamds     = param_auxp.get_xlamds();
	unsigned int npart     = param_chi.get_npart();
	double      gam0_avg   = func_mean(gam0, npart);
	double 	   *tmp_t0 	   = new double [npart];
	double 	   *tmp_gam0   = new double [npart];
	double 	   *tmp_x0 	   = new double [npart];
	double 	   *tmp_y0 	   = new double [npart];
	double 	   *tmp_betax0 = new double [npart];
	double 	   *tmp_betay0 = new double [npart];
	check_scansetup(scanparam, scanbegin, scanstep, scanend);
	double pfunc_val; // panelty function value

	post_process sliceAnalysis;
	sliceAnalysis.set_dataSize( param_chi.get_npart  ());

	for(double vscan = scanbegin;vscan <= scanend;vscan += scanstep)
	{
		if(scanecho)
		{
			std::cout << std::left << std::setw(10) << scanparam << " = " << std::setw(10) << vscan << "\n";
		}
		refresh_var(scanparam, vscan, param_chi, param_auxp, var);

		sliceAnalysis.set_nbins   (param_auxp.get_nbins  ());
		sliceAnalysis.set_pCharge (param_auxp.get_pCharge());
		
		tmp_t0     = copyArray(t0    , npart);
		tmp_gam0   = copyArray(gam0  , npart);
		tmp_x0     = copyArray(x0    , npart);
		tmp_y0     = copyArray(y0    , npart);
		tmp_betax0 = copyArray(betax0, npart);
		tmp_betay0 = copyArray(betay0, npart);
		passChicane(param_chi, tmp_t0, tmp_gam0, tmp_x0, tmp_y0, tmp_betax0, tmp_betay0);//use tmp arrays!
		
		sliceAnalysis.set_data(tmp_t0);

		if(param_scan.get_spfunc())//1:bunching factor[n]
		{
			pfunc_val = sliceAnalysis.get_bunching(nharm, xlamds);
		}
		else //0:peak current
		{
			pfunc_val = sliceAnalysis.get_peakCurrent();
		}
		outfile.precision(16);
		outfile.width(10);
		outfile << std::left;
		outfile << std::scientific;
		outfile << vscan <<" "<< pfunc_val << " " << param_chi.r56(gam0_avg) << "\n";
		delete[] tmp_t0;
		delete[] tmp_gam0;
		delete[] tmp_x0;
		delete[] tmp_y0;
		delete[] tmp_betax0;
		delete[] tmp_betay0;
	}
	outfile.close();
}

void check_scansetup(std::string scanparam, double scanbegin, double scanstep, double scanend)
{
	
	if(!check_scanparam(scanparam))
	{
		std::cout << "Scan parameter name setting error!\n";
		exit(1);
	}

	if(scanstep<0 || scanend < scanbegin)
	{
		std::cout << "Scan range setup error!\n";
		exit(1);
	}
}

int check_scanparam(std::string scanparam)
{
	int ifind = 0;
	std::string AllScanParam[6] = { "bend_length",
							 	    "bend_field",
							 	    "drift_length",
									"seed_wavelength",
									"nharm",
									"nbins"};

	for(int i=0;i<6;i++)
	{
		if(AllScanParam[i]==scanparam)ifind = 1;
	}

	return ifind;
}

double *copyArray(double *a, unsigned int size)
{
	double *b = new double [size];
	for(unsigned int i = 0; i< size; i++)b[i]=a[i];
	return b;
}

