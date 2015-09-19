local width = 620
local height = 480

local ortho;
local image;
local batch;
local shader;

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

   simple.window.create("Simple - A new era", width, height)

   --shader = simple.graphics.newDefaultShader("texture")
   shader = simple.graphics.newShader(gl_texture_vertex,gl_texture_fragment);
   font_shader = simple.graphics.newDefaultShader("font")

   image = simple.graphics.newImage("res/test3.png")

   batch = simple.graphics.newBatch(shader, 17000)
   simple.getVersion()

   font = simple.graphics.newFont(font_shader, "res/vera.ttf", 24)
end

local rotation = 10
function simple.draw()
   simple.graphics.clearScreen(125, 114, 89, 255)
   simple.graphics.setViewport(0, 0, width, height);

   --shader:bindShader()
end

local timer = 2;
function simple.update(delta)
   rotation = rotation + 108 * delta;
end
