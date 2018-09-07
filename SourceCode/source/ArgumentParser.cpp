
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

#include "ArgumentParser.h"
#include <iostream> 


void ArgumentParser::setInput(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
	{
		inputString.push_back(argv[i]); 
	}	
}

void ArgumentParser::setSize(int s)
{
	size = s; 
}

bool ArgumentParser::check(std::string x)
{
	for (int i = 0; i < inputString.size(); i++)
	{

		if (inputString[i].compare(x) == 0)
		{
			return true;
		}
	}

	return false;

}


std::string ArgumentParser::getString(std::string x)
{

	for (int i = 0; i < inputString.size(); i++)
	{
	
		if (inputString[i].compare(x) == 0)
		{
			return inputString[i + 1];
		}
	}

	return ""; 

}


double ArgumentParser::getDouble(std::string x)
{
	std::string res = getString(x); 
	return atof(res.c_str()); 

}


int ArgumentParser::getInt(std::string x)
{
	std::string res = getString(x);
	return atoi(res.c_str());

}


