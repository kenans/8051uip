#ifndef _RINGBUF_H_
#define _RINGBUF_H_

/**
 * -------------------------------------------------------------------------------------------
 *                                          Includes
 * -------------------------------------------------------------------------------------------
*/
#include "types.h"
/**
 * -------------------------------------------------------------------------------------------
 *                                          LocalBuffer
 * -------------------------------------------------------------------------------------------
*/
#define LocalBuf_IsEmpty()          ((_start)==(_end))
#define LocalBuf_IsFull()           (((_end+1)%(_size))==(_start))
#define LocalBuf_NumOfElements()    (((_end)>=(_start))?((_end)-(_start)):((_end)+(_size)-(_start)))
#define LocalBuf_Put(item)          do{_local_buf[_end]=item; ++_end; _end=_end%_size;}while(0)
#define LocalBuf_Get()              ((++_start,_start=_start%_size), (_start==0)?(_local_buf[_size-1]):(_local_buf[_start-1]))
#define LocalBuf_Peek()             (_local_buf[_start])
#define LocalBuf_PeekIndex(index)   (_local_buf[(_start+index)%_size])
#define LocalBuf_Remove()           do{++_start;_start%=_size;}while(0)
#define LocalBuf_Init()             do{(_start)=0;(_end)=0;}while(0)
#define LocalBuf_Clear()            LocalBuf_Init()
/**
 * -------------------------------------------------------------------------------------------
 *                                          RingBuffer
 * -------------------------------------------------------------------------------------------
*/
#define RingBufDeclare(ring_buf_name, item_type, count_type, buf_count) \
            struct{item_type _data[buf_count];count_type start,end,size;}ring_buf_name
#define RingBufInit(ring_buf) \
    do{(((ring_buf)->start))=0;(((ring_buf)->end))=0;\
    (((ring_buf)->size))=sizeof((ring_buf)->_data);}while(0)
#define RingBufResize(ring_buf,size)      do{(((ring_buf)->size))=size;(((ring_buf)->start))=0;(((ring_buf)->end))=0;}while(0)
#define RingBufIsEmpty(ring_buf)          ((((ring_buf)->start))==(((ring_buf)->end)))
#define RingBufIsFull(ring_buf)           (((((ring_buf)->end)+1)%(((ring_buf)->size)))==(((ring_buf)->start)))
#define RingBufNumOfElements(ring_buf) \
            (((((ring_buf)->end))>=(((ring_buf)->start)))?\
            ((((ring_buf)->end))-(((ring_buf)->start))):\
            ((((ring_buf)->end))+(((ring_buf)->size))-(((ring_buf)->start))))
#define RingBufPut(ring_buf,item) \
            do{((ring_buf)->_data[(ring_buf)->end])=item;\
            ++((ring_buf)->end);((ring_buf)->end)=((ring_buf)->end)%((ring_buf)->size);}while(0)
#define RingBufGet(ring_buf) \
            ((++((ring_buf)->start),((ring_buf)->start)=((ring_buf)->start)%((ring_buf)->size)),\
            (((ring_buf)->start)==0)?((ring_buf)->_data[((ring_buf)->size)-1]):((ring_buf)->_data[((ring_buf)->start)-1]))
#define RingBufPeek(ring_buf)             (((ring_buf)->_data[(ring_buf)->start]))
#define RingBufPeekIndex(ring_buf,index)  ((ring_buf)->_data[((ring_buf)->start+index)%((ring_buf)->size)])
#define RingBufRemove(ring_buf)           do{++((ring_buf)->start);((ring_buf)->start)%=((ring_buf)->size);}while(0)
#define RingBufClear(ring_buf)            RingBufInit(ring_buf)

#endif
