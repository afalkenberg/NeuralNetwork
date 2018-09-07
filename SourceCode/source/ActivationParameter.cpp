
//  Created by Andreas Falkenberg on 9/01/18.
//  Copyright (c) 2018 Andreas Falkenberg. All rights reserved.
//
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#include "ActivationParameter.h"
#include <cstdlib>

ActivationParameter::ActivationParameter()
{

	// srand(99);

	double h = ((double)(rand() % 1000) / 1000.0) - 0.5;  ;
	set(0, h); 

	h = ((double)(rand() % 1000) / 1000.0) - 0.5;
	set(1, h);

	/*
	h = ((double)(rand()  % 1000) / 1000.0) - 0.5;
	set(2, h);

	h = ((double)(rand() % 1000) / 1000.0) - 0.5;
	set(3, h);

	h = ((double)(rand() % 1000) / 1000.0) - 0.5;
	set(4, h);

	h = (double)(rand() % 1000) / 1000.0f;
	set(5, h);

	h = (double)(rand() % 1000) / 1000.0f;
	set(6, h);
	*/ 
}


ActivationParameter::ActivationParameter(double a, double b) // , double c, double d, double e, double f, double g)
{
	set(0, a);
	set(1, b);

	/*
	set(2, c);
	set(3, d);
	set(4, e);
	set(5, f);
	set(6, g);
	*/ 
}


void ActivationParameter::set(int i, double k)
{
	par[i] = k; 
}

double ActivationParameter::get(int i)
{
	return par[i]; 
}
