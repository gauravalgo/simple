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

#ifndef MESH_H
#define MESH_H
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "shader.h"
#include <vector>
#include <iostream>


namespace simple
{
class mesh
{
public:
    mesh();
    ~mesh();
private:
int m_position_attribute;
int m_color_attribute;
int m_tex_attribute;
shader* m_shader;
public:
float* m_vertices;
short* m_indices;
    void create(shader &a_shader, float vertices[], int sizeV, short indices[], short sizeI);
    void draw(int count);
};
}
#endif
