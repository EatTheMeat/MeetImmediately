

/**
 * @file
 * a very simple circular buffer FIFO implementation,from ffmpeg
 */

#ifndef __AUDIO_FIFO_H__
#define __AUDIO_FIFO_H__

#include <stdint.h>

typedef struct _FifoBuffer {
    uint8_t *buffer;
    uint8_t *rptr, *wptr, *end;
    uint32_t rndx, wndx;
} FifoBuffer;

/**
 * Initialize an FifoBuffer.
 * @param size of FIFO
 * @return FifoBuffer or NULL in case of memory allocation failure
 */
FifoBuffer *fifo_alloc(unsigned int size);

/**
 * Free an FifoBuffer.
 * @param f FifoBuffer to free
 */
void fifo_free(FifoBuffer *f);

/**
 * Reset the FifoBuffer to the state right after fifo_alloc, in particular it is emptied.
 * @param f FifoBuffer to reset
 */
void fifo_reset(FifoBuffer *f);

/**
 * Return the amount of data in bytes in the FifoBuffer, that is the
 * amount of data you can read from it.
 * @param f FifoBuffer to read from
 * @return size
 */
int fifo_size(FifoBuffer *f);

/**
 * Return the amount of space in bytes in the FifoBuffer, that is the
 * amount of data you can write into it.
 * @param f FifoBuffer to write into
 * @return size
 */
int fifo_space(FifoBuffer *f);

/**
 * Feed data from an FifoBuffer to a user-supplied callback.
 * @param f FifoBuffer to read from
 * @param buf_size number of bytes to read
 * @param func generic read function
 * @param dest data destination
 */
int fifo_generic_read(FifoBuffer *f, void *dest, int buf_size, void (*func)(void*, void*, int));

/**
 * Feed data from a user-supplied callback to an FifoBuffer.
 * @param f FifoBuffer to write to
 * @param src data source; non-const since it may be used as a
 * modifiable context by the function defined in func
 * @param size number of bytes to write
 * @param func generic write function; the first parameter is src,
 * the second is dest_buf, the third is dest_buf_size.
 * func must return the number of bytes written to dest_buf, or <= 0 to
 * indicate no more data ailable to write.
 * If func is NULL, src is interpreted as a simple byte array for source data.
 * @return the number of bytes written to the FIFO
 */
int fifo_generic_write(FifoBuffer *f, void *src, int size, int (*func)(void*, void*, int));

/**
 * Resize an FifoBuffer.
 * In case of reallocation failure, the old FIFO is kept unchanged.
 *
 * @param f FifoBuffer to resize
 * @param size new FifoBuffer size in bytes
 * @return <0 for failure, >=0 otherwise
 */
int fifo_realloc2(FifoBuffer *f, unsigned int size);

/**
 * Enlarge an FifoBuffer.
 * In case of reallocation failure, the old FIFO is kept unchanged.
 * The new fifo size may be larger than the requested size.
 *
 * @param f FifoBuffer to resize
 * @param additional_space the amount of space in bytes to allocate in addition to fifo_size()
 * @return <0 for failure, >=0 otherwise
 */
int fifo_grow(FifoBuffer *f, unsigned int additional_space);

/**
 * Read and discard the specified amount of data from an FifoBuffer.
 * @param f FifoBuffer to read from
 * @param size amount of data to read in bytes
 */
void fifo_drain(FifoBuffer *f, int size);

/**
 * Return a pointer to the data stored in a FIFO buffer at a certain offset.
 * The FIFO buffer is not modified.
 *
 * @param f    FifoBuffer to peek at, f must be non-NULL
 * @param offs an offset in bytes, its absolute value must be less
 *             than the used buffer size or the returned pointer will
 *             point outside to the buffer data.
 *             The used buffer size can be checked with fifo_size().
 */
static inline uint8_t *fifo_peek2(const FifoBuffer *f, int offs)
{
    uint8_t *ptr = f->rptr + offs;
    if (ptr >= f->end)
        ptr = f->buffer + (ptr - f->end);
    else if (ptr < f->buffer)
        ptr = f->end - (f->buffer - ptr);
    return ptr;
}

#endif /* UTIL_FIFO_H */
