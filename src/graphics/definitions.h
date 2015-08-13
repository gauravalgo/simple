#ifndef DEFINITIONS_H
#define DEFINITIONS_H

namespace simple {

  typedef unsigned int uint;
  const float PI = 3.141592654f;

#define SAFE_DELETE(p) { if(p) { delete   (p); (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p); (p)=NULL; } }
}

#endif
