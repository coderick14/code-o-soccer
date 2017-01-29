#pragma once
#include "skills.h"
#include "GoalKeeper.hpp"


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
	void centreBack(BeliefState *state, int botID)
	{
		/*Vec2D destPos;
		strips currentStrip = whichStrip(state->ballPos.x, state->ballPos.y);
		if (currentStrip == MIDDLE_STRIP) {
			goalkeeper(state, botID);
		}
		else if (currentStrip == TOP_STRIP) {
		}*/

		int safeX = -4250;
		if (botID != 0)
		{
			safeX = -3500;
		}

		int THRESHOLD_VELOCITY = 60;

		if (state->homeVel[botID].abs() > THRESHOLD_VELOCITY && state->homeVel[botID].x < 0 && state->homePos[botID].x > state->ballPos.x && whichStrip(state->ballPos.x, state->ballPos.y) == MIDDLE_STRIP && state->homePos[botID].x < (-HALF_FIELD_MAXX + 3 * DBOX_WIDTH)) {
			Stop(botID);
			return;
		}

		int dist = Vec2D::distSq(state->ballPos, homeGoal);
		Vec2D safepoint(-4000, 0);

		Vec2D pos = state->homePos[botID];
		Vec2D dest = Vec2D(pos);
		Vec2D ballpos = state->ballPos;
		int THRESH_VEL = 80;
		// conditions for clearing the ball
		if (dist < DBOX_WIDTH*DBOX_WIDTH * 2 && (state->ballVel.x > -THRESH_VEL) && !(botID == 2 && abs(state->ballPos.y) < OUR_GOAL_Y)) {
			//print("Shoot!!!");
			GoToBall(botID, state, false);
			save_goal(botID, state, Vector2D<float>(state->ballPos.x, state->ballPos.y));
			return;
		}
		dest.x = safeX;

		if (botID == 0 && Vec2D::dist(state->ballPos, state->homePos[botID]) < DBOX_WIDTH * 1.5)
		{
			dest.y = state->ballPos.y;
		}
		else
		{
			dest.y = rayCastY(state, botID);
		}
		const int THRESH = 350, THRESH_X = 300;
		if (dest.y > OUR_GOAL_MAXY + THRESH) {
			dest.y = OUR_GOAL_MAXY + THRESH;
			dest.x -= THRESH_X;
		}
		else if (dest.y < OUR_GOAL_MINY - THRESH) {
			dest.y = OUR_GOAL_MINY - THRESH;
			dest.x -= THRESH_X;
		}
		if (botID == 3)
		{
			dest.y = -dest.y;
		}
		//print("RayCast")
		GoToPointStraight(botID, state, dest, PI / 2, false, false);
		save_goal(botID, state, Vector2D<float>(state->ballPos.x, state->ballPos.y));

	}
}