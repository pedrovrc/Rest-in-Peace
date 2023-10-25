#include "TileMap.h"
#include "Camera.h"

#define TILESET_FILE "img/tileset.png"

/*
 * TileMap::TileMap(GameObject& associated, string file, TileSet* tileSet)
 *
 * Inicializa o objeto com a leitura do mapa e abre a imagem do tileset.
 */
TileMap::TileMap(GameObject& associated, string file, TileSet* tileSet) : Component(associated) {
	Load(file);
	this->tileSet = new TileSet(64, 64, TILESET_FILE, associated);
	renderFlag = false;
}

/*
 * void TileMap::Load(string file)
 *
 * Responsável por ler o arquivo texto do tile map e armazenar as informações em tileMatrix.
 */
void TileMap::Load(string file) {
	ifstream map;
	map.open(file);

	string line, buffer;
	int i = 0, j = 0;

	// obtem parametros gerais do mapa
	getline(map, line);
	for (i = 0; i < int(line.length()); i++) {
		if (line[i] == ',') continue;

		buffer += line[i];

		if (line[i+1] == ',') {
			if (j == 0) {
				mapWidth = stoi(buffer);
			} else if (j == 1) {
				mapHeight = stoi(buffer);
			} else if (j == 2) {
				mapDepth = stoi(buffer);
			}
			j++;
			buffer.clear();
		}
	}

	// obtem valores do mapa
	for (int k = 0; k < mapDepth; k++) {
		getline(map, line);

		for (j = 0; j < mapHeight; j++) {

			getline(map, line);

			for (i = 0; i < int(line.length()); i++) {
				if (line[i] == ',') continue;

				buffer += line[i];

				if (line[i+1] == ',') {
					tileMatrix.push_back(stoi(buffer) - 1);
					buffer.clear();
				}
			}
		}
	}
}

/*
 * int& TileMap::At(int x, int y, int z)
 *
 * Retorna o índice correspondente às coordenadas fornecidas do tile map.
 */
int& TileMap::At(int x, int y, int z) {
	int xAcesso = x;
	int yAcesso = y * mapWidth;
	int zAcesso = z * mapWidth * mapHeight;
	int& access = tileMatrix[xAcesso + yAcesso + zAcesso];
	return access;
}

/*
 * void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
 *
 * Renderiza todos os tiles de uma única camada do tile map.
 */
void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
	int index = 0;
	float x = 0, y = 0;
	int widthOffset = tileSet->GetTileWidth();
	int heightOffset = tileSet->GetTileHeight();

	for (int j = 0; j < mapHeight; j++) {
		for (int i = 0; i < mapWidth; i++) {
			index = At(i, j, layer);
			if (index < 0) continue;

			x =	i * widthOffset;
			y = j * heightOffset;
			tileSet->RenderTile(index, x - cameraX, y - cameraY);
		}
	}
}

/*
 * void TileMap::Render()
 *
 * Renderiza todas as camadas do tile map, sendo chamado duas vezes por frame.
 * Na primeira vez que é chamado, renderiza camadas abaixo dos GameObjects.
 * Na segunda vez, renderiza camadas acima dos GameObjects.
 */
void TileMap::Render() {
	if (renderFlag == false) {
		for (int i = 0; i < mapDepth - 1; i++) {
			RenderLayer(i, Camera::pos.x * (i+1), Camera::pos.y * (i+1));
		}
	} else {
		for (int i = mapDepth - 1; i < mapDepth; i++) {
			RenderLayer(i, Camera::pos.x * (i+1), Camera::pos.y * (i+1));
		}
	}
	renderFlag = !renderFlag;
}

void TileMap::Start() {

}

void TileMap::SetTileSet(TileSet* tileSet) {
	this->tileSet = tileSet;
}

int TileMap::GetWidth() {
	return mapWidth;
}

int TileMap::GetHeight() {
	return mapHeight;
}

int TileMap::GetDepth() {
	return mapDepth;
}

void TileMap::Update(float dt) {

}

bool TileMap::Is(string type) {
	if (type == "TileMap") return true;
	return false;
}

void TileMap::NotifyCollision(GameObject& other) {

}
