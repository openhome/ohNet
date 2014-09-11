/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggVorbis 'TREMOR' CODEC SOURCE CODE.   *
 *                                                                  *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis 'TREMOR' SOURCE CODE IS (C) COPYRIGHT 1994-2003    *
 * BY THE Xiph.Org FOUNDATION http://www.xiph.org/                  *
 *                                                                  *
 ********************************************************************

 function: subsumed libogg includes

 ********************************************************************/
#ifndef _OGG_H
#define _OGG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "os_types.h"

typedef struct ogg_buffer_state{
  struct ogg_buffer    *unused_buffers;
  struct ogg_reference *unused_references;
  int                   outstanding;
  int                   shutdown;
} ogg_buffer_state;

typedef struct ogg_buffer {
  unsigned char      *data;
  long                size;
  int                 refcount;
  
  union {
    ogg_buffer_state  *owner;
    struct ogg_buffer *next;
  } ptr;
} ogg_buffer;

typedef struct ogg_reference {
  ogg_buffer    *buffer;
  long           begin;
  long           length;

  struct ogg_reference *next;
} ogg_reference;

typedef struct oggpack_buffer {
  int            headbit;
  unsigned char *headptr;
  long           headend;

  /* memory management */
  ogg_reference *head;
  ogg_reference *tail;

  /* render the byte/bit counter API constant time */
  long              count; /* doesn't count the tail */
} oggpack_buffer;

typedef struct oggbyte_buffer {
  ogg_reference *baseref;

  ogg_reference *ref;
  unsigned char *ptr;
  long           pos;
  long           end;
} oggbyte_buffer;

typedef struct ogg_sync_state {
  /* decode memory management pool */
  ogg_buffer_state *bufferpool;

  /* stream buffers */
  ogg_reference    *fifo_head;
  ogg_reference    *fifo_tail;
  long              fifo_fill;

  /* stream sync management */
  int               unsynced;
  int               headerbytes;
  int               bodybytes;

} ogg_sync_state;

typedef struct ogg_stream_state {
  ogg_reference *header_head;
  ogg_reference *header_tail;
  ogg_reference *body_head;
  ogg_reference *body_tail;

  int            e_o_s;    /* set when we have buffered the last
                              packet in the logical bitstream */
  int            b_o_s;    /* set after we've written the initial page
                              of a logical bitstream */
  long           serialno;
  long           pageno;
  ogg_int64_t    packetno; /* sequence number for decode; the framing
                              knows where there's a hole in the data,
                              but we need coupling so that the codec
                              (which is in a seperate abstraction
                              layer) also knows about the gap */
  ogg_int64_t    granulepos;

  int            lacing_fill;
  ogg_uint32_t   body_fill;

  /* decode-side state data */
  int            holeflag;
  int            spanflag;
  int            clearflag;
  int            laceptr;
  ogg_uint32_t   body_fill_next;
  
} ogg_stream_state;

typedef struct {
  ogg_reference *packet;
  long           bytes;
  long           b_o_s;
  long           e_o_s;
  ogg_int64_t    granulepos;
  ogg_int64_t    packetno;     /* sequence number for decode; the framing
                                  knows where there's a hole in the data,
                                  but we need coupling so that the codec
                                  (which is in a seperate abstraction
                                  layer) also knows about the gap */
} ogg_packet;

typedef struct {
  ogg_reference *header;
  int            header_len;
  ogg_reference *body;
  long           body_len;
} ogg_page;

/* Ogg BITSTREAM PRIMITIVES: bitstream ************************/

#define oggpack_readinit    vorbis_oggpack_readinit
#define oggpack_look        vorbis_oggpack_look
#define oggpack_adv         vorbis_oggpack_adv
#define oggpack_read        vorbis_oggpack_read
#define oggpack_bytes       vorbis_oggpack_bytes
#define oggpack_bits        vorbis_oggpack_bits
#define oggpack_eop         vorbis_oggpack_eop

extern void  oggpack_readinit(oggpack_buffer *b,ogg_reference *r);
extern long  oggpack_look(oggpack_buffer *b,int bits);
extern void  oggpack_adv(oggpack_buffer *b,int bits);
extern long  oggpack_read(oggpack_buffer *b,int bits);
extern long  oggpack_bytes(oggpack_buffer *b);
extern long  oggpack_bits(oggpack_buffer *b);
extern int   oggpack_eop(oggpack_buffer *b);

/* Ogg BITSTREAM PRIMITIVES: decoding **************************/

