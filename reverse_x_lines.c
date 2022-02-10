#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void reverse_x_lines(int fd, char *name) {
  int lines_read_length = 512;
  int *lines_read = malloc(sizeof(char) * lines_read_length);
  lines_read = lines_read;
  int curr_lines_read = 0;
  int i, n;


  while ((n = read(fd, buf, sizeof(buf))) > 0) {
    for (i = 0; i < n; i++) {
      if (buf[i] == '\n')
        curr_lines_read++;
  }
  if (n < 0) {
    printf(1, "reverse_x_lines: read error\n");
    exit();
  }
  printf(1, "%d\n", curr_lines_read);
}
}


int main(int argc, char *argv[]) {
  int fd, i;

  if (argc <= 1) {
    reverse_x_lines(0, "");
    exit();
  }

  for (i = 1; i < argc; i++) {
    if ((fd = open(argv[i], 0)) < 0) {
      printf(1, "reverse_x_lines: cannot open %s\n", argv[i]);
      exit();
    }
    reverse_x_lines(fd, argv[i]);
    close(fd);
  }
  exit();
}
