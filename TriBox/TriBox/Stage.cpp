#include "Stage.h"
#include "DxLib.h"
#include <stdio.h>
#include <iostream>
#include "Player.h"
#include "Geometry.h"
#include <algorithm>
#include "Vector2D.h"

#include "Block.h"
#include "Goal.h"
#include "ElevatorRail.h"
#include "Elevator.h"
#include "Lava.h"

const int objectSize = 50;

Stage::Stage(Player& _pl) : player(_pl), stageSpeed(0.f), lastHitBlock(0), underLine(0),stageFarLeft(WindowSizeX),stageFarRight(0)
{
	LoadStageData();
	lava = std::make_shared<Lava>(Vector2f(0,WindowSizeY));
	int a = 0;
}


Stage::~Stage()
{
}

void Stage::LoadStageData()
{
	//ステージデータの読み込み
	FILE* fp = fopen("Resource/map/縦ステージ2.fmf", "rb");
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
	

	int dummyNum = 0;//ダミーデータ用
	int stageNum = 0;//保存データ用

	//ステージデータを行から列に並べ替える
	//for (int layerCount = 0; layerCount < stagedata.layercount; ++layerCount)
	//{
	//	//読み込んでいるX座標
	//	int dataX = 0;
	//	//読み込んでいるレイヤー数目 * ステージサイズ(width * height)
	//	int layerMapwidth = stagedata.mapwidth * stagedata.mapheight * layerCount;
	//	while (true)
	//	{
	//		for (int y = 0; y < stagedata.mapheight; ++y)
	//		{
	//			dummyNum = layerMapwidth + y * stagedata.mapwidth + dataX;
	//			stageNum = layerMapwidth + dataX * stagedata.mapheight + y;

	//			stageArrangement[stageNum] = dummyData[dummyNum];
	//		}

	//		++dataX;

	//		if (dataX >= stagedata.mapwidth)
	//		{
	//			break;
	//		}
	//	}
	//}

	//ステージデータの読み込みを上→下から下→上になるように並べ替える
	for (int layerCount = 0; layerCount < stagedata.layercount; ++layerCount)
	{
		//読み込んだレイヤーの合計最大マップチップ数
		int layerMaxMapchip = stagedata.mapwidth * stagedata.mapheight * layerCount;
		int dataY = 0;

		for (int height = stagedata.mapheight - 1; height > 0; --height)
		{
			for (int width = 0; width < stagedata.mapwidth; ++width)
			{
				dummyNum = layerMaxMapchip + height * stagedata.mapwidth + width;
				stageNum = layerMaxMapchip + dataY * stagedata.mapwidth + width;
				stageArrangement[stageNum] = dummyData[dummyNum];
			}
			++dataY;
		}
	}

	//ダミーデータの解放
	dummyData.clear();

	//読み込んだデータの数
	int dataNum = 0;

	for (int layerCount = 0; layerCount < stagedata.layercount; ++layerCount)
	{
		//読み込んでいるレイヤー数目 * ステージサイズ(width * height)
		int layerMapwidth = stagedata.mapwidth * stagedata.mapheight * layerCount;
		
		float objectY = WindowSizeY;

		for (int y = 0; y < stagedata.mapheight; ++y)
		{
			float objectX = 0;
			objectY = objectY - objectSize;
			for (int x = 0; x < stagedata.mapwidth; ++x)
			{
				dataNum = layerMapwidth + y * stagedata.mapwidth + x;
				//空白
				if (stageArrangement[dataNum] == 0)
				{
					objectX = objectX + objectSize;
				}

				//ブロック生成
				if (stageArrangement[dataNum] == 1)
				{
					block.push_back(Block(player, Position2f(objectX + objectSize / 2, objectY)));
					objectX = objectX + objectSize;
					underLine = std::max<float>(underLine, static_cast<float>(objectSize * y));//いずれ消す
					stageFarLeft = block[0].GetBlockPos().x - block[0].GetRect().width / 2;
					stageFarRight = std::max<float>(stageFarRight, static_cast<float>(objectX - objectSize / 2));

				}

				//ゴール生成
				if (stageArrangement[dataNum] == 2)
				{
					goal.push_back(Goal(Position2f(objectX + objectSize / 2, objectY)));
					objectX = objectX + objectSize;
				}

				//エレベーターレール(中部分)
				if (stageArrangement[dataNum] == 3)
				{
					rail.push_back(ElevatorRail(Position2f(objectX + objectSize / 2, objectY), RailType::normalRail));
					objectX = objectX + objectSize;
				}
				//エレベーターレール(下部分)
				if (stageArrangement[dataNum] == 4)
				{
					rail.push_back(ElevatorRail(Position2f(objectX + objectSize / 2, objectY), RailType::bottomRail));
					objectX = objectX + objectSize;
				}
				//エレベーターレール(上部分)
				if (stageArrangement[dataNum] == 5)
				{
					rail.push_back(ElevatorRail(Position2f(objectX + objectSize / 2, objectY), RailType::topRail));
					objectX = objectX + objectSize;
				}

				//エレベータ
				if (stageArrangement[dataNum] == 6)
				{
					elevator.push_back(Elevator(player, Position2f(objectX + objectSize / 2, objectY)));
					objectX = objectX + objectSize;
				}
			}
		}
		int a = 0;
	}
}

