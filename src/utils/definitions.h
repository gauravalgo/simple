/*******************************************************************************
 * Copyright 2015 See AUTHORS file.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <cmath>
#include <iostream>

using namespace std;

namespace simple {
  
  typedef unsigned int uint;
  typedef unsigned int ushort;
  typedef unsigned char uchar;
  
#define DEBBUG 1
#define VERSION "0.2.3"
  
#define PI (atan(1) * 4)
#define RADIANS(deg)  ((deg) * PI / 180)
#define DEGREES(rad)  ((rad) * 180 / PI)

#define LOG(m) cout << m << endl
#define LENGTH(v) (sizeof(v)/sizeof(*v))

#define SAFE_DELETE(p) { if(p != NULL) { delete (p); (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p != NULL) { delete[] (p); (p)=NULL; } }
#define SAFE_FREE(p) {if (p != NULL){ free(p); p = NULL; }}
}

#endif
