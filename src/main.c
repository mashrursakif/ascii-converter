#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <string.h>

#include "../include/image_process.h"
#include "../include/utils.h"
#include "../include/video_process.h"

int is_image_file(const char *filename);
int is_video_file(const char *filename);
char *get_output_path(const char *path);

int main(int argc, char *argv[]) {

  // HANDLE FLAGS

  char *input_path = NULL;
  // char *save_file_path = NULL;
  int save_output = 0;
  char *open_file_path = NULL;
  int output_size = 80;

  for (int i = 0; i < argc; ++i) {
    // INPUT IMAGE PATH
    if (strcmp(argv[i], "-i") == 0 && (i + 1) < argc) {
      input_path = argv[i + 1];
    }

    // SAVE FILE
    if (strcmp(argv[i], "-s") == 0) {
      // save_file_path = argv[i + 1];
      save_output = 1;
    }

    // OPEN EXISTING TXT FILE
    if ((strcmp(argv[i], "-o") == 0) && (i + 1) < argc) {
      open_file_path = argv[i + 1];
    }

    // RESOLUTION
    if (strcmp(argv[i], "-r") == 0 && (i + 1) < argc) {
      output_size = atoi(argv[i + 1]);
    }
  }

  if (input_path && open_file_path) {
    fprintf(stderr, "Error: both -i (input file path) and -o (open file path) "
                    "are being used. Specify only one of these options\n");
    exit(EXIT_FAILURE);
  }

  if (input_path) {
    // CONVERT INPUT

    // Set output file, use stdout if none provided
    FILE *output_file = NULL;
    if (save_output) {
      char *input_path_copy = malloc(strlen(input_path) + 1);
      if (!input_path_copy) {
        fprintf(stderr, "Error: Failed to allocate memory for input path");
        exit(EXIT_FAILURE);
      }

      strcpy(input_path_copy, input_path);

      char *output_path = get_output_path(input_path_copy);

      if (!output_path) {
        fprintf(stderr, "Error: invalid output path");
        exit(EXIT_FAILURE);
      }
      output_file = fopen(output_path, "w");
      if (!output_file) {
        fprintf(stderr, "Error: failed to open output file\n");
        exit(EXIT_FAILURE);
      }

      free(input_path_copy);
      free(output_path);
    } else {
      output_file = stdout;
    }

    // Validating output_size
    if (!output_size || output_size <= 0) {
      fprintf(stderr, "Error: Invalid output resolution\n");
      exit(EXIT_FAILURE);
    }

    if (is_image_file(input_path)) {
      print_image_from_input(input_path, output_file, output_size);
    } else if (is_video_file(input_path)) {
      print_video_from_input(input_path, output_file, output_size);
    } else {
      fprintf(stderr, "Error: file format not supported\n");
      exit(EXIT_FAILURE);
    }
  } else if (open_file_path) {
    // OPEN AND DISPLAY CONVERTED FILE
    display_ascii(open_file_path);
  } else {
    fprintf(stderr, "Error: neither -i (input file path) nor -o (open file "
                    "path) is defined\n");
    exit(EXIT_FAILURE);
  }

  return 0;
}

char *get_output_path(const char *path) {
  const char *base = path;
  const char *slash1 = strrchr(path, '/');
  const char *slash2 = strrchr(path, '\\');

  if (slash1 && slash1 > base)
    base = slash1 + 1;
  if (slash2 && slash2 > base)
    base = slash2 + 1;

  char *dot = strrchr(base, '.');
  if (dot) {
    *dot = '\0';
  }

  char *output_dir = "outputs/";
  char *ext = ".txt";
  char *result = malloc(strlen(output_dir) + strlen(base) + strlen(ext) + 1);
  if (!result)
    return NULL;

  sprintf(result, "%s%s%s", output_dir, base, ext);

  return result;
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