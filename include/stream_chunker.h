#pragma once
#include <fcntl.h>

#include <memory>

#include "fastcdc-rs.h"

class StreamChunker {
public:
    StreamChunker(const char* path, uint32_t min_size, uint32_t avg_size,
                  uint32_t max_size) {
        chunker_ = stream_create_chunker(path, min_size, avg_size, max_size);
        if (!chunker_) {
            throw std::runtime_error("Failed to create chunker");
        }
    }

    ~StreamChunker() {
        if (chunker_ != nullptr) {
            stream_free_chunker(chunker_);
        }
    }

    ChunkData* nextChunk() {
        ChunkData* rawChunk = stream_next_chunk(chunker_);
        if (rawChunk == nullptr)
            return nullptr;
        return rawChunk;
    }

    static void freeChunkData(ChunkData* data) {
        if (data != nullptr) {
            stream_free_chunk_data(data);
        }
    }

private:
    Chunker chunker_;
};