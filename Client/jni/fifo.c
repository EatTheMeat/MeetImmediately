
#include "fifo.h"
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) > (b) ? (b) : (a))

void in_freepointer(void *arg)
{
    void **ptr= (void**)arg;
    free(*ptr);
    *ptr = NULL;
}


FifoBuffer *fifo_alloc(unsigned int size)
{
    FifoBuffer *f= malloc(sizeof(FifoBuffer));
    if (!f){
        return NULL;

    }
    f->buffer = malloc(size);
    f->end = f->buffer + size;
    fifo_reset(f);
    if (!f->buffer){
        in_freepointer(&f);

    }
    memset(f->buffer,0,size);
    return f;
}

void fifo_free(FifoBuffer *f)
{
    if (f) {
        in_freepointer(&f->buffer);
        free(f);
    }
}

void fifo_reset(FifoBuffer *f)
{
    f->wptr = f->rptr = f->buffer;
    f->wndx = f->rndx = 0;
}

int fifo_size(FifoBuffer *f)
{
    return (uint32_t)(f->wndx - f->rndx);
}

int fifo_space(FifoBuffer *f)
{
    return f->end - f->buffer - fifo_size(f);
}

int fifo_realloc2(FifoBuffer *f, unsigned int new_size)
{
    unsigned int old_size = f->end - f->buffer;

    if (old_size < new_size) {
        int len = fifo_size(f);
        FifoBuffer *f2 = fifo_alloc(new_size);

        if (!f2)
            return -1;
        fifo_generic_read(f, f2->buffer, len, NULL);
        f2->wptr += len;
        f2->wndx += len;
        free(f->buffer);
        *f = *f2;
        free(f2);
    }
    return 0;
}

int fifo_grow(FifoBuffer *f, unsigned int size)
{
    unsigned int old_size = f->end - f->buffer;
    if(size + (unsigned)fifo_size(f) < size)
        return -1;

    size += fifo_size(f);

    if (old_size < size)
        return fifo_realloc2(f, MAX(size, 2*size));
    return 0;
}

// src must NOT be const as it can be a context for func that may need updating (like a pointer or byte counter)
int fifo_generic_write(FifoBuffer *f, void *src, int size, int (*func)(void*, void*, int))
{
    int total = size;
    uint32_t wndx= f->wndx;
    uint8_t *wptr= f->wptr;

    do {
        int len = MIN(f->end - wptr, size);
        if (func) {
            if (func(src, wptr, len) <= 0)
                break;
        } else {
            memcpy(wptr, src, len);
            src = (uint8_t*)src + len;
        }
// Write memory barrier needed for SMP here in theory
        wptr += len;
        if (wptr >= f->end)
            wptr = f->buffer;
        wndx += len;
        size -= len;
    } while (size > 0);
    f->wndx= wndx;
    f->wptr= wptr;
    return total - size;
}


int fifo_generic_read(FifoBuffer *f, void *dest, int buf_size, void (*func)(void*, void*, int))
{
// Read memory barrier needed for SMP here in theory
    do {
        int len = MIN(f->end - f->rptr, buf_size);
        if(func) func(dest, f->rptr, len);
        else{
            memcpy(dest, f->rptr, len);
            dest = (uint8_t*)dest + len;
        }
// memory barrier needed for SMP here in theory
        fifo_drain(f, len);
        buf_size -= len;
    } while (buf_size > 0);
    return 0;
}

/** Discard data from the FIFO. */
void fifo_drain(FifoBuffer *f, int size)
{
    f->rptr += size;
    if (f->rptr >= f->end)
        f->rptr -= f->end - f->buffer;
    f->rndx += size;
}
