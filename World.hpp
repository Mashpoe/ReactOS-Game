#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include "Tile.hpp"
#include "Chunk.hpp"
#include "Entity.hpp"
#include <vector>
#include <cstdint>

class World {

    int loadDistance = 2;

    // 2d array of chunk pointers
    // dimensions: [(loadDistance * 2) + 1] * [(loadDistance * 2) + 1]
    Chunk** world = nullptr;
    // width and height of the buffer in chunks
    int buffWidth = 0, buffHeight = 0;

    // allocates the 2d chunk array
    void createBuffer();

    // the distance in chunks between (0,0) and the
    // top left corner of the loaded chunks
    int offsetX = 0, offsetY = 0;

public:

    void create(uint64_t seed = 1234567890);
    void load(const char* path);

    int width();
    int height();

    int getOffsetX() { return offsetX; }
    int getOffsetY() { return offsetY; }

    int get(int x, int y);

    void set(int x, int y, int block);

    // loads or unloads chunks based on player coords
    // sets player coords relative to loaded chunks
    void updateChunks(Entity& entity);

};

#endif // WORLD_HPP_INCLUDED
