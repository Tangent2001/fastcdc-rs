#pragma once
#include <cstdint>
#include <stddef.h>

typedef void* Chunker;
typedef struct ChunkData {
    uint64_t hash;    // The gear hash value as of the end of the chunk.
    uint64_t offset;  // Starting byte position within the source.
    size_t length;    // Length of the chunk in bytes.
    const uint8_t* data;  // Pointer to the chunk data.
} ChunkData;

#ifdef __cplusplus
extern "C" {
#endif
Chunker stream_create_chunker(int fd, uint32_t min_size, uint32_t avg_size,
                              uint32_t max_size);
ChunkData* stream_next_chunk(Chunker chunker);
void stream_free_chunk_data(ChunkData* data);
void stream_free_chunker(Chunker chunker);
#ifdef __cplusplus
}
#endif