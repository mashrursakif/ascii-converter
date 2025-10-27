#include <stddef.h>
#include <stdio.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../include/stb_image_resize2.h"

char map_px_to_char(unsigned char brightness, const char *ascii);

int main() {

  const char *ascii = "@#*+=-:. ";

  int width, height, channels;
  unsigned char *original_img =
      stbi_load("test_image_2.jpg", &width, &height, &channels, 1);

  int new_height = height * 0.5;
  size_t buffer_size = width * new_height * channels;
  unsigned char *scaled_img = malloc(buffer_size);

  stbir_resize_uint8_linear(original_img, width, height, 0, scaled_img, width,
                            new_height, 0, 1);

  // printf("Image width: %d, height: %d, channels: %d\n", width, height,
  // channels);

  // Loop through the pixels and output char

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
