#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>

#include "../include/image_process.h"

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

  print_image_from_file(image_path, output_file, output_size);

  return 0;
}
