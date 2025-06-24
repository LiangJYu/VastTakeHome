#include <algorithm>
#include <cmath>
#include <format>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include "Stats.h"

double compute_std_dev(std::vector<unsigned int>& values, double mean) {
  double sq_sum = std::accumulate(values.begin(), values.end(), 0.0, [&mean](double accumulator, double y) {
    return accumulator + (static_cast<double>(y) - mean) * (static_cast<double>(y) - mean);
    });

  double variance = sq_sum / values.size();

  return sqrt(variance);
}

MiningTruckStats& MiningTruckStats::operator+=(const MiningTruckStats& other) {
  t_transit += other.t_transit;
  t_mining += other.t_mining;
  t_in_queue += other.t_in_queue;
  t_unloading += other.t_unloading;
  n_trips += other.n_trips;
  ++n_trucks;

  all_t_transit.push_back(other.t_transit);
  all_t_mining.push_back(other.t_mining);
  all_t_in_queue.push_back(other.t_in_queue);
  all_t_unloading.push_back(other.t_unloading);
  all_n_trips.push_back(other.n_trips);

  return *this;
}

void MiningTruckStats::print_stats() {
  const double n_trucks_dbl = static_cast<double>(n_trucks);

  std::vector<unsigned int> sums = {t_transit, t_mining, t_in_queue, t_unloading, n_trips};

  // Compute averages.
  std::vector<double> means;
  means.reserve(sums.size());
  std::transform(sums.begin(), sums.end(), std::back_inserter(means),
      [n_trucks_dbl](unsigned int x) { return static_cast<double>(x) / n_trucks_dbl; });

  // Compute standard deviations.
  std::vector<std::vector<unsigned int>> samples = {all_t_transit, all_t_mining, all_t_in_queue, all_t_unloading, all_n_trips};
  std::vector<double> stddevs;
  stddevs.reserve(samples.size());
  std::transform(samples.begin(), samples.end(), means.begin(), std::back_inserter(stddevs),
      [](std::vector<unsigned int>& sample, double mean) { return compute_std_dev(sample, mean); });

  // Print resulting stats.
  std::vector<std::string> val_names = {"transit", "mining", "in_queue", "unloading", "trips"};
  for (int i = 0; i < samples.size(); ++i) {
    std::cout << std::format("{:12} mean = {:10.2f}, std = {:10.2f}\n", val_names[i], means[i], stddevs[i]);
  }
}
