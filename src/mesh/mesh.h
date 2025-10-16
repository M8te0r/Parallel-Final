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

        std::vector<size_t> &GetEV(size_t ei);
        std::vector<size_t> &GetEE(size_t ei);
        std::vector<size_t> &GetEF(size_t ei);

        std::vector<size_t> &GetVV(size_t vi);
        std::vector<size_t> &GetVE(size_t vi);
        std::vector<size_t> &GetVF(size_t vi);

        std::vector<size_t> &GetFV(size_t fi);
        std::vector<size_t> &GetFE(size_t fi);
        std::vector<size_t> &GetFF(size_t fi);

    private:
        void BuildTopology();
        void GetLAR(Eigen::SparseMatrix<int> &mat_ev, Eigen::SparseMatrix<int> &mat_ef);

    private:
        Eigen::MatrixXd vertices;
        Eigen::MatrixXi faces;

        // ------------------------
        // Linear Algebra Representation
        // ------------------------
        Eigen::SparseMatrix<int> m_1;  // basic: m_ev
        Eigen::SparseMatrix<int> m_2;  // basic: m_fv

        Eigen::SparseMatrix<int> m_ev;  // basic
        Eigen::SparseMatrix<int> m_ee;
        Eigen::SparseMatrix<int> m_ef;  // basic

        Eigen::SparseMatrix<int> m_vv;
        Eigen::SparseMatrix<int> m_ve;
        Eigen::SparseMatrix<int> m_vf;

        Eigen::SparseMatrix<int> m_fv;
        Eigen::SparseMatrix<int> m_fe;
    };

} // namespace PF
