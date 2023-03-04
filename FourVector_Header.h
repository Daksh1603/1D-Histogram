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
  public: Vector(double arr[]) {
    x = arr[0];
    y = arr[1];
    z = arr[2];
  }
  Vector(double a, double b, double c) {
    x = a;
    y = b;
    z = c;
  }
  double TAxis() {
    return (sqrt(x * x + y * y));
  }
  double magnitude() {
    return sqrt(x * x + y * y + z * z);
  }
  Vector normalize() {
    double mag = magnitude();
    return Vector(x / mag, y / mag, z / mag);
  }
  double dot(Vector & vec) {
    return x * vec.x + y * vec.y + z * vec.z;
  }

  Vector cross(Vector & vec) {
    return Vector(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
  }

  double angle(Vector & vec) {
    double dot_product = dot(vec);
    double mag_product = magnitude() * vec.magnitude();
    return acos(dot_product / mag_product);
  }
  double pX() {
    return x;
  }
  double pY() {
    return y;
  }
  double pZ() {
    return z;
  }
};

class FourVector: public Vector {
  double e;
  public:
    FourVector(double arr[]): Vector(arr) {
      e = arr[3];
    }
  FourVector(double a, double b, double c, double d): Vector(a, b, c) {
    e = d;
  }
  double mass() {
    return sqrt(e * e - magnitude() * magnitude());
  }
  double pE() {
    return e;
  }
};


class Reader
{
  string *filename;
public:
  Reader(string * a)
  {
    filename = a;
  }
  void readFromFile(vector < FourVector > & dataObjects){
  ifstream inputFile( * filename);
  string line;
  string word;
  double a[4];
  while (getline(inputFile, line)) {
    stringstream ss(line);
    int i = 0;
    while (ss >> word) {
      a[i++] = stod(word);
    }
    FourVector vec(a);
    dataObjects.push_back(vec);
    i = 0;
  }
  inputFile.close();
  }
};




class Output
{
  double xmin,xmax;
  int bins;
  vector<double> frequency;
public:
  Output(double a,double b,int c)
  {
    xmin = a;
    xmax = b;
    bins = c;
  }
  void generateData(vector < double > & vect) {
  const double diff = (xmax - xmin) / bins;
  vector < double > frequency(bins, 0);
  for (const double & x: vect) {
    int bin = floor((x - xmin) / diff);
    if(x==xmax)
        frequency[bins-1]++;
    if ((bin < 0) || (bin >= bins))
      continue;
    frequency[bin]++;
  }
  const double total = static_cast < double > (vect.size());
  for (int i = 0; i < bins; i++) {
    double temp = static_cast < double > (frequency[i]) / total;
    frequency[i] = temp;
  }
  ofstream outfile("output.txt");
  outfile << "   x-axis   " << "" << "   y-axis   " << endl;

  for (int i = 0; i < bins; i++) {
    double x = xmin + i * diff;
    outfile << setw(9) << x << "   " << setprecision(8) << frequency[i] << endl;
  }
  outfile << setw(9) << xmax << endl;
  outfile.close();
}
};

#endif
