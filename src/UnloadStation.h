#ifndef UNLOADSTATION_H
#define UNLOADSTATION_H

#include <queue>
#include "Constants.h"
#include "Stats.h"

class UnloadStation {
  unsigned int id;
  unsigned int id_current_truck_unloading;
  unsigned int t_unload_end;
  std::queue<unsigned int> waiting_queue;
  UnloadStationStats stats;

public:
  UnloadStation(unsigned int id = Constants::INVALID_ID)
      : id(id), id_current_truck_unloading(Constants::INVALID_ID), t_unload_end(Constants::unload_time){};

  unsigned int get_id() const { return id; }

  std::size_t get_queue_length() const { return waiting_queue.size(); }

  unsigned int get_wait_time() const {
    return static_cast<unsigned int>(waiting_queue.size()) *
           Constants::unload_time;
  }

  unsigned int get_current_truck_id() const {
    return id_current_truck_unloading;
  }

  UnloadStationStats get_stats() const { return stats; }

  unsigned int assign_truck_get_queue_pos(unsigned int truck_id,
                                          unsigned int t_now);

  unsigned int dispatch_truck(unsigned int t_now);
};

#endif // UNLOADSTATION_H
