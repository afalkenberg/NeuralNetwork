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


#include "NeuralNetwork.h"
#include <iostream>


void NeuralNetwork::defineNetwork(std::vector<int> v)
{
	// we have v.size() - 1 Layers 
	
	input.resize(v[0]); 
	output.resize(v[v.size() - 1]); 

	NN.resize(v.size() - 1);

	// create each layer now // 
	for (int i = 0; i < v.size() - 1; i++)
	{
		LearningNeuronLayer* nl = new LearningNeuronLayer(v[i], v[i + 1]); 
		NN[i] = nl; 
	}

}


std::vector<int>  NeuralNetwork::getNetworkDefinition()
{
	std::vector<int> netDef; 
	int numLay = NN.size(); 
	netDef.push_back(NN[0]->getInput().size()); 
	for (int i = 0; i < numLay; i++)
	{
		netDef.push_back(NN[i]->getOutput().size()); 
	}

	return netDef; 

}


void NeuralNetwork::setLearningRate(std::vector<double> lr)
{
	for (int i = 0; i < NN.size(); i++)
	{
		NN[i]->setLearningRate(lr); 
	}

}


void NeuralNetwork::defineParameter(int y, int i, int j, ActivationParameter* ap)
{
	NN[y]->setParameter(i, j, ap); 
}

ActivationParameter* NeuralNetwork::getParameter(int y, int i, int j)
{
	ActivationParameter* res; 
	res = NN[y]->getParameter(i, j);

	return res; 
}

void NeuralNetwork::setInput(std::vector<double> inp)
{
	inp.resize(input.size()); 

	input = inp; 


	//for (int i = 0; i < input.size(); i++)
	//{
	//	std::cout << input[i] << " " << std::endl; 
	//}


}

void NeuralNetwork::applyForward()
{
	
	std::vector<double> temp = input; 

	for (int i = 0; i < NN.size(); i++)
	{
		NN[i]->setInput(temp); 
		NN[i]->applyForward(); 
		temp = NN[i]->getOutput(); 
	}
	output = temp; 
}



std::vector<double> NeuralNetwork::getOutput()
{
	return output;  
}

// and the backward process //
void NeuralNetwork::setExpected(std::vector<double> ex)
{
	
	outputError.resize(output.size());

	//std::cout << outputError.size() << " <> " << ex.size() << std::endl; 

	for (int i = 0; i < ex.size(); i++)
	{
		outputError[i] = ex[i] - output[i] ;


//		if (ex[i] - output[i] < 0.0)
//		{
//			outputError[i] = -1.0;             ///   = ex[i] - output[i];
//		}
//		else
//		{
//			outputError[i] = 1.0; 
//		}
	}


}


void NeuralNetwork::applyBackward(bool withUpdate)
{

	std::vector<double>  tempErr; 
	tempErr  = outputError;


	for (int i = NN.size() - 1; i >= 0; i--)
	{

		NN[i]->setOutputError(tempErr);  // set error in the output layer 
		NN[i]->calculateGradient(); // we calculate the gradient first // 

		// NN[i]->printGradient(); 

 		NN[i]->applyBackward(withUpdate);     // assumes that output error is already set // 
		NN[i]->propagateError();    // then we calculate the error at the input // 
		tempErr = NN[i]->getInputError();  // set tempErr which then is used for the next layer //
		
	}

}



void NeuralNetwork::printParameter()
{
	std::cout << " -------- Parameters --------" << std::endl; 
	for (int i = 0; i < NN.size(); i++)
	{
		std::cout << " ---- Layer " << i << " ------- " << std::endl; 
		NN[i]->printParameter(); 
	}

}
