#include "Stage.h"
//#include "DxLib.h"
#include <stdio.h>
#include "Block.h"
#include <iostream>

Stage::Stage()
{
	LoadStageData();
}


Stage::~Stage()
{
}

void Stage::LoadStageData()
{
	FILE* fp = fopen("Resource/map/TriBox仮配置データ.fmf", "rb");

	std::vector<unsigned char> dummyData;

	fread(&stagedata, sizeof(StageData), 1, fp);

	auto layersize = stagedata.mapwidth * stagedata.mapheight * (stagedata.bitcount / 8);

	dummyData.resize(layersize);
	stageArrangement.resize(dummyData.size());

	for (auto& stage : dummyData)
	{
		fread(&stage, sizeof(unsigned char), 1, fp);
	}
	
	fclose(fp);

	for (int x = 0; x < stagedata.mapwidth; /*++x*/)
	{
		for (int y = 0; y < stagedata.mapheight; ++y)
		{
			if (y % stagedata.mapheight == 0)
			{
				//stageArrangement[y * stagedata.mapheight + x];
				stageArrangement[y * stagedata.mapheight + x] = dummyData[x * stagedata.mapwidth + y];
			}
		}
		++x;
	}

	//ダミーデータの解放
	dummyData.clear();

	int a = 0;

	//int mapy = 0;
	//for (int i = 0; i < layersize; ++i)
	//{
	//	if (i % 60 == 0)
	//	{
	//		//ステージ端まで行ったら+1
	//		mapy += 1;
	//	}
	//	//if (stageArrangement[i] == 1)
	//	{
	//		//block.push_back(Block(Position2f(50 * i, 50 * mapy )));
	//	}
	//}
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
	//for (int i = 0; i < block.size() - 1; ++i)
	//{
	//	block[i].Draw();
	//}
}
