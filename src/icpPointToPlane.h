/*
Copyright 2011. All rights reserved.
Institute of Measurement and Control Systems
Karlsruhe Institute of Technology, Germany

Authors: Andreas Geiger

libicp is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or any later version.

libicp is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
libicp; if not, write to the Free Software Foundation, Inc., 51 Franklin
Street, Fifth Floor, Boston, MA 02110-1301, USA 
*/

#ifndef ICP_POINT_TO_PLANE_H
#define ICP_POINT_TO_PLANE_H

#include "icp.h"
#include <iostream>

class IcpPointToPlane : public Icp {

public:
  
  IcpPointToPlane (double *M,const int32_t M_num,const int32_t dim,const int32_t num_neighbors=10,const double flatness=5.0) : Icp(M,M_num,dim) {
    M_normal = computeNormals(num_neighbors,flatness);
    M_tang = M_normal + M_num * 3;
  }

  virtual ~IcpPointToPlane () {
    free(M_normal);
  }
  std::vector<double> computeRayNormal(std::vector<float> query);
  std::vector<double> computRayNormalByIdx(int idx);

private:

	double fitStep (double *T,const int32_t T_num,ICP::Matrix &R,ICP::Matrix &t,ICP::Matrix &initial_t,const std::vector<int32_t> &active);
	std::vector<int32_t> getInliers (double *T,const int32_t T_num,const ICP::Matrix &R,const ICP::Matrix &t,const double indist);
	double getResidual(double *T,const int32_t T_num,const ICP::Matrix &R,const ICP::Matrix &t,const std::vector<int> &active);
	// utility functions to compute normals from the model tree
	void computeNormal (const std::tuple<float, float, float> &pt, const kdtree::KDTreeResultVector &neighbors,double *M_normal, double *M_tang, const double flatness);
	double* computeNormals (const int32_t num_neighbors,const double flatness);

	// normals of model points
	double *M_normal;
	double *M_tang;
};

#endif // ICP_POINT_TO_PLANE_H
