#pragma once
#include <vector>
#include "behavior.h"
#include "ball/ball.h"

struct BehaviorFrame
{
	BehaviorFrame(Behavior* _mBehavior, float _mStartTime)
		:mBehavior(_mBehavior), mStartTime(_mStartTime)
	{}
	Behavior* mBehavior;
	float	mStartTime;
	bool operator < (const BehaviorFrame& rhs) const
	{
		return mStartTime < rhs.mStartTime;
	}
	friend bool operator < (const BehaviorFrame& lhs, const float rhs);
	friend bool operator < (const float lhs, const BehaviorFrame& rhs);
};
bool operator < (const BehaviorFrame& lhs, const float rhs) 
{
	return lhs.mStartTime < rhs;
}
bool operator < (const float lhs, const BehaviorFrame& rhs) 
{
	return lhs < rhs.mStartTime;
}
typedef std::vector<BehaviorFrame> BehaviorFrames;

class BehaviorAnimator
{
public:
	bool started;
	bool paused;
	float elapsedTime;
	float stopTime;
	BehaviorFrames mBehaviorFrames;

	inline BehaviorAnimator() : elapsedTime(0), started(false), paused(false), stopTime(0){}
	~BehaviorAnimator(){}

	void AddBehavior(Behavior* b, float time);
	void AddBehaviorFrame(BehaviorFrame b);
	void Sort();
	void Update(Ball* b, float dt);
	Behavior* GetNowBehavior(float time);
	void Start();
	void Stop();
	Behavior* Pause(float stopTime = 0);
};

