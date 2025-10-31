#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../include/stb_image_resize2.h"

char map_px_to_char(unsigned char brightness);
void print_output(FILE *output, unsigned char *img, int output_width,
                  int output_height);

const char *ascii = "@#*+=-:. ";
// const char *ascii = "$@B8&WM#*/()1{}[]?-_+~<>i!lI;:,^. ";

int main() {

  char image_path[256] = "samples/test_image.jpg";
  printf("Enter path to image:");
  scanf("%s", image_path);

  int width, height, channels;
  unsigned char *original_img =
      stbi_load(image_path, &width, &height, &channels, 1);

  if (!original_img) {
    printf("Error: failed to load image. %s\n", stbi_failure_reason());
    exit(EXIT_FAILURE);
  }

  int output_size = 80;
  int output_width = output_size;
  int output_height = output_size * 0.5;
  int output_channels = 1;
  size_t buffer_size = output_width * output_height * output_channels;
  unsigned char *scaled_img = malloc(buffer_size);

  printf("allocated %zu bytes\n", buffer_size);

  stbir_resize_uint8_linear(original_img, width, height, 0, scaled_img,
                            output_width, output_height, 0, output_channels);

  // if (save_to_file) {
  //   FILE *output_file = fopen("output.txt", "w");
  //   if (!output_file) {
  //     perror("Output file cannot be opened");
  //   }

  // } else {
  //   FILE *output_file = stdout;
  // }

  FILE *output_file = stdout;

  print_output(output_file, scaled_img, output_width, output_height);

  stbi_image_free(original_img);
  stbi_image_free(scaled_img);

  return 0;
}

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
      // printf("%c", map_px_to_char(brightness));
      fputc(map_px_to_char(brightness), output_file);
    }
    // printf("\n");
    fputc('\n', output_file);
  }
}
