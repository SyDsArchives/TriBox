#include "Stage.h"
#include "DxLib.h"
#include <stdio.h>
#include "Block.h"
#include <iostream>
#include "Player.h"
#include "Geometry.h"

Stage::Stage(Player& _pl) : player(_pl)
{
	LoadStageData();
}


Stage::~Stage()
{
}

void Stage::LoadStageData()
{
	//ステージデータの読み込み
	FILE* fp = fopen("Resource/map/仮stage1.fmf", "rb");
	std::vector<unsigned char> dummyData;

	//ステージのサイズ、横幅縦幅、1マップチップの横幅縦幅、レイヤー数、ビットサイズの取得
	fread(&stagedata, sizeof(StageData), 1, fp);

	//1レイヤー辺りのサイズを計算
	auto layersize = stagedata.mapwidth * stagedata.mapheight * (stagedata.bitcount / 8);

	//vector配列のサイズ変更
	dummyData.resize(layersize);
	stageArrangement.resize(dummyData.size());

	//ダミー変数にステージ配置を一時保存
	for (auto& dummy : dummyData)
	{
		fread(&dummy, sizeof(unsigned char), 1, fp);
	}

	//auto a = stagedata.mapheight * stagedata.chipheight;
	
	fclose(fp);
	
	//ステージデータを行から列に並べ替える
	int dataX = 0;

	while (true)
	{
		for (int y = 0; y < stagedata.mapheight; ++y)
		{
			stageArrangement[dataX * stagedata.mapheight + y] = dummyData[y * stagedata.mapwidth + dataX];
		}

		++dataX;

		if (dataX >= stagedata.mapwidth)
		{
			break;
		}
	}
	
	//ダミーデータの解放
	dummyData.clear();

	for (int y = 0; y < stagedata.mapheight; ++y)
	{
		for (int x = 0; x < stagedata.mapwidth; ++x)
		{
			if (stageArrangement[x * stagedata.mapheight + y] == 1)
			{
				block.push_back(Block(Position2f(50 * x, 50 * y)));
			}
		}
	}
}

//std::vector<unsigned char> Stage::GetStageData()const
//{
//	//return stageArrangement;
//}

//unsigned int Stage::GetStageWidth()const
//{
//	return stagedata.mapwidth;
//}

void Stage::Draw()
{
	int count = 0;

	for(int i = 0; i < block.size(); ++i)
	{
		block[i].Update(5.f);
		
		if (block[i].GetBlockPos().x > -100 && block[i].GetBlockPos().x < WindowSizeX + 50)
		{
			block[i].Draw();
			block[i].HitCheck(player.GetPosition());
		}
	}
}
