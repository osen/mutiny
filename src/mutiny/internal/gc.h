#ifndef MUTINY_ENGINE_INTERNAL_GC_H
#define MUTINY_ENGINE_INTERNAL_GC_H

#include <string.h>

struct GcContext;

struct GcContext *gc_context();
void *gc_alloc(struct GcContext *ctx, size_t size);
int gc_finalizer(struct GcContext *ctx, void *ptr, void (*deleter)(void*));
void gc_collect(struct GcContext *ctx);
void gc_destroy(struct GcContext *ctx);

#endif
