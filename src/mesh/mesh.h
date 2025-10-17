#pragma once
#include <Eigen/Core>
#include <Eigen/Sparse>
#include <vector>

namespace PF
{
class Mesh
{
  public:
    Mesh() = default;
    Mesh(const Eigen::MatrixXd &V, const Eigen::MatrixXi &F);
    ~Mesh() = default;

    bool LoadFromFile(const char *filename);

    // 顶点拓扑
    std::vector<size_t> &GetVV(size_t vi);


    // 边拓扑

    // 面拓扑

  private:
    void BuildTopology();
    void GetLAR(Eigen::SparseMatrix<int> &base_mev, Eigen::SparseMatrix<int> &base_mfe);

    Eigen::SparseMatrix<int> &Circle(const Eigen::SparseMatrix<int> &a, const Eigen::SparseMatrix<int> &b);
    Eigen::VectorXi &Wedge(const Eigen::SparseMatrix<int> &a, const Eigen::SparseMatrix<int> &b, size_t idx);
    Eigen::VectorXi &Wedge(const Eigen::VectorXi &a, const Eigen::VectorXi &b);


  private:
    Eigen::MatrixXd vertices;
    Eigen::MatrixXi faces;

    // ------------------------
    // Linear Algebra Representation
    // ------------------------
    Eigen::SparseMatrix<int> partial_1; // boundary operatior matrix of 1-cell(edge) m_ev
    Eigen::SparseMatrix<int> partial_2; // boundary operatior matrix of 2-cell(face) m_fe

    Eigen::SparseMatrix<int> m_ev; // m1
    Eigen::SparseMatrix<int> m_ee;
    Eigen::SparseMatrix<int> m_ef; // basic

    Eigen::SparseMatrix<int> m_vv;
    Eigen::SparseMatrix<int> m_ve;
    Eigen::SparseMatrix<int> m_vf;

    Eigen::SparseMatrix<int> m_fv; // m2
    Eigen::SparseMatrix<int> m_fe;
};

} // namespace PF
