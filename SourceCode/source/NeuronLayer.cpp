
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

#include "NeuronLayer.h"
#include <iostream>


NeuronLayer::NeuronLayer()
{
	init(2, 2); 
}

NeuronLayer::NeuronLayer(int i, int o)
{
	init(i, o);
}


void NeuronLayer::init(int inp, int out)
{

	
	for (int i = 0; i < inp; i++)
	{
		input.push_back(0.0); 

		std::vector<ActivationParameter*> hlp;
		
		for (int j = 0; j < out; j++)
		{
			hlp.push_back(new ActivationParameter()); 
		}
		parameter.push_back(hlp);
	}

	for (int j = 0; j < out; j++)
	{
		outp.push_back(0.1);
	}

}


void NeuronLayer::setNumberInputs(int n)
{}
void NeuronLayer::setNumberOutputs(int n)
{}

void NeuronLayer::setInput(std::vector<double> inp)
{
	input = inp; 
}

std::vector<double> NeuronLayer::getInput()
{
	return input;
}



std::vector<double> NeuronLayer::getOutput()
{
	return outp; 
}

void NeuronLayer::setParameter(int i, int j, ActivationParameter* ap)
{
	parameter[i][j] = ap; 
}

void NeuronLayer::setParameter(int i, int j, int k, double x)
{
	parameter[i][j]->set(k, x); 
}

ActivationParameter* NeuronLayer::getParameter(int i, int j)
{
	return parameter[i][j]; 
}


void NeuronLayer::applyForward()
{

	ActivationFunction af; 

	for (int j = 0; j < outp.size(); j++)
	{

		double hlp = 0.0; 
		for (int i = 0; i < input.size(); i++)
		{
			af.setParameter(parameter[i][j]); 

			double r = af.calculateFunction(input[i]);

			hlp = hlp + r; 

		}

		outp[j] = hlp / (double)input.size(); 

	}


}



void NeuronLayer::printParameter()
{
	
	

	for (int j = 0; j < outp.size(); j++)
	{
		for (int i = 0; i < input.size(); i++)
		{

			std::cout << "Parameter[" << i << "][" << j << "]  :: ";

			for (int k = 0; k < 2; k++)
			{
				std::cout << parameter[i][j]->get(k) << " ";
			}
			std::cout << std::endl;
		}
	    std::cout << " := " << outp[j] << " ; " << std::endl;
	}
	std::cout << std::endl;
	


}
