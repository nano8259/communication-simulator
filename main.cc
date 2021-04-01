/*
 * main.cc
 *
 *  Created on: Mar 21, 2021
 *      Author: zczhang
 */

#include <iostream>

#include "grobal-attributes.h"
#include "simulator.h"

int main(int argc, char** argv){
  if(argc != 2){
    cerr << "please specify the config file!" << endl;
    return -1;
  }
  GrobalAttributes::LoadSettings(argv[1]);
  // cout << Grobal::host_num << endl;
  Simulator simulator;
  simulator.CalculateCentralizedResult();
  simulator.Run();
  return 0;
}