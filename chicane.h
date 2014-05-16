#ifndef _CHICANE_H
#define _CHICANE_H

#include <string>

const double M0   = 9.10938188E-31;     // electron mass, [kg]
const double E0   = 1.60218E-19;        // electron charge, [coulomb]
const double C0   = 299792458.0;        // light speed, [meter/sec]
const double PI   = 3.141592653589793;  // pi

class Chicane
{
	private:
		double bend_field,   // dipole magnetic field
			   bend_length,  // dipole length
			   drift_length; // drift length between dipole#1#2 or dipole#3#4
		unsigned npart; 	 // particle number
		bool print_list; 	 // if print variable list
	public:
		double r56(double gam0);
		void set_npart  (unsigned int n);
		void set_field  (double x);
		void set_blength(double x);
		void set_dlength(double x);
		unsigned int get_npart();
		double get_field  ();
		double get_blength();
		double get_dlength();

		void set_print(bool flag);
		bool get_print();
	
		void printall();
	
		void disperse(double &t0, double &gam0, double &x0, double &y0, double &betax0, double &betay0, double &r56val, double &gam0_avg);
};

class scanPanel
{
	private:
		bool scan_flag; 				// scan_flag = 1, do scan parameter, or not
		bool scan_echo; 				// scan_echo = 1, print scanning result to stdout, otherwise, do not print
		bool scan_pfunc; 				// panelty function, 1: bunching_n; 0: peak current
		std::string scan_param; 		// specify the parameter name to scan
		double scan_begin, scan_step, scan_end; // specify the scan range, beginning ,step and ending
	public:
		void set_sflag   (bool flag);
		void set_secho   (bool flag);
		void set_sparam  (std::string str);
		void set_sbegin  (double x);
		void set_sstep   (double x);
		void set_send    (double x);
		void set_spfunc  (bool flag);

		bool  	 	 get_sflag   ();
		bool  		 get_secho   ();
		std::string  get_sparam  ();
		double 		 get_sbegin  ();
		double 		 get_sstep   ();
		double 		 get_send    ();
		bool 		 get_spfunc  ();
		void 		 printall    ();
};

class auxParam
{
	private:
		unsigned int nharm; 		// bunching harmonic number
		unsigned int nbins; 		// nbins for histogram
		double xlamds; 			// seed wavelength, [m]
		double pCharge; 			// total charge, [C]
	public:
		void set_nharm  (unsigned int n);
		void set_nbins  (unsigned int n);
		void set_xlamds (double x);
		void set_pCharge(double x);
		unsigned int get_nharm  ();
		unsigned int get_nbins  ();
		double 		 get_xlamds ();
		double 		 get_pCharge();
		void 		 printall   ();
};

#endif //_CHICANE_H
