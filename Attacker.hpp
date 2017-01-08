#pragma once
#include "skills.h"

namespace MyStrategy
{

	
	// Naive example for attacker
	void attacker(BeliefState *state, int botID)
	{

		Vec2D awayGoal(HALF_FIELD_MAXX, 0);
		Vec2D ballPoint(state->ballPos.x, state->ballPos.y);
		//Go to ball if ball is far
	   //Take ball to the goal
		strips currStrip = whichStrip(state->ballPos.x, state->ballPos.y);

		//Try crossing to striker if ball in corner
		if (state->ballPos.x > 4200 - 4 * BOT_RADIUS) {
			if (currStrip == TOP_STRIP && state->homePos[botID].y < state->ballPos.y) {
				shootForAssist(state, botID);
				//Spin(botID, -MAX_BOT_OMEGA / 5);
				return;
			}
			else if (currStrip == BOTTOM_STRIP && state->homePos[botID].y > state->ballPos.y) {
				shootForAssist(state, botID);
				//Spin(botID, MAX_BOT_OMEGA / 5);
				return;
			}
		}
/*
		float botAngle = state->homeAngle[botID];
		Vec2D displacement = state->ballPos - state->homePos[botID];
		float ballAngle = atan2( displacement.y , displacement.x );*/
	
		
		/*******************************************pretty unpredictable code**************************************************/

		/*if (Vec2D::distSq(state->homePos[botID], state->ballPos) < 4 * BOT_BALL_THRESH * BOT_BALL_THRESH ) {
			if (Vec2D::distSq(state->homePos[botID], awayGoal) > 4 * DBOX_WIDTH * DBOX_WIDTH)
			{
				print("Move Towards goal");
				ballPoint = predictBallPos(state, botID);
				GoToPoint(botID, state, ballPoint, PI / 2, true, false);
			}
			else
			{
				print("Spin for goal");
				shootForGoal(state, botID);
			}
		}
		else
			GoToPoint(botID, state, ballPoint, 0, true, true);*/
		if (Vec2D::distSq(state->homePos[botID], state->ballPos) < 4 * BOT_BALL_THRESH * BOT_BALL_THRESH) {
			if (Vec2D::distSq(state->homePos[botID], awayGoal) > 8 * DBOX_WIDTH * DBOX_WIDTH)
				GoToPoint(botID, state, awayGoal, PI / 2, true, false);
			else
				shootForGoal(state, botID);
		}
		else
			GoToPoint(botID, state, ballPoint, 0, true, true);

		//shoot(botID, state, Vector2D<float>(awayGoal.x, awayGoal.y));
	}

}