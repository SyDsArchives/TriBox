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


const int objectSize = 50;

Stage::Stage(Player& _pl) : player(_pl), stageSpeed(0.f), lastHitBlock(0), underLine(0)
{
	LoadStageData();
}


Stage::~Stage()
{
}

void Stage::LoadStageData()
{
	//�X�e�[�W�f�[�^�̓ǂݍ���
	FILE* fp = fopen("Resource/map/test.fmf", "rb");
	std::vector<unsigned char> dummyData;

	//�X�e�[�W�̃T�C�Y�A�����c���A1�}�b�v�`�b�v�̉����c���A���C���[���A�r�b�g�T�C�Y�̎擾
	fread(&stagedata, sizeof(StageData), 1, fp);

	//1���C���[�ӂ�̃T�C�Y���v�Z
	auto layersize = stagedata.mapwidth * stagedata.mapheight * (stagedata.bitcount / 8);

	//vector�z��̃T�C�Y�ύX
	dummyData.resize(layersize * stagedata.layercount);
	stageArrangement.resize(dummyData.size());

	//�_�~�[�ϐ��ɃX�e�[�W�z�u���ꎞ�ۑ�
	for (auto& dummy : dummyData)
	{
		fread(&dummy, sizeof(unsigned char), 1, fp);
	}
	
	
	fclose(fp);
	
	//�X�e�[�W�f�[�^���s�����ɕ��בւ���
	
	//int layerMapwidth = 0;//�ǂݍ���ł��郌�C���[���� * �X�e�[�W�T�C�Y(width * height)
	int dummyNum = 0;//�_�~�[�f�[�^�p
	int stageNum = 0;//�ۑ��f�[�^�p

	for (int layerCount = 0; layerCount < stagedata.layercount; ++layerCount)
	{
		//�ǂݍ���ł���X���W
		int dataX = 0;
		//�ǂݍ���ł��郌�C���[���� * �X�e�[�W�T�C�Y(width * height)
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

	//�_�~�[�f�[�^�̉��
	dummyData.clear();

	//�ǂݍ��񂾃f�[�^�̐�
	int dataNum = 0;

	for (int layerCount = 0; layerCount < stagedata.layercount; ++layerCount)
	{
		//�ǂݍ���ł��郌�C���[���� * �X�e�[�W�T�C�Y(width * height)
		int layerMapwidth = stagedata.mapwidth * stagedata.mapheight * layerCount;

		//for (int y = 0; y < stagedata.mapheight; ++y)
		//{
		//	for (int x = 0; x < stagedata.mapwidth; ++x)
		//	{
		//		dataNum = layerMapwidth + x * stagedata.mapheight + y;
		//		//�u���b�N����
		//		if (stageArrangement[dataNum] == 1)
		//		{
		//			block.push_back(Block(player, Position2f(objectSize * x, objectSize * y)));
		//			underLine = std::max<float>(underLine, static_cast<float>(objectSize * y));
		//		}

		//		//�S�[������
		//		if (stageArrangement[dataNum] == 2)
		//		{
		//			goal.push_back(Goal(Position2f(objectSize * x, objectSize * y)));
		//		}

		//		//�G���x�[�^�[���[��(������)
		//		if (stageArrangement[dataNum] == 3)
		//		{
		//			rail.push_back(ElevatorRail(Position2f(objectSize * x, objectSize * y), RailType::normalRail));
		//		}
		//		//�G���x�[�^�[���[��(������)
		//		if (stageArrangement[dataNum] == 4)
		//		{
		//			rail.push_back(ElevatorRail(Position2f(objectSize * x, objectSize * y), RailType::bottomRail));
		//		}
		//		//�G���x�[�^�[���[��(�㕔��)
		//		if (stageArrangement[dataNum] == 5)
		//		{
		//			rail.push_back(ElevatorRail(Position2f(objectSize * x, objectSize * y), RailType::topRail));
		//		}

		//		if (stageArrangement[dataNum] == 6)
		//		{
		//			int a = 0;
		//			elevator.push_back(Elevator(player, Position2f(objectSize * x, objectSize * y)));
		//		}
		//	}

	
		for (int x = 0; x < stagedata.mapwidth; ++x)
		{
			for (int y = 0; y < stagedata.mapheight; ++y)
			{
				dataNum = layerMapwidth + x * stagedata.mapheight + y;
				//�u���b�N����
				if (stageArrangement[dataNum] == 1)
				{
					block.push_back(Block(player, Position2f(objectSize * x, objectSize * y)));
					underLine = std::max<float>(underLine, static_cast<float>(objectSize * y));
				}

				//�S�[������
				if (stageArrangement[dataNum] == 2)
				{
					goal.push_back(Goal(Position2f(objectSize * x, objectSize * y)));
				}

				//�G���x�[�^�[���[��(������)
				if (stageArrangement[dataNum] == 3)
				{
					rail.push_back(ElevatorRail(Position2f(objectSize * x, objectSize * y), RailType::normalRail));
				}
				//�G���x�[�^�[���[��(������)
				if (stageArrangement[dataNum] == 4)
				{
					rail.push_back(ElevatorRail(Position2f(objectSize * x, objectSize * y), RailType::bottomRail));
				}
				//�G���x�[�^�[���[��(�㕔��)
				if (stageArrangement[dataNum] == 5)
				{
					rail.push_back(ElevatorRail(Position2f(objectSize * x, objectSize * y), RailType::topRail));
				}

				if (stageArrangement[dataNum] == 6)
				{
					int a = 0;
					elevator.push_back(Elevator(player, Position2f(objectSize * x, objectSize * y)));
				}
			}
		}
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
	Rect rect;//��`��r�p�ϐ�
	Position2 playerSize = player.GetPlayerSize();

	//�u���b�N
	for (auto& _block : block)
	{
		_block.Update(stageSpeed);

		//block.at(20).Draw();

		//Vector2f vecTopLeft(block.at(20).GetRect().centerX - block.at(20).GetRect().width / 2, block.at(20).GetRect().centerY - block.at(20).GetRect().height / 2);//����
		//Vector2f vecBottomLeft(block.at(20).GetRect().centerX - block.at(20).GetRect().width / 2, block.at(20).GetRect().centerY + block.at(20).GetRect().height / 2);//����
		//Vector2f vecTopRight(block.at(20).GetRect().centerX + block.at(20).GetRect().width / 2, block.at(20).GetRect().centerY - block.at(20).GetRect().height / 2);//�E��
		//Vector2f vecBottomRight(block.at(20).GetRect().centerX + block.at(20).GetRect().width / 2, block.at(20).GetRect().centerY + block.at(20).GetRect().height / 2);//�E��

		////����
		//Vector2f vecLeft(vecBottomLeft - vecTopLeft);
		//Vector2f vecLP(vecBottomLeft - player.GetPosition());
		////�㑤
		//Vector2f vecTop(vecTopLeft - vecTopRight);
		//Vector2f vecTP(vecTopLeft - player.GetPosition());
		////�E��
		//Vector2f vecRight(vecTopRight - vecBottomRight);
		//Vector2f vecRP(vecTopRight - player.GetPosition());
		////����
		//Vector2f vecBottom(vecBottomRight - vecBottomLeft);
		//Vector2f vecBP(vecBottomRight - player.GetPosition());

		////�߂荞�݂��m�F���邽�߂̒l���O�ςŏo��
		//float c1 = FCross(vecLeft, vecLP);//��
		//float c2 = FCross(vecTop, vecTP);//��
		//float c3 = FCross(vecRight, vecRP);//�E
		//float c4 = FCross(vecBottom, vecBP);//��

		//if (c2 < 0 && c1 > 0 && c3 > 0)
		//{
		//	player.SetOnGround(true);
		//	player.SetPosition(Vector2f(0, block.at(20).GetRect().centerY - block.at(20).GetRect().height), true, false);
		//	DrawFormatString(0, 0, 0xffffffff, "��������");
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
					player.SetPosition(Vector2f(0, _block.GetBlockPos().y - 54), true, false);
					
				}
				else if (SignCheck(iny) == -1)
				{
					player.SetPosition(Vector2f(0, _block.GetBlockPos().y + 54), true, false);
				}
				else
				{
					player.SetOnGround(true);
					player.SetPosition(Vector2f(0, _block.GetBlockPos().y - 54), true, false);
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

	//�S�[��
	for (auto& _goal : goal)
	{
		_goal.Update(stageSpeed);
	}
	
	//�G���x�[�^�[���[��
	for (auto& _rail : rail)
	{
		_rail.Update(stageSpeed);
	}

	//�G���x�[�^�[
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
					player.SetOnGround(true);
					player.SetPosition(Vector2f(0, _elevator.GetPosition().y - 55), true, false);
				}
				else if (SignCheck(iny) == -1)
				{
					player.SetPosition(Vector2f(0, _elevator.GetPosition().y + 50), true, false);
				}
				else
				{
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