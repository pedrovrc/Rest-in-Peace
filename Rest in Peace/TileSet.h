#ifndef TILESET_H
#define TILESET_H

#include <bits/stdc++.h>
using namespace std;

#include "Sprite.h"

/*
 * Classe TileSet
 *
 * Contém um sprite com a imagem dos tiles a serem usados na construção do mapa.
 */
class TileSet {
	Sprite tileSet;
	int rows;
	int columns;
	int tileWidth = 0;
	int tileHeight = 0;
public:
	TileSet(int tileWidth, int tileHeight, string file, GameObject& associated);
	void RenderTile(unsigned index, float x, float y);
	int GetTileWidth();
	int GetTileHeight();
};

#endif
