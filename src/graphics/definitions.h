#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <iostream>
using namespace std;

namespace simple {

  typedef unsigned int uint;
  const float PI = 3.141592654f;

#define VERSION "0.0.1"
#define DEBBUG 1

#define LOG(m) std::cout << m << std::endl;

#define SAFE_DELETE(p) { if(p) { delete   (p); (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p); (p)=NULL; } }
}

#endif
