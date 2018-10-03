
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

#include "LearningLoop.h"
#include <stdlib.h>






LearningLoop::LearningLoop()
{
   selectCheckFunction = 0;

}


void LearningLoop::setNeuralNetwork(NeuralNetwork* n)
{
	NET = n; 
}


void LearningLoop::setLearningRate(std::vector<double> x)
{
	 learningRate = x;

}


void LearningLoop::setTrainingVectors(std::vector<std::vector<double> > ts, std::vector<std::vector<double> > tl)
{
	trainingSet    = ts; 
	trainingLabel  = tl; 
}

void LearningLoop::setTestVectors(std::vector<std::vector<double> > ts, std::vector<std::vector<double> > tl)
{
	testSet = ts;
	testLabel = tl;
}


bool  LearningLoop::checkOutput(std::vector<double> exp, std::vector<double> output)
{
	if (selectCheckFunction == 0)
	{
		return checkOutputWinner(exp, output);
	}
	else
	{
		return checkOutputThreshold(exp, output);
	}
}



bool LearningLoop::learningStep(bool withUpdate)
{

	// NET->printParameter();

	// pick a random training sample // 
	int nr = (int)rand() % trainingSet.size();
	std::vector<double> inp = trainingSet[nr];
	std::vector<double> exp = trainingLabel[nr];

	NET->setLearningRate(learningRate); 

	NET->setInput(inp);
	NET->applyForward();
	std::vector<double> out = NET->getOutput();

	NET->setExpected(exp);

	bool corr = checkOutput(exp, out);    // I think this is for reporting only // 
	
	
	NET->applyBackward(withUpdate);                 // propagates the error and reset                //

	return corr; 

}



double LearningLoop::checkCorrect()
{

	// check all four
	bool res = true;

	int numSam = testSet.size(); 

	int resCounter = 0; 

	for (int ca = 0; ca < numSam; ca++)
	{
		
		std::vector<double> inp = testSet[ca];
		std::vector<double> exp = testLabel[ca];

		NET->setInput(inp);
		NET->applyForward();
		std::vector<double> out = NET->getOutput();

		bool corr = checkOutput(exp, out);  // is ca other wise 

		if (corr == true)
		{
			resCounter++; 
		}

		

	}

	return (double)resCounter / (double)numSam; 
	             
}








// there is only one maximum number which is denoted as +1 in expected all others are -1 in exp // 
// the result is true if the max number in exp is also the max identified then we are good     //
// so basically we search for the maximum in both and if they agree return true // 

bool LearningLoop::checkOutputWinner(std::vector<double> exp, std::vector<double> output)
{

	// this only gives +1 to the highest and assumes there is always one answer // 

	int mOut = -1;
	int mExp = -1; 
	double maxOut = -2.0;
	double maxExp = -2.0; 

	for (int i = 0; i < output.size(); i++)
	{
		if (output[i]  >  maxOut)
		{
			maxOut  = output[i];
			mOut = i; 
		}

		if (exp[i] > maxExp)
		{
			maxExp = exp[i]; 
			mExp = i; 
		}


	}

	if (mOut == mExp)
	{
		return true;
	}
	else
	{
		return false;
	}
}




bool LearningLoop::checkOutputThreshold(std::vector<double> expected, std::vector<double> output)
{
	// this one checks which output is > 0 and < 0
	for (int i = 0; i < output.size(); i++)
	{
		 

		if (output[i] > 0.0)
		{
			if (expected[i] == -1.0)
			{
				return false;
			}
		}
		else  // output < 0
		{
			if (expected[i] == 1.0)
			{
				return false;
			}
		}
	}


	return true;

}

