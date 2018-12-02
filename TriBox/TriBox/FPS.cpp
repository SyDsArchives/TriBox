#include "FPS.h"
#include <Windows.h>
#include <mmsystem.h>
#include "DxLib.h"

#pragma comment(lib,"winmm.lib")


FPS::FPS():startTime(0),count(0),fps(0)
{
}


FPS::~FPS()
{
}

void FPS::Update()
{
	if (count == 0)
	{
		startTime = timeGetTime();
	}
	if (count == N) { 
		int t = timeGetTime();
		fps = 1000.f / ((t - startTime) / (float)N);
		count = 0;
		startTime = t;
	}
	count++;
}

bool FPS::Wait()
{
	if (WaitTime() > 0) {
		return true;
	}
	else {
		return false;
	}
}

int FPS::WaitTime()
{
	int tookTime = timeGetTime() - startTime;	//‚©‚©‚Á‚½ŽžŠÔ
	int waitTime = count * 1000 / settingFPS - tookTime;//‘Ò‚Â‚×‚«ŽžŠÔ

	return waitTime;
}
