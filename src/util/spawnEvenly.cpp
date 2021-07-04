#include <vector>

#include "../vectors.h"

std::vector<RealPos> spawnEvenly(int width, int height, int count)
{
    std::vector<RealPos> toReturn;
    int h = 0, n_hor = std::ceil(std::sqrt(count)), n_ver = std::ceil((static_cast<float>(count) / n_hor));
    toReturn.reserve(n_hor * n_ver);

    auto commitToList = [&toReturn, width, height, n_hor, n_ver] (int h, int v)
    {
        RealPos spawnPos(width, height);
        spawnPos /= RealPos(n_hor, n_ver);
        spawnPos *= RealPos(h, v);
        toReturn.push_back(spawnPos);

    };

    for(; h < n_hor - 1; ++h)
    {
        int v = 0;
        for (; v < n_ver; ++v)
        {
            commitToList(h, v);

        }
    }

    assert (h == n_hor - 1); // TODO redundant?
    int remaining = count - h * n_ver;

    for(int v = 0; v < remaining; ++v )
    {
        commitToList(h,v);
    }

    return toReturn;
}
