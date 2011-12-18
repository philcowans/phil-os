// common.c -- Defines some global functions.
// From JamesM's kernel development tutorials.

#include "common.h"

// Write a byte out to the specified port.
void outb(u16int port, u8int value)
{
  asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

u8int inb(u16int port)
{
  u8int ret;
  asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
}

u16int inw(u16int port)
{
  u16int ret;
  asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
}

void *memset(void *s, int c, size_t n) 
{
  int i;
  for(i = 0; i < n; ++i) {
    ((char *)s)[i] = c;
  }
  return s;
}

void *memcpy(void *dest, void *src, size_t n)
{
  int i;
  for(i = 0; i < n; ++i) {
    ((char *)dest)[i] = ((char *)src)[i];
  }
  return dest;
}

char *strcpy(char *dest, char *src) 
{
  int i = 0;
  while(src[i] != 0) {
    dest[i] = src[i];
    ++i;
  }
  return dest;
}

size_t strlen(const char *s) 
{
  size_t i = 0;
  while(s[i] != 0) {
    ++i;
  }
  return i;
}

int strcmp(const char *s1, const char *s2) 
{
  int i = 0;
  while(s1[i] != 0) {
    if(s1[i] > s2[i])
      return 1;
    else if (s1[i] < s2[i])
      return -1;
    ++i;
  }
  
  if(s2[i] == 0)
    return 0;
  else
    return -1;
}


extern void panic(const char *message, const char *file, u32int line)
{
    // We encountered a massive problem and have to stop.
    asm volatile("cli"); // Disable interrupts.

    monitor_write("PANIC(");
    monitor_write(message);
    monitor_write(") at ");
    monitor_write(file);
    monitor_write(":");
    monitor_write_hex(line);
    monitor_write("\n");
    // Halt by going into an infinite loop.
    for(;;);
}

extern void panic_assert(const char *file, u32int line, const char *desc)
{
    // An assertion failed, and we have to panic.
    asm volatile("cli"); // Disable interrupts.

    monitor_write("ASSERTION-FAILED(");
    monitor_write(desc);
    monitor_write(") at ");
    monitor_write(file);
    monitor_write(":");
    monitor_write_hex(line);
    monitor_write("\n");
    // Halt by going into an infinite loop.
    for(;;);
}
