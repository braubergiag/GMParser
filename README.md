# Simple gmi parser
## Build
cd GMParser
cmake .
cmake -S . -B build
cmake --build build
cd build && ctest
./GMParser input_src target_src