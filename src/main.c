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

int main(int argc, char *argv[]) {
  char *image_path = NULL;
  char *output_file_path = NULL;
  int output_size = 80;

  for (int i = 0; i < argc; ++i) {

    // INPUT IMAGE PATH
    if (strcmp(argv[i], "-i") == 0 && (i + 1) < argc) {
      image_path = argv[i + 1];
    }

    // OUTPUT FILE PATH
    if (strcmp(argv[i], "-o") == 0 && (i + 1) < argc) {
      output_file_path = argv[i + 1];
    }

    // RESOLUTION
    if (strcmp(argv[i], "-r") == 0 && (i + 1) < argc) {
      output_size = atoi(argv[i + 1]);
    }
  }

  // Set default image path if nothing is provided
  if (!image_path) {
    fprintf(stderr, "Error: image path not defined");
    exit(EXIT_FAILURE);
  }

  // Set default output file, use stdout if none provided
  FILE *output_file = NULL;
  if (output_file_path) {
    output_file = fopen("output.txt", "w");
  } else {
    output_file = stdout;
  }

  // Validating output_size
  if (!output_size || output_size <= 0) {
    fprintf(stderr, "Error: Invalid output resolution\n");
    exit(EXIT_FAILURE);
  }

  int width, height, channels;
  unsigned char *original_img =
      stbi_load(image_path, &width, &height, &channels, 1);

  if (!original_img) {
    fprintf(stderr, "Error: failed to load image. %s\n", stbi_failure_reason());
    exit(EXIT_FAILURE);
  }

  int output_width = output_size;
  int output_height = output_size * 0.3;
  int output_channels = 1;
  size_t buffer_size = output_width * output_height * output_channels;
  unsigned char *scaled_img = malloc(buffer_size);

  stbir_resize_uint8_linear(original_img, width, height, 0, scaled_img,
                            output_width, output_height, 0, output_channels);

  print_output(output_file, scaled_img, output_width, output_height);

  printf("\nOutput complete!\n");

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
