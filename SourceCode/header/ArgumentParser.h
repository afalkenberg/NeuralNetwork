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

#include <string>
#include <vector>


class ArgumentParser
{
   
private:
	std::vector<std::string> inputString; 
	int size; 

public:

	void setInput(int argc, char* argv[]); 
	void setSize(int s); 
	bool check(std::string x); 
	std::string getString(std::string p);
	double      getDouble(std::string p);
	int         getInt(std::string p);

	

};
