#ifndef INTERFACE_H
#define INTERFACE_H

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

class Interface
{
 public:
  pcl::PointCloud<pcl::PointXYZ> cloud;
  virtual int fit() = 0;
  /* coefficients of model
     plane: Ax+By+Cz+D=0, where A^2+B^2+C^2=1
   */
  std::vector<float> model_coeffs;
};


#endif