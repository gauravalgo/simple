#ifndef REGISTER_INPUT_H
#define REGISTER_INPUT_H

namespace simple
{
        namespace lang
        {
                class register_input
                {
                public:
                        register_input();
                        ~register_input();
                public:
                        void registerModule(lua_State* L);
                        void registerMetatable(lua_State* L);
                private:
                        static int getPointerX(lua_State* L);
                        static int getPointerY(lua_State* L);
                        static int getPointer(lua_State* L);
                        static int isPointerPressed(lua_State* L);
                        static int isPointerReleased(lua_State* L);

                };
        }
}
#endif
