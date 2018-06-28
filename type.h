#ifndef _TYPE_H_
#define _TYPE_H_
 
/* exact-width signed integer types */
typedef   signed           char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;
 
 
/* exact-width unsigned integer types */
typedef unsigned           char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned           int size_t;
typedef unsigned       __int64 uint64_t;
 
#ifndef NULL
#ifdef __cplusplus              // EC++
#define NULL   0
#else
#define NULL   ((void *) 0)
#endif
#endif
 
#ifndef boolean
typedef uint8_t boolean;
#endif
 
#ifndef TRUE
#define TRUE  1
#endif
 
#ifndef FALSE
#define FALSE 0
#endif
 
#endif /* _TYPE_H_ */
