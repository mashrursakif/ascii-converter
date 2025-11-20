#include "../include/image_process.h"
#include "../include/utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../include/stb_image_resize2.h"

void print_image_from_file(char *image_path, FILE *output_file,
                           int output_size) {

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
}
