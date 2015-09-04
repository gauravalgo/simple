local width = 620
local height = 480

local ortho;
local image;
local batch;
local shader;

function simple_init()
   simple.window.create("Simple - A new era", width, height)
   simple.graphics.setViewport(0, 0, width, height);

   shader = simple.graphics.newDefaultShader()
   image = simple.graphics.loadTexture("res/test.png")

   batch = simple.graphics.newBatch(shader, 7000)
   simple.math.setOrtho(0,width,height, 0, 0, 100, shader)
   simple.getVersion()

   --W,H = simple.window.getSize()
   --print(W .. " " .. H)
   print("SIMPLE_INIT")
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
   simple.graphics.bindShader(shader)

   simple.graphics.beginBatch(batch)
   simple.graphics.bindTexture(image)
   simple.graphics.drawBatch(batch, 70, 300, w, h, 0, originX, originY)
   simple.graphics.drawBatch(batch, 112, 100, w*2, h*2, rotation, originX*2, originY*2)
   simple.graphics.drawBatch(batch, x, y, w, h, 180, originX, originY)
   simple.graphics.renderMesh(batch)
   simple.graphics.unBindTexture(image)
   simple.graphics.endBatch(batch)

   simple.graphics.unBindShader(shader)
end

local timer = 2;
function simple_update(delta)
  rotation = rotation + 108 * delta;

  if simple.input.isKeyDown("d") then
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
