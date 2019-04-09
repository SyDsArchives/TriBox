#pragma once
#include <vector>
#include <memory>
#include "Vector2D.h"

//�X�e�[�W�̑傫��
struct StageSize
{
	StageSize() : beginX(0),beginY(0),endX(0),endY(0) {}
	StageSize(float _beginX,float _beginY,float _endX, float _endY) : beginX(_beginX), beginY(_beginY), endX(_endX), endY(_endY) {}
	
	float beginX;
	float beginY;
	float endX;
	float endY;
};

//fmf�t�@�C���ǂݍ��ݗp
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

	std::vector<Block> block;//���u���b�N���
	std::vector<Goal> goal;//�S�[�����
	std::vector<ElevatorRail> rail;//�G���x�[�^�[�̃��[�����
	std::vector<Elevator> elevator;//�G���x�[�^�[�̏��

	Player& player;
	std::shared_ptr<Lava> lava;

	std::vector<unsigned char> stageArrangement;

public:
	Stage(Player & _pl);
	~Stage();
	//Get
	//�X�e�[�W�̑傫�����擾
	const StageSize GetStageSize();
	//�X�e�[�W�̈�ԒႢ���W�̎擾
	const float GetStageUnderLine();

	//Set
	//�X�e�[�W�S�̂̈ړ����x�̐ݒ�
	void SetStageSpeed(float _stageSpeed);

	//���t���[��
	void Update();

	//�����擾
	int SignCheck(int _num);

	bool LavaHitCheck();

	//�S�[������
	bool GoalCheck();
};

