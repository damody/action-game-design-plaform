#include "BehaviorAnimator.h"
#include <algorithm>

void BehaviorAnimator::AddBehavior( Behavior* b, float time )
{
	mBehaviorFrames.push_back(BehaviorFrame(b, time));
}

void BehaviorAnimator::AddBehaviorFrame( BehaviorFrame b )
{
	mBehaviorFrames.push_back(b);
}

void BehaviorAnimator::Sort()
{
	sort(mBehaviorFrames.begin(), mBehaviorFrames.end());
}

Behavior* BehaviorAnimator::GetNowBehavior( float time )
{
	return lower_bound(mBehaviorFrames.begin(), mBehaviorFrames.end(), time)->mBehavior;
}

void BehaviorAnimator::Start()
{
	started = true;
	paused = false;
}

void BehaviorAnimator::Stop()
{
	started = false;
	paused = false;
	elapsedTime = 0;
}

Behavior* BehaviorAnimator::Pause(float stopTime)
{
	paused = true;
	this->stopTime = stopTime;

	return GetNowBehavior(elapsedTime);
}

void BehaviorAnimator::Update(Ball* b, float dt)
{
	if(!paused && started)
	{
		b->mpBehavior = GetNowBehavior(elapsedTime);
		elapsedTime += dt;
	}
	else if(paused && stopTime > 0)
	{
		stopTime -= dt;

		if(stopTime < 0)
		{
			stopTime = 0;
			paused = false;
		}
	}
}