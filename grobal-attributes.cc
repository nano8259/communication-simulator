/*
 * grobal-attributes.cc
 *
 *  Created on: Mar 20, 2021
 *      Author: zczhang
 */

#include "grobal-attributes.h"

#include <iostream>
#include <simpleini/SimpleIni.h>

using namespace std;

// predefined values 
int GrobalAttributes::host_num;
int GrobalAttributes::interval;
int GrobalAttributes::shelf_life;
int GrobalAttributes::time_span;
int GrobalAttributes::bandwidth;
GrobalAttributes::Pattern GrobalAttributes::pattern;
bool GrobalAttributes::debug;
int GrobalAttributes::seed;
double GrobalAttributes::select_ratio;
string GrobalAttributes::trace_file;
double GrobalAttributes::time_scale;

GrobalAttributes::GrobalAttributes(){
}

void GrobalAttributes::LoadSettings(string file){
  CSimpleIniA ini;
	SI_Error rc = ini.LoadFile(file.c_str());
	if (rc < 0) { cerr << "error in load .ini file!" << endl; };
	// ASSERT_EQ(rc, SI_OK);

  // begin to read config
  const char* section = "simulator";
  host_num = stoi(ini.GetValue(section, "hosts-number"));
  // cout << host_num << endl;
  interval = stoi(ini.GetValue(section, "interval"));
  shelf_life = stoi(ini.GetValue(section, "shelf-life"));
  time_span = stoi(ini.GetValue(section, "time-span"));
  bandwidth = stoi(ini.GetValue(section, "bandwidth"));
  debug = strcmp(ini.GetValue(section, "debug"), "true") == 0 ? true : false;

  const char* pv = ini.GetValue(section, "behavior-pattern");
  if(strcmp(pv, "poll") == 0){
    pattern = Pattern::poll;
  }else if(strcmp(pv, "random") == 0){
    pattern = Pattern::random;
  }else if(strcmp(pv, "trace") == 0){
    pattern = Pattern::trace;
  }else{
    cerr << "can not identify the bahavior pattern in " << file << endl;
  }

  // now read pattern specific attributes
  switch (pattern){
  case Pattern::poll:
    /* code */
    break;

  case Pattern::random:
    /* code */
    break;

  case Pattern::trace:
    /* code */
    break;
  
  default:
    break;
  }
}