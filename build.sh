root_dir=~/programming/c/sdl/pong/;
libs="-lSDL3";
clang -g ${root_dir}src/*.c -o ${root_dir}build/pong $libs;
