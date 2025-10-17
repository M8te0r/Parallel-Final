#include "mesh.h"
#include <igl/edge_topology.h>
#include <igl/readOBJ.h>

namespace PF
{
Mesh::Mesh(const Eigen::MatrixXd &V, const Eigen::MatrixXi &F) : vertices(V), faces(F)
{
}

bool Mesh::LoadFromFile(const char *filename)
{
    if (!igl::readOBJ(filename, this->vertices, this->faces))
    {
        return false;
    }

    BuildTopology();
    return true;
}

std::vector<size_t> &Mesh::GetVV(size_t vi)
{
    static std::vector<size_t> indices;
    indices.clear();

    if (m_vv.size() == 0)
    {
        // m_vv_raw = (m_ev.transpose()) * m_ev;
        m_vv = Circle(m_ev.transpose(), m_ev);
    }

    std::cout << m_vv << std::endl;

    indices.reserve(m_vv.rows());
    for (Eigen::SparseMatrix<int>::InnerIterator it(m_vv, vi); it; ++it)
    {
        indices.push_back(it.index());
    }

    return indices;
}

void Mesh::BuildTopology()
{
    // LAR
    GetLAR(partial_1, partial_2);
    m_ev = partial_1;
    m_fe = partial_2;
}

void Mesh::GetLAR(Eigen::SparseMatrix<int> &p1, Eigen::SparseMatrix<int> &p2)
{
    Eigen::MatrixXi EV, FE, EF; // EV:Ex2 FE:Fx3
    igl::edge_topology(this->vertices, this->faces, EV, FE, EF);

    p1 = Eigen::SparseMatrix<int>(EV.rows(), this->vertices.rows());
    for (size_t i = 0; i < EV.rows(); ++i)
    {
        int v_i = EV(i, 0);
        int v_j = EV(i, 1);
        p1.insert(i, v_i) = 1; // TODO：应该是-1？
        p1.insert(i, v_j) = 1;
    }

    p2 = Eigen::SparseMatrix<int>(this->faces.rows(), EV.rows());
    for (size_t i = 0; i < this->faces.rows(); ++i)
    {
        int e_i = this->faces(i, 0);
        int e_j = this->faces(i, 1);
        int e_k = this->faces(i, 2);
        p2.insert(i, e_i) = 1;
        p2.insert(i, e_j) = 1;
        p2.insert(i, e_k) = 1;
    }
}

Eigen::SparseMatrix<int> &Mesh::Circle(const Eigen::SparseMatrix<int> &mat_a, const Eigen::SparseMatrix<int> &mat_b)
{
    if (mat_a.cols() != mat_b.rows())
    {
        throw std::runtime_error("INVALID circle operation!");
    }

    int d = 1; // mat_b.cols();

    Eigen::SparseMatrix<int> A = mat_a * mat_b;
    Eigen::SparseMatrix<int> rslt(mat_a.rows(), mat_b.cols());
    int rslt_row_index = 0;


    for (int k = 0; k < A.outerSize(); ++k)
    {
        // 遍历第k行的非零元素
        for (Eigen::SparseMatrix<int>::InnerIterator it(A, k); it; ++it)
        {
            int i = it.row();
            int j = it.col();
            int a_ij = it.value();
            // 处理非对角、且值大于等于d的元素a_{ij}。表示存在公共元素
            if ((i != j) && (a_ij >= d))
            {
                // 获取a的第i行和b的第j列，做二进制与运算
                Eigen::VectorXi rslt_row = Wedge(Eigen::VectorXi(mat_a.row(i)), Eigen::VectorXi(mat_b.col(j)));
                // 将结果保存至稀疏矩阵中
                for (int row_inner_index = 0; row_inner_index < rslt_row.size(); ++row_inner_index)
                {
                    if (rslt_row(row_inner_index) != 0)
                    {
                        rslt.insert(rslt_row_index, row_inner_index) = rslt_row(row_inner_index);
                    }
                }
                rslt_row_index++;
            }
        }
    }
    return rslt;
}

Eigen::VectorXi &Mesh::Wedge(const Eigen::SparseMatrix<int> &a, const Eigen::SparseMatrix<int> &b, size_t idx)
{
    Eigen::VectorXi rslt(a.cols());
    for (size_t i = 0; i < a.cols(); ++i)
    {
        rslt[i] = a.coeff(idx, i) & b.coeff(i, idx);
    }
    return rslt;
}

Eigen::VectorXi &Mesh::Wedge(const Eigen::VectorXi &a, const Eigen::VectorXi &b)
{
    if (a.size() != b.size())
    {
        throw std::runtime_error("Error: INVLAID vector wedge operation!");
    }

    Eigen::VectorXi rslt(a.size());

    for (size_t i = 0; i < a.size(); ++i)
    {
        rslt(i) = a(i) & b(i);
        std::cout<<rslt(i)<<std::endl;
    }
    return rslt;
}

} // namespace PF
