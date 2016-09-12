#pragma once

/*Game class which is basically a repository for global data

Dean Lawson
Champlain College
2011
*/

#include <Trackable.h>

class Timer;

const float LOOP_TARGET_TIME = 1000.0f;//how long should each frame of execution take? 30fps = 33.3ms/frame

class Game:public Trackable
{
public:
	Game();
	~Game();

	int getFrameCount() const { return mFrameCount; };
	bool shouldExit() const { return mShouldExit; };
	void markShouldExit() { mShouldExit = true; };

	bool update();

private:
	Timer* mpTimer;
	int mFrameCount;
	bool mShouldExit;
};

extern Game* gpGame;
