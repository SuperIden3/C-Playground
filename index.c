#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#include <complex.h>
#include <inttypes.h>
#include <tgmath.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "custom/string.h"
#include "custom/io.h"
#include "custom/node.h"
#include "custom/funcs.h"

int main() {
  srand(time(0));

  struct String *str = new_String("Hello, World!");
  if (str == NULL) {
    perror("Failed to allocate memory for String object");
    return 1;
  }
  printf("%s\n", str->buffer);
  if (!free_String(str)) {
    perror("Failed to free memory for String object");
    return 1;
  }

  return 0;
}
