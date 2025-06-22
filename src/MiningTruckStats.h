#ifndef MININGTRUCKSTATS_H
#define MININGTRUCKSTATS_H

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

#endif
