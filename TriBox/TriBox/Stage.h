#pragma once
#include <vector>
#include <memory>

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

class Goal;
class Player;
class Block;
class Stage
{
private:
	float stageSpeed;

	void LoadStageData();
	StageData stagedata;

	std::vector<Block> block;
	std::vector<Goal> goal;
	Player& player;

	std::vector<unsigned char> stageArrangement;
public:
	Stage(Player& _pl);
	~Stage();
	//Get
	std::vector<unsigned char> GetStageData()const;
	unsigned int GetStageWidth()const;

	//Set
	void SetStageSpeed(float _stageSpeed);

	//�`��
	void Draw();

	bool GoalCheck();
};

