local width = 620
local height = 480

local ortho;
local image;
local batch;
local shader;
local image2;
local image3;
function simple_init()
   simple_makeWindow("Simple - 0.2.0", width, height)
   simple_setWindowPosition(-1, -1)
   simple_setWindowVSync(true)
   simple_setViewport(0, 0, width, height);
 
 shader = simple_makeShader()	
 image = simple_loadTexture("res/test.png")
 image2 = simple_loadTexture("res/test1.png")
 image3 = simple_loadTexture("res/test2.png")
 
batch = simple_makeBatch(shader)
 simple_makeOrthoView(0,width,height,0,0,100,shader)
end
local x = 100
local y = 100
function simple_draw()
   simple_clearScreen(.4,.5,.2,1)
    simple_bindShader(shader)
  

   simple_beginBatch(batch) 
   --texture2
   simple_bindTexture(image3)
   simple_drawBatch(batch, 300, 100, 25, 25)
   simple_renderMesh(batch)
   simple_unBindTexture(image3)
   --texture2
   simple_endBatch(batch)

   simple_beginBatch(batch) 
   --texture2
   simple_bindTexture(image2)
   simple_drawBatch(batch, 100, 100, 40, 40)
   simple_renderMesh(batch)
   simple_unBindTexture(image2)
   --texture2
   simple_endBatch(batch)

   --texture3
    simple_beginBatch(batch)
   simple_bindTexture(image)
   simple_drawBatch(batch, 200, 200, 40, 40)
   simple_renderMesh(batch)
   simple_unBindTexture(image)
       simple_endBatch(batch)
   --texture3

simple_unBindShader(shader)

end

local timer = 2;
function simple_update()
   timer = timer + 2 * simple_getDeltaTime();
   if timer > 4 then 
      print("FPS: " .. simple_getFPS()) 
      timer = 0
   end
	x = x + 40 * simple_getDeltaTime();
	y = y + 40 * simple_getDeltaTime();
end
