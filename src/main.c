#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../include/stb_image_resize2.h"

char map_px_to_char(unsigned char brightness, const char *ascii);

int main() {
  const char *ascii = "@#*+=-:. ";
  // const char *ascii = "$@B8&WM#*/()1{}[]?-_+~<>i!lI;:,^. ";

  int width, height, channels;
  unsigned char *original_img =
      stbi_load("samples/test_image.jpg", &width, &height, &channels, 1);

  if (!original_img) {
    printf("Error: failed to load image\n");
    exit(EXIT_FAILURE);
  }

  int output_size = width;
  int target_width = output_size;
  int target_height = output_size * 0.5;
  int output_channels = 1;
  size_t buffer_size = target_width * target_height * output_channels;
  unsigned char *scaled_img = malloc(buffer_size);

  printf("allocated %zu bytes\n", buffer_size);

  stbir_resize_uint8_linear(original_img, width, height, 0, scaled_img,
                            target_width, target_height, 0, output_channels);

  // printf("Image width: %d, height: %d, channels: %d\n", width, height,
  // channels);

  // Loop through the pixels and output char

  printf("width x height: %dx%d\n", target_width, target_height);
  // exit(EXIT_FAILURE);

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      unsigned char brightness = scaled_img[y * width + x];
      printf("%c", map_px_to_char(brightness, ascii));
    }
    printf("\n");
  }

  stbi_image_free(original_img);
  stbi_image_free(scaled_img);

  return 0;
}

char map_px_to_char(unsigned char brightness, const char *ascii) {
  int ascii_len = strlen(ascii);

  int idx = (brightness / 256.0) * ascii_len;
  return ascii[idx];
}
