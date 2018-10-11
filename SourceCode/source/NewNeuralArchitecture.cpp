

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




// NewNeuralArchitecture.cpp : Defines the entry point for the console application.
//



// -fr input file name
// -fw output file name 
// -l0 learning rate 0
// -l1 learning rate 1 
// -n0 number neurons inner layer 0
// -n1 number neurons inner layer 1
// -n2 number neurons inner layer 2

// if -nx is not specified there is no inner layer 






#include "ActivationFunction.h"
#include "ActivationParameter.h"

#include "LearningNeuronLayer.h"

#include "NeuralNetwork.h"
#include "FileReader.h"

#include "ParameterFileReader.h"

#include <iostream>

#include "LearningLoop.h"

#include "ArgumentParser.h"



std::vector<double> createInput(int nr)
{

	std::vector<double>  inp(3);

	if (nr == 0)
	{
		inp[0] = -1.0;
		inp[1] = -1.0;
		inp[2] = -1.0; 

	}
	if (nr == 1)
	{
		inp[0] = 1.0;
		inp[1] = -1.0;
		inp[2] = -1.0;

	}


	if (nr == 2)
	{
		inp[0] = -1.0;
		inp[1] = 1.0;
		inp[2] = -1.0;

	}
	if (nr == 3)
	{
		inp[0] = 1.0;
		inp[1] = 1.0;
		inp[2] = -1.0;

	}
	

	if (nr == 4)
	{
		inp[0] = -1.0;
		inp[1] = -1.0;
		inp[2] = 1.0;

	}
	if (nr == 5)
	{
		inp[0] = 1.0;
		inp[1] = -1.0;
		inp[2] = 1.0;

	}

	if (nr == 6)
	{
		inp[0] = -1.0;
		inp[1] = 1.0;
		inp[2] = 1.0;

	}
	if (nr == 7)
	{
		inp[0] = 1.0;
		inp[1] = 1.0;
		inp[2] = 1.0;

	}




	return inp; 
}


std::vector<double> createExpected(int nr)
{

	std::vector<double>  exp(8); 

	for (int i = 0; i < 8; i++)
	{
		exp[i] = -1.0;
	}
	exp[nr] = 1.0;

	return exp; 
}




int main(int argc, char* argv[])
{


	ArgumentParser AG; 
	AG.setInput(argc, argv);



	FileReader FR;
	FileReader FRT;

	LearningLoop LL;




	// prepare training samples // 
	std::vector<std::vector<double> > expected;
	std::vector<std::vector<double> > input;

	std::vector<std::vector<double> > expectedTest;
	std::vector<std::vector<double> > inputTest;



	std::vector<double> learningRate; 
        learningRate.push_back(0.4);
        learningRate.push_back(0.3);


	// we can have as many layers with diffent nodes as we want // 
	
	std::vector<int> n;  //  = { 784, 100, 10 };

    
	// our perceptron needs 2 learning rates will write a paper to explain difference 
	// to exisiting perceptrons 

	if (AG.check("-l0"))
	{
		learningRate[0] = AG.getDouble("-l0"); 
	}
	
	if (AG.check("-l1"))
	{
		learningRate[1] = AG.getDouble("-l1");
	}


	// the first layer has 784 nodes which is for MINST //
	n.push_back(784);
	
	// if we use the -n0 parameter with a following number we can add another layer //
	if (AG.check("-n0"))
	{
		n.push_back(AG.getInt("-n0"));
	}

	// with the -n1 parameter we can add a second inner layer //
	if (AG.check("-n1"))
	{
		n.push_back(AG.getInt("-n1"));
	}
	// with the -n2 parameter we can add a third inner layer // 
	if (AG.check("-n2"))
	{
		n.push_back(AG.getInt("-n2"));
	}

	// we can extend this and add as many inner layers as we want // 


	// then the last layer is again fixed to 10 nodes as defined by MINST example // 
	n.push_back(10);


	std::cout << "Learning Rate : " << learningRate[0] << " " << learningRate[1] << std::endl;
	std::cout << "inner Nodes " << std::endl;
	for (int i = 0; i < n.size(); i++)
	{
		std::cout << "nodes " << n[i] << std::endl;
	}


        // number of samples to learn (default 10000 so not enough) 
        //
        
        int numSamples = 10000; 
 
        if(AG.check("-N"))
	{
	   numSamples = AG.getInt("-N"); 	
	}
	/* MINST example  */


	FR.readImages(10000, 784);
	FR.readLabels(10000);

	FRT.readImages(1000, 784);
	FRT.readLabels(1000);


	expected     = FR.getAllLabels();
	input        = FR.getAllImages();

	expectedTest = FRT.getAllLabels();
	inputTest    = FRT.getAllImages();



	// we use expected and input for both training and testing // 

	NeuralNetwork* NET;

	std::string fr = "netWrk99.txt";
	

	// the following section reads an existing network definition from a file // 
	if (AG.check("-fr"))  // overrules some of the other parameters // 
	{

		std::cout << " file name ? " << AG.getString("-fr") << std::endl;

		fr = AG.getString("-fr");
	    
		std::cout << fr << std::endl; 


	    ParameterFileReader pread;
	    
	    std::cout << " file name ? " << fr << std::endl;
	    
	    pread.setFileName(fr);
	    std::cout << " .. " << std::endl;
	    pread.readNetwork();
	    std::cout << " ... " << std::endl;
	    NET = pread.getNetwork();
	    std::cout << " .... " << std::endl;
    }

	else  // starting a new network with all new random parameters // 
	{
		NET = new NeuralNetwork(); 
		NET->defineNetwork(n);
	}

	// now we can define the neural network // 
	// we defined the learning loop as LL // 
	// add the neural network definition in which is in NET //
	// then the training set which is in input with the expected results // 
	// then the test set with expected results // 

	LL.setNeuralNetwork(NET); 
	LL.setTrainingVectors(input, expected); 

	LL.setTestVectors(inputTest, expectedTest);
	LL.setLearningRate(learningRate); 

    // lets train and check the result always // 

	bool betterThan70 = false; 

	// the following loop calls the learning Steps 
	// we have a batch size of 5 so avery 5 steps the weights are updated. (i.e. true) 
	// otherwise we only accumulate interim results 


	for (int i = 0; i < numSamples; i++)
	{

		if (i % 5 == 0) // batch size of 5 in this case
		{
			LL.learningStep(true);
		}
		else
		{
			LL.learningStep(false);
		}


		std::cout << "."; 

		if ((i % 100 == 0) || ((i % 10 == 0 ) && (betterThan70 == true)))
		{

			double cc = LL.checkCorrect(); 
			std::cout << std::endl; 
			std::cout << i << " := " << cc * 100.0 << "%" << std::endl;
			if (cc > 0.7)
			{
				betterThan70 = true; 
			}
			else
			{
				betterThan70 = false; 
			}
		}
	}

	// now once the network is learned we can write it back in a file //
	ParameterFileReader para;
	para.setNetwork(NET); 


	std::string fw = "netWrk99.txt";

	// parameter -fw provides a name to write the result // 

	if (AG.check("-fw"))
	{
		fw = AG.getString("-fw"); 
	}

	para.setFileName(fw);  // and overwriting theresults  // 

	para.writeNetwork(); 

	char x; 
	std::cin >> x; 


	return 0;

}



