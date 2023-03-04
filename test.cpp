#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "FourVector_Header.h"
double tolerance = 0.001; // On account of how floating point calculations operate in the computers memory , it is expected that accurate comparision may not be equal . In order for this to work , a tolerance level is implemented .

TEST_CASE("Vector operations") {
  double a1[] = {1.0, 2.0, 3.0};
  double a2[] = {2.0, 3.0, 4.0};
  Vector vec1(a1);
  Vector vec2(a2);

  SECTION("TAxis") {
    REQUIRE(abs(vec1.TAxis() - 2.236) < tolerance);
    REQUIRE(abs(vec2.TAxis() - 3.605) < tolerance);
  }

  SECTION("Magnitude") {
    REQUIRE(abs(vec1.magnitude() - 3.742) < tolerance);
    REQUIRE(abs(vec2.magnitude() - 5.385) < tolerance);
  }

  SECTION("Normalize") {
    Vector norm1 = vec1.normalize();
    Vector norm2 = vec2.normalize();
    REQUIRE(abs(norm1.magnitude() - 1.0) < tolerance);
    REQUIRE(abs(norm2.magnitude() - 1.0) < tolerance);
  }

  SECTION("Dot product") {
    double dot_prod = vec1.dot(vec2);
    REQUIRE(abs(dot_prod - 20.0) < tolerance);
  }

  SECTION("Cross product") {
    Vector cross_prod = vec1.cross(vec2);
    Vector expected_cross_prod(-1.0, 2.0, -1.0);
    REQUIRE(abs(cross_prod.pX() - expected_cross_prod.pX()) < tolerance);
    REQUIRE(abs(cross_prod.pY() - expected_cross_prod.pY()) < tolerance);
    REQUIRE(abs(cross_prod.pZ() - expected_cross_prod.pZ()) < tolerance);
  }

  SECTION("Angle") {
    double angle = vec1.angle(vec2);
    REQUIRE(abs(angle - 0.121) < tolerance);
  }
}

TEST_CASE("FourVector operations") {
  double arr[] = {1.0, 2.0, 3.0, 4.0};
  FourVector fv(arr);

  SECTION("Mass") {
    REQUIRE(abs(fv.mass() - 1.414) < tolerance);
  }
}

TEST_CASE("Reader") {
  string filename = "test.txt";
  Reader reader(&filename);

  SECTION("Read from file") {
    vector<FourVector> dataObjects;
    reader.readFromFile(dataObjects);
    REQUIRE(dataObjects.size() == 2);
  }
}

TEST_CASE("Output") {
  double xmin = 0.0;
  double xmax = 5.0;
  int bins = 5;
  Output output(xmin, xmax, bins);

  SECTION("Generate data") {
    vector<double> vect = {1.0, 2.0, 3.0, 4.0};
    output.generateData(vect);
  }
}