#ifndef IMAGE_PROCESS
#define IMAGE_PROCESS

#include <stdio.h>

void print_image_from_file(char *image_path, FILE *output_file, int output_size);
char map_px_to_char(unsigned char brightness);
void print_output(FILE *output, unsigned char *img, int output_width, int output_height);

#endif