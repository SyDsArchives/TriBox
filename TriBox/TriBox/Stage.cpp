#include "Stage.h"
//#include "DxLib.h"
#include <stdio.h>
#include "Block.h"

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
	fread(&stagedata, sizeof(StageData), 1, fp);
	auto layersize = stagedata.mapwidth * stagedata.mapheight;
	//stageArrangement.resize(layersize);
	for (int i = 0; i < layersize; ++i)
	{
		//fread(&stageArrangement[i], layersize, 1, fp);
	}
	fclose(fp);


	int mapy = 0;
	for (int i = 0; i < layersize; ++i)
	{
		if (i % 60 == 0)
		{
			//ステージ端まで行ったら+1
			mapy += 1;
		}
		//if (stageArrangement[i] == 1)
		{
			//block.push_back(Block(Position2f(50 * i, 50 * mapy )));
		}
	}
}

//std::vector<unsigned char> Stage::GetStageData()const
//{
//	//return stageArrangement;
//}

unsigned int Stage::GetStageWidth()const
{
	return stagedata.mapwidth;
}

void Stage::Draw()
{
	//for (int i = 0; i < block.size() - 1; ++i)
	//{
	//	block[i].Draw();
	//}
}
