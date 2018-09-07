#pragma once

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


// double alpha; 
// double beta;
// double gamma;
// double delta;
// double theta; 
// double eta; 
// double nu; 

class ActivationFunction
{

private:
	ActivationParameter* parameter; 


public:

	void setParameter(ActivationParameter* ap); 

	double calculateFunction(double input); 
	double deriveX(double input);

	double deriveAlpha(double input);
	double deriveBeta (double input);
	double deriveGamma(double input);
	double deriveDelta(double input);
	double deriveTheta(double input);
	double deriveEta( double input);
	double deriveNu( double input);
	double deriveP(int p, double input);

	double limit(int, double);

};
