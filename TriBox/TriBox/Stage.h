#pragma once
#include <vector>
#include <memory>
#include "Vector2D.h"

//ステージの大きさ
struct StageSize
{
	StageSize() : beginX(0),beginY(0),endX(0),endY(0) {}
	StageSize(float _beginX,float _beginY,float _endX, float _endY) : beginX(_beginX), beginY(_beginY), endX(_endX), endY(_endY) {}
	
	float beginX;
	float beginY;
	float endX;
	float endY;
};

//fmfファイル読み込み用
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
class Lava;

class Stage
{
private:
	int lastHitBlock;
	float stageSpeed;
	float underLine;
	float stageFarRight;
	float stageFarLeft;

	void LoadStageData();
	StageData stagedata;

	std::vector<Block> block;//床ブロック情報
	std::vector<Goal> goal;//ゴール情報
	std::vector<ElevatorRail> rail;//エレベーターのレール情報
	std::vector<Elevator> elevator;//エレベーターの情報

	Player& player;
	std::shared_ptr<Lava> lava;

	std::vector<unsigned char> stageArrangement;

public:
	Stage(Player & _pl);
	~Stage();
	//Get
	//ステージの大きさを取得
	const StageSize GetStageSize();
	//ステージの一番低い座標の取得
	const float GetStageUnderLine();

	//Set
	//ステージ全体の移動速度の設定
	void SetStageSpeed(float _stageSpeed);

	//毎フレーム
	void Update();

	//符号取得
	int SignCheck(int _num);

	bool LavaHitCheck();

	//ゴール判定
	bool GoalCheck();
};

