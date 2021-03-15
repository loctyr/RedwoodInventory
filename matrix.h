#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <map>

template< class T1, class T2, unsigned int DIMENSION> class Matrix {
public:

    //!Default constructor of a cloud of point
    /*!Constructs a cloud object
        \param dimension vector dimensions of cloud
        \param refPoint reference point of cloud
        \param delta_ vector of delta for all axies
    */
    Cloud(std::vector<unsigned long> dimension,
          std::vector<T1> refPoint,
          std::vector<T1> delta_) {
        dim = dimension;
        referencePoint = refPoint;
        delta = delta_;
        data.clear();
    }

    //!Get dimension
    /*!Get dimension by index
        \param idx index of dimension
    */
    unsigned long getDimension(unsigned int idx) {
        if (idx >= DIMENSION) throw misc::mwIdxRangeException(DIMENSION, idx );
        return dim[idx];
    }

    //!Get delta
    /*!Get delta by index
        \param idx index of delta
    */
    T1& getDelta(const size_t idx) {
        if (idx >= DIMENSION) throw misc::mwIdxRangeException(DIMENSION, idx );
        return delta[idx];
    }

    bool isValidIndex(std::vector<unsigned long> idx) {
        if (DIMENSION != idx.size()) return false;
        for(unsigned int i = 0; i < DIMENSION; ++i) {
            if (idx[i] >= dim[i]) return false;
        }
        return true;
    }

    size_t calculateInternalIndex(std::vector<unsigned long> idx) {
        if (DIMENSION != idx.size()) throw misc::mwIdxRangeException(DIMENSION, idx.size() );
        size_t offset = 1;
        size_t internalIndex = offset*idx[0];
        for(unsigned int i = 1; i < DIMENSION; ++i) {
            offset *= dim[i-1];
            internalIndex += offset*idx[i];
        }
        return internalIndex;
    }

    std::vector<unsigned long> calculateExternalIndex(size_t idx) {
        std::vector<unsigned long> externalIndex;
        size_t offset = 1;
        for(unsigned int i = 0; i < DIMENSION; ++i) {
            externalIndex.push_back(idx/offset % dim[i]);
            offset *= dim[i];
        }
        return externalIndex;
    }

    //!Get index of point in cloud
    /*!Get item by index
        \param point vector of point coordinates
    */
    std::vector<unsigned long> getPointIndex(const std::vector<T1> point) {

        std::vector<unsigned long> result;

        if (DIMENSION != point.size()) throw misc::mwIdxRangeException(DIMENSION, point.size() );
        for(size_t i = 0;i < DIMENSION; ++i) {
            result.push_back(static_cast<unsigned long>((point[i]-referencePoint[i])/delta[i]));
        }

        return result;
    }

protected:
    std::vector<unsigned long> dim;
    std::vector<T1> referencePoint;
    std::vector<T1> delta;
    std::map<size_t,T2> data;
};

#endif //MATRIX_H
