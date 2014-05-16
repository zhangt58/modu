#include "chicane.h"
#include <iomanip>
#include <cmath>
#include <iostream>

//chicane
void Chicane::set_npart(unsigned int n)
{
	npart = n;
}

void Chicane::set_field(double x)
{
	bend_field = x;
}

void Chicane::set_blength(double x)
{
	bend_length = x;
}

void Chicane::set_dlength(double x)
{
	drift_length = x;
}

void Chicane::set_print(bool flag)
{
	print_list = flag;
}

unsigned int Chicane::get_npart()
{
	return npart;
}

double Chicane::get_field()
{
	return bend_field;
}

double Chicane::get_blength()
{
	return bend_length;
}

double Chicane::get_dlength()
{
	return drift_length;
}

bool Chicane::get_print()
{
	return print_list;
}

void Chicane::printall()
{
	std::cout << std::left;
	std::cout << "------------------------------\n";
	std::cout << "Chicane:\n";
	std::cout << std::setw(16) << "total particle: " << std::setw(12) << npart        <<"\n";
	std::cout << std::setw(16) << "bend_field: "     << std::setw(12) << bend_field   <<"\n";
	std::cout << std::setw(16) << "bend_lenfth: "    << std::setw(12) << bend_length  <<"\n";
	std::cout << std::setw(16) << "drift_lenfth: "   << std::setw(12) << drift_length << std::endl;
	std::cout << "------------------------------\n\n";

}

double Chicane::r56(double gam0)
{
	double theta;
	theta = asin(bend_length*bend_field*E0/M0/C0/sqrt(gam0*gam0-1));
	return -2*theta*theta*(drift_length+2.0/3.0*bend_length);
}

void Chicane::disperse(double &t0, double &gam0, double &x0, double &y0, double &betax0, double &betay0, double &r56val, double &gam0_avg)
{
	t0 +=(r56val/C0*(gam0/gam0_avg-1.0));
}

/*************************************************************************************\
\*************************************************************************************/

//scanPanel
void scanPanel::set_sflag(bool flag)
{
	scan_flag = flag;
}

void scanPanel::set_secho(bool flag)
{
	scan_echo = flag;
}

void scanPanel::set_sparam(std::string str)
{
	scan_param = str;
}

void scanPanel::set_sbegin(double x)
{
	scan_begin = x;
}

void scanPanel::set_sstep(double x)
{
	scan_step = x;
}

void scanPanel::set_send(double x)
{
	scan_end = x;
}

void scanPanel::set_spfunc(bool flag)
{
	scan_pfunc = flag;
}

bool scanPanel::get_sflag()
{
	return scan_flag;
}

bool scanPanel::get_secho()
{
	return scan_echo;
}

std::string scanPanel::get_sparam()
{
	return scan_param;
}

double scanPanel::get_sbegin()
{
	return scan_begin;
}

double scanPanel::get_sstep()
{
	return scan_step;
}

double scanPanel::get_send()
{
	return scan_end;
}

bool scanPanel::get_spfunc()
{
	return scan_pfunc;
}

void scanPanel::printall()
{
	std::cout << std::left;
	std::cout << "------------------------------\n";
	std::cout << "scanPanel:\n";
	std::cout << std::setw(16) << "scan_flag: " << std::setw(12) << scan_flag << "\n";
	if(scan_flag)
	{
		std::cout << std::setw(16) << "scan_param: " << std::setw(12) << scan_param << "\n";
		std::cout << std::setw(16) << "scan_begin: " << std::setw(12) << scan_begin << "\n";
		std::cout << std::setw(16) << "scan_step: "  << std::setw(12) << scan_step  << "\n";
		std::cout << std::setw(16) << "scan_end: "   << std::setw(12) << scan_end   << "\n";
		std::cout << std::setw(16) << "scan_echo: "  << std::setw(12) << scan_echo  << std::endl;
	}
	std::cout << "------------------------------\n\n";
}

/*************************************************************************************\
\*************************************************************************************/

//auxParam

void auxParam::set_nharm(unsigned int n)
{
	nharm = n;
}

void auxParam::set_nbins(unsigned int n)
{
	nbins = n;
}

void auxParam::set_xlamds(double x)
{
	xlamds = x;
}

void auxParam::set_pCharge(double x)
{
	pCharge = x;
}

unsigned int auxParam::get_nharm()
{
	return nharm;
}

unsigned int auxParam::get_nbins()
{
	return nbins;
}

double auxParam::get_xlamds()
{
	return xlamds;
}

double auxParam::get_pCharge()
{
	return pCharge;
}

void auxParam::printall()
{
	std::cout << std::left;
	std::cout << "------------------------------\n";
	std::cout << "Other needed parameters:\n";
	std::cout << std::setw(16) << "seed_wavelenth:" << std::setw(12) << xlamds  << "\n";
	std::cout << std::setw(16) << "total_charge:"   << std::setw(12) << pCharge << "\n";
	std::cout << std::setw(16) << "nbins:"          << std::setw(12) << nbins   << "\n";
	std::cout << std::setw(16) << "nharm:"          << std::setw(12) << nharm   << std::endl; 
	std::cout << "------------------------------\n\n";
}



