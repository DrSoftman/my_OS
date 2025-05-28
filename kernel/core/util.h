#ifndef UTIL_H
#define UTIL_H


#ifdef __cplusplus
extern "C" {
#endif 

// fixed width integer types
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;
typedef u32 size_t;
typedef u32 uintptr_t;
typedef float f32;
typedef double f64;

#ifndef __cplusplus
typedef u8 bool;
#define true (1)
#define false (0)
#endif

#define NULL (0)


#define PACKED __attribute__((packed))

#ifndef asm
#define asm __asm__ volatile
#endif

#define CLI() asm ("cli")
#define STI() asm ("sti")

static inline u16 inports(u16 port) {
    u16 r;
    asm("inw %1, %0" : "=a" (r) : "dN" (port));
    return r;
}

static inline void outports(u16 port, u16 data) {
    asm("outw %1, %0" : : "dN" (port), "a" (data));
}

static inline u8 inportb(u16 port) {
    u8 r;
    asm("inb %1, %0" : "=a" (r) : "dN" (port));
    return r;
}

static inline void outportb(u16 port, u8 data) {
    asm("outb %1, %0" : : "dN" (port), "a" (data));
}

static inline size_t strlen(const char *str) {
    size_t l = 0;
    while (*str++ != 0) {
        l++;
    }
    return l;
}



static inline void memset(void *dst, u8 value, size_t n) {
    u8 *d = (u8*)dst;

    while (n-- > 0) {
        *d++ = value;
    }
}

static inline void *memcpy(void *dst, const void *src, size_t n) {
    u8 *d = (u8*)dst;
    const u8 *s = (const u8*)src;

    while (n-- > 0) {
        *d++ = *s++;
    }

    return d;
}

static inline void *memmove(void *dst, const void *src, size_t n) {
    // since we know that memcpy copies forwards
    if (dst < src) {
        return memcpy(dst, src, n);
    }

    u8 *d = (u8*)dst;
    const u8 *s = (const u8*)src;

    for (size_t i = n; i > 0; i--) {
        d[i - 1] = s[i - 1];
    }

    return dst;
}


#ifdef __cplusplus
}
#endif 


#endif
