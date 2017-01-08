#pragma once
#include "skills.h"
#include "Attacker.hpp"

namespace MyStrategy
{
	Vec2D awayGoal(4200, 0);

	void striker(BeliefState *state, int botID, strips strip, bool isShoot = false)
	{
		Vec2D dpoint;
		dpoint.x = HALF_FIELD_MAXX - 2 * DBOX_WIDTH;
		if (isShoot)
		{
			//GoToPoint(botID, state, state->ballPos, PI, true, true);
			//shootForGoal(state, botID);
			Vec2D pos = predictBallPos(state, botID);
			shoot(botID, state, Vector2D<float>(pos.x, pos.y));
			return;
		}
		if (strip == TOP_STRIP)
		{
			//print("In top strip");
			dpoint.y = DBOX_HEIGHT;	
			GoToPoint(botID, state, dpoint, /*Vec2D::angle(dpoint, awayGoal)*/ -PI / 4, true, true);

		}
		else
		{
			//print("In bottom strip");
			dpoint.y = -DBOX_HEIGHT;
			GoToPoint(botID, state, dpoint, /*Vec2D::angle(dpoint, awayGoal)*/ PI / 4, true, true);

		}
	}
}
