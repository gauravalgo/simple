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

#include "file_system.h"

using namespace simple;

#include <stdarg.h>
#include <iostream>
#include <stdio.h>

file_system::file_system()
{
  
}

file_system::~file_system()
{

}

void file_system::open(const char* path, const char* mode)
{
  close();
  file_system::m_file = fopen(path,mode);
}

int file_system::close()
{
  int v = 0;
  if(m_file){
    v = fclose(m_file);
    m_file = 0;
  }
  return v;
}

size_t file_system::read(void* dest, size_t size, size_t count)
{
  if(m_file)
    return fread(dest, size, count, m_file);
  return 0;
}

size_t file_system::write(const void * str, size_t size, size_t count)
{
  if(m_file)
    return fwrite(str, size, count, m_file);
  return 0;
}



