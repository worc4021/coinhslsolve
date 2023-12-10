#pragma once
#include <iostream>
#include <concepts>
#include <cassert>
#include <vector>
#include <span>


template<std::floating_point T>
struct CoordinateFormat
{
    std::vector<std::size_t> iRow;
    std::vector<std::size_t> jCol;
    std::vector<T> values;
    std::size_t mRows, nCols;
};

template<std::floating_point T>
class CSRMatrix
{
private:
    std::vector<T> values;
    std::vector<std::size_t> rowIndex;
    std::vector<std::size_t> jCol;
    std::size_t _mRows, _nCols;
    
public:
    CSRMatrix() = delete;
    CSRMatrix(std::size_t mRows, std::size_t nCols) : _mRows(mRows), _nCols(nCols), rowIndex(mRows+1,0) {}
    CSRMatrix(const CSRMatrix& other) = default;
    CSRMatrix(CSRMatrix&& other) = default;
    CSRMatrix& operator=(const CSRMatrix& other) = default;
    T& operator()(std::size_t i, std::size_t j) { 
        assert (i < _mRows && j < _nCols);
        if (nnz()){
            std::size_t k = rowIndex[i];
            while (k < jCol.size() && jCol.at(k) < j && k < rowIndex[i+1]) {
                k++;
            }
            if (k >= nnz()) {
                values.push_back(static_cast<T>(0));
                jCol.push_back(j);
                for (std::size_t k = i+1; k <= _mRows; k++) {
                    rowIndex[k]++;
                }
                return values.back();
            }
            else if (jCol.at(k) != j) {
                values.insert(values.begin() + k,static_cast<T>(0));
                jCol.insert(jCol.begin() + k, j);
                for (std::size_t k = i+1; k <= _mRows; k++) {
                    rowIndex[k]++;
                }
            }
            return values[k];
        } else {
            values.push_back(0);
            jCol.push_back(j);
            for (std::size_t k = i+1; k <= _mRows; k++) {
                rowIndex[k]++;
            }
            return values.back();
        }
    }


    void print() const {
        std::span<const T> valSpan(values);
        std::span<const std::size_t> colSpan(jCol);
        for (std::size_t iRow = 0; iRow < _mRows; iRow++) {
            auto cols = colSpan.subspan(rowIndex[iRow], rowIndex[iRow+1] - rowIndex[iRow]);
            auto vals = valSpan.subspan(rowIndex[iRow], rowIndex[iRow+1] - rowIndex[iRow]);
            for (std::size_t k = 0; k < cols.size(); k++) {
                std::cout << "("  << iRow << ", " << cols[k]  << ") = " <<vals[k] << std::endl;
            }
        }
    }

    CoordinateFormat<T> toCoordinateFormat() const {
        CoordinateFormat<T> result;
        result.iRow.reserve(nnz());
        result.jCol.reserve(nnz());
        result.values.reserve(nnz());
        std::span<const T> valSpan(values);
        std::span<const std::size_t> colSpan(jCol);
        for (std::size_t iRow = 0; iRow < _mRows; iRow++) {
            auto cols = colSpan.subspan(rowIndex[iRow], rowIndex[iRow+1] - rowIndex[iRow]);
            auto vals = valSpan.subspan(rowIndex[iRow], rowIndex[iRow+1] - rowIndex[iRow]);
            for (std::size_t k = 0; k < cols.size(); k++) {
                result.iRow.push_back(iRow);
                result.jCol.push_back(cols[k]);
                result.values.push_back(vals[k]);
            }
        }
        result.mRows = _mRows;
        result.nCols = _nCols;
        return result;
    }
    std::size_t nnz() const {
        if (rowIndex.size() == 0) 
            return 0;
        return rowIndex[_mRows];
    }

    void fromCoordinateFormat(const CoordinateFormat<T>& other) {
        _mRows = other.mRows;
        _nCols = other.nCols;
        values = other.values;
        jCol = other.jCol;
        for (std::size_t i = 0; i < other.iRow.size(); i++) {
            operator()(other.iRow[i], other.jCol[i]) = other.values[i];
        }
    }

    
};