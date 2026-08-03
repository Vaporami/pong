root_dir=~/programming/c/sdl/pong/;
libs="-lSDL3";
flags="-g -pedantic-errors -Werror";
srcs="${root_dir}src/*.c";
output="-o ${root_dir}build/pong";
clang $flags $srcs $output $libs;
