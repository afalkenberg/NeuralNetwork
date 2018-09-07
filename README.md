# NeuralNetwork
Implemented a neural network in C++ from scratch using a newly developed Perceptron

Perform the following three steps in a terminal. This was tested on Macos but should work on Ubuntu as well. 

cd SampleData
g++ -std=c++14 ../SourceCode/source/*.cpp -I../SourceCode/header -o NewPerceptron.exe
rm *.o
./NewPerceptron.exe

This provides a means to run it with the standard settings. There are a lot of other options as listed below: 

-fr input file name
-fw output file name 
-l0 learning rate 0
-l1 learning rate 1 
-n0 number neurons inner layer 0
-n1 number neurons inner layer 1
-n2 number neurons inner layer 2

Actually all of the parameters have some default values. 
The main program which is called NewNeuralArchitecture.cpp reads in the MNIST data. 
You can provide different settings if needed. I only show how three inner layers are configured, but that can be 
extended easily. 

The -fr and -fw are pointing to predefined neural networks. So you can let the neural network learn and then save it and come 
back and learn a bit more. 

Everything is written in C++ from scratch nothing is optimized this was only to proove that my Neuron works (having two learning rates is different from other neural networks). 
No exisiting AI libraries are used because I wanted to walk through the entire process myself. 
I have the paper almost ready showing the math behind it which I will check in also. 
I basically wrote most of the paper first and then implemented it but the paper is not in a conference or journal form so 
I have to probably get some results and then publish the paper. 
The next step could be to write a Kernel for a GPP or so. 

Have fun for now 
 Andreas Falkenberg 
 

