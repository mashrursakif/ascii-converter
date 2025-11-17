#include <stdio.h>

#ifndef UTILS
#define UTILS

char map_px_to_char(unsigned char brightness);
void print_output(FILE *output, unsigned char *img, int output_width, int output_height);


#endif