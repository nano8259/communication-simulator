/*
 * grobal-attributes.cc
 *
 *  Created on: Mar 28, 2021
 *      Author: zczhang
 */

#ifndef GROBAL_ATTRIBUTES_H_
#define GROBAL_ATTRIBUTES_H_

#include <string>

using namespace std;

class GrobalAttributes{
public:
  static int host_num;
  static int interval;
  static int shelf_life;
  static int time_span;

  GrobalAttributes(/* args */);
  ~GrobalAttributes();

  static void LoadSettings(string file);
};

// for ease of use 
// maybe a bad behavior :(
typedef GrobalAttributes Grobal;

#endif //GROBAL_ATTRIBUTES_H_