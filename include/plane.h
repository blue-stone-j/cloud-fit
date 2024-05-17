#ifndef PLANE_H
#define PLANE_H

#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

#include "interface.h"

class PlaneFit : public Interface
{
 public:
  int fit();
};

#endif