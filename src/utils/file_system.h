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

#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <iostream>

#include "../utils/definitions.h"

namespace simple
{
  class file_system
  {
  public:
    file_system();
    ~file_system();
  private:
    FILE* m_file;
    int f;
  public:
    void open(const char* path, const char* mode);
    size_t read(void* dest, size_t size, size_t count);
    size_t write(const void * str, size_t size, size_t count);
    int close();
  };
}

#endif
