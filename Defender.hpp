#pragma once
#include "skills.h"

namespace MyStrategy
{
  // Naive example for defender
  void defender(BeliefState *state,int botID)
  {
    //print("Defender\n");
	//It follows the ball
	Vec2D dpoint;
	dpoint.x = -HALF_FIELD_MAXX / 2;
	dpoint.y = state->ballPos.y;
	if (state->ballPos.x < state->homePos[botID].x) {
		dpoint.x = state->ballPos.x + BOT_BALL_THRESH;
		dpoint.y = state->ballPos.y;
		//print("defend");
	}
	else if (state->ballPos.x < 0 && state->ballPos.x > state->homePos[botID].x && state->ballPos.x - 3*COLLISION_DIST < state->homePos[botID].x) {
		//print("shoot");
		shoot(botID, state, Vector2D<float>(state->ballPos.x, state->ballPos.y));
		return;
	}
	if (state->pr_ballOurSide)
		print("%d",state->pr_ballOurSide);
    GoToPoint(botID,state,dpoint,PI/2,false,false);
  }
}