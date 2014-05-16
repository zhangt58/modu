#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <map>
#include <iomanip>
#include "chicane.h"
#include "readinput.h"

void trimline(std::string &str) // trim leading and tailing whitespaces or ",'
{
	size_t pos1, pos2;
	pos1 = str.find_first_not_of(" \t\n\"\';,");
	pos2 = str.find_last_not_of (" \t\n\"\';,");
	str  = str.substr(pos1, pos2-pos1+1);
}

void getfield(std::ifstream &infile, std::map <std::string, std::string> & var)
{
	std::string line, vname, value;
	while(getline(infile, line))
	{
		if(line.empty())continue;
		trimline(line);
		if(line[0] == '#' || line[0] == '!' || line[0] == '/')continue;
		std::istringstream sline(line);
		getline(sline, vname, '=');
		getline(sline, value, '=');
		trimline(vname);
		trimline(value);
		var[vname] = value.c_str();
	}
}

void printlist(std::map <std::string, std::string> & var)
{
	int i = 0;
	std::map <std::string, std::string> :: iterator it;
	for(it = var.begin(); it != var.end(); it++,++i)
		std::cout << std::left << std::setw(18) << it->first << " ==> " << std::setw(18) << std::setprecision(6)<< it->second << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "Total " << i << " records printed.\n" << std::endl;
}

void set_Chicane(Chicane &param_chi, std::map <std::string, std::string> & var)
{
	param_chi.set_npart  (atoi((var.find("npart"       )->second).c_str()));
	param_chi.set_field  (atof((var.find("bend_field"  )->second).c_str()));
	param_chi.set_blength(atof((var.find("bend_length" )->second).c_str()));
	param_chi.set_dlength(atof((var.find("drift_length")->second).c_str()));
	param_chi.set_print  (atoi((var.find("print_list"  )->second).c_str()));
}

/*
void set_elementType(elementType &param_ele, std::map <std::string, std::string> & var)
{
	param_ele.set_flag (var.find("use_element")->second);
	param_ele.set_print(atoi((var.find("print_list")->second).c_str()));
	param_ele.set_npart(atoi((var.find("npart")->second).c_str()));
}
*/

void set_scanPanel(scanPanel &param_scan, std::map <std::string, std::string> & var)
{
	param_scan.set_sparam  (      var.find("scan_param")->second);
	param_scan.set_sflag   (atoi((var.find("scan_flag" )->second).c_str()));
	param_scan.set_secho   (atoi((var.find("scan_echo" )->second).c_str()));
	param_scan.set_sbegin  (atof((var.find("scan_begin")->second).c_str()));
	param_scan.set_sstep   (atof((var.find("scan_step" )->second).c_str()));
	param_scan.set_send    (atof((var.find("scan_end"  )->second).c_str()));
	param_scan.set_spfunc  (atoi((var.find("scan_pfunc")->second).c_str()));
}


void set_auxParam(auxParam &param_auxp, std::map <std::string, std::string> & var)
{
	param_auxp.set_xlamds (atof((var.find("seed_wavelength")->second).c_str()));
	param_auxp.set_pCharge(atof((var.find("total_Charge"   )->second).c_str()));
	param_auxp.set_nbins  (atoi((var.find("nbins"          )->second).c_str()));
	param_auxp.set_nharm  (atoi((var.find("nharm"          )->second).c_str()));
}

/*
void set_dipole(dipole &param_dipole, std::map <std::string, std::string> & var)
{
	param_dipole.set_field (atof((var.find("dipole_field" )->second).c_str()));
	param_dipole.set_length(atof((var.find("dipole_length")->second).c_str()));
	param_dipole.set_nstep (atoi((var.find("dipole_nstep" )->second).c_str()));
	param_dipole.set_type  (atoi((var.find("dipole_type"  )->second).c_str()));
}

void set_undulator(undulator &param_undulator, std::map <std::string, std::string> & var)
{
	param_undulator.set_field (atof((var.find("undulator_field" )->second).c_str()));
	param_undulator.set_period(atof((var.find("undulator_period")->second).c_str()));
	param_undulator.set_nstep (atoi((var.find("undulator_nstep" )->second).c_str()));
	param_undulator.set_num   (atoi((var.find("undulator_num"   )->second).c_str()));
}
*/

void set_filestream(std::ifstream &infile, std::ofstream &outfile, std::map <std::string, std::string> & var)
{
	infile.open ((var.find("infilename" )->second).c_str());
	outfile.open((var.find("outfilename")->second).c_str());
}

void check_filestream(std::ifstream &infile, std::ofstream &outfile)
{
	if ( !infile || !outfile )
	{
		std::cout << "File can not open, please check 'infilename' and 'outfilename' in namelist!" << std::endl;
		exit(1);
	}
}

void unset_filestream(std::ifstream &infile, std::ofstream &outfile)
{
	infile.close();
	outfile.close();
}

/*
unsigned int set_whichelement(elementType &param_eletype, dipole &param_dipole, undulator &param_undulator, std::map <std::string, std::string> & var)
{
	std::string flag = param_eletype.get_flag();
	if(flag == "dipole")
	{
		set_dipole(param_dipole, var);
		return 0;
	}
	else if(flag == "undulator")
	{
		set_undulator(param_undulator, var);
		return 1;
	}
	else
	{
		std::cout << "Please specify the 'use_element' in namelist file explicitly!" << std::endl;
		exit(1);
	} 
}
*/

void refresh_var(std::string vname, double value, Chicane &param_chi, auxParam &param_auxp, std::map <std::string, std::string> & var)
{
	var.find(vname)->second = dbl2str(value);
	set_Chicane (param_chi , var);
	set_auxParam(param_auxp, var);
}

std::string dbl2str(double &x)
{
	std::stringstream sstr;
	sstr << x;
	return sstr.str();
}
