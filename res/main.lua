local width = 620
local height = 480

local ortho;
local image;
local batch;
local shader;
local image2;
local image3;
function simple_init()
   simple.window.create("Simple - A new era", width, height)
   simple.graphics.setViewport(0, 0, width, height);

   shader = simple.graphics.newShader()
   image = simple.graphics.loadTexture("res/test.png")
   image2 = simple.graphics.loadTexture("res/test1.png")
   image3 = simple.graphics.loadTexture("res/test2.png")

   batch = simple.graphics.newBatch(shader,7000)
   simple.math.setOrtho(0,width,height,0,0,100,shader)
   --simple.getVersion()
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
   --texture2
   simple.graphics.bindTexture(image)
   --  for i=1, 20 do
   simple.graphics.drawBatch(batch, x, 300, w, h, 0, originX, originY)
   simple.graphics.drawBatch(batch, x, 100, w*2, h*2, rotation, originX*2, originY*2)
   --end
   simple.graphics.renderMesh(batch)
   simple.graphics.unBindTexture(image)
   --texture2
   simple.graphics.endBatch(batch)

   simple.graphics.unBindShader(shader)

end

local timer = 2;
function simple_update()
   timer = timer + 2 * simple.time.delta();
   if timer > 4 then 
      print("Ticks:" .. simple.time.getTicks())
      print("FPS: " .. simple.time.getFPS())
      timer = 0
   end
   rotation = rotation + 108 * simple.time.delta();

   x = x + 40 * simple.time.delta();
   y = y + 40 * simple.time.delta();
end

function simple_dumb()
   --simple_dumbShader(shader);
   --simple_dumbBatch(batch);
   --simple_dumbTexture(image);
   -- simple_dumbTexture(image2);
   --simple_dumbTexture(image3);
end
