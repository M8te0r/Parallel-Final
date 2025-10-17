#include "mesh.h"
#include <igl/readOBJ.h>
#include <igl/edge_topology.h>

namespace PF
{
    Mesh::Mesh(const Eigen::MatrixXd &V, const Eigen::MatrixXi &F)
        : vertices(V), faces(F)
    {
    }

    bool Mesh::LoadFromFile(const char *filename)
    {
        return igl::readOBJ(filename, this->vertices, this->faces);
    }

    std::vector<size_t> &Mesh::GetVV(size_t vi)
    {
        static std::vector<size_t> indices;
        indices.clear();

        if (m_vv.size() == 0)
        {
            m_vv = (m_ev.transpose()) * m_ev;
        }

        indices.reserve(m_vv.rows());
        for (Eigen::SparseMatrix<int>::InnerIterator it(m_vv, vi); it; ++it)
        {
            indices.push_back(it.index());
        }

        return indices;
    }

    std::vector<size_t> &Mesh::GetVF(size_t vi)
    {
        static std::vector<size_t> indices;
        indices.clear();

        if (m_vf.size() == 0)
        {
            m_vf = (m_ev.transpose()) * m_ef;
        }

        indices.reserve(m_vv.rows());
        for (Eigen::SparseMatrix<int>::InnerIterator it(m_vf, vi); it; ++it)
        {
            indices.push_back(it.index());
        }

        return indices;
    }


    std::vector<size_t> &Mesh::GetEV(size_t ei)
    {
        std::vector<size_t> indices(2); // [0] from, [1] to
        for (Eigen::SparseMatrix<int>::InnerIterator it(m_ev, ei); it; ++it)
        {
            if (it.col() < 0)
                indices[0] = it.index();
            if (it.col() > 0)
                indices[1] = it.index();
        }

        return indices;
    }

    std::vector<size_t> &Mesh::GetEF(size_t ei)
    {
        static std::vector<size_t> indices;
        indices.clear();
        indices.reserve(2);
        for (Eigen::SparseMatrix<int>::InnerIterator it(m_ef, ei); it; ++it)
        {
            indices.push_back(it.index());
        }
    }

    

    std::vector<size_t> &Mesh::GetFV(size_t fi)
    {
        std::vector<size_t> indices(3); // v0, v1, v2
        if (m_fv.size() == 0)
        {
            m_fv = (m_ef.transpose()) * m_ev;
        }

        for (Eigen::SparseMatrix<int>::InnerIterator it(m_fe, fi); it; ++it)
        {
            if (std::abs(it.col()) == 1)
                indices[0] = it.index();
            else if (std::abs(it.col()) == 2)
                indices[1] = it.index();
            else if (std::abs(it.col()) == 3)
                indices[2] = it.index();
        }
    }

    std::vector<size_t> &Mesh::GetFE(size_t fi)
    {
        std::vector<size_t> indices(3);

        if (m_fe.size() == 0)
        {
            m_fe = m_ef.transpose();
        }

        for (Eigen::SparseMatrix<int>::InnerIterator it(m_fe, fi); it; ++it)
        {
            if (std::abs(it.col()) == 1)
                indices[0] = it.index();
            else if (std::abs(it.col()) == 2)
                indices[1] = it.index();
            else if (std::abs(it.col()) == 3)
                indices[2] = it.index();
        }

        return indices;
    }

    void Mesh::BuildTopology()
    {
        // LAR
        GetLAR(m_ev, m_ef);
    }

    void Mesh::GetLAR(Eigen::SparseMatrix<int> &mat_ev, Eigen::SparseMatrix<int> &mat_ef)
    {
        Eigen::MatrixXi EV, FE, EF; // EV:Ex2 FE:Fx3
        igl::edge_topology(this->vertices, this->faces, EV, FE, EF);

        mat_ev = Eigen::SparseMatrix<int>(EV.rows(), this->vertices.rows());
        for (size_t i = 0; i < EV.rows(); ++i)
        {
            int v_i = EV(i, 0);
            int v_j = EV(i, 1);
            mat_ev.insert(i, v_i) = -1;
            mat_ev.insert(i, v_j) = 1;
        }

        mat_ef = Eigen::SparseMatrix<int>(EF.rows(), this->faces.rows());
        for (size_t i = 0; i < EF.rows(); ++i)
        {
            int f_i = EF(i, 0);
            int f_j = EF(i, 1);
            mat_ef.insert(i, f_i) = 1;
            mat_ef.insert(i, f_j) = 1;
        }
    }

    Eigen::SparseMatrix<int> &Mesh::Circle(const Eigen::SparseMatrix<int> &a, const Eigen::SparseMatrix<int> &b)
    {
        if (a.rows() != b.cols())
        {
            throw std::runtime_error("INVALID circle operation!");
        }

        int d = 2;

        Eigen::SparseMatrix<int> tempSparse = a * b;

        for (size_t i = 0; i < tempSparse.rows(); ++i)
        {
            for (size_t j = 0; j < i; j++)
            {
                if (tempSparse.coeff(i, j) >= 2)
                {
                    int binResult = 0;
                    for (size_t index = 0; index < tempSparse.rows(); ++index)
                    {
                        binResult |= a.coeff(i, index) & b.coeff(index, i);
                    }
                }
            }
        }
    }

} // namespace PF
