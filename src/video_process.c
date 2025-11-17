#include <libavcodec/avcodec.h>
#include <libavcodec/codec.h>
#include <libavcodec/codec_par.h>
#include <libavcodec/packet.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavutil/error.h>
#include <libavutil/frame.h>
#include <libavutil/imgutils.h>
#include <libavutil/mem.h>
#include <libavutil/pixfmt.h>
#include <libswscale/swscale.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/utils.h"

void print_video_from_file(const char *input_path, FILE *output_file,
                           int output_size) {
  AVFormatContext *format_context = NULL;

  if (avformat_open_input(&format_context, input_path, NULL, NULL) < 0) {
    fprintf(stderr, "Error: Could not open video file\n");
    exit(EXIT_FAILURE);
  }

  if (avformat_find_stream_info(format_context, NULL) < 0) {
    fprintf(stderr, "Error: Could not find video stream info\n");
    exit(EXIT_FAILURE);
  }

  int video_stream_idx = -1;

  for (unsigned int i = 0; i < format_context->nb_streams; ++i) {
    if (format_context->streams[i]->codecpar->codec_type ==
        AVMEDIA_TYPE_VIDEO) {
      video_stream_idx = i;
      break;
    }
  }

  AVCodecParameters *codec_params =
      format_context->streams[video_stream_idx]->codecpar;
  const AVCodec *codec = avcodec_find_decoder(codec_params->codec_id);
  AVCodecContext *codec_context = avcodec_alloc_context3(codec);

  avcodec_parameters_to_context(codec_context, codec_params);
  avcodec_open2(codec_context, codec, NULL);

  AVFrame *original_frame = av_frame_alloc();
  AVPacket *packet = av_packet_alloc();

  int output_width = output_size;
  int output_height = output_size * 0.3;

  struct SwsContext *sws_context =
      sws_getContext(codec_context->width, codec_context->height,
                     codec_context->pix_fmt, output_width, output_height,
                     AV_PIX_FMT_GRAY8, SWS_BILINEAR, NULL, NULL, NULL);

  AVFrame *scaled_frame = av_frame_alloc();
  int buffer_size = av_image_get_buffer_size(
      AV_PIX_FMT_GRAY8, codec_context->width, codec_context->width, 1);
  uint8_t *buffer = (uint8_t *)av_malloc(buffer_size * sizeof(uint8_t));

  av_image_fill_arrays(scaled_frame->data, scaled_frame->linesize, buffer,
                       AV_PIX_FMT_GRAY8, output_width, output_height, 1);

  printf("\033[2J");

  int fps = 24;
  long frame_time = 1000000 / fps;

  while (av_read_frame(format_context, packet) >= 0) {
    if (packet->stream_index == video_stream_idx) {
      if (avcodec_send_packet(codec_context, packet) == 0) {
        while (avcodec_receive_frame(codec_context, original_frame) == 0) {
          sws_scale(sws_context, (uint8_t const *const *)original_frame->data,
                    original_frame->linesize, 0, original_frame->height,
                    scaled_frame->data, scaled_frame->linesize);

          print_output(stdout, scaled_frame->data[0], output_width,
                       output_height);
          printf("\033[H");
          usleep(frame_time);
          fflush(stdout);
        }
      }
    }
    av_packet_unref(packet);
  }

  av_free(buffer);
  av_frame_free(&original_frame);
  av_frame_free(&scaled_frame);
  av_packet_free(&packet);
  avcodec_free_context(&codec_context);
  avformat_close_input(&format_context);
  sws_freeContext(sws_context);
}