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

#include <vector>
#include <iostream>

#include "NeuralNetwork.h"

class LearningLoop
{
private: 

	NeuralNetwork* NET;

	// this is used for training // 
	std::vector<std::vector<double> >  trainingSet;
	std::vector<std::vector<double> >  trainingLabel;


	// this is used for testing // 
	std::vector<std::vector<double> >  testSet;
	std::vector<std::vector<double> >  testLabel;

    std::vector<double> learningRate; 

	int selectCheckFunction;   // =0 


public: 


        LearningLoop(); 
 
	void setNeuralNetwork(NeuralNetwork* n); 
	void setTrainingVectors(std::vector<std::vector<double> >, std::vector<std::vector<double> >);
	void setTestVectors(std::vector<std::vector<double> >, std::vector<std::vector<double> >);
	void setLearningRate(std::vector<double> x); 

	bool learningStep(bool); 

	bool checkOutput(std::vector<double> exp, std::vector<double> output); 
	bool checkOutputWinner(std::vector<double> exp, std::vector<double> output); 
	bool checkOutputThreshold(std::vector<double> expected, std::vector<double> output); 

	double checkCorrect();   // as percentage ( ? ) 



};

