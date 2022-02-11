#include "types.h"
#include "stat.h"
#include "user.h"


void reverse_lines(char* lines_read, char* reversed_lines, int lines_length);
void print_lines(char* lines_to_print, int length);
int check_palindrome(char* lines_read, char* reversed_lines, int lines_read_length);
char buf[512];

// grep some_pattern *file_extencion 


void is_palindrome(int fd, char *name, int num_lines) {
  int lines_read_size = 512;
  int lines_read_length = 0;
  char *lines_read = malloc(sizeof(char) * lines_read_size);
  int curr_lines_read = 0;
  int i, n;


  while ((n = read(fd, buf, sizeof(buf))) > 0) {

    for (i = 0; i < n; i++) {

      // resize the array if neccessary
      if (lines_read_length >= lines_read_size) {
          printf(1, "resizing the buffer");
        // create a new container that is twice the size of the old one 
        char *new_lines_container = malloc(2 * lines_read_size);
        // copy over the data from the old container
        // void *memmove(void *dst, const void *src, uint n)
        memmove(new_lines_container, lines_read, lines_read_size);
        lines_read_size *= 2;
        // deallocate the old data to avoid memory leak 
        free(lines_read);
        // assign lines_read variable to point to a new location 
        lines_read = new_lines_container; 
      }

      lines_read[lines_read_length] = buf[i];
 
      lines_read_length++;


      if (buf[i] == '\n') {
        curr_lines_read++;
      }


    if (curr_lines_read == num_lines) {
        char *reversed_lines = malloc(sizeof(char) * lines_read_size);
        reverse_lines(lines_read, reversed_lines, lines_read_length);
        if (check_palindrome(lines_read, reversed_lines, lines_read_length)) {
            printf(1, "Palindrome\n");
        }
        else {
            printf(1, "Not a palindrome\n");
        }
        // print_lines(reversed_lines, lines_read_length);
        // printf(1, "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
        // print_lines(lines_read, lines_read_length);
        free(lines_read);
        free(reversed_lines);
        exit();
  }

  if (n < 0) {
    printf(1, "is_palindrome: read error\n");
    exit();
  }
}
//   printf(1, "%d\n", num_lines);
}
}


void reverse_lines(char* lines_read, char* reversed_lines, int lines_length) {
    int j = 0;
    for (int i = lines_length - 1; i >= 0; i--) {
        reversed_lines[j] = lines_read[i];
        j++;
    }
}


void print_lines(char* lines_to_print, int length) {
    for (int i = 0; i < length; i++)
        printf(1, "%c", lines_to_print[i]);
}


// we are ignoring new line characters 
int check_palindrome(char* lines_read, char* reversed_lines, int lines_read_length) {
    int i = 0;
    int j = 0;
    while (i < lines_read_length && j < lines_read_length) {
        if (lines_read[i] == '\n') {
            i++;
        }
        if (reversed_lines[j] == '\n') {
            j++;
        }
        if (lines_read[i] != reversed_lines[j]) {
            return 0;
        }
        i++;
        j++;
    }
    return 1;
}


int main(int argc, char *argv[]) {
  int fd, i;
  int num_lines;

  // program name and the number of lines
  if (argc < 2) {
      printf(2, "is_palindrome: double-check your input \n");
      exit();
  }

  num_lines = atoi(argv[1]);
  printf(1, "The number of arguments is %d\n", argc);
  printf(1, "The first argument is %s\n", argv[0]);
  // pipe is not working
  if (argc <= 2) {
    is_palindrome(0, "", num_lines);
    exit();
  }

  for (i = 2; i < argc; i++) {
    if ((fd = open(argv[i], 0)) < 0) {
      printf(2, "is_palindrome: cannot open %s\n", argv[i]);
      exit();
    }
    is_palindrome(fd, argv[i], num_lines);
    close(fd);
  }
  exit();
}
