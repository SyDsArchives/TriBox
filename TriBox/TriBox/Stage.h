#pragma once
#include <vector>
#include <memory>

enum class StageObject
{
	none,
	block,
};

struct StageSize
{
	StageSize() : beginX(0),beginY(0),endX(0),endY(0) {}
	StageSize(float _beginX,float _beginY,float _endX, float _endY) : beginX(_beginX), beginY(_beginY), endX(_endX), endY(_endY) {}
	
	float beginX;
	float beginY;
	float endX;
	float endY;
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
class Elevator;
class ElevatorRail;
class Goal;
class Player;
class Block;

class Stage
{
private:
	int lastHitBlock;
	float stageSpeed;
	float underLine;

	void LoadStageData();
	StageData stagedata;

	std::vector<Block> block;
	std::vector<Goal> goal;
	std::vector<ElevatorRail> rail;
	std::vector<Elevator> elevator;

	Player& player;

	std::vector<unsigned char> stageArrangement;
public:
	Stage(Player & _pl);
	~Stage();
	//Get
	std::vector<unsigned char> GetStageData()const;
	const StageSize GetStageSize();
	const float GetStageUnderLine();

	//Set
	void SetStageSpeed(float _stageSpeed);

	//ñàÉtÉåÅ[ÉÄ
	void Update();

	int SignCheck(int _num);

	bool GoalCheck();
};

