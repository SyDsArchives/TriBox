#pragma once
class FPS
{
private:
	int startTime;
	int count;
	float fps;

	static const int N = 60;//����
	static const int settingFPS = 60;//�ݒ�FPS
public:
	FPS();
	~FPS();

	void Update();
	bool Wait();
	int WaitTime();
};

