/*
Copyright 2011. All rights reserved.
Institute of Measurement and Control Systems
Karlsruhe Institute of Technology, Germany

This file is part of libicp.
Authors: Andreas Geiger

libicp is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation; either version 3 of the License, or any later version.

libicp is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
libicp; if not, write to the Free Software Foundation, Inc., 51 Franklin
Street, Fifth Floor, Boston, MA 02110-1301, USA 
*/

// Demo program showing how libicp can be used

#include <iostream>
#include <algorithm>
#include "icpPointToPlane.h"

using namespace std;
using namespace ICP;

int main (int argc, char** argv) {

  // define a 3 dim problem with 10000 model points
  // and 10000 template points:
  int32_t dim = 3;
  int32_t num = 10000;

  // allocate model and template memory
  double* M = (double*)calloc(3*num,sizeof(double));
  double* T = (double*)calloc(3*num,sizeof(double));

  // set model and template points
  cout << endl << "Creating model with 10000 points ..." << endl;
  cout << "Creating template by shifting model by (1,0.5,-1) ..." << endl;
  int32_t k=0;
  for (double x=-2; x<2; x+=0.04) {
    for (double y=-2; y<2; y+=0.04) {
      double z=5*x*exp(-x*x-y*y) + 1.0;
      M[k*3+0] = x / z;
      M[k*3+1] = y / z;
      M[k*3+2] = 1.0;
      T[k*3+0] = x-0.01;
      T[k*3+1] = y-0.01;
      T[k*3+2] = z+0.01;
      k++;
    }
  }

  /*for (int i = 0; i < num - 1; i++) {
    int j = std::rand() % (num - i);
    for (int t = 0; t < 3; t++) {
      std::swap(M[i * 3 + t], M[(num - j - 1) * 3 + t]);
    }
  }*/

  // start with identity as initial transformation
  // in practice you might want to use some kind of prediction here
  Matrix R = Matrix::eye(3);
  Matrix t(3,1);

  // run point-to-plane ICP (-1 = no outlier threshold)
  cout << endl << "Running ICP (point-to-plane, no outliers)" << endl;
  IcpPointToPlane icp(M,num,dim);
  double residual = icp.fit(T,num,R,t,-1);

  // results
  cout << endl << "Transformation results:" << endl;
  cout << "R:" << endl << R << endl << endl;
  cout << "t:" << endl << t << endl << endl;
  cout << "Residual:"<<residual;

  // free memory
  free(M);
  free(T);

  // success
  return 0;
}

