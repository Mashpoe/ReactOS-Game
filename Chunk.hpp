#ifndef CHUNK_HPP_INCLUDED
#define CHUNK_HPP_INCLUDED

//#define CHUNK_WIDTH 4
//#define CHUNK_HEIGHT 4

class Chunk {

public:

    static const int width = 4, height = 4;

private:

    int data[width][height];

public:

    int* operator[](int pos) {
        return &data[pos][0];
    }

    Chunk(int x, int y) {

        int fillBlock = y > 0 ? y/10 + 1 : 0;


        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                data[x][y] = fillBlock;
            }
        }


    }

};


#endif // CHUNK_HPP_INCLUDED
