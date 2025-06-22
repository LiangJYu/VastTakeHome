#ifndef STATS_H
#define STATS_H

#include <tuple>
#include <vector>

struct MiningTruckStats
{
    unsigned int t_transit;
    unsigned int t_mining;
    unsigned int t_in_queue;
    unsigned int t_unloading;
    unsigned int n_trips;

    MiningTruckStats()
        : t_transit(0)
        , t_mining(0)
        , t_in_queue(0)
        , t_unloading(0)
        , n_trips(0) {}
};

struct UnloadStationStats
{
    unsigned int n_unloads;

    // Convienence typedef to reduce verbosity.
    typedef std::tuple<unsigned int, unsigned int> queue_len_time_pair;

    // Vector of queue length and time of queue length change.
    std::vector<queue_len_time_pair> queue_len_vs_time;

    UnloadStationStats()
        : n_unloads(0)
    {
        queue_len_vs_time.push_back(queue_len_time_pair(0, 0));
    }

    void add_queue_stat(unsigned int len, unsigned int t_add) {
        queue_len_vs_time.push_back(queue_len_time_pair(len, t_add));
    }
};

#endif
