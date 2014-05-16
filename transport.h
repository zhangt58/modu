#ifndef _TRANSPORT_H
#define _TRANSPORT_H

#include "chicane.h"
#include <fstream>
#include <map>

double func_mean(double *a, int size);

void readdata(std::ifstream &infile, Chicane &param_chi, double* &t0, double* &gam0, double* &x0, double* &y0, double* &betax0, double* &betay0);

void passChicane(Chicane &param_chi, double* &t0, double* &gam0, double* &x0, double* &y0, double* &betax0,double* &betay0);

void dumpout(std::ofstream &outfile, Chicane &param_chi, double *t0, double *gam0, double *x0, double *y0, double *betax0, double *betay0);

void performScan(std::ofstream &outfile, scanPanel &param_scan, Chicane &param_chi, auxParam &param_auxp, std::map <std::string, std::string> &var, double *t0, double *gam0, double *x0, double *y0, double *betax0, double *betay0);

void check_scansetup(std::string scanparam, double scanbegin, double scanstep, double scanend);

int check_scanparam(std::string scanparam);

double *copyArray(double *a, unsigned int size);

#endif //_TRANSPORT_H
