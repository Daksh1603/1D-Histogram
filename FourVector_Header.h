/**
 * @file FourVector_Header.h
 * @author Daksh Rathore (drathore_be20@thapar.edu)
 * 
 * + Vector Class : Contains the x , y and z input of a vector . The following class supports basic vector computation such as magnitude,normalize(unit vector),Angle between vectors , Dot product , Cross product , Transverse Momentum vector and return the x,y and z parameters .
 * + FourVector Class : Inherits the Vector class and adds an extra data member e for accessing the energy parameter of the input four vector . This class is capable of finding the mass of the particle , energy and return the e parameter to the call function .
 * + Reader Class : This class takes in the filename as input and contains a function that reads data from the input file(in the required format) and stores the data in a vector of FourVector objects which are passed by reference to this function .
 * +Output class : This class takes in the user defined parameters for the 1 Dimensional Histogram and appropriately scans the data vector , to generate an output file contains the x values (bin edges) and the y values (probablity of each bin)
 * @version 0.1
 * @date 2023-03-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef FourVector_Header
#define FourVector_Header

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <iomanip>

using namespace std;

class Vector {
  protected: double x,
  y,
  z;
  public: Vector(double arr[]) { // Constructor to take information from the reader class function.
    x = arr[0];
    y = arr[1];
    z = arr[2];
  }
  Vector(double a, double b, double c) { // Constructor that takes in three values for ease of vector object creation and calculation .
    x = a;
    y = b;
    z = c;
  }
  double TAxis() {// Function to calculate Transverse axis of a four vector .
    return (sqrt(x * x + y * y));
  }
  double magnitude() {// Function to calculate magnitude .
    return sqrt(x * x + y * y + z * z);
  }
  Vector normalize() {// Function to return normalized vector .
    double mag = magnitude();
    return Vector(x / mag, y / mag, z / mag);
  }
  double dot(Vector & vec) {// Function to calculate the dot product between 2 vectors.
    return x * vec.x + y * vec.y + z * vec.z;
  }

  Vector cross(Vector & vec) {// Function to calculate the cross product between 2 vectors.
    return Vector(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
  }

  double angle(Vector & vec) {// Function to calculate the angle between two vectors .
    double dot_product = dot(vec);
    double mag_product = magnitude() * vec.magnitude();
    return acos(dot_product / mag_product);
  }
  double pX() {// Function to return x parameter.
    return x;
  }
  double pY() {// Function to return y parameter.
    return y;
  }
  double pZ() {// Function to return z parameter.
    return z;
  }
};

class FourVector: public Vector {
  double e;
  public:
    FourVector(double arr[]): Vector(arr) {
      e = arr[3];
    }
  FourVector(double a, double b, double c, double d): Vector(a, b, c) {// Constructor that takes in four values for ease of four vector object creation and calculation .
    e = d;
  }
  double mass() { // Function to calcualte the mass of the particle .
    return sqrt(e * e - magnitude() * magnitude());
  }
  double pE() { // Function to return the energy of the particle .
    return e;
  }
};


class Reader
{
  string *filename;
public:
  Reader(string * a)// Parameterized constructor to assign data members .
  {
    filename = a;
  }
  void readFromFile(vector < FourVector > & dataObjects){  // DataObjects vector passed by reference
  ifstream inputFile( * filename);// Object of ifstream created to read from entered file .
  string line; // Temp string variable to pass to stringstream
  string word; // Temp string variable to store the value from stringstream
  double a[4];
  while (getline(inputFile, line)) { // Loop to go through each data line of the input file
    stringstream ss(line); // Stringstream object created and called for ease of string manipulation
    int i = 0;
    while (ss >> word) { // Traversing the stringstream to extract values and store it in an array
      a[i++] = stod(word);
    }
    FourVector vec(a);// Create and initialise an object of FourVector using data array .
    dataObjects.push_back(vec);// Pass the FourVector object to dataObjects .
  }
  inputFile.close();// Closing the inputFile object .
  }
};




class Output
{
  double xmin,xmax;
  int bins;
public:
  Output(double a,double b,int c) // Parameterized constructor to assign data members .
  {
    xmin = a;
    xmax = b;
    bins = c;
  }
  void generateData(vector < double > & vect) { // Data vector passed by reference
  const double diff = (xmax - xmin) / bins; // Bin width stored in diff
  vector < double > frequency(bins, 0); // All bin counts assigned 0 frequency.
  for (const double & x: vect) { // Traverse the data vector .
    int bin = floor((x - xmin) / diff); // Find the appropriate bin .
    if(x==xmax) // The last bin is inclusive of upper limit . Hence , checks if xmax entered .
        frequency[bins-1]++;
    if ((bin < 0) || (bin >= bins)) // If out of range , skip the iteration .
      continue;
    frequency[bin]++;
  }
  const double total = static_cast < double >(vect.size()); // Storing total no. of data points
  for (int i = 0; i < bins; i++) {
    frequency[i] = static_cast < double > (frequency[i]) / total;// Converting frequency of each bin to its probablity .
  }
  ofstream outfile("output.txt");// Creating the outfile object to write to output.txt
  outfile << "   x-axis   " << "" << "   y-axis   " << endl; 

  for (int i = 0; i < bins; i++) {
    double x = xmin + i * diff; // Calculating bin edge .
    outfile << setw(9) << x << "   " << setprecision(8) << frequency[i] << endl; // Writing to output file .
  }
  outfile << setw(9) << xmax << endl;
  outfile.close(); // Closing the outfile object .
}
};

#endif
