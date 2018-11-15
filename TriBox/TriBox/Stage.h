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

struct Rect;
class Ground;
class Goal;
class Player;
class Block;
class Stage
{
private:
	int lastHitBlock;
	float stageSpeed;

	void LoadStageData();
	StageData stagedata;

	std::vector<Block> block;
	std::vector<Goal> goal;
	Player& player;
	Ground& ground;

	std::vector<unsigned char> stageArrangement;
public:
	//Stage(Player& _pl);
	Stage(Player & _pl, Ground & _ground);
	~Stage();
	//Get
	std::vector<unsigned char> GetStageData()const;
	const Rect GetStageSize();

	//Set
	void SetStageSpeed(float _stageSpeed);

	//�`��
	void Draw();

	bool GoalCheck();
};

