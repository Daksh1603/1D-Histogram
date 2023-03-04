#include "FourVector_Header.h"

int main(int argc, char * argv[]) {
  string datafile = argv[1];   //Information is extracted from the command line arguments passed to the program 
  string distribution = argv[2];
  double xMin = stod(argv[3]);
  double xMax = stod(argv[4]);
  int numBins = stoi(argv[5]);
  vector < FourVector > dataObjects; // A vector of FourVector objects to store data from input file 
  Reader read1( & datafile); // Reader object to read the input file
  Output out1(xMin, xMax, numBins);// Output Object to generate output.txt file
  read1.readFromFile(dataObjects);// dataObjects passed by reference to the Reader object

  unordered_map < string, int > myMap = { // Unordered Hash map to store the distributions equivalent int form for switch case . The following logic has a modular approach since adding new distributions for support will require just minimal additions in main function .
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

  while (1) { // Finding the right distribution and if not found , displaying a message .
    if (myMap.find(distribution) != myMap.end()) 
      break;
      else {
      cout << "You entered an unknown Distribution." << endl;
      cout << "Enter a supported Distribution ." << endl;
      cin >> distribution;
    }
  }

  int n = myMap[distribution]; // Distribution's integer equivalent stored .
  vector < double > data; // Creating a vector of only required data .

  for (FourVector & x: dataObjects) { // Switch case logic for storing data . Modular approach
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
  out1.generateData(data); // Calling the Output object to generate output.txt
  return 0;
}