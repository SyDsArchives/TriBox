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

const Rect Stage::GetStageSize()
{
	return Rect(0, stagedata.mapheight * 50, block[0].GetBlockPos().x, block[block.size() - 1].GetBlockPos().x);
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
	
	Rect rect;
	//ブロック
	int i = 0;
	for (auto& _block : block)
	{
		_block.Update(stageSpeed);

		if (rect.HitRect(player.GetRect(),_block.GetRect()).isHit_All)
		{
			player.SetOnGround(true);
			
		}

		if (_block.GetBlockPos().x > -100 && _block.GetBlockPos().x < WindowSizeX + 50)
		{
			_block.Draw();
		}
		++i;
	}

	float inx = block[8].GetBlockPos().x - player.GetPosition().x;
	float iny = block[8].GetBlockPos().y - player.GetPosition().y;
	Position2f dispos(inx, iny);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "%f", dispos.x);
	DrawFormatString(0, 40, GetColor(255, 255, 255), "%f", dispos.y);

	if (rect.HitRect(block[8].GetRect(), player.GetRect()).isHit_All)
	{
		int a = 0;
	}

	if (rect.IsCollision(block[8].GetRect(), player.GetRect()))
	{
		int a = 0;
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
