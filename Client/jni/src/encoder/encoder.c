

#include "encoder.h"
#include <android/log.h>

AVCodecContext * video_encoder_set_format(char *mine,enum AVMediaType codec_type, enum AVPixelFormat pix_fmt,int width,int height){
	if(mine==NULL || width<=0 || height<=0 || pix_fmt<0 || codec_type<0){
		return NULL;
	}
	
	__android_log_print(5,"TEST","mine:%s",mine);
	AVCodec* pCodec = avcodec_find_encoder_by_name(mine);
	if(pCodec==NULL){
		__android_log_print(5,"TEST", "can not find codec");
		return NULL;
	}
	__android_log_print(5,"TEST", "get codec");
	AVCodecContext *pCodecCtx = avcodec_alloc_context3(pCodec);
	if(pCodecCtx==NULL){
		__android_log_print(5,"TEST", "can not get context by codec");

		return NULL;
	}
	__android_log_print(5,"TEST", "get context by codec");
		//set codec param
    pCodecCtx->codec_id = pCodec->id;  
    pCodecCtx->codec_type = pCodec->type;  
    pCodecCtx->pix_fmt = pix_fmt;  
    pCodecCtx->width = width;    
    pCodecCtx->height = height;
    //pCodecCtx->bit_rate = 400000;    
    //pCodecCtx->gop_size=250;  
    //pCodecCtx->time_base.num = 1;    
    //pCodecCtx->time_base.den = 25;    
    //pCodecCtx->qmin = 10;  
    //pCodecCtx->qmax = 51;  
    //pCodecCtx->max_b_frames=3; 

	return pCodecCtx;
}

int video_encoder_start(AVCodecContext *pCodecCtx){
	if(pCodecCtx==NULL || pCodecCtx->codec==NULL){
		return -1;
	}
	if (avcodec_open2(pCodecCtx, pCodecCtx->codec,NULL) < 0){  
        __android_log_print(5,"TEST","Failed to open encoder! \n");  
        return -1;  
    }  
	return 0;
}

int video_encoder_stop(AVCodecContext *pCodecCtx){
	if(pCodecCtx==NULL){
		return -1;
	}
	avcodec_close(pCodecCtx);
	return 0;
}

int video_encoder_get_packet(AVCodecContext *pCodecCtx,AVPacket *pkt,uint8_t* picture_buf){
    int got_picture=0,ret=-1;  
	if(pCodecCtx==NULL || pkt==NULL || picture_buf==NULL){
		return -1;
	}
	AVFrame* pFrame = av_frame_alloc();  
	if(pFrame==NULL){
		return -1;
	}

    avpicture_fill((AVPicture *)pFrame, picture_buf, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height);  
   
    ret = avcodec_encode_video2(pCodecCtx, pkt,pFrame, &got_picture);  
    if(ret < 0){  
        printf("Failed to encode! \n");  
        return -1;  
    }  
    if (got_picture==1){  
		ret=0;
        //av_free_packet(&pkt);  
    }  
	
	if(pFrame){
	    av_free(pFrame);
	}		
	return ret;
}

int audio_encoder_set_format(){
	return 0;
}

int audio_encoder_get_package(){
	return 0;
}
int audio_encoder_start(){
	return 0;
}
int audio_encoder_stop(){
	return 0;
}

  
