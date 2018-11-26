#include "Stage.h"
#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#include "Player.h"
#include "Geometry.h"
#include <algorithm>

#include "Block.h"
#include "Goal.h"
#include "ElevatorRail.h"
#include "Elevator.h"




Stage::Stage(Player& _pl) : player(_pl), stageSpeed(0.f), lastHitBlock(0), underLine(0)
{
	LoadStageData();
}


Stage::~Stage()
{
}

void Stage::LoadStageData()
{
	//ステージデータの読み込み
	FILE* fp = fopen("Resource/map/test.fmf", "rb");
	std::vector<unsigned char> dummyData;

	//ステージのサイズ、横幅縦幅、1マップチップの横幅縦幅、レイヤー数、ビットサイズの取得
	fread(&stagedata, sizeof(StageData), 1, fp);

	//1レイヤー辺りのサイズを計算
	auto layersize = stagedata.mapwidth * stagedata.mapheight * (stagedata.bitcount / 8);

	//vector配列のサイズ変更
	dummyData.resize(layersize * stagedata.layercount);
	stageArrangement.resize(dummyData.size());

	//ダミー変数にステージ配置を一時保存
	for (auto& dummy : dummyData)
	{
		fread(&dummy, sizeof(unsigned char), 1, fp);
	}
	
	
	fclose(fp);
	
	//ステージデータを行から列に並べ替える
	
	//int layerMapwidth = 0;//読み込んでいるレイヤー数目 * ステージサイズ(width * height)
	int dummyNum = 0;//ダミーデータ用
	int stageNum = 0;//保存データ用

	for (int layerCount = 0; layerCount < stagedata.layercount; ++layerCount)
	{
		//読み込んでいるX座標
		int dataX = 0;
		//読み込んでいるレイヤー数目 * ステージサイズ(width * height)
		int layerMapwidth = stagedata.mapwidth * stagedata.mapheight * layerCount;
		while (true)
		{
			for (int y = 0; y < stagedata.mapheight; ++y)
			{
				dummyNum = layerMapwidth + y * stagedata.mapwidth + dataX;
				stageNum = layerMapwidth + dataX * stagedata.mapheight + y;

				stageArrangement[stageNum] = dummyData[dummyNum];
			}

			++dataX;

			if (dataX >= stagedata.mapwidth)
			{
				break;
			}
		}
	}

	//ダミーデータの解放
	dummyData.clear();

	int dataNum = 0;

	for (int layerCount = 0; layerCount < stagedata.layercount; ++layerCount)
	{
		//読み込んでいるレイヤー数目 * ステージサイズ(width * height)
		int layerMapwidth = stagedata.mapwidth * stagedata.mapheight * layerCount;

		for (int y = 0; y < stagedata.mapheight; ++y)
		{
			for (int x = 0; x < stagedata.mapwidth; ++x)
			{
				dataNum = layerMapwidth + x * stagedata.mapheight + y;
				//ブロック生成
				if (stageArrangement[dataNum] == 1)
				{
					block.push_back(Block(player, Position2f(50 * x, 50 * y)));
					underLine = std::max<float>(underLine, static_cast<float>(50 * y));
				}

				//ゴール生成
				if (stageArrangement[dataNum] == 2)
				{
					goal.push_back(Goal(Position2f(50 * x, 50 * y)));
				}

				//エレベーターレール(中部分)
				if (stageArrangement[dataNum] == 3)
				{
					rail.push_back(ElevatorRail(Position2f(50 * x, 50 * y), RailType::normalRail));
				}
				//エレベーターレール(下部分)
				if (stageArrangement[dataNum] == 4)
				{
					rail.push_back(ElevatorRail(Position2f(50 * x, 50 * y), RailType::bottomRail));
				}
				//エレベーターレール(上部分)
				if (stageArrangement[dataNum] == 5)
				{
					rail.push_back(ElevatorRail(Position2f(50 * x, 50 * y), RailType::topRail));
				}

				if (stageArrangement[dataNum] == 6)
				{
					int a = 0;
					elevator.push_back(Elevator(player, Position2f(50 * x, 50 * y)));
				}
			}
		}
	}
}

const StageSize Stage::GetStageSize()
{
	//return Rect(0, stagedata.mapheight * 50, block[0].GetBlockPos().x, block[block.size() - 1].GetBlockPos().x);
	return StageSize(block[0].GetBlockPos().x, block[0].GetBlockPos().y, block[block.size() - 1].GetBlockPos().x, block[block.size() - 1].GetBlockPos().y);
}

const float Stage::GetStageUnderLine()
{
	return underLine;
}

void Stage::SetStageSpeed(float _stageSpeed)
{
	stageSpeed = _stageSpeed;
}

void Stage::Update()
{
	Rect rect;//矩形比較用変数

	//ブロック
	for (auto& _block : block)
	{
		_block.Update(stageSpeed);

		float inx = _block.GetBlockPos().x - player.GetPosition().x;
		float iny = _block.GetBlockPos().y - player.GetPosition().y;
		Position2f dispos(inx, iny);

		if (rect.IsCollision(_block.GetRect(), player.GetRect()))
		{
			int numx = SignCheck(static_cast<int>(inx)) == -1 ? inx * -1 : inx;
			int numy = SignCheck(static_cast<int>(iny)) == -1 ? iny * -1 : iny;
			char direction = numx > numy ? 'X' : 'Y';

			if (numx == numy)
			{
				int a = 0;
			}

			if (direction == 'X')
			{
				if (SignCheck(inx) == 1)
				{
					player.SetPosition(Vector2f(_block.GetBlockPos().x - 50, 0), false, true);
				}
				else if (SignCheck(inx) == -1)
				{
					player.SetPosition(Vector2f(_block.GetBlockPos().x + 50, 0), false, true);
				}
				else 
				{
					player.SetPosition(Vector2f(_block.GetBlockPos().x + 50, 0), false, true);
				}
			}
			else  if (direction == 'Y')
			{
				if (SignCheck(iny) == 1)
				{
					player.SetOnGround(true);
					player.SetPosition(Vector2f(0, _block.GetBlockPos().y - 60), true, false);
				}
				else if (SignCheck(iny) == -1)
				{
					player.SetPosition(Vector2f(0, _block.GetBlockPos().y + 50), true, false);
				}
				else
				{
					player.SetOnGround(true);
					player.SetPosition(Vector2f(0, _block.GetBlockPos().y - 60), true, false);
				}
			}
		}
		
		if (_block.GetBlockPos().x > -100 && _block.GetBlockPos().x < WindowSizeX + 50)
		{
			_block.Draw();
		}
	}

	//ゴール
	for (auto& _goal : goal)
	{
		_goal.Update(stageSpeed);
	}
	
	//エレベーターレール
	for (auto& _rail : rail)
	{
		_rail.Update(stageSpeed);
	}

	//エレベーター
	HitType hitType = {};
	for (auto& _elevator : elevator)
	{
		_elevator.Draw();
		_elevator.Update(stageSpeed);

		for (auto& _rail : rail)
		{
			hitType = _rail.HitCheck(_elevator.GetPosition());
			if (hitType.isHit)
			{
				_elevator.Active(&hitType.railType);
			}
		}
	}
}

int Stage::SignCheck(int _num)
{
	return ((_num > 0) - (_num < 0));
}

bool Stage::GoalCheck()
{
	bool ret = false;
	for (int i = 0; i < goal.size(); ++i)
	{
		if (goal[i].HitCheck(player.GetPosition()))
		{
			ret = true;
		}
	}
	return ret; 
}
