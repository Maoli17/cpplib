/**
 * Copyright (C) by J.Z. (06/30/2017 20:06)
 * Distributed under terms of the MIT license.
 */

#ifndef __TRIAD_H__
#define __TRIAD_H__

#include <vector>
#include <unordered_map>
#include <algorithm>

namespace graph {
/**
 * Count the number of directed triads the node belonging to
 */
template <class Graph>
int countNodeDirTriads(const Graph& G, const int& node) {
    if (G.getNode(node).getDeg() < 2) return 0;
    int closed_triads = 0;
    // get unique neighbors
    std::unordered_map<int, int> nbr_cnt;
    auto& nd_obj = G.getNode(node);
    for (int d = 0; d < nd_obj.getDeg(); d++) {
        int nbr = nd_obj.getNbr(d);
        if (nbr != node) nbr_cnt[nbr]++;
    }
    std::vector<int> nbr_vec;
    nbr_vec.reserve(nbr_cnt.size());
    for (auto& it : nbr_cnt) nbr_vec.push_back(it.first);
    // count connected neighbors
    for (int i = 0; i < nbr_vec.size(); i++) {
        int src = nbr_vec[i];
        auto& src_obj = G.getNode(src);
        std::unordered_map<int, int> src_nbr_cnt;
        for (int d = 0; d < src_obj.getDeg(); d++)
            src_nbr_cnt[src_obj.getNbr(d)]++;
        for (int j = i + 1; j < nbr_vec.size(); j++) {
            int dst = nbr_vec[j];
            closed_triads += src_nbr_cnt[dst] * nbr_cnt[src] * nbr_cnt[dst];
        }
    }
    return closed_triads;
}

/**
 * state the triads frequency, i.e., how many nodes have a particular number of
 * triads.
 */
template <class Graph>
std::vector<std::pair<int, int>> statDirTriads(const Graph& G) {
    std::vector<std::pair<int, int>> triads_hist;
    std::unordered_map<int, int> triads_map;
    for (auto&& ni = G.beginNI(); ni != G.endNI(); ni++)
        triads_map[countNodeDirTriads(G, ni->first)]++;
    for (auto& it : triads_map) triads_hist.emplace_back(it.first, it.second);
    std::sort(triads_hist.begin(), triads_hist.end());
    return triads_hist;
}

} /* end of namespace graph */

#endif /* __TRIAD_H__ */