local w = 620
local h = 480

local ortho;
local image;
local batch;
local shader;
local _math;
local window;
local graphics;

function simple.load()
  
   window = Window.new()
   window:init("Simple playground", w, h)

   shader = Shader.new()
   shader:init("default")
    
  _math = Math.new()

   graphics = Graphics.new()
    
   font = Font.new()
   font:init(shader,"vera.ttf", 12)
   
   input = Input.new()
   timer = Timer.new()

   texture = Texture.new()
   texture:init("t.png")

   batch = Batch.new()
   batch:init(shader,200)
 end

function simple.draw()
  graphics:clear()
  graphics:setBackgroundColor(124,69,69,255)
  
  batch:bind()
  texture:bind()
  batch:draw(200,100,12,32,190)
  batch:renderMesh()
  texture:unbind()
  batch:unbind()


  shader:bind()
  font:bind()
  _math:setOrtho(shader, 0, w, h, 0, 0, 100)
  font:draw(shader,"Multiple Texts are working",100,100,1,1,105,85,155)
  font:draw(shader,"Made by Muresan Vlad Mihail akaaa Murii :)  " .. timer:getFPS(),100,150)
   
  font:unbind()

  batch:bind()
  texture:bind()
  batch:draw(100,100,32,32,90)
  batch:renderMesh()
  texture:unbind()
  batch:unbind()
end

function simple.update(delta)
  
  if input:isKeyDown("esc") then
    simple.quit()
  end
end

function simple.dump()
  
end