#define ogg_sync_create         vorbis_ogg_sync_create
#define ogg2_sync_destroy       vorbis_ogg2_sync_destroy
#define ogg2_sync_reset         vorbis_ogg2_sync_reset
#define ogg2_sync_bufferin      vorbis_ogg2_sync_bufferin
#define ogg2_sync_wrote         vorbis_ogg2_sync_wrote
#define ogg2_sync_pageseek      vorbis_ogg2_sync_pageseek
#define ogg2_sync_pageout       vorbis_ogg2_sync_pageout
#define ogg2_stream_pagein      vorbis_ogg2_stream_pagein
#define ogg2_stream_packetout   vorbis_ogg2_stream_packetout
#define ogg2_stream_packetpeek  vorbis_ogg2_stream_packetpeek

extern ogg_sync_state *ogg2_sync_create(void);
extern int      ogg2_sync_destroy(ogg_sync_state *oy);
extern int      ogg2_sync_reset(ogg_sync_state *oy);

extern unsigned char *ogg2_sync_bufferin(ogg_sync_state *oy, long size);
extern int      ogg2_sync_wrote(ogg_sync_state *oy, long bytes);
extern long     ogg2_sync_pageseek(ogg_sync_state *oy,ogg_page *og);
extern int      ogg2_sync_pageout(ogg_sync_state *oy, ogg_page *og);
extern int      ogg2_stream_pagein(ogg_stream_state *os, ogg_page *og);
extern int      ogg2_stream_packetout(ogg_stream_state *os,ogg_packet *op);
extern int      ogg2_stream_packetpeek(ogg_stream_state *os,ogg_packet *op);

/* Ogg BITSTREAM PRIMITIVES: general ***************************/

#define ogg2_stream_create          vorbis_ogg2_stream_create
#define ogg2_stream_destroy         vorbis_ogg2_stream_destroy
#define ogg2_stream_reset           vorbis_ogg2_stream_reset
#define ogg2_stream_reset_serialno  vorbis_ogg2_stream_reset_serialno
#define ogg2_stream_eos             vorbis_ogg2_stream_eos
#define ogg2_page_checksum_set      vorbis_ogg2_page_checksum_set
#define ogg2_page_version           vorbis_ogg2_page_version
#define ogg2_page_continued         vorbis_ogg2_page_continued
#define ogg2_page_bos               vorbis_ogg2_page_bos
#define ogg2_page_eos               vorbis_ogg2_page_eos
#define ogg2_page_granulepos        vorbis_ogg2_page_granulepos
#define ogg2_page_serialno          vorbis_ogg2_page_serialno
#define ogg2_page_pageno            vorbis_ogg2_page_pageno
#define ogg2_page_packets           vorbis_ogg2_page_packets
#define ogg2_page_getbuffer         vorbis_ogg2_page_getbuffer
#define ogg2_packet_release         vorbis_ogg2_packet_release
#define ogg2_page_release           vorbis_ogg2_page_release
#define ogg2_page_dup               vorbis_ogg2_page_dup

extern ogg_stream_state *ogg2_stream_create(int serialno);
extern int      ogg2_stream_destroy(ogg_stream_state *os);
extern int      ogg2_stream_reset(ogg_stream_state *os);
extern int      ogg2_stream_reset_serialno(ogg_stream_state *os,int serialno);
extern int      ogg2_stream_eos(ogg_stream_state *os);

extern int      ogg2_page_checksum_set(ogg_page *og);

extern int      ogg2_page_version(ogg_page *og);
extern int      ogg2_page_continued(ogg_page *og);
extern int      ogg2_page_bos(ogg_page *og);
extern int      ogg2_page_eos(ogg_page *og);
extern ogg_int64_t  ogg2_page_granulepos(ogg_page *og);
extern ogg_uint32_t ogg2_page_serialno(ogg_page *og);
extern ogg_uint32_t ogg2_page_pageno(ogg_page *og);
extern int      ogg2_page_packets(ogg_page *og);
extern int      ogg2_page_getbuffer(ogg_page *og, unsigned char **buffer);

extern int      ogg2_packet_release(ogg_packet *op);
extern int      ogg2_page_release(ogg_page *og);

extern void     ogg2_page_dup(ogg_page *d, ogg_page *s);

/* Ogg BITSTREAM PRIMITIVES: return codes ***************************/

#define  OGG_SUCCESS   0

#define  OGG_HOLE     -10
#define  OGG_SPAN     -11
#define  OGG_EVERSION -12
#define  OGG_ESERIAL  -13
#define  OGG_EINVAL   -14
#define  OGG_EEOS     -15


#ifdef __cplusplus
}
#endif

#endif  /* _OGG_H */
