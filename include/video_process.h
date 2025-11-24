#ifndef VIDEO_PROCESS
#define VIDEO_PROCESS

#include <stdio.h>

void print_video_from_input(const char *input_path, FILE *output_file, int output_size);
void display_video(char *buffer);

#endif