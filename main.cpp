#include "FourVector_Header.h"

int main(int argc, char * argv[]) {
  string datafile = argv[1];
  string distribution = argv[2];
  double xMin = stod(argv[3]);
  double xMax = stod(argv[4]);
  int numBins = stoi(argv[5]);
  vector < FourVector > dataObjects;
  Reader read1( & datafile);
  Output out1(xMin, xMax, numBins);
  read1.readFromFile(dataObjects);

  unordered_map < string, int > myMap = {
    {
      "pT",
      1
    },
    {
      "pX",
      2
    },
    {
      "pY",
      3
    },
    {
      "pZ",
      2
    },
    {
      "energy",
      4
    },
    {
      "mass",
      5
    }
  };

  while (1) {
    if (myMap.find(distribution) != myMap.end()) {
      cout << "Searching" << endl;
      cout << "You entered " << distribution << " with value " << myMap[distribution] << endl;
      break;
    } else {
      system("CLS");
      cout << "You entered an unknown string." << endl;
      cout << "Enter a distribution again!" << endl;
      cin >> distribution;
    }
  }

  int n = myMap[distribution];
  vector < double > data;

  for (FourVector & x: dataObjects) {
    switch (n) {
    case 1:
      data.push_back(x.TAxis());
      break;
    case 2:
      data.push_back(x.pX());
      break;
    case 3:
      data.push_back(x.pY());
      break;
    case 4:
      data.push_back(x.pZ());
      break;
    case 5:
      data.push_back(x.pE());
      break;
    case 6:
      data.push_back(x.mass());
      break;
    default:
      cout << "invalid" << endl;
    }
  }
  for (double & x: data)
    cout << x << " ";
  cout << data.size() << endl;
  out1.generateData(data);
  return 0;
}