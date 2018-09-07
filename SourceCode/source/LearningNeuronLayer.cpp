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

#include "LearningNeuronLayer.h"
#include <iostream> 



LearningNeuronLayer::LearningNeuronLayer()
{

	//init(2, 2); 
}


LearningNeuronLayer::LearningNeuronLayer(int i, int j):NeuronLayer(i,j)
{
	initGradient();
}


void LearningNeuronLayer::setOutputError(std::vector<double> oe)
{
	outputError = oe; 
}

std::vector<double> LearningNeuronLayer::getOutputError()
{
	return outputError;
}


void LearningNeuronLayer::setLearningRate(std::vector<double> lr)
{
	learningRate = lr;
}


void LearningNeuronLayer::setExpected(std::vector<double> ex)
{

	outputError.resize(outp.size());


	for (int i = 0; i < ex.size(); i++)
	{
		outputError[i] = ex[i] - outp[i]; 

	}

}


std::vector<double> LearningNeuronLayer::getInputError()
{
	return inputError; 
}


void LearningNeuronLayer::initGradient()
{

	for (int i = 0; i < input.size(); i++)
	{
		std::vector<ActivationParameter*> hlp;
		std::vector<ActivationParameter*> accuHlp; 

		for (int j = 0; j < outp.size(); j++)
		{
			hlp.push_back(new ActivationParameter());
			accuHlp.push_back(new ActivationParameter(0.0, 0.0)); 
		}
		gradient.push_back(hlp);
		accumulatedParameter.push_back(accuHlp); 
	}

}





void LearningNeuronLayer::calculateGradient()
{
	// the input is given 
	// the error at the output is given 
	// then this error is applied each parameter using the gradient function of that particular parameter at position x

	// initGradient(); 

	 

	for (int j = 0; j < outp.size(); j++)
	{

		for (int i = 0; i < getInput().size(); i++)
		{
			activation.setParameter(parameter[i][j]);
                                                                                                         
			for (int k = 0; k < 2; k++)   // was 7 now 2 
			{
				double gra = activation.deriveP(k, input[i]);
 
				gradient[i][j]->set(k, gra);
			}
			 
		}
	}
}
 

void LearningNeuronLayer::applyBackward(bool withUpdate)
{
	

	for (int j = 0; j < outp.size(); j++)
	{
		for (int i = 0; i < getInput().size(); i++)
		{
			
			for (int k = 0; k < 2; k++)    // was 7 now 2
			{

				double p   =   parameter[i][j]->get(k); 
				double err =   outputError[j];
				double g   =   gradient[i][j]->get(k);

				accumulatedParameter[i][j]->set(k, accumulatedParameter[i][j]->get(k) + err*g*learningRate[k]);
				
				if (withUpdate == true)
				{
					parameter[i][j]->set(k, p + accumulatedParameter[i][j]->get(k));   // here we need to interfere with batch learning 
					accumulatedParameter[i][j]->set(k, 0.0); 
				}
			}
		}
	}

}





// the backpropagation is really the error which is propagated backward // 


void LearningNeuronLayer::propagateError()
{
	
	ActivationFunction af;
	inputError.resize(input.size());  // inputError initialization
	
	for (int i = 0; i < getInput().size(); i++)
	{
		double hlp = 0.0; 
		for (int j = 0; j < outp.size(); j++)
		{
			af.setParameter(parameter[i][j]);
			// calculate derivate at [i,j] for x // 
			double err = outputError[j];
		    hlp = hlp + err * af.deriveX(input[i]);   	
		}

		inputError[i] = hlp / outp.size();  

	}


}



void LearningNeuronLayer::printGradient()
{
	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < outp.size(); j++)
		{
			for (int k = 0; k < 2; k++)  // was 7 
			{
				std::cout << gradient[i][j]->get(k) << " "; 
			}
			std::cout << " ; ";
		}
		std::cout << std::endl;
	}
}


