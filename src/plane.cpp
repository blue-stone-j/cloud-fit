#include "plane.h"

int PlaneFit::fit()
{
  { // 主成分分析（PCA）
    int num_points = cloud.size();

    Eigen::MatrixXd points(num_points, 3);
    for (int i = 0; i < num_points; i++)
    {
      points(i, 0) = cloud[i].x;
      points(i, 1) = cloud[i].y;
      points(i, 2) = cloud[i].z;
    }

    // 计算点云的质心
    Eigen::Vector3d centroid = points.colwise().mean();

    // 计算去中心化的点云
    Eigen::MatrixXd demeaned_points = points.rowwise() - centroid.transpose();

    // 计算协方差矩阵
    Eigen::Matrix3d cov_matrix = demeaned_points.transpose() * demeaned_points / double(num_points);

    // 计算特征值和特征向量
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> es(cov_matrix);

    // 找到最小特征值对应的特征向量
    Eigen::Vector3d normal_vector = es.eigenvectors().col(0);

    // 计算平面方程的d值
    double d = -normal_vector.dot(centroid);

    std::cout << "The plane equation is " << normal_vector(0) << "x + " << normal_vector(1) << "y + " << normal_vector(2) << "z + " << d << " = 0" << std::endl;
  }

  { // 最小二乘法
    int num_points = cloud.size();

    Eigen::MatrixXd points(num_points, 3);
    for (int i = 0; i < num_points; i++)
    {
      points(i, 0) = cloud[i].x;
      points(i, 1) = cloud[i].y;
      points(i, 2) = cloud[i].z;
    }
    // 构建矩阵 A 和向量 B
    Eigen::MatrixXd A(num_points, 3);
    A.col(0) = points.col(0);                     // x
    A.col(1) = points.col(1);                     // y
    A.col(2) = Eigen::VectorXd::Ones(num_points); // 常数项

    Eigen::VectorXd B = points.col(2); // z

    // 使用最小二乘法求解
    Eigen::VectorXd coeff = A.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(B);

    double norm = std::sqrt(1 + coeff(0) * coeff(0) + coeff(1) * coeff(1));

    std::cout << "The plane equation is " << -coeff(0) / norm << "x + " << -coeff(1) / norm << "y + " << 1 / norm << "z + " << -coeff(2) / norm << " = 0" << std::endl;
  }

  return 0;
}