const StageSize Stage::GetStageSize()
{
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
	Position2 playerSize = player.GetPlayerSize();

	//ブロック
	for (auto& _block : block)
	{
		_block.Update(stageSpeed);

		//block.at(20).Draw();

		//Vector2f vecTopLeft(block.at(20).GetRect().centerX - block.at(20).GetRect().width / 2, block.at(20).GetRect().centerY - block.at(20).GetRect().height / 2);//左上
		//Vector2f vecBottomLeft(block.at(20).GetRect().centerX - block.at(20).GetRect().width / 2, block.at(20).GetRect().centerY + block.at(20).GetRect().height / 2);//左下
		//Vector2f vecTopRight(block.at(20).GetRect().centerX + block.at(20).GetRect().width / 2, block.at(20).GetRect().centerY - block.at(20).GetRect().height / 2);//右上
		//Vector2f vecBottomRight(block.at(20).GetRect().centerX + block.at(20).GetRect().width / 2, block.at(20).GetRect().centerY + block.at(20).GetRect().height / 2);//右下

		////左側
		//Vector2f vecLeft(vecBottomLeft - vecTopLeft);
		//Vector2f vecLP(vecBottomLeft - player.GetPosition());
		////上側
		//Vector2f vecTop(vecTopLeft - vecTopRight);
		//Vector2f vecTP(vecTopLeft - player.GetPosition());
		////右側
		//Vector2f vecRight(vecTopRight - vecBottomRight);
		//Vector2f vecRP(vecTopRight - player.GetPosition());
		////下側
		//Vector2f vecBottom(vecBottomRight - vecBottomLeft);
		//Vector2f vecBP(vecBottomRight - player.GetPosition());

		////めり込みを確認するための値を外積で出す
		//float c1 = FCross(vecLeft, vecLP);//左
		//float c2 = FCross(vecTop, vecTP);//上
		//float c3 = FCross(vecRight, vecRP);//右
		//float c4 = FCross(vecBottom, vecBP);//下

		//if (c2 < 0 && c1 > 0 && c3 > 0)
		//{
		//	player.SetOnGround(true);
		//	player.SetPosition(Vector2f(0, block.at(20).GetRect().centerY - block.at(20).GetRect().height), true, false);
		//	DrawFormatString(0, 0, 0xffffffff, "ああああ");
		//}

		//float playerVecLength = sqrt(player.GetVelocity().x * player.GetVelocity().x + player.GetVelocity().y * player.GetVelocity().y);

		//float leftAPDot = FDot(vecTP, player.GetVelocity());
		//float lpDot = leftAPDot / playerVecLength;

		//float rightAPDot = FDot(vecRP, player.GetVelocity());
		//float rpDot = rightAPDot / playerVecLength;

		//if (c2 > 0 && c1 > 0 && c3 > 0 && c4 > 0)
		//{
		//	if (lpDot < 0)
		//	{
		//		/*player.SetPosition(Vector2f(block.at(20).GetRect().centerX - block.at(20).GetRect().width + player.GetRect().width / 2, 0), false, true);*/
		//		player.SetVelocity(Vector2f(0, player.GetVelocity().y));
		//	}
		//	
		//	if (rpDot < 0)
		//	{
		//		//player.SetPosition(Vector2f(block.at(20).GetRect().centerX + block.at(20).GetRect().width - player.GetRect().width / 2, 0), false, true);
		//		player.SetVelocity(Vector2f(0, player.GetVelocity().y));
		//	}
		//}


		//if (player.GetPosition().y > 500)
		//{
		//	player.SetOnGround(true);
		//	player.SetPosition(Vector2f(0, 500), true, false);
		//}

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

			if (direction == 'Y')
			{
				if (SignCheck(iny) == 1)
				{
					player.SetOnGround(true);
					player.SetPosition(Vector2f(0, _block.GetBlockPos().y - 50), true, false);
					
				}
				else if (SignCheck(iny) == -1)
				{
					player.SetPosition(Vector2f(0, _block.GetBlockPos().y + 50), true, false);
				}
				else
				{
					player.SetOnGround(true);
					player.SetPosition(Vector2f(0, _block.GetBlockPos().y - 50), true, false);
				}
			}
			else if (direction == 'X')
			{
				if (SignCheck(inx) == 1)
				{
					player.SetPosition(Vector2f(_block.GetBlockPos().x - 40, 0), false, true);
				}
				else if (SignCheck(inx) == -1)
				{
					player.SetPosition(Vector2f(_block.GetBlockPos().x + 40, 0), false, true);
				}
				else 
				{
					player.SetPosition(Vector2f(_block.GetBlockPos().x + 40, 0), false, true);
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

		float inx = _elevator.GetPosition().x - player.GetPosition().x;
		float iny = _elevator.GetPosition().y - player.GetPosition().y;
		Position2f dispos(inx, iny);

		if (rect.IsCollision(_elevator.GetRect(), player.GetRect()))
		{
			int numx = SignCheck(static_cast<int>(inx)) == -1 ? inx * -1 : inx;
			int numy = SignCheck(static_cast<int>(iny)) == -1 ? iny * -1 : iny;
			char direction = numx > numy ? 'X' : 'Y';

			if (numx == numy)
			{
				int a = 0;
			}

			if (direction == 'Y')
			{
				if (SignCheck(iny) == 1)
				{
					_elevator.onPlayer(true);
					player.SetOnGround(true);
					player.SetPosition(Vector2f(0, _elevator.GetPosition().y - 55), true, false);
				}
				else if (SignCheck(iny) == -1)
				{
					player.SetPosition(Vector2f(0, _elevator.GetPosition().y + 50), true, false);
				}
				else
				{
					_elevator.onPlayer(true);
					player.SetOnGround(true);
					player.SetPosition(Vector2f(0, _elevator.GetPosition().y - 55), true, false);
				}
			}
			else if (direction == 'X')
			{
				if (SignCheck(inx) == 1)
				{
					player.SetPosition(Vector2f(_elevator.GetPosition().x - 40, 0), false, true);
				}
				else if (SignCheck(inx) == -1)
				{
					player.SetPosition(Vector2f(_elevator.GetPosition().x + 40, 0), false, true);
				}
				else
				{
					player.SetPosition(Vector2f(_elevator.GetPosition().x + 40, 0), false, true);
				}
			}
		}
		else
		{
			_elevator.onPlayer(false);
		}

		for (auto& _rail : rail)
		{
			hitType = _rail.HitCheck(_elevator.GetPosition());
			if (hitType.isHit)
			{
				_elevator.Active(&hitType.railType);
			}
		}
	}

	lava->Update(stageSpeed);

	DrawFormatString(0, 50, 0xffffff, "%f", stageFarLeft);
	DrawFormatString(0, 75, 0xffffff, "%f", stageFarRight);

	if (player.GetPosition().x >= stageFarRight)
	{
		player.SetPosition(Vector2f(stageFarLeft + 10, 0), false, true);
	}
	else if (player.GetPosition().x <= stageFarLeft)
	{
		player.SetPosition(Vector2f(stageFarRight - 10, 0), false, true);
	}
}


int Stage::SignCheck(int _num)
{
	return ((_num > 0) - (_num < 0));
}

bool Stage::LavaHitCheck()
{
	if (lava->GetPosition().y <= player.GetPosition().y)
	{
		return true;
	}
	return false;
}

bool Stage::GoalCheck()
{
	bool ret = false;
	Rect rect;
	//for (int i = 0; i < goal.size(); ++i)
	//{
	//	if (rect.IsCollision(goal[i].GetRect(),player.GetRect()))
	//	{
	//		ret = true;
	//	}
	//}
	for (auto& g : goal)
	{
		if (rect.IsCollision(g.GetRect(), player.GetRect()))
		{
			ret = true;
		}
	}
	return ret; 
}
