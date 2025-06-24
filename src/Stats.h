#ifndef STATS_H
#define STATS_H

#include <tuple>
#include <vector>

struct MiningTruckStats {
  unsigned int t_transit;
  unsigned int t_mining;
  unsigned int t_in_queue;
  unsigned int t_unloading;
  unsigned int n_trips;
  unsigned int n_trucks;

  std::vector<unsigned int> all_t_transit;
  std::vector<unsigned int> all_t_mining;
  std::vector<unsigned int> all_t_in_queue;
  std::vector<unsigned int> all_t_unloading;
  std::vector<unsigned int> all_n_trips;

  MiningTruckStats()
      : t_transit(0), t_mining(0), t_in_queue(0), t_unloading(0), n_trips(0), n_trucks(0) {}

  MiningTruckStats& operator+=(const MiningTruckStats& other);

  void print_stats();
};

struct UnloadStationStats {
  unsigned int n_unloads;

  unsigned int n_stations;

  // Convienence typedef to reduce verbosity.
  // First unsigned int is queue size. Second unsigned int is t_start.
  typedef std::tuple<unsigned int, unsigned int> queue_len_time_pair;

  // Vector of queue length and time of queue length change.
  std::vector<queue_len_time_pair> queue_len_vs_time;

  UnloadStationStats() : n_unloads(0) {
    queue_len_vs_time.push_back(queue_len_time_pair(0, 0));
  }

  void add_queue_stat(unsigned int len, unsigned int t_add) {
    queue_len_vs_time.push_back(queue_len_time_pair(len, t_add));
  }
};

#endif
