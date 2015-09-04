CFLAGS= -s USE_GLFW=3 -s FULL_ES2=1 -s ASSERTIONS=1
SOURCE=	/home/vlad/Dev/emscripten-master/emcc src/main.cpp src/graphics/batch2d.cpp src/graphics/default_shaders.cpp src/graphics/gl_graphics.cpp src/graphics/mesh.cpp src/graphics/shader.cpp src/graphics/texture2D.cpp  src/utils/core.cpp  src/utils/file.cpp src/utils/lua_lang_init.cpp src/input/keyboard.cpp src/input/pointer.cpp src/window/glfw_window.cpp deps/lua/lapi.c deps/lua/lauxlib.c deps/lua/lbaselib.c deps/lua/lbitlib.c deps/lua/lcode.c deps/lua/lcorolib.c deps/lua/lctype.c deps/lua/ldblib.c deps/lua/ldebug.c deps/lua/ldo.c deps/lua/ldump.c deps/lua/lfunc.c deps/lua/lgc.c deps/lua/linit.c deps/lua/liolib.c deps/lua/llex.c deps/lua/lmathlib.c deps/lua/lmem.c deps/lua/loadlib.c deps/lua/lobject.c deps/lua/lopcodes.c deps/lua/loslib.c deps/lua/lparser.c deps/lua/lstate.c deps/lua/lstring.c deps/lua/lstrlib.c deps/lua/ltable.c deps/lua/ltablib.c deps/lua/ltm.c deps/lua/lundump.c deps/lua/lutf8lib.c deps/lua/lvm.c deps/lua/lzio.c deps/stb_image/stb_image.c
LOAD= --preload-file
TARGET=simple_web_makefile.html

all: $(TARGET)

$(TARGET):
	$(SOURCE) $(CFLAGS) -O2 -o $(TARGET) $(LOAD) res/test.png $(LOAD) res/main.lua
clean:
	rm $(TARGET)
