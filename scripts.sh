start() {
  gcc index.c -o index
  ./index
}
test() {
  gcc -g -O0 -DDEBUG -fdiagnostics-color=always -Wall -Wextra index.c -o index
  ./index
}
alias ls="ls -lsA"