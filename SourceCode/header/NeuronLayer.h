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
#include "ActivationFunction.h"
#include <vector>

class NeuronLayer
{

	protected: 
		std::vector<std::vector<ActivationParameter*> > parameter; 
		std::vector<double> input;
		std::vector<double> outp;

	public:

		NeuronLayer(); 
		NeuronLayer(int i, int o); 

		void init(int i, int o); 

		void setNumberInputs(int n); 
		void setNumberOutputs(int n);

		void setInput(std::vector<double> inp); 
		std::vector<double> getInput(); 
		std::vector<double> getOutput(); 
		void setParameter(int i, int j, ActivationParameter*); 
		void setParameter(int i, int j, int k, double x); 
		ActivationParameter* getParameter(int i, int j); 
		void applyForward(); 
		void printParameter();
};

