#ifndef __FF_ENCODER_H__
#define __FF_ENCODER_H__

#include "libavutil/opt.h" 
#include "libavutil/avutil.h"  
#include "libavcodec/avcodec.h"  
#include "libavformat/avformat.h"
  
int video_encoder_get_packet(AVCodecContext *pCodecCtx,AVPacket *pkt,uint8_t* picture_buf);
int video_encoder_stop(AVCodecContext *pCodecCtx);
int video_encoder_start(AVCodecContext *pCodecCtx);
AVCodecContext * video_encoder_set_format(char *mine,enum AVMediaType codec_type, enum AVPixelFormat pix_fmt,int width,int height);

#endif