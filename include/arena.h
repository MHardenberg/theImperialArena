#ifndef ARENA_H
#define ARENA_H

#include <assert.h>
#include <stdint.h>
#include <string.h>

#define DEFAULT_ARENA_RESERVATION_SIZE (256 * 1024 * 1024) // 256 MB
#ifdef DEBUG
#include <stdio.h>

#define LOG(...)                                                               \
        do {                                                                   \
                fprintf(stderr, __VA_ARGS__);                                  \
                fprintf(stderr, "\n");                                         \
        } while (0)

#define LOGERROR(...)                                                          \
        do {                                                                   \
                fprintf(stderr, "Error: <%s on line %d>\n\t", __FILE__,        \
                        __LINE__);                                             \
                LOG(__VA_ARGS__);                                              \
        } while (0)
#else

#define LOG(fmt, ...)                                                          \
        do {                                                                   \
        } while (0)
#define LOGERROR(fmt, ...)                                                     \
        do {                                                                   \
        } while (0)
#define CHECK_GL_ERROR()                                                       \
        do {                                                                   \
        } while (0)

#endif


#define PushArray(arena, type, count)                                          \
  (type *)ArenaPush((arena), sizeof(type) * (count))

#define PushArrayZero(arena, type, count)                                      \
  (type *)ArenaPushZero((arena), sizeof(type) * (count))

#define PushStruct(arena, type) PushArray((arena), (type), 1)
#define PushStructZero(arena, type) PushArrayZero((arena), (type), 1)

typedef struct {
  size_t reserved;
  size_t capacity;

  size_t offset;
  void *buffer;
} Arena;

typedef struct {
  Arena *arena;
  size_t prevOffset;

  void *buffer;
} ScratchPad;

int ArenaInit(Arena *arena);

void ArenaRelease(Arena *arena);

void *ArenaPush(Arena *arena, size_t bytes);

void *ArenaPushZero(Arena *arena, size_t bytes);

void ArenaClear(Arena *arena);

// scratchPad
ScratchPad *ScratchPadBegin(Arena *arena, size_t bytes);

void ScratchPadEnd(ScratchPad *pad);
#endif // ARENA_H
