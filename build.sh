root_dir=~/programming/c/sdl/pong/;
compiler="clang";
libs="-lSDL3 -lm";
clang_flags="-fcolor-diagnostics";
flags="-g -pedantic-errors -Wall -Wextra";
srcs="${root_dir}src/*.c";
output="-o ${root_dir}build/pong";

$compiler $flags $clang_flags $srcs $output $libs;
