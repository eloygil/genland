#pragma once
#include "Tile.h"
#include "Simplex2d.h"
#include "TextureManager.h"
class Chunk
{
public:	
	Chunk(sf::Vector2i pos, std::mt19937 *generator, std::ofstream &myfile);
    Chunk(sf::Vector2i pos, std::ifstream &myfile, int &id_temp);
	~Chunk();


	const static int N_TILES_X = 100;
	const static int N_TILES_Y = 200;
	const static int N_TILES_Z = 2;
	const static int TILE_SIZE = 32;

	sf::Vector2i chunk_pos;

	Tile* getTile(float x, float y, int z);
    Tile* getTileByIndex(int x, int y, int z);
    void DrawChunk(sf::RenderWindow& renderWindow, sf::Vector2f pos1, sf::Vector2f pos2, TextureManager &t, sf::Shader &tile_shader, sf::VertexArray &vertexArray);
    void DrawGrassTiles(sf::RenderWindow& renderWindow,TextureManager &t, sf::VertexArray &vertexArray);
	sf::Vector2i getTileIndex(float x, float y);
	void setTileNeighbors(int index_x, int index_y);
	void calcLateralNeighborsTiles(int latelal);
    void saveToFile();
    void initializeLights();
	Chunk* neighbors[2] = { nullptr };
	void recalcReachFloor();
	void recalcReachSun();

private:
	Tile* tile_mat[N_TILES_Y][N_TILES_X][N_TILES_Z];
    std::vector<Tile*> grass_tiles;


};