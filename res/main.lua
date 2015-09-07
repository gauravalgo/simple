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

   image = simple.graphics.loadTexture("res/test.png")

   batch = simple.graphics.newBatch(shader, 7000)
   simple.getVersion()

   font = simple.graphics.newFont(font_shader, "res/vera.ttf")
   --simple.graphics.setFontSize(font, 12);

end
local x = 100
local y = 100
local rotation = 10
local w = 32;
local h = 32;
local originX = w / 2
local originY = h / 2
function simple_draw()

   simple.graphics.clearScreen(.4,.5,.2,1)
   simple.graphics.setViewport(0, 0, width, height);

   simple.graphics.bindShader(shader)
   simple.math.setOrtho(0, width, height, 0, 0, 100, shader)
   simple.graphics.beginBatch(batch)
   simple.graphics.bindTexture(image)
   simple.graphics.drawBatch(batch, 70, 300, w, h, 0, originX, originY)
   simple.graphics.drawBatch(batch, 112, 100, w*2, h*2, rotation, originX*2, originY*2)
   simple.graphics.drawBatch(batch, x, y, w, h, 180, originX, originY)
   simple.graphics.renderMesh(batch)
   simple.graphics.unBindTexture(image)
   simple.graphics.endBatch(batch)

   simple.graphics.bindShader(font_shader)
   simple.math.setOrtho(0, width, height, 0, 0, 100, font_shader)
   simple.graphics.beginFont(font);
   simple.graphics.drawFont(font, font_shader, "Hello World", 100, 100, 1, 1, .9, .8, .87)
   simple.graphics.endFont(font);
end

local timer = 2;
function simple_update(delta)
  rotation = rotation + 108 * delta;

  if simple.input.isKeyDown("d") then
     simple.quit()
     x = x + 120 * delta;
  end
  if simple.input.isKeyDown("a") then
     x = x - 120 * delta;
  end
end

function simple_dumb()

   print("SIMPLE DUMP")
   --simple_dumpBatch(batch);
   --simple_dumpShader(shader) --make it work !
   --simple_dumpTexture(image);
end
