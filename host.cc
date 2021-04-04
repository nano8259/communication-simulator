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

void Host::UpdateItself(){
  // update timestamp of itself
  int now = simulator->now;
  table[id]->timestamp = now;
}

void Host::Update(){
  // Update expired entries
  if(Grobal::pattern == Grobal::Pattern::poll){
    Poll();
  }else if(Grobal::pattern == Grobal::Pattern::random){
    RandomSelect();
  }
}

void Host::Poll(){
  // find expired entry
  int now = simulator->now;
  for(vector<unique_ptr<Entry>>::iterator iter = table.begin(); iter != table.end(); iter++){
    if(now - iter->get()->timestamp > Grobal::shelf_life){
      simulator->hosts[iter->get()->id]->Notify(table, id);
    }
  }
}

void Host::RandomSelect(){
  int now = simulator->now;
  // now randomly select hosts
  int select_num = Grobal::host_num * Grobal::select_ratio;
  vector<int> selected_hosts;
  while(selected_hosts.size() < select_num){
    int selected_host = Grobal::dist_host(Grobal::rng);
    // the selected host must not be itself
    if(selected_host == id){
      continue;
    }
    // the selected host must not be the same
    for(auto it =  selected_hosts.begin(); it != selected_hosts.end(); it++){
      if(selected_host == *it){
        continue;
      }
    }

    selected_hosts.push_back(selected_host);
  }

  // now poll the selected hosts
  for(auto it = selected_hosts.begin(); it != selected_hosts.end(); it++){
    int selected_host = *it;
    if(now - table[selected_host]->timestamp > Grobal::shelf_life){
      if(Grobal::reduce_mode){
        PreNotify(selected_host);
      }else{
        simulator->hosts[selected_host]->Notify(table, id);
      }
    }
  }
}

void Host::PreNotify(int peer_id){
  // select the unexpired entries to send
  int now = simulator->now;
  vector<unique_ptr<Entry>>* send_table = new vector<unique_ptr<Entry>>;
  for(int i = 0; i < Grobal::host_num; i++){
    if(now - table[i]->timestamp <= Grobal::shelf_life){
      send_table->push_back(make_unique<Entry>(*(table[i].get())));
    }
  }

  // send selected entries
  simulator->hosts[peer_id]->Notify(*send_table, id);
}

vector<unique_ptr<Entry>>* Host::CompareTable(vector<unique_ptr<Entry>>& t){
  int n = t.size();
  vector<unique_ptr<Entry>>* feedback = new vector<unique_ptr<Entry>>;

  for(int i = 0; i < n; i++){
    int entry_id = t[i]->id;
    
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
  simulator->IncreaseDataAmount(t.size());

  vector<unique_ptr<Entry>>* feedback =  CompareTable(t);
  if(!feedback->empty()){
    // if feedback is not empty, then reply the feedback
    if(Grobal::reduce_mode){
      PreReply(id, *feedback, t);
    }else{
      simulator->hosts[id]->Reply(*feedback);
    }
  }

  // for debug
  if(Grobal::debug){
      cout << "this is " << this->id << " being notified by " << id 
        << ", and the feedback size is " << feedback->size() << endl;
  }
}

void Host::PreReply(int peer_id, vector<unique_ptr<Entry>>& feedback, vector<unique_ptr<Entry>>& received_table){
  int now = simulator->now;
  
  for(int i = 0; i < Grobal::host_num; i++){
    if(now - table[i]->timestamp <= Grobal::shelf_life){
      // the i-th entry is unexpired
      bool is_in_receive_table = false;
      for(auto it = received_table.begin(); it != received_table.end(); it++){
        if(i == it->get()->id){
          // the entry is in received_table
          is_in_receive_table = true;
        }
      }

      if(!is_in_receive_table){
        // the i-th entry is unexpired and not in received_table
        feedback.push_back(make_unique<Entry>(*(table[i].get())));
      }
    }
  }

  simulator->hosts[peer_id]->Reply(feedback);
}

void Host::Reply(vector<unique_ptr<Entry>>& t){
  simulator->IncreaseSum();
  simulator->IncreaseDataAmount(t.size());

  vector<unique_ptr<Entry>>* feedback =  CompareTable(t);
  if(!feedback->empty()){
    cerr << "the feedback is not empty! ..but it is all right" << endl;
  }

  if(Grobal::debug){
      cout << "this is " << this->id << " being replied"
        << ", and the feedback size is " << feedback->size() << endl;
  }
}