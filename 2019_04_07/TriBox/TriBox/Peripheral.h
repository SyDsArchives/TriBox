#pragma once
///���Ӌ@��(�L�[�{�[�h�A�p�b�h)�̐��������N���X
class Peripheral
{
private:
	int padState;
	int lastPadState;

public:
	Peripheral();
	~Peripheral();

	///���݂̉�����Ԃ̌��o
	///@param keyid ���ׂ����L�[�ԍ�
	///@retval true �����Ă�
	///@retval false �����ĂȂ�
	const bool IsPressing(int _keyid)const;

	///����̃L�[�̃g���K�[�̌��o
	///@param keyid ���ׂ����L�[�̔ԍ�
	///@retval true �����Ă�
	///@retval false �����ĂȂ�
	const bool IsTrigger(int _keyid)const;

	///���͏�Ԃ��X�V����
	///@attention ���t���[�����s���Ă�������
	void Update();
};

