/*
 * host.cc
 *
 *  Created on: Mar 20, 2021
 *      Author: zczhang
 */

#include "host.h"
#include "simulator.h"

Entry::Entry(int i, int u, int d, int t){
  this->id = i;
  this->up_bandwidth = u;
  this->down_bandwidth = d;
  this->timestamp = t;
}

Host::Host(int id, int host_num, int interval, Simulator *simulator)
:id(id), interval(interval), simulator(simulator){  
  for(int i = 0; i < host_num; i++){
    // unique_ptr<Entry> up(new Entry(i, BANDWIDTH, BANDWIDTH, 0));
    // this->table.push_back(move(up));
    this->table.push_back(make_unique<Entry>(i, BANDWIDTH, BANDWIDTH, 0));
  }
}

void Host::Update(int now){
  table[id]->timestamp = now;
  for(vector<unique_ptr<Entry>>::iterator iter = table.begin(); iter != table.end(); iter++){
    if(now - iter->get()->timestamp >= interval){
      simulator->hosts[iter->get()->id]->Notify(table, id);
    }
  }
}

void Host::CompareTable(vector<unique_ptr<Entry>>& t){
  int n = t.size();
  for(int i = 0; i < n; i++){
    this->table[i]->timestamp = this->table[i]->timestamp > t[i]->timestamp ? this->table[i]->timestamp : t[i]->timestamp;
  }
}

void Host::Notify(vector<unique_ptr<Entry>>& t, int id){
  CompareTable(t);
  simulator->hosts[id]->Acknowledge(table);
}

void Host::Acknowledge(vector<unique_ptr<Entry>>& t){
  CompareTable(t);
}