# 1D-Histogram
------
## Introduction
The main program takes in 5 command line arguments : datafile, distribution name, number of bins, min value for the x-axis, and max value for the x-axis.
The program currently supports the following distributions : pT, pX, pY, pZ, energy, and mass.

The datafile argument is the filename which contains the input data . For this project , an input.dat file is provided.

This program reads data from a file containing four-momentum data of particles and calculates various properties of those particles. It then allows the user to select a distribution of the data to plot and generates a histogram of the selected distribution.

The program consists of two main classes: Vector and FourVector. 
The Vector class represents a three-dimensional vector, with x, y, and z components, and contains various methods for calculating properties of the vector such as its magnitude, normalization, dot product, cross product, and angle with respect to another vector. 
The FourVector class is a subclass of Vector and represents a four-dimensional vector, with an additional component representing the energy of the particle. It contains a method for calculating the mass of the particle.

## Workflow

## How to run the following program

+ Step 1 : Clone the following github repository - > 
+ Step 2 : Run command prompt
+ Step 3 : Change the directory to that of downloaded folder.
+ Step 4 : Run the main executable file and pass the arguments along with it in the following order ( filename , distribution , xmin , xmax , number of bins )
For Example :
```main input.dat pX -500 500 100```

+ Optional : In order to run the unit test for the following program , enter the following code to the command prompt terminal .
```test```
