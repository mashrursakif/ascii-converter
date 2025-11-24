#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/image_process.h"
#include "../include/video_process.h"

const char *ascii = "@#*+=-:. ";
// const char *ascii = "@8&W#/1{}()[]?_~<>;:^*+-,. ";

char map_px_to_char(unsigned char brightness) {
  int ascii_len = strlen(ascii);

  int idx = (brightness / 256.0) * ascii_len;
  return ascii[idx];
}

void print_output(FILE *output_file, unsigned char *img, int output_width,
                  int output_height) {
  for (int y = 0; y < output_height; ++y) {
    for (int x = 0; x < output_width; ++x) {
      unsigned char brightness = img[y * output_width + x];
      fputc(map_px_to_char(brightness), output_file);
    }
    fputc('\n', output_file);
  }
}

void display_ascii(char *open_file_path) {
  FILE *file = fopen(open_file_path, "r");
  if (!file) {
    fprintf(stderr, "Error: failed to open %s\n", open_file_path);
    exit(EXIT_FAILURE);
  } else {
    printf("FILE OPENED \n");
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  printf("file size: %ld\n", file_size);

  char *buffer = malloc(file_size + 1);
  size_t read_items = fread(buffer, 1, file_size, file);

  printf("Allocating: %lu bytes\n", read_items);

  if (read_items == 0) {
    fprintf(stderr, "Error: failed to fread to buffer\n");
    exit(EXIT_FAILURE);
  }

  buffer[file_size] = '\0';

  int is_video = 0;
  if (strstr(buffer, "<FRAME>") != NULL) {
    is_video = 1;
  }

  if (is_video) {
    display_video(buffer);
  } else {
    display_image(buffer);
  }

  free(buffer);
}