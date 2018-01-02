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

#ifdef  __cplusplus
extern "C" {
#endif
int player_set_video_format(player_ctrl_h *p_ctrl, char *pix_fmt, int width, int height);
int player_init(player_ctrl_h *p_ctrl);
int player_start(player_ctrl_h *p_ctrl);
int player_stop(player_ctrl_h *p_ctrl);
int player_get_video(player_ctrl_h *p_ctrl,uint8_t* pbuf,int psize);
#ifdef  __cplusplus
}
#endif

#endif