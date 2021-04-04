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
    void Notify(vector<unique_ptr<Entry>>& t, int id);
    void Reply(vector<unique_ptr<Entry>>& t);
    void PreNotify(int peer_id);
    void PreReply(int peer_id, vector<unique_ptr<Entry>>& feedback, vector<unique_ptr<Entry>>& received_table);
    vector<unique_ptr<Entry>>* CompareTable(vector<unique_ptr<Entry>>& table);
    void UpdateItself();
    void Update();
    void Poll();
    void RandomSelect();

    int id;
    Simulator *simulator;
    vector<unique_ptr<Entry>> table;
};

#endif // HOST_H_
