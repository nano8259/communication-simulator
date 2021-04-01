/*
 * host.cc
 *
 *  Created on: Mar 20, 2021
 *      Author: zczhang
 */

#include <iostream>

#include "host.h"
#include "simulator.h"
#include "grobal-attributes.h"

Entry::Entry(int id)
:id(id), timestamp(0), up_bandwidth(Grobal::bandwidth), down_bandwidth(Grobal::bandwidth){
}

Entry::Entry(const Entry& e){
  id = e.id;
  timestamp = e.timestamp;
  up_bandwidth = e.up_bandwidth;
  down_bandwidth = e.down_bandwidth;
}

Host::Host(int id, Simulator *simulator)
:id(id), simulator(simulator){ 
  // init entry table of all hosts 
  for(int i = 0; i < Grobal::host_num; i++){
    this->table.push_back(make_unique<Entry>(i));
  }
}

void Host::Update(int now){
  // update timestamp of itself
  table[id]->timestamp = now;

  // find expired entry
  for(vector<unique_ptr<Entry>>::iterator iter = table.begin(); iter != table.end(); iter++){
    if(now - iter->get()->timestamp >= Grobal::shelf_life){
      simulator->hosts[iter->get()->id]->Notify(table, id);
    }
  }
}

vector<unique_ptr<Entry>>* Host::CompareTable(vector<unique_ptr<Entry>>& t){
  int n = t.size();
  vector<unique_ptr<Entry>>* feedback = new vector<unique_ptr<Entry>>;

  for(int i = 0; i < n; i++){
    int entry_id = table[i]->id;
    
    if(table[entry_id]->timestamp > t[i]->timestamp){
      // local entry is newer than peer's
      feedback->push_back(make_unique<Entry>(*(table[entry_id].get())));
    }else{
      table[entry_id]->timestamp = t[i]->timestamp;
    }
  }

  return feedback;
}

void Host::Notify(vector<unique_ptr<Entry>>& t, int id){
  simulator->IncreaseSum();

  vector<unique_ptr<Entry>>* feedback =  CompareTable(t);
  if(!feedback->empty()){
    // if feedback is not empty, then reply the feedback
    simulator->hosts[id]->Reply(table);
  }

  // for debug
  if(Grobal::debug){
      cout << "this is " << this->id << " being notified by " << id 
        << ", and the feedback size is " << feedback->size() << endl;
  }
}

void Host::Reply(vector<unique_ptr<Entry>>& t){
  simulator->IncreaseSum();

  vector<unique_ptr<Entry>>* feedback =  CompareTable(t);
  if(!feedback->empty()){
    cerr << "the feedback is not empty!" << endl;
  }

  if(Grobal::debug){
      cout << "this is " << this->id << " being replied"
        << ", and the feedback size is " << feedback->size() << endl;
  }
}