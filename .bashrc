start() {
  gcc index.c -o index
  ./index
}
test() {
  gcc -v -g -O0 -DDEBUG -fdiagnostics-color=always -Wall -Wextra index.c -o index
  ./index
}