
#include <pcl/io/pcd_io.h>
#include <pcl/segmentation/sac_segmentation.h>

#include "plane.h"

int main()
{
  std::string path = "../assets/cloud/plane1.pcd";
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
  if (pcl::io::loadPCDFile<pcl::PointXYZ>(path, *cloud) == -1)
  {
    PCL_ERROR("Couldn't read file point_cloud_file.pcd \n");
    return (-1);
  }

  // pcl
  pcl::SACSegmentation<pcl::PointXYZ> seg;
  pcl::PointIndices inliers;
  inliers.indices.clear();
  pcl::ModelCoefficients coefficients;

  seg.setOptimizeCoefficients(true);
  seg.setModelType(pcl::SACMODEL_PLANE);
  seg.setMethodType(pcl::SAC_RANSAC);
  seg.setMaxIterations(1000);
  seg.setDistanceThreshold(0.2);
  seg.setInputCloud(cloud);
  seg.segment(inliers, coefficients);

  // plane equation
  std::cout << "The plane equation is " << coefficients.values[0] << "x + "
            << coefficients.values[1] << "y + " << coefficients.values[2] << "z + "
            << coefficients.values[3] << " = 0" << std::endl;


  // customized
  PlaneFit plane_fit;
  plane_fit.cloud = *cloud;

  plane_fit.fit();

  return 0;
}