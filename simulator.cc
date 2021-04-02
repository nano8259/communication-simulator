/*
 * simulator.cc
 *
 *  Created on: Mar 20, 2021
 *      Author: zczhang
 */
#include <iostream>

#include "simulator.h"
#include "grobal-attributes.h"

Simulator::Simulator()
:sum(0){
  for(int i = 0; i < Grobal::host_num; i++){
    hosts.push_back(make_unique<Host>(i, this));
  }
}

void Simulator::IncreaseSum(){
  sum += 1;
}

void Simulator::CalculateCentralizedResult(){
  int times;
  // *2, one for sending and one for receiving
  times = Grobal::host_num * Grobal::time_span / Grobal::shelf_life * 2;
  cout << "the times of communication in centralized approach is " << times << endl;
  // data amount: half of the communication contains data of host itself, 
  // and the other half contains all hosts' infomation
  cout << "the amount of data to transfer in centralized approach is " << 
    times * Grobal::host_num / 2 + times << endl;
}

void Simulator::Run(){
  for(int now = 0; now < Grobal::time_span; now += Grobal::interval){
    for(int i = 0; i < Grobal::host_num; i++){
      hosts[i]->Update(now);
    }
  }

  cout << "simulation end" << endl;
  cout << "the times of communication in decentralized approach is " << sum << endl;
}