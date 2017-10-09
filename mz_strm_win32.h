/* mz_sstrm_win32.h -- Stream for filesystem access for windows
   Version 2.0.0, October 4th, 2017
   part of the MiniZip project

   Copyright (C) 2012-2017 Nathan Moinvaziri
     https://github.com/nmoinvaz/minizip
   Copyright (C) 2009-2010 Mathias Svensson
     Modifications for Zip64 support
     http://result42.com
   Copyright (C) 1998-2010 Gilles Vollant
     http://www.winimage.com/zLibDll/minizip.html

   This program is distributed under the terms of the same license as zlib.
   See the accompanying LICENSE file for the full text of the license.
*/

#ifndef _MZ_STREAM_WIN32_H
#define _MZ_STREAM_WIN32_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************/

int32_t mz_stream_win32_open(void *stream, const char *path, int32_t mode);
int32_t mz_stream_win32_is_open(void *stream);
int32_t mz_stream_win32_read(void *stream, void *buf, int32_t size);
int32_t mz_stream_win32_write(void *stream, const void *buf, int32_t size);
int64_t mz_stream_win32_tell(void *stream);
int32_t mz_stream_win32_seek(void *stream, int64_t offset, int32_t origin);
int32_t mz_stream_win32_close(void *stream);
int32_t mz_stream_win32_error(void *stream);

void*   mz_stream_win32_create(void **stream);
void    mz_stream_win32_delete(void **stream);

void*   mz_stream_win32_get_interface(void);

/***************************************************************************/

#if defined(_WIN32) || defined(USEWIN32IOAPI)
#define mz_stream_os_open    mz_stream_win32_open
#define mz_stream_os_is_open mz_stream_win32_is_open
#define mz_stream_os_read    mz_stream_win32_read
#define mz_stream_os_write   mz_stream_win32_write
#define mz_stream_os_tell    mz_stream_win32_tell
#define mz_stream_os_seek    mz_stream_win32_seek
#define mz_stream_os_close   mz_stream_win32_close
#define mz_stream_os_error   mz_stream_win32_error

#define mz_stream_os_create  mz_stream_win32_create
#define mz_stream_os_delete  mz_stream_win32_delete

#define mz_stream_os_get_interface \
                             mz_stream_win32_get_interface

#define mz_os_rand           mz_win32_rand
#define mz_os_get_file_date  mz_win32_get_file_date
#define mz_os_set_file_date  mz_win32_set_file_date
#define mz_os_change_dir     mz_win32_change_dir
#define mz_os_make_dir       mz_win32_make_dir
#define mz_os_open_dir       mz_win32_open_dir
#define mz_os_read_dir       mz_win32_read_dir
#define mz_os_close_dir      mz_win32_close_dir
#define mz_os_is_dir         mz_win32_is_dir
#endif

/***************************************************************************/

#ifdef __cplusplus
}
#endif

#endif
