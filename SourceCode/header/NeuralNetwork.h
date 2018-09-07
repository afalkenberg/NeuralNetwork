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

#include "LearningNeuronLayer.h"
#include <vector>

class NeuralNetwork
{

private:

	std::vector<double> input;
	std::vector<double> output;
	std::vector<LearningNeuronLayer*> NN;
	std::vector<double> outputError; 
	std::vector<double> inputError; 

public: 

	// a vector with number of nodes shall sufficient to initialize a neural network // 
	void defineNetwork(std::vector<int> v);
	// return network definition 
	std::vector<int> getNetworkDefinition(); 

	// then we can also predefine parameters // 
	void defineParameter(int y, int i, int j, ActivationParameter* ap); 
	// and read the paramters back //
	ActivationParameter* getParameter(int y, int i, int j); 

	// set learning rate , for now it is all the same throughout the layers // 
	void setLearningRate(std::vector<double> lr); 

	void setInput(std::vector<double> inp); 
	void applyForward(); 
	std::vector<double> getOutput(); 

	// and the backward process //
	void setExpected(std::vector<double> inp); 
	void applyBackward(bool); 

	void printParameter(); 

};
