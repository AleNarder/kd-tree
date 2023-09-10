#ifndef KD_POINT_HPP
#define KD_POINT_HPP

#include <vector>
#include <math.h>

typedef std::vector<float> KdPoint;

inline bool operator==(KdPoint pt1, KdPoint pt2)
{

    if (pt1.size() != pt2.size())
        return false;

    for (std::vector<float>::size_type i = 0; i < pt1.size(); i++)
    {
        if (pt1[i] != pt2[i])
            return false;
    };

    return true;
}

inline bool operator!=(KdPoint pt1, KdPoint pt2)
{
    return !(pt1 == pt2);
};

inline float euc_kd_distance(KdPoint pt1, KdPoint pt2)
{
    float dist = 0.0;

    for (std::vector<float>::size_type i = 0; i < pt1.size(); i++)
    {
        dist += pow(pt1[i] - pt2[i], 2);
    };

    return sqrt(dist);
};

#endif