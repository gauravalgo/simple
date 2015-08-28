local width = 620
local height = 480

local ortho;
local image;
local batch;
local shader;
function simple_init()
   simple_makeWindow("Coming closer to 0.2.0", width, height, false, -1, -1)
   simple_setWindowTitle("Coming closer to 0.2.0!!")
   simple_setWindowPosition(-1, -1)
   simple_setWindowVSync(true)
   simple_setViewport(0, 0, width, height);
 
 shader = simple_makeShader()	
 image = simple_loadTexture("res/test.png") 
 batch = simple_makeBatch(shader)
 simple_makeOrthoView(0,width,height,0,0,100,shader)
end
local x = 100
local y = 100
function simple_draw()
   simple_clearScreen(.5, .654, .435, 1)
   
   simple_bindShader(shader)
   simple_bindTexture(image)
   --draw image
   simple_beginBatch(batch)
   simple_drawBatch(batch,x,300,8,8)
   simple_drawBatch(batch,100,y,16,16)
   
   simple_renderMesh(batch)		
   simple_endBatch(batch)
   simple_unBindTexture(image) 
   simple_unBindShader(shader)

end

local timer = 2;
--TODO show errors!
function simple_update()
   timer = timer + 2 * simple_getDeltaTime();
   if timer > 4 then 
      print("FPS: " .. simple_getFPS()) 
      timer = 0
   end
	x = x + 40 * simple_getDeltaTime();
	y = y + 40 * simple_getDeltaTime();
end
