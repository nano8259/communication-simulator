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
  
}

void Simulator::IncreaseSum(){
  sum += 1;
}

void Simulator::CalculateCentralizedResult(){
  int times;
  // *2, one for sending and one for receiving
  times = Grobal::host_num * Grobal::time_span / Grobal::shelf_life * 2;
  cout << "the times of communication in centralized approach is " << times << endl;
}