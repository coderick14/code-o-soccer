#pragma once
#include "skills.h"

namespace MyStrategy
{
	// Naive example for defender
	void strike_supporter(BeliefState *state, int botID)
	{
		//print("Defender\n");
		//It follows the ball
		Vec2D dpoint;
		dpoint.x = 1000;

		dpoint.y = rayCastY(state, botID, false);
		/*if (dpoint.y > 3 * OUR_GOAL_MAXY) {
			dpoint.y = OUR_GOAL_MAXY;
		}
		else if (dpoint.y < 3 * OUR_GOAL_MINY) {
			dpoint.y = OUR_GOAL_MINY;
		}*/

		int THRESHOLD_VELOCITY = 60;

		if (state->homeVel[botID].abs() < THRESHOLD_VELOCITY && state->homeVel[botID].x < 0 && state->homePos[botID].x > state->ballPos.x && state->ballPos.x < (-HALF_FIELD_MAXX + 2 * DBOX_WIDTH) && whichStrip(state->ballPos.x, state->ballPos.y) == MIDDLE_STRIP && state->homePos[botID].x < (-HALF_FIELD_MAXX + 3 * DBOX_WIDTH)) {
			Stop(botID);
			return;
		}
		bool isSpin = true;
		if (state->ballPos.x < state->homePos[botID].x) {
			isSpin = false;
			if (state->ballPos.y > 0/*Vec2D::distSq(state->ballPos, state->homePos[botID]) < 4 * BOT_BALL_THRESH * BOT_BALL_THRESH*/)
			{
				dpoint.x = state->ballPos.x - 2 * BOT_BALL_THRESH;
				dpoint.y = state->ballPos.y - 2 * BOT_BALL_THRESH;
			}
			else
			{
				dpoint.x = state->ballPos.x - 2 * BOT_BALL_THRESH;
				dpoint.y = state->ballPos.y + 2 * BOT_BALL_THRESH;
			}

			//dodge(state, botID, Vec2D(state->ballPos.x, state->ballPos.y), PI / 2, true);
			//print("defend");
		}
		else if (state->ballPos.x < 0 && state->ballPos.x > state->homePos[botID].x /*&& state->ballPos.x - 3*COLLISION_DIST < state->homePos[botID].x*/) {
			//print("shoot");
			//GoToBall(botID, state, true);
			//GoToPoint(botID, state, dpoint, PI / 2, false, false);
			dodge(state, botID, Vec2D(OPP_GOAL_X, 0), 0, true);
			//save_goal(botID, state, Vector2D<float>(state->ballPos.x, state->ballPos.y));
			return;
		}
		if (state->pr_ballOurSide)
			print("%d", state->pr_ballOurSide);

		GoToPoint(botID, state, dpoint, PI / 2, true, false);
		if (isSpin)
		{
			save_goal(botID, state, Vector2D<float>(state->ballPos.x, state->ballPos.y));
		}

	}
}