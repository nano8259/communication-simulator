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
  GrobalAttributes::LoadSettings("config.ini");
  // cout << Grobal::host_num << endl;
  Simulator simulator;
  simulator.CalculateCentralizedResult();
  return 0;
}