# He-3 Mining Simulation Take Home Challenge
Run a single mining simulation over 72 hours for a number of user specified mining trucks and unloading stations, and compute mining truck and unloading station statistics to determine efficiency.

:warning: **NOTICE**: The simulation is incomplete. Only meaningful details shared with the user are mining truck statistics. See **To Do** section below for more detail.

## To Do
In order of descending importance:
* Fix `UnloadStationStats` class not correctly counting things.
* Expand unit test coverage. `MiningTruckStats` and `UnloadStationStats` classes do not have enough tests.
* Add ability to run multiple times with same number of mining trucks and unload stations for greater confidence in sample statistics.
* Refactor `*Stats` classes and the corresponding classes they are tracking. `*Stats` should track the accumulated statistics and individual stats should track its own statistics.
* Add more input validation for number of trucks and stations.
* Add more documentation.

## Installation
1. If necessary, install CMake and a C++ compiler.
2. In terminal, call the following commands sequentially:
```
$ git clone https://github.com/LiangJYu/VastTakeHome.git
$ cd VastTakeHome/
$ mkdir build; cd build
$ cmake ..
$ make
```

## Usage
In terminal from the `build` directory, execute: `./moon $N_TRUCKS $N_STATIONS`. Both `$N_TRUCKS` and  `$N_STATIONS` need to be greater than 0 due to severely lacking input validation. Example:
```
$ ./moon_mining 10 3                                                            
n_trucks 10, n_stations 3                                                                                              
transit      mean =    1330.50, std =     142.30, percent =  31.12                                                     
mining       mean =    2478.70, std =     177.27, percent =  57.99                                                     
in_queue     mean =     356.00, std =      30.71, percent =   8.33                                                     
unloading    mean =     109.50, std =      11.06, percent =   2.56                                                     
trips        mean =      21.90, std =       2.21, percent =   0.00 
```
## How It Works
The simulation is driven by processing a min-heap priority queue.
* min-heap priority queue holds events of when the state of a mining truck changes and other relevant details. 
* min-heap priority queue is keyed on the time when an event is to occur thus ensuring that the earliest event is processed.

An event can either be the completion of mining trip (mining and round-trip from station to mine) or unloading (with possible queuing to unload).

When an event is processed:
* changes to state of the mining truck and possibly associated unloading station are updated
* the statistics from just-occurred state are gathered
*  event popped off the priority queue 
* new event for the subsequent state is pushed into the priority queue. 

The cycle above continues until the simulation clock expires.

At the end of a simulation:
* time leftover in the state of each mining truck is accounted for
* statistics for all trucks and stations are computed
* results are printed to screen.
