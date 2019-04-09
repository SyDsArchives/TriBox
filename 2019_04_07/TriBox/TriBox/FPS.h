#pragma once
class FPS
{
private:
	int startTime;
	int count;
	float fps;

	static const int N = 60;//•½‹Ï
	static const int settingFPS = 60;//İ’èFPS
public:
	FPS();
	~FPS();

	void Update();
	bool Wait();
	int WaitTime();
};

