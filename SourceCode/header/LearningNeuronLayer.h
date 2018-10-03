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

#include "NeuronLayer.h"
#include <vector>

class LearningNeuronLayer : public NeuronLayer
{

   private: 
	   std::vector<double> outputError;  // this will be calculated by forward  
	   std::vector<double> inputError;   // this will be calculated by backward 

	   std::vector<std::vector<ActivationParameter*> > gradient; 

	   std::vector<std::vector<ActivationParameter*> > accumulatedParameter;  // for batch training 

	   void initGradient(); 

	   ActivationFunction activation;
	   std::vector<double> learningRate; // = { 0.04, 0.013 };  // 0.0001 ok 


   public: 

	   LearningNeuronLayer();
	   LearningNeuronLayer(int i, int j); 

	   void setOutputError(std::vector<double> oe);
	   void setExpected(std::vector<double> ex); 
	   std::vector<double> getOutputError();

	   std::vector<double> getInputError(); 

	   void calculateGradient(); 
	   void applyBackward(bool withUpdate);   // call this first to update the weights based on the output error (batch == false)
	   void propagateError();  // then we can also calculate estimated errors on the input 

	   void printGradient(); 

	   void setLearningRate(std::vector<double>); 
};
