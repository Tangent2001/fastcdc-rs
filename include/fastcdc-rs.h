#pragma once
#include <cstdint>
#include <stddef.h>

typedef void* StreamCDC_FilePtr;
typedef struct ChunkDataC {
    uint64_t hash;    // The gear hash value as of the end of the chunk.
    uint64_t offset;  // Starting byte position within the source.
    size_t length;    // Length of the chunk in bytes.
} ChunkDataC;

#ifdef __cplusplus
extern "C" {
#endif


StreamCDC_FilePtr stream_create_chunker(const char* path, uint32_t min_size,
                                        uint32_t avg_size, uint32_t max_size);
ChunkDataC* stream_next_chunk(StreamCDC_FilePtr chunker);
void stream_free_chunker(StreamCDC_FilePtr chunker);

#ifdef __cplusplus
}
#endif