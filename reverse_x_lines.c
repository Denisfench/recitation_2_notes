#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

// change it to is_palindrome functon
// check whether x lines form a palindrome 
void reverse_x_lines(int fd, char *name, int num_lines) {
  int lines_read_size = 512;
  int lines_read_length 
  int *lines_read = malloc(sizeof(char) * lines_read_size);
  lines_read = lines_read;
  int curr_lines_read = 0;
  int i, n;


  while ((n = read(fd, buf, sizeof(buf))) > 0) {
    for (i = 0; i < n; i++) {

      if (buf[i] == '\n')
        curr_lines_read++;
        // if (curr_lines_read == )
  }
  if (n < 0) {
    printf(1, "reverse_x_lines: read error\n");
    exit();
  }
}
  printf(1, "%d\n", num_lines);
}


int main(int argc, char *argv[]) {
  int fd, i;
  int num_lines;

  // program name and the number of lines
  if (argc < 2) {
      printf(1, "is_palindrome: double-check your input \n");
      exit();
  }

  num_lines = atoi(argv[1]);
  
  if (argc == 2) {
    reverse_x_lines(0, "", num_lines);
    exit();
  }

  for (i = 2; i < argc; i++) {
    if ((fd = open(argv[i], 0)) < 0) {
      printf(1, "reverse_x_lines: cannot open %s\n", argv[i]);
      exit();
    }
    reverse_x_lines(fd, argv[i], num_lines);
    close(fd);
  }
  exit();
}
