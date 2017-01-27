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
	Vec2D homeGoal(-4200, 0);


	// Naive Example for GoalKeeper
	void goalkeeper(BeliefState *state, int botID)
	{
	//	int dist = Vec2D::distSq(state->ballPos, homeGoal);
	//	Vec2D safepoint(-4000, 0);

	//	Vec2D pos = state->homePos[botID];
	//	Vec2D dest = Vec2D(pos);
	//	Vec2D ballpos = state->ballPos;
	//	if (pos.x > -4100
	//		|| Vec2D::distSq(state->homePos[botID], safepoint) > 1100 * 1100) {
	//		print("ET go home");
	//		Vec2D safepoint(-4100, 0);
	//		dest.x = -4100;
	//	}

	//	dest.y = ballpos.y;
	//	if (dest.y > OUR_GOAL_MAXY) {
	//		dest.y = OUR_GOAL_MAXY;
	//	}
	//	else if (dest.y < OUR_GOAL_MINY) {
	//		dest.y = OUR_GOAL_MINY;
	//	}
	//	if (pos.x < -(HALF_FIELD_MAXX - 1.23*GOAL_DEPTH) && dist > 800 * 800) {
	//		dest.x = -4100;
	//		dest.y = pos.y;
	//	}
	//	GoToPoint(botID, state, dest, PI / 2, true, false);
	//	//vibrate(state, botID, 200);

	//	if (dist < DBOX_WIDTH*DBOX_WIDTH * 4) {
	//		print("Shoot!!!");
	//		GoToBall(botID, state, false);
	//		save_goal(botID, state, Vector2D<float>(state->ballPos.x, state->ballPos.y));
	//	}
	//}
		/**********************Good Old code with ray cast starts here********************************************************/
		int safeX = -4250;
		if (botID == 2)
		{
			safeX = -3650;
		}
		int dist = Vec2D::distSq(state->ballPos, homeGoal);

		Vec2D pos = state->homePos[botID];
		Vec2D safepoint(-4250, pos.y );


		//if ( botID == 0 && pos.x < safeX)
		//{
		//	GoToPointStraight(botID, state, safepoint, PI / 2, true, true);
		//	return;
		//}
		Vec2D dest = Vec2D(pos);
		Vec2D ballpos = state->ballPos;
		int THRESH_VEL = 50;
		if (dist < DBOX_WIDTH*DBOX_WIDTH * 2 && (state->ballVel.x > -THRESH_VEL) && !(botID == 2 && abs(state->ballPos.y) < OUR_GOAL_Y) ) {
			print("Shoot!!! %d ", botID);
			GoToBall(botID, state, false);
			save_goal(botID, state, Vector2D<float>(state->ballPos.x, state->ballPos.y));

			return;
		}
		dest.x = safeX;


		if ( botID == 0 && Vec2D::dist(state->ballPos, state->homePos[botID]) < 1000 )
		{
			print("follow y");
			dest.y = state->ballPos.y;
		}
		else
		{
			print("RayCast");
			dest.y = rayCastY(state, botID);
		}

		if (dest.y > OUR_GOAL_MAXY ) {
			dest.y = OUR_GOAL_MAXY;
		}
		else if (dest.y < OUR_GOAL_MINY)  {
			dest.y = OUR_GOAL_MINY;
		}
		//print("RayCast")
		if (Vec2D::distSq(state->homePos[botID], state->ballPos) > DBOX_WIDTH* DBOX_WIDTH * 3)
		{
			GoToPoint(botID, state, dest, PI / 2, false, false);
		}
		else
		{
			GoToPointStraight(botID, state, dest, PI / 2, false, true);
		}
		save_goal(botID, state, Vector2D<float>(state->ballPos.x, state->ballPos.y));

	}
}