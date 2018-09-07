
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


#include "ActivationFunction.h"
#include <cmath> 
#include <iostream>


void  ActivationFunction::setParameter(ActivationParameter* ap)
{
	parameter = ap; 
}



double ActivationFunction::limit(int p, double input)
{
	
	double res; 

	switch (p)
	{
	   case 0:
	   case 1: 
	   case 2: 
	   case 3: 
	   case 4: 
	   
	   	  if (input > 1.0)
	   	  	return 1.0; 
	   	  if (input < -1.0)
	   	  	return -1.0; 
	   	  break; 
	   
	   case 5:
	   case 6: 
		   if (input > 1.0)
			   return 1.0;
		   if (input <= 0.0)
			   return 0.000001;
		   break; 
	   default:
	   	  return input;
	}

	return input; 

}



double ActivationFunction::calculateFunction(double input)
{
	
	double res; 	
	double inp;

	inp = input; 

	/*
	res = 	parameter->get(3) +
		(parameter->get(4)  *  pow(inp, parameter->get(6))) +
		 parameter->get(2)  *  exp(parameter->get(0) * pow(inp, parameter->get(5)) + parameter->get(1));
    */ 

	double zp = exp(parameter->get(0)   * input + parameter->get(1)); 
	double zm = exp(-(parameter->get(0) * input + parameter->get(1)));

	res = (zp - zm) / (zp + zm); 


	return res; 
}





double ActivationFunction::deriveX(double input)
{

	double res; 
	
//	double inp;
//	inp = ((input > 0.0) ? input : 0.000000001);
//		
//	res = 	(
//		parameter->get(4) *
//		parameter->get(6) *
//
//		pow(inp, parameter->get(6) - 1.0)) +
//		
//		(parameter->get(2) *
//			exp((parameter->get(0) *
//				pow(inp, parameter->get(5))) +
//				parameter->get(1)) *
//			parameter->get(0) *
//			parameter->get(6) *
//			pow(inp, parameter->get(5) - 1.0)
//			); 

	
	res = (1 - pow(calculateFunction(input), 2)) * parameter->get(0); 


	return res; 


}


double ActivationFunction::deriveAlpha(double input)
{
	double res; 
	// double inp;
	// inp = ((input > 0.0) ? input : 0.000000001);
	// 
	// return parameter->get(2) *
	// 	pow(inp, parameter->get(5)) *
	// 	exp(parameter->get(0) *
	// 		pow(inp, parameter->get(5)) +
	// 		parameter->get(1));

	res = (1 - pow(calculateFunction(input), 2)) * input;

	return res; 

}

double ActivationFunction::deriveBeta(double input)
{
	double res; 

/// 	double inp;
/// 	inp = ((input > 0.0) ? input : 0.000000001);
/// 
/// 
/// 	return  parameter->get(2) *
/// 		exp(parameter->get(0) *
/// 			pow(inp, parameter->get(5)) +
/// 			parameter->get(1));


	res = 1 - pow(calculateFunction(input), 2);

	return res; 
}

double ActivationFunction::deriveGamma(double input)
{
	double inp;
	inp = ((input > 0.0) ? input : 0.000000001);

	return exp(parameter->get(0) *
		         pow(inp, parameter->get(5)) +
		       parameter->get(1));
}

double ActivationFunction::deriveDelta(double input)
{
	return 1.0;
}

double ActivationFunction::deriveTheta(double input)
{

	double inp;
	inp = ((input > 0.0) ? input : 0.000000001);

	return pow(inp, parameter->get(6));
}

double ActivationFunction::deriveEta(double input)
{

	double res; 

	double inp; 
	inp = ((input > 0.0) ? input : 0.000000001); 

	res = parameter->get(0) * 
		   log(inp) * 
		   parameter->get(2) *
		   exp(parameter->get(0) *
			   pow(inp, parameter->get(5)) + 
			              parameter->get(1)) *
		   pow(inp, parameter->get(5));

	

	return res; 

}

double ActivationFunction::deriveNu(double input)
{
	double res; 
	double inp;
	inp = ((input > 0.0) ? input : 0.000001);
		
	res =	parameter->get(4) *
		    log(inp) * 
		    pow(inp, parameter->get(6));


	return res; 

}

double ActivationFunction::deriveP(int p, double input)
{
	switch (p)
	{
	   case 0:
		   return deriveAlpha(input); 
	   case 1:
		   return deriveBeta(input); 
	   case 2:
		   return deriveGamma(input);
	   case 3:
		   return deriveDelta(input);
	   case 4:
		   return deriveTheta(input);
	   case 5:
		   return deriveEta(input);
	   case 6:
		   return deriveNu(input);

	   default:
		   return 42; 
	}
}


// double alpha; 
// double beta;
// double gamma;
// double delta;
// double theta; 
// double eta; 
// double nu; 
