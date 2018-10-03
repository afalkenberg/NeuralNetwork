
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


#include "ParameterFileReader.h"

#include "FileReader.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>


ParameterFileReader::ParameterFileReader()
{
   fileName = "neuronalNetDescription.what"; 
}



void ParameterFileReader::setFileName(std::string f)
{
	fileName = f; 
}


void ParameterFileReader::setNetwork(NeuralNetwork* nn)
{
	NET = nn; 

}


NeuralNetwork* ParameterFileReader::getNetwork()
{

	return NET; 
}


void ParameterFileReader::readNetwork()
{

	NET = new NeuralNetwork(); 

	std::cout << "in read Network " << fileName << std::endl;
	std::ifstream file(fileName.c_str(), std::ios::binary);

	//  number of layers 
	int numberLayers; 
	// read number of layers // 
	file.read((char*)&numberLayers, sizeof(numberLayers));

	std::vector<int> ndef(numberLayers);  

	

	for (int layer = 0; layer < numberLayers; layer++)
	{
		int lSize;
		file.read((char*)&lSize, sizeof(lSize));   // read size of each layer
        ndef[layer] = lSize; 
	}
 
	NET->defineNetwork(ndef);
 
	for (int layer = 0; layer < numberLayers - 1; layer++)
	{
		for (int j = 0; j < ndef[layer + 1]; j++)
		{
			for (int i = 0; i < ndef[layer]; i++)
			{
				//double a = NET.getParameter(layer, i, j)->get(0);
				//double b = NET.getParameter(layer, i, j)->get(1);

				double a; 
				double b; 
				file.read((char*)&a, sizeof(a));
				file.read((char*)&b, sizeof(b));

				ActivationParameter* ap = new ActivationParameter(a, b); 

				NET->defineParameter(layer, i, j, ap);  
				
				std::cout << a << " " << b << std::endl;

			}
		}

	}


	file.close();


}
 

void ParameterFileReader::writeNetwork()
{
	std::ofstream file(fileName.c_str(), std::ios::binary);

	//  number of layers 

	std::vector<int> ndef = NET->getNetworkDefinition(); 

	// go through all layers and pull the parameters out // 


	int numberLayers = ndef.size(); 

	// write number of layers // 
	file.write((char*)&numberLayers, sizeof(numberLayers));
	
	for (int layer = 0; layer < numberLayers; layer++)
	{
		int lSize = ndef[layer];
		file.write((char*)&lSize, sizeof(lSize));
	}

	for (int layer = 0; layer < numberLayers - 1; layer++)
	{

		for (int j = 0; j < ndef[layer+1]; j++)
		{
			for(int i = 0; i < ndef[layer]; i++)
			{
				double a = NET->getParameter(layer, i, j)->get(0); 
				double b = NET->getParameter(layer, i, j)->get(1);

				file.write((char*)&a, sizeof(a));
				file.write((char*)&b, sizeof(b));

			}
		}
		
	}


	file.close();


	

}


