/*
 * host.h
 *
 *  Created on: Mar 20, 2021
 *      Author: zczhang
 */
#ifndef HOST_H_
#define HOST_H_

#define BANDWIDTH 1

#include <vector>
#include <memory>

//#include "simulator.h"

// forward declaration
class Simulator;

using namespace std;

class Entry{
  public:

    Entry(int i, int u, int d, int t);

    int id;
    int up_bandwidth;
    int down_bandwidth;
    int timestamp;
};

class Host{
  public:
    Host(int id, int host_num, int interval, Simulator *s);
    // must use reference pass instead of value pass
    // because the unique_ptr can not be reproduced
    void Notify(vector<unique_ptr<Entry>>& table, int id);
    void Acknowledge(vector<unique_ptr<Entry>>& table);
    void CompareTable(vector<unique_ptr<Entry>>& table);
    void Update(int now);

    int id;
    int interval;
    int up_bandwidth;
    int down_bandwidth;
    Simulator *simulator;
    vector<unique_ptr<Entry>> table;
};

#endif // HOST_H_
