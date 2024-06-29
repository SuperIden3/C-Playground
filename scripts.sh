start() {
  restart
  gcc index.c -o index
  ./index
}
test() {
  restart
  gcc -g -O0 -DDEBUG -fdiagnostics-color=always -Wall -Wextra index.c -o index
  time ./index
}
alias ls="ls -lsA"
restart() {
  reset
  printf "Terminal type: "
  tset -rqw
  echo
}