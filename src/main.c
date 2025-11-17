#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <string.h>

#include "../include/image_process.h"
#include "../include/video_process.h"

int is_image_file(const char *filename);
int is_video_file(const char *filename);

int main(int argc, char *argv[]) {
  char *input_file = NULL;
  char *output_file_path = NULL;
  int output_size = 80;

  for (int i = 0; i < argc; ++i) {

    // INPUT IMAGE PATH
    if (strcmp(argv[i], "-i") == 0 && (i + 1) < argc) {
      input_file = argv[i + 1];
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
  if (!input_file) {
    fprintf(stderr, "Error: input path not defined");
    exit(EXIT_FAILURE);
  }

  // Set default output file, use stdout if none provided
  FILE *output_file = NULL;
  if (output_file_path) {
    output_file = fopen(output_file_path, "w");
  } else {
    output_file = stdout;
  }

  // Validating output_size
  if (!output_size || output_size <= 0) {
    fprintf(stderr, "Error: Invalid output resolution\n");
    exit(EXIT_FAILURE);
  }

  if (is_image_file(input_file)) {
    print_image_from_file(input_file, output_file, output_size);
  } else if (is_video_file(input_file)) {
    print_video_from_file(input_file, output_file, output_size);
  } else {
    fprintf(stderr, "Error: file format not supported\n");
    exit(EXIT_FAILURE);
  }

  return 0;
}

int is_image_file(const char *filename) {
  const char *ext = strrchr(filename, '.');
  if (!ext)
    return 1;
  ext++;

  return (strcmp(ext, "jpg") == 0 || strcmp(ext, "jpeg") == 0 ||
          strcmp(ext, "png") == 0 || strcmp(ext, "webp") == 0 ||
          strcmp(ext, "bmp") == 0);
}

int is_video_file(const char *filename) {
  const char *ext = strrchr(filename, '.');
  if (!ext)
    return 1;
  ext++;

  return (strcmp(ext, "mp4") == 0 || strcmp(ext, "mov") == 0 ||
          strcmp(ext, "fiv") == 0 || strcmp(ext, "avi") == 0 ||
          strcmp(ext, "mkv") == 0);
}