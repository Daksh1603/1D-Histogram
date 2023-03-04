#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "FourVector_Header.h"
double tolerance = 0.001;

TEST_CASE("Vector operations") {
  double arr1[] = {1.0, 2.0, 3.0};
  double arr2[] = {2.0, 3.0, 4.0};
  Vector v1(arr1);
  Vector v2(arr2);

  SECTION("TAxis") {
    REQUIRE(abs(v1.TAxis() - 2.236) < tolerance);
    REQUIRE(abs(v2.TAxis() - 3.605) < tolerance);
  }

  SECTION("Magnitude") {
    REQUIRE(abs(v1.magnitude() - 3.742) < tolerance);
    REQUIRE(abs(v2.magnitude() - 5.385) < tolerance);
  }

  SECTION("Normalize") {
    Vector norm1 = v1.normalize();
    Vector norm2 = v2.normalize();
    REQUIRE(abs(norm1.magnitude() - 1.0) < tolerance);
    REQUIRE(abs(norm2.magnitude() - 1.0) < tolerance);
  }

  SECTION("Dot product") {
    double dot_prod = v1.dot(v2);
    REQUIRE(abs(dot_prod - 20.0) < tolerance);
  }

  SECTION("Cross product") {
    Vector cross_prod = v1.cross(v2);
    Vector expected_cross_prod(-1.0, 2.0, -1.0);
    REQUIRE(abs(cross_prod.pX() - expected_cross_prod.pX()) < tolerance);
    REQUIRE(abs(cross_prod.pY() - expected_cross_prod.pY()) < tolerance);
    REQUIRE(abs(cross_prod.pZ() - expected_cross_prod.pZ()) < tolerance);
  }

  SECTION("Angle") {
    double angle = v1.angle(v2);
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
  double xmax = 10.0;
  int bins = 5;
  Output output(xmin, xmax, bins);

  SECTION("Generate data") {
    vector<double> vect = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    output.generateData(vect);
  }
}