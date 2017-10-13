// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "TileList.h"
#include "Tile.h"

TileList::TileList()
{
    listCap = 10;
    listTiles = new Tile[listCap];
    topIndex = 0;
}

TileList::~TileList()
{
    delete[] listTiles;
}

void TileList::addTile(Tile tile)
{
    // Check that next index lies within listTiles
    if(topIndex == listCap)
    {
        Tile * tmpTileList = new Tile[listCap + 10];
        listCap += 10;
        for(int i = 0; i < topIndex; i++)
        {
            tmpTileList[i] = listTiles[i];
        }
        delete[] listTiles;
        listTiles = tmpTileList;
    }

    listTiles[topIndex] = tile;
    topIndex += 1;
}

void TileList::drawAll(QGraphicsScene * scene)
{
    for (int i = 0; i <= topIndex; i++)
    {
        listTiles[i].draw(scene);
    }
}

int TileList::indexOfTopTile(int x, int y)
{
    for (int i = topIndex; 0 <= i; i--)
    {
        if ( listTiles[i].contains(x, y) )
        {
            return i;
        }
    }
    return -1;
}

void TileList::raise(int x, int y)
{
    int tileIndex = indexOfTopTile(x, y);
    if(0 < tileIndex)
    {
        Tile tmpTile = listTiles[tileIndex];

        for (int i = tileIndex; i < topIndex; i++)
        {
            listTiles[i] = listTiles[i+1];
        }
        listTiles[topIndex - 1] = tmpTile;
    }
}

void TileList::lower(int x, int y)
{
    int tileIndex = indexOfTopTile(x, y);
    if(0 < tileIndex)
    {
        Tile tmpTile = listTiles[tileIndex];

        for (int i = tileIndex; 0 < i; i--)
        {
            listTiles[i] = listTiles[i - 1];
        }
        listTiles[0] = tmpTile;
        //listTiles[tileIndex] = listTiles[tileIndex - 1];
    }
}

void TileList::remove(int x, int y)
{
    int tileIndex = indexOfTopTile(x, y);
    if(tileIndex != -1)
    {
        cout << tileIndex << endl;
        for (int i = tileIndex; i < topIndex; i++)
        {
            listTiles[i] = listTiles[i+1];
        }
        topIndex -= 1;
    }
}

void TileList::removeAll(int x, int y)
{
    int tileIndex = indexOfTopTile(x, y);
    while (tileIndex != -1)
    {
        for (int i = tileIndex; i < topIndex; i++)
        {
            listTiles[i] = listTiles[i+1];
        }

        tileIndex = indexOfTopTile(x, y);
        topIndex -= 1;
    }
}
