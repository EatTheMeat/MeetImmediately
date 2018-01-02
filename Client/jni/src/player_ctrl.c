#include "player_ctrl.h"
#include "encoder.h"
#include <android/log.h>
#include "libavutil/log.h"

enum AVPixelFormat pixfmt_android_covert_to_ffmpeg(char *pix_fmt){
	enum AVPixelFormat pixfmt=-1;
	if(pix_fmt==NULL){
		return 0;
	}
	if(strcmp(pix_fmt,"yuv422sp")==0){
		pixfmt = AV_PIX_FMT_YVYU422;
	}else if(strcmp(pix_fmt,"yuv420sp")==0){
		pixfmt = AV_PIX_FMT_YUYV422;
	}else if(strcmp(pix_fmt,"yuv422i-yuyv")==0){
		pixfmt = AV_PIX_FMT_YUYV422;
	}else if(strcmp(pix_fmt,"yuv420p")==0){
		pixfmt = AV_PIX_FMT_YUV420P;
	}else if(strcmp(pix_fmt,"rgb565")==0){
		pixfmt = AV_PIX_FMT_RGB565BE;
	}else if(strcmp(pix_fmt,"rgba8888")==0){
		pixfmt = AV_PIX_FMT_RGBA;
	}
	return pixfmt;
}

void ffmpeg_log(char *tag,int level, const char *fmt, va_list ap){
	//__android_log_print(5,"TEST","xxx %s, valist:%s\n",fmt,xx);
	//__android_log_print(5,"ffmpeg",fmt,xx);
	char buf[1024];
	vsnprintf(buf, 1024, fmt, ap);
	__android_log_write(5, tag, buf);
}
int player_init(player_ctrl_h *p_ctrl){
	if(p_ctrl==NULL){
		return -1;
	}
	av_register_all();
	av_log_set_level(64);
	av_log_set_callback(&ffmpeg_log);
	p_ctrl->pVideoCodecCtx=NULL;
	p_ctrl->pAudioCodecCtx=NULL;
	p_ctrl->isVideoOpen=0;
	p_ctrl->inAudioOpen=0;
}

int player_set_video_format(player_ctrl_h *p_ctrl, char *pix_fmt, int width, int height){
	
	__android_log_print(5,"TEST","setformat start \n");
	if(pix_fmt==NULL || width<=0 || height<=0){
		return -1;
	}


	enum AVPixelFormat pixfmt = pixfmt_android_covert_to_ffmpeg(pix_fmt);
		__android_log_print(5,"TEST","pix_fmt:%s, pixfmt:%d,width:%d,height:%d\n",pix_fmt,pixfmt,width,height);
	if(pixfmt<0){
		return -1;
	}
	AVCodecContext *pCodecCtx=video_encoder_set_format("libx264",AVMEDIA_TYPE_VIDEO,pixfmt,width,height);
	if(pCodecCtx==NULL){
		return -1;
	}
	p_ctrl->pVideoCodecCtx = pCodecCtx;
	
	return 0;
}

int player_start(player_ctrl_h *p_ctrl){
	if(p_ctrl==NULL || (p_ctrl->pVideoCodecCtx==NULL && p_ctrl->pAudioCodecCtx==NULL)){
		return -1;
	}
	
	if(p_ctrl->pVideoCodecCtx){

		video_encoder_start(p_ctrl->pVideoCodecCtx);
	}
	if(p_ctrl->pAudioCodecCtx){
		//p_ctrl->apkt=av_new_packet();
		
	}
}

int player_stop(player_ctrl_h *p_ctrl){
	if(p_ctrl==NULL){
		return -1;
	}
	if(p_ctrl->pVideoCodecCtx){
		av_free_packet(&p_ctrl->vpkt); 
		video_encoder_stop(p_ctrl->pVideoCodecCtx);
	}
	if(p_ctrl->pAudioCodecCtx){
		
	}
}

int player_get_video(player_ctrl_h *p_ctrl,uint8_t* pbuf,int psize){
	int ret=-1;
	
	if(p_ctrl==NULL || pbuf==NULL || p_ctrl->pVideoCodecCtx==NULL){
		return -1;
	}
	
	av_new_packet(&p_ctrl->vpkt,psize);
	ret=video_encoder_get_packet(p_ctrl->pVideoCodecCtx,&p_ctrl->vpkt,pbuf);
	if(ret==0){
		//fifo write
	}
	
	return 0;
}

int player_get_audio(){
	return 0;
}
