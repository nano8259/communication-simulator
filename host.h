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
    // constructor to be used in init of the host
    Entry(int id);
    // copy constructor
    Entry(const Entry& e);

    int id;
    int up_bandwidth;
    int down_bandwidth;
    int timestamp;
};

class Host{
  public:
    Host(int id, Simulator *s);
    // must use reference pass instead of value pass
    // because the unique_ptr can not be reproduced
    void Notify(vector<unique_ptr<Entry>>& table, int id);
    void Reply(vector<unique_ptr<Entry>>& table);
    vector<unique_ptr<Entry>>* CompareTable(vector<unique_ptr<Entry>>& table);
    void Update(int now);
    void Poll(int now);
    void RandomSelect(int now);

    int id;
    Simulator *simulator;
    vector<unique_ptr<Entry>> table;
};

#endif // HOST_H_
