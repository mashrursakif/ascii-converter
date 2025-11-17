#include <stdio.h>
#include <string.h>

const char *ascii = "@#*+=-:. ";
// const char *ascii = "$@B8&WM#*/()1{}[]?-_+~<>i!lI;:,^. ";

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