#ifndef __MOVPAT_H__
#define __MOVPAT_H__

#include "p2Point.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include <math.h>

#define MAX_MOVEMENTS 25

struct Movements
{
	dPoint speed;
	dPoint finalPoint;
	double frames;
};

class MovePath
{
public:
	dPoint originPoint;
	int currentMov = 0;
	bool movFinished = false;
private:
	Movements movements[MAX_MOVEMENTS];
	int currentFrame = 0;
	dPoint position;
	uint last_mov = 0;

public:
	MovePath() {}
	~MovePath() {};

	void PushBack(dPoint finalPoint , double frames)
	{
		movements[last_mov].finalPoint = finalPoint;

		if (last_mov == 0) {
			movements[last_mov].speed.x = (finalPoint.x - originPoint.x) / frames;
			movements[last_mov].speed.y = (finalPoint.y - originPoint.y) / frames;
			movements[last_mov].frames = frames;
			++last_mov;
		}
		else {
			movements[last_mov].speed.x = (finalPoint.x - movements[last_mov - 1].finalPoint.x ) / frames;
			movements[last_mov].speed.y = (finalPoint.y - movements[last_mov - 1].finalPoint.y) / frames;
			movements[last_mov].frames = frames;
			++last_mov;
		}
	}

	void PushBack(int frames)
	{
		
		if (last_mov == 0) {
			movements[last_mov].finalPoint = originPoint;
			movements[last_mov].speed.x = 0;
			movements[last_mov].speed.y = 0;
			movements[last_mov].frames = frames;
			++last_mov;
		}
		else {
			movements[last_mov].finalPoint = movements[last_mov - 1].finalPoint;
			movements[last_mov].speed.x = 0;
			movements[last_mov].speed.y = 0;
			movements[last_mov].frames = frames;
			++last_mov;
		}
	}

	dPoint GetCurrentPosition()
	{
		//LOG("current frame :  %i", currentFrame);
		//LOG("position : (%i,%i)", position.x, position.y);



		if (currentFrame < movements[currentMov].frames)
		{
			movFinished = false;
			position.x += movements[currentMov].speed.x;
			position.y += movements[currentMov].speed.y;
			++currentFrame;
		}
		else if (currentMov >= last_mov) {
			movFinished = false;
			return position;
		}
		else {
			currentFrame = 0;
			++currentMov;
			movFinished = true;
		}
		return position;
	}


};

#endif // __MOVPAT_H__

