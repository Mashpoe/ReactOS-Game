#include "World.hpp"
#include <cstdlib>

void World::createBuffer() {
    buffWidth = loadDistance*2 + 1;
    buffHeight = buffWidth;

    world = (Chunk**)malloc(sizeof(Chunk*) * buffWidth * buffHeight);
}

void World::create(uint64_t seed) {

    createBuffer();

    offsetX = 0;
    offsetY = 0;

    // generate the world
    int col = 0, row;
    for (int x = offsetX; x < offsetX + buffWidth; x++) {
        row = 0;
        for (int y = offsetY; y < offsetY + buffHeight; y++) {
            world[col*buffHeight + row] = new Chunk(x,y);
            row++;
        }
        col++;
    }
}

int World::width() {
    return buffWidth * Chunk::width;
}

int World::height() {
    return buffHeight * Chunk::height;
}

int World::get(int x, int y) {

    //return 0;
    return (*world
    [x/Chunk::width * buffHeight + y/Chunk::height])
    [x%Chunk::width]
    [y%Chunk::height];
}

void World::set(int x, int y, int block) {

    (*world
    [x/Chunk::width * buffHeight + y/Chunk::height])
    [x%Chunk::width]
    [y%Chunk::height]
    = block;
}

void World::updateChunks(Entity& entity) {

    int newOffsetX = offsetX, newOffsetY = offsetY;

    int xChunk = entity.x/TILE_WIDTH/Chunk::width;
    if (xChunk < loadDistance) {
        newOffsetX--;
        entity.x += Chunk::width * TILE_WIDTH;
    } else if (xChunk > loadDistance + 1) {
        newOffsetX++;
        entity.x -= Chunk::width * TILE_WIDTH;
    }

    int yChunk = entity.y/TILE_HEIGHT/Chunk::height;
    if (yChunk < loadDistance) {
        newOffsetY--;
        entity.y += Chunk::height * TILE_HEIGHT;
    } else if (yChunk > loadDistance + 1) {
        newOffsetY++;
        entity.y -= Chunk::height * TILE_HEIGHT;
    }

    int xDiff = newOffsetX - offsetX;
    int yDiff = newOffsetY - offsetY;

    if (xDiff || yDiff) {

        // create a new buffer
        Chunk** oldWorld = world;
        createBuffer();

        int col = 0, row;
        for (int x = newOffsetX; x < newOffsetX + buffWidth; x++) {
            row = 0;
            for (int y = newOffsetY; y < newOffsetY + buffHeight; y++) {

                // check if the chunk is in the old buffer
                if (x >= offsetX &&
                    x < offsetX + buffWidth &&
                    y >= offsetY &&
                    y < offsetY + buffHeight
                ) {
                    // the chunk is already loaded, keep it
                    int oldWorldIndex = (col+xDiff)*buffHeight + (row+yDiff);
                    world[col*buffHeight + row] = oldWorld[oldWorldIndex];
                    oldWorld[oldWorldIndex] = nullptr; // set it to null so it isn't deleted
                } else {
                    world[col*buffHeight + row] = new Chunk(x, y);
                }

                row++;
            }
            col++;
        }

        // unload chunks that are out of view
        for (int x = 0; x < buffWidth; x++) {
            for (int y = 0; y < buffHeight; y++) {
                Chunk* currChunk = oldWorld[x*buffHeight + y];
                if (currChunk != nullptr) {
                    delete currChunk;
                }
            }
        }
        delete oldWorld;


    }

    offsetX = newOffsetX;
    offsetY = newOffsetY;

}
