/* mz_strm_lzma.h -- Stream for lzma inflate/deflate
   Version 2.0.0, October 4th, 2017
   part of the MiniZip project

   Copyright (C) 2012-2017 Nathan Moinvaziri
      https://github.com/nmoinvaz/minizip

   This program is distributed under the terms of the same license as lzma.
   See the accompanying LICENSE file for the full text of the license.
*/

#ifndef _MZ_STREAM_LZMA_H
#define _MZ_STREAM_LZMA_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************/

int32_t mz_stream_lzma_open(void *stream, const char *filename, int32_t mode);
int32_t mz_stream_lzma_is_open(void *stream);
int32_t mz_stream_lzma_read(void *stream, void *buf, int32_t size);
int32_t mz_stream_lzma_write(void *stream, const void *buf, int32_t size);
int64_t mz_stream_lzma_tell(void *stream);
int32_t mz_stream_lzma_seek(void *stream, int64_t offset, int32_t origin);
int32_t mz_stream_lzma_close(void *stream);
int32_t mz_stream_lzma_error(void *stream);

void    mz_stream_lzma_set_level(void *stream, int16_t level);
int64_t mz_stream_lzma_get_total_in(void *stream);
int64_t mz_stream_lzma_get_total_out(void *stream);
void    mz_stream_lzma_set_max_total_in(void *stream, int64_t max_total_in);

void*   mz_stream_lzma_create(void **stream);
void    mz_stream_lzma_delete(void **stream);

void*   mz_stream_lzma_get_interface(void);

/***************************************************************************/

#ifdef __cplusplus
}
#endif

#endif
