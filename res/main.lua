local width = 620
local height = 480

local ortho;
local image;
local batch;
local shader;
local font_shader;
local font;

function simple_init()
   simple.window.create("Simple - A new era", width, height)

   shader = simple.graphics.newDefaultShader("texture")
   font_shader = simple.graphics.newDefaultShader("font")

   image = simple.graphics.loadTexture("res/test3.png")

   batch = simple.graphics.newBatch(shader, 17000)
   simple.getVersion()

   font = simple.graphics.newFont(font_shader, "res/vera.ttf", 24)
end
local x = 100
local y = 100
local rotation = 10
local w = 32;
local h = 32;
local originX = w / 2
local originY = h / 2
function simple_draw()
   simple.graphics.clearScreen(125, 114, 89, 255)
   simple.graphics.setViewport(0, 0, width, height);

   simple.graphics.bindShader(shader)
   simple.math.setOrtho(0, width, height, 0, 0, 100, shader)

   simple.graphics.beginBatch(batch)
   simple.graphics.bindTexture(image)
   simple.graphics.drawBatch(batch, 100, 100, w, h, rotation, originX, originY, 0, 0, 16, 32)

   simple.graphics.renderMesh(batch)
   simple.graphics.unBindTexture(image)
   simple.graphics.endBatch(batch)

   simple.graphics.bindShader(font_shader)
   simple.math.setOrtho(0, width, height, 0, 0, 100, font_shader)
   simple.graphics.beginFont(font);
   simple.graphics.drawFont(font, font_shader, "Hello World", 200, 100, 1,1, 255, 120, 120, 255)
   simple.graphics.endFont(font);
end

local timer = 2;
function simple_update(delta)
  rotation = rotation + 108 * delta;

  if(simple.input.isKeyDown("esc")) then
     simple.quit()
  end

  if simple.input.isKeyDown("d") then
     x = x + 120 * delta;
  end
  if simple.input.isKeyDown("a") then
     x = x - 120 * delta;
  end
  if simple.input.isKeyDown("s") then
     y = y + 120 * delta;
  end
  if simple.input.isKeyDown("w") then
     y = y - 120 * delta;
  end
  print(simple.time.getFPS());
end

function simple_dumb()

   print("SIMPLE DUMP")
   --simple_dumpBatch(batch);
   --simple_dumpShader(shader) --make it work !
   --simple_dumpTexture(image);
end
