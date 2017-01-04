#pragma once
#include "skills.h"

/*
	Vec2D can be used to make variables that can store points as (x,y) and provide utility functions.
	Vec2D point1;
	Vec2D point2;
	point1.x = HALF_FIELD_MAXX;
	point1.y = 0;
	similarly for point2 can be specified
	Some utility functions:
	These will appear automatically as you type Vec2D::
	float angle = Vec2D::angle(point1,point2);   
	int distance = Vec2D::distSq(point1,point2);
*/

namespace MyStrategy
{
	Vec2D homeGoal(OUR_GOAL_X, 0);
  // Naive Example for GoalKeeper
  void goalkeeper(BeliefState *state,int botID)
  {
	int dist = Vec2D::distSq(state->ballPos, homeGoal);
	if (dist < DBOX_WIDTH*DBOX_WIDTH * 4) {
		print("Sparta!!!!!!!!\n");
		shoot(botID, state, Vector2D<float>(state->ballPos.x, state->ballPos.y));
		return;
	}
	Vec2D pos = state->homePos[botID];
	if (pos.x < -(HALF_FIELD_MAXX - 1.23*GOAL_DEPTH)) {
		Vec2D safepoint(-4000, 0);
		GoToPoint(botID, state, safepoint, PI / 2, false, true);
		print("Come out");
		return;
	}
	if (/*abs(pos.x - (OUR_GOAL_X + DBOX_HEIGHT)) > 220*/ Vec2D::distSq(state->homePos[botID], Vec2D(-4200, 0)) > 1100*1100) {
		print("GOALKEEPER: MOVE BACK TO BASE %d\t%d\t%d\n", pos.x, OUR_GOAL_X + DBOX_HEIGHT, abs(pos.x - (OUR_GOAL_X + DBOX_HEIGHT)));
		Vec2D dpoint(OUR_GOAL_X + DBOX_HEIGHT, state->ballPos.y);

		if (dpoint.y > OUR_GOAL_MAXY - 300)
			dpoint.y = OUR_GOAL_MAXY - 300;
		if (dpoint.y < OUR_GOAL_MINY + 300)
			dpoint.y = OUR_GOAL_MINY + 300;
		GoToPoint(botID, state, dpoint, PI / 2, true, true);
		return;
	}
	if(fabs(fabs(state->homeAngle[botID]) - PI / 2) > 0.2) {
		print("Goalkeeper TURNING %f\n", state->homeAngle[botID]);
		TurnToAngle(botID, state, PI / 2);
	}
	else {
		print("Goalkeeper RUNNING\n");
		if (state->homePos[botID].y > OUR_GOAL_MAXY) {
			Velocity(botID, -MAX_BOT_SPEED, -MAX_BOT_SPEED);
		}
		else if (state->homePos[botID].y < -OUR_GOAL_MAXY) {
			Velocity(botID, MAX_BOT_SPEED, MAX_BOT_SPEED);
		}
		else if (state->homePos[botID].y > state->ballPos.y) {
			Velocity(botID, -MAX_BOT_SPEED, -MAX_BOT_SPEED);
		}
		else {
			Velocity(botID, MAX_BOT_SPEED, MAX_BOT_SPEED);
		}
	}
  }
}