# Pong

For å kompilere for windows tror jeg du jeg tenger å allerede ha kompilert raylib og bruke denne kommandoen

```Shell
gcc main.c -o pong -Iinclude/ -Llib/ -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows
```

For å kompilere for web trenger du raylib og emscripten, og denne helvetes kommandoen (se på linking)

```Shell
emcc -o pong.html main-web.c -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result -Os -I. -I C:/Users/amund/Downloads/raylib-5.0/raylib-5.0/src -I C:/Users/amund/Downloads/raylib-5.0/raylib-5.0/src/external -L. -L C:/Users/amund/Downloads/raylib-5.0/raylib-5.0/src -s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1 --preload-file sounds --shell-file C:/Users/amund/Downloads/raylib-5.0/raylib-5.0/src/shell.html C:/Users/amund/Downloads/raylib-5.0/raylib-5.0/src/web/libraylib.a -DPLATFORM_WEB -s 'EXPORTED_FUNCTIONS=["_free","_malloc","_main"]' -s EXPORTED_RUNTIME_METHODS=ccall
```
