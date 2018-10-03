
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

#include <iostream>
#include <vector>

#include "FileReader.h"
#include <vector>
#include <iostream>
#include <fstream>


FileReader::FileReader()
{
    imageFileName = (char*)"train-images.idx3-ubyte";
    labelFileName = (char*)"train-labels.idx1-ubyte"; 
                                                                                                              }




int FileReader::ReverseInt(int i)
{
	unsigned char ch1, ch2, ch3, ch4;
	ch1 = i & 255;
	ch2 = (i >> 8) & 255;
	ch3 = (i >> 16) & 255;
	ch4 = (i >> 24) & 255;
	return((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

//, std::vector<std::vector<double>> &arr


void FileReader::readLabels(int numberOfLabels)
{
	labels.resize(numberOfLabels);

	// std::ifstream file("train-images.idx3-ubyte", std::ios::binary);
	std::ifstream file(labelFileName, std::ios::binary);


	if (file.is_open())
	{
		std::cout << "file  open" << std::endl;
		int magic_number     = 0;
		int number_of_items = 0;
		//int n_rows = 0;
		//int n_cols = 0;
		file.read((char*)&magic_number, sizeof(magic_number));
		magic_number = ReverseInt(magic_number);

		file.read((char*)&number_of_items, sizeof(number_of_items));
		number_of_items = ReverseInt(number_of_items);
		

		//file.read((char*)&n_rows, sizeof(n_rows));
		//n_rows = ReverseInt(n_rows);
		
		//file.read((char*)&n_cols, sizeof(n_cols));
		//n_cols = ReverseInt(n_cols);

		//std::cout << n_cols << " " << n_rows << std::endl;
		std::cout << number_of_items << std::endl;


		for (int i = 0; i < numberOfLabels; ++i)
		{
			//for (int r = 0; r < n_rows; ++r)
			//{
			//	for (int c = 0; c < n_cols; ++c)
			//	{
					// unsigned char temp = 0;
					// file.read((char*)&temp, sizeof(temp));
					// res[i][(n_rows*r) + c] = (char)temp;

					char temp;
					file.read(&temp, 1);

					labels[i] = temp;

			//	}

			// }

		}

		file.close();
	}
	else
	{
		std::cout << "file not open" << std::endl;
	}



	std::cout << "done" << std::endl;


}




void FileReader::readImages(int numberOfImages, int sizeOfImage)
{
	images.resize(numberOfImages, std::vector<char>(sizeOfImage));

	// std::ifstream file("train-images.idx3-ubyte", std::ios::binary);
	std::ifstream file(imageFileName, std::ios::binary);


	if (file.is_open())
	{
		std::cout << "file  open" << std::endl;
		int magic_number = 0;
		int number_of_images = 0;
		int n_rows = 0;
		int n_cols = 0;
		file.read((char*)&magic_number, sizeof(magic_number));
		magic_number = ReverseInt(magic_number);
		file.read((char*)&number_of_images, sizeof(number_of_images));
		number_of_images = ReverseInt(number_of_images);
		file.read((char*)&n_rows, sizeof(n_rows));
		n_rows = ReverseInt(n_rows);
		file.read((char*)&n_cols, sizeof(n_cols));
		n_cols = ReverseInt(n_cols);

		std::cout << n_cols << " " << n_rows << std::endl;
		std::cout << number_of_images << std::endl;


		for (int i = 0; i < numberOfImages; ++i)
		{
			for (int r = 0; r < n_rows; ++r)
			{
				for (int c = 0; c < n_cols; ++c)
				{
					// unsigned char temp = 0;
					// file.read((char*)&temp, sizeof(temp));
					// res[i][(n_rows*r) + c] = (char)temp;

					char temp; 
					file.read(&temp,1);

					images[i][(n_cols*r) + c] = temp;

				}
				 
			}
			 
		}

		file.close(); 
	}
	else
	{
		std::cout << "file not open" << std::endl; 
	}



	std::cout << "done" << std::endl;

}


std::vector<char> FileReader::getImage( int i )
{


	return images[i];

}

std::vector<double> FileReader::getdoubleImage(int i)
{
	std::vector<char>  cimg = getImage(i); 

	std::vector<double> fimg(cimg.size());

	for (int k = 0; k < cimg.size(); k++)
	{

		//std::cout << cimg[k] << " => ";

		unsigned char x = (unsigned char)cimg[k];
        
		// std::cout << x << " => " ;

		double y = ((double)x - 128.0) / 128.0 ; 

		// std::cout << y << std::endl;


		fimg[k] = y; 
	}

	return fimg; 

}



std::vector<double> FileReader::getLabel(int i)
{

	std::vector<double> rv;
	rv.resize(10); 
	
	int lab = (int)labels[i];

	
	for (int j = 0; j < 10; j++)
	{
		rv[j] =  -1.0; 

		if (lab == j)
		{
			rv[j] = 1.0;
		}
 	}


	return rv;                   // labels[i]; 
}



std::vector<std::vector<double> > FileReader::getAllImages()
{

	std::vector<std::vector<double> > dimg;

	for (int i = 0; i < images.size(); i++)
	{

		dimg.push_back(getdoubleImage(i)); 

	}

	return dimg; 
}


std::vector<std::vector<double> > FileReader::getAllLabels()
{
	std::vector<std::vector<double> > lab;

	for (int i = 0; i < images.size(); i++)
	{

		lab.push_back(getLabel(i));

	}

	return lab;

}






void FileReader::printImage(int m)
{

	std::vector<char>   xx = getImage(m);
	std::vector<double> la = getLabel(m);

	std::cout << "size of Image " << xx.size() << std::endl;

	std::cout << " Label     "; 
	for (int c = 0; c < 10; c++)
	{
		std::cout << la[c] << " ";
	}
	std::cout << std::endl; 


	for (int i = 0; i < 28; i++)
	{
		for (int j = 0; j < 28; j++)
		{
			if ((char)(((128 + xx[i + j * 28]) / 26) + 48) != '4')
			{
				std::cout << (char)(((128 + xx[i + j * 28]) / 26) + 48) << " ";
			}
			else
			{
				std::cout << " " << " ";
			}

		}
		std::cout << std::endl;
	}


}
