/*
 * simulator.h
 *
 *  Created on: Mar 20, 2021
 *      Author: zczhang
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <vector>
#include <memory>

#include "host.h"

using namespace std;

class Simulator{
  public:

    Simulator();
    void IncreaseSum();
    void Run();
    void CalculateCentralizedResult(); 

    int sum; // number of communication times
    vector<unique_ptr<Host>> hosts;
    
};

#endif // SIMULATOR_H_