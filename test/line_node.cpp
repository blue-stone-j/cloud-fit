#include <pcl/io/pcd_io.h>
#include <pcl/sample_consensus/ransac.h>
#include <pcl/sample_consensus/sac_model_line.h> // 拟合直线
#include <pcl/visualization/pcl_visualizer.h>

int main()
{
  //-------------------------- 加载点云 --------------------------
  std::string path = "../assets/cloud/line1.pcd";
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
  if (pcl::io::loadPCDFile(path, *cloud) < 0)
  {
    PCL_ERROR("点云读取失败！\n");
    return -1;
  }
  std::cout << "点云点数为：" << cloud->points.size() << std::endl;
  //-----------------------------拟合直线-----------------------------
  pcl::SampleConsensusModelLine<pcl::PointXYZ>::Ptr model_line(new pcl::SampleConsensusModelLine<pcl::PointXYZ>(cloud));
  pcl::RandomSampleConsensus<pcl::PointXYZ> ransac(model_line);
  ransac.setDistanceThreshold(0.01); // 内点到模型的最大距离
  ransac.setMaxIterations(1000);     // 最大迭代次数
  ransac.computeModel();             // 直线拟合
  //--------------------------根据索引提取内点------------------------
  std::vector<int> inliers;
  ransac.getInliers(inliers);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_line(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::copyPointCloud<pcl::PointXYZ>(*cloud, inliers, *cloud_line);

  //----------------------------输出模型参数--------------------------
  Eigen::VectorXf coef;
  ransac.getModelCoefficients(coef);
  std::cout << "直线方程为：\n"
            << "   (x - " << coef[0] << ") / " << coef[3]
            << " = (y - " << coef[1] << ") / " << coef[4]
            << " = (z - " << coef[2] << ") / " << coef[5] << std::endl;


  // customized

  return 0;
}