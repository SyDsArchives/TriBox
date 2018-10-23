#pragma once
#include <vector>

enum class StageObject
{
	none,
	block,
};

struct StageData
{
	unsigned char identifier[4];
	unsigned int size;
	unsigned int mapwidth;
	unsigned int mapheight;
	unsigned char chipwidth;
	unsigned char chipheight;
	unsigned char layercount;
	unsigned char bitcount;
};

class Block;
class Stage
{
private:
	void LoadStageData();
	StageData stagedata;

	std::vector<Block> block;

	//std::vector<unsigned char> stageArrangement;
public:
	Stage();
	~Stage();
	std::vector<unsigned char> GetStageData()const;
	unsigned int GetStageWidth()const;
	void Draw();
};

