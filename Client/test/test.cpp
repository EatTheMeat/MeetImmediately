#include <linux/fb.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <android/log.h>

#define PIXEL_FORMAT_RGB_565 4
#define PIXEL_FORMAT_RGB_888 3
#define PIXEL_FORMAT_RGBX_8888 2
#define PIXEL_FORMAT_RGBA_8888 1

static int vinfoToPixelFormat(const fb_var_screeninfo& vinfo,
        uint32_t* bytespp, uint32_t* f)
{

    switch (vinfo.bits_per_pixel) {
        case 16:
            *f = PIXEL_FORMAT_RGB_565;
            *bytespp = 2;
            break;
        case 24:
            *f = PIXEL_FORMAT_RGB_888;
            *bytespp = 3;
            break;
        case 32:
            // TODO: do better decoding of vinfo here
            *f = PIXEL_FORMAT_RGBX_8888;
            *bytespp = 4;
            break;
        default:
            return -1;
    }
    return 0;
}

int main(){
	
	int fb = open("/dev/graphics/fb0", O_RDONLY);
	int pwidth=0, pheight=0,psize=0;
	uint32_t f=0;
	void const* mapbase = MAP_FAILED;
    ssize_t mapsize = -1;
    void const* base = 0;
	__android_log_print(0,"TEST","xxxxxxxxxxxxxxxxxxxxxxxxxxstart");
	if(fb>=0){
		struct fb_var_screeninfo vinfo;
		if (ioctl(fb, FBIOGET_VSCREENINFO, &vinfo) == 0) {
			uint32_t bytespp;
			if (vinfoToPixelFormat(vinfo, &bytespp, &f) == 0) {
                size_t offset = (vinfo.xoffset + vinfo.yoffset*vinfo.xres) * bytespp;
                pwidth = vinfo.xres;
                pheight = vinfo.yres;
                psize = pwidth*pheight*bytespp;
                mapsize = offset + psize;
                mapbase = mmap(0, mapsize, PROT_READ, MAP_PRIVATE, fb, 0);
                if (mapbase != MAP_FAILED) {
                     base = (void const *)((char const *)mapbase + offset);
                 }
            }
		}
		close(fb);
	}
	return 0;
}