#ifndef __FF_CTRL_H__
#define __FF_CTRL_H__
#include <libavutil/opt.h>  
#include <libavcodec/avcodec.h>  
#include <libavformat/avformat.h>  
typedef struct {
	AVPacket vpkt;
	AVPacket apkt;
	AVCodecContext *pVideoCodecCtx;
	AVCodecContext *pAudioCodecCtx;
	int isVideoOpen;
	int inAudioOpen;
}player_ctrl_h;
#endif