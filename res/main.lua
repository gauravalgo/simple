local w = 620
local h = 480

local ortho;
local image;
local batch;
local shader;
local _math;
local window;

local gl_texture_fragment;
local gl_texture_vertex;

function simple.load()
   gl_texture_vertex =
      "#version 130\n" ..
   "in vec2 position;" ..
   "in vec4 color;" ..
   "in vec2 texcoords;" ..
   "out vec4 Color;" ..
   "out vec2 Texcoords;" ..
   "uniform mat4 proj;" ..
   "void main(void) {" ..
   "Color = color;" ..
   "Texcoords = texcoords;" ..
   "gl_Position = proj *  vec4(position, 0.0f, 1.0f);" ..
   "}";
   gl_texture_fragment =
      "#version 130\n"..
   "in vec4 Color;" ..
   "in vec2 Texcoords;"..
   "uniform sampler2D tex;"..
   "void main(void) {"..
   "gl_FragColor = Color * texture2D(tex, Texcoords);"..
   "}";

   window = Window.new()
   window:init("Simple - A new era", w, h)

   shader = Shader.new()
   shader:init("texture");

   shader2 = Shader.new()
   shader2:init("font")

   font = Font.new()
   font:init(shader, "res/vera.ttf", 24)

   graphics = Graphics.new()

   _math = Math.new()

   batch = Batch.new()
   batch:init(shader,1200)

   image = Texture.new()
   image:init("res/test3.png")

   input = Input.new()
   simple.getVersion();
end

local rotation = 10
function simple.draw()
   graphics:clear(156,125,124,255)
   graphics:viewPort(0, 0, w, h)

   shader:bind()
   _math:setOrtho(shader, 0, w, h, 0, 0, 100)
   batch:begin()
   image:bind()
   batch:draw(100,100,16,16)
   batch:renderMesh()
   batch:stop()
   image:unbind()

   shader2:bind()
   font:begin()
   _math:setOrtho(shader2, 0, w, h, 0, 0, 100)
   font:draw(shader2, "Hello World", 200, 100, 1,1, 255, 120, 120, 255)
   font:stop()
end

local timer = 2;
function simple.update(delta)
   rotation = rotation + 108 * delta;
   if input:isKeyDown("esc") then
      simple.quit()
   end
end

function simple.dump()
   input:gc()
   font:gc()
   shader:gc()
   shader2:gc()
   batch:gc()
   window:gc()
end
