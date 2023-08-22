#ifndef KD_POINT_HPP
#define KD_POINT_HPP

#include <vector>
#include <math.h>

typedef std::vector<float> KD_Point;

inline bool operator==(KD_Point pt1, KD_Point pt2)
{

    if (pt1.size() != pt2.size())
        return false;

    for (int i = 0; i < pt1.size(); i++)
    {
        if (pt1[i] != pt2[i])
            return false;
    };

    return true;
}

inline bool operator!=(KD_Point pt1, KD_Point pt2)
{
    return !(pt1 == pt2);
};

inline float euc_kd_distance(KD_Point pt1, KD_Point pt2)
{
    float dist = 0.0;

    for (int i = 0; i < pt1.size(); i++)
    {
        dist += pow(pt1[i] - pt2[i], 2);
    };

    return sqrt(dist);
};

#endif