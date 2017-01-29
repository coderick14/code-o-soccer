// For adding header files define your includes here and add the headers in Game folder.
// For example, You may see these files - Attacker.hpp,Defender.hpp and Goalkeeper.hpp
// For checking out the skills you may see skills.h placed in Skills folder.
#pragma once
#include "skills.h"
#include "Attacker.hpp"
#include "Striker.hpp"
#include "Defender.hpp"
#include "GoalKeeper.hpp"
#include "CentreBack.hpp"
#include "StrikeSupporter.hpp"

// Change your team color here (BLUE_TEAM/YELLOW_TEAM)face

Simulator::TeamColor teamColor = Simulator::BLUE_TEAM;

// Make usingDebugger is false when playing against an opponent
bool usingDebugger = true;

namespace MyStrategy
{
	extern int defend_bot = 1;
	extern int attack_bot = 2;

	// Write your strategy here in game function.
	// You can also make new functions and call them from game function.
	void game(BeliefState *state)
	{
		/* Attacker states*/
		if (state->ballPos.x < -HALF_FIELD_MAXX + 2.5 * DBOX_WIDTH) // Ball on our side Dont do some shit
		{
			// just go to opposite corner
			int x = -4000, y = 3000;
			if (state->ballPos.y < 0) 
			{
				GoToPoint(2, state, Vec2D(x, y), PI / 2, true, true);
			}
			else
			{
				GoToPoint(2, state, Vec2D(x, -y), PI / 2, true, true);
			}
		}
		else // Normal Attacker
		{
			attacker(state, 2);
		}
		//attacker(state, 4);
		

		///*Defender modes*/
		if (state->ballPos.x > 0) {
			strips currStrip = whichStrip(state->ballPos.x, state->ballPos.y);
			//Go into oooohh mode only in middle strip. Else become attacker.
			if (currStrip == MIDDLE_STRIP) {
				// Shoot mode
					if (abs(state->ballPos.y) < OUR_GOAL_MAXY) {
						striker(state, 1, MIDDLE_STRIP, true);
					}
				// Wait mode
					else
					{
						striker(state, 1, currStrip);
					}
			}
			else {
				attacker(state, 1);
			}
			
		}
		else {
			defender(state, 1);
		}

		/*Defender modes*/
		if (state->ballPos.x < -HALF_FIELD_MAXX + 2.5 * DBOX_WIDTH)
		{
			centreBack(state, 3);
		}
		else if (state->ballPos.x > 1000) {
			strips currStrip = whichStrip(state->ballPos.x, state->ballPos.y);
			// Shoot mode
			if (currStrip == MIDDLE_STRIP /*abs(state->ballPos.y) < OUR_GOAL_MAXY*/) {
				attacker(state, 3);
			}
			// Wait mode
			else
			{
				strike_supporter(state, 3);
			}
		}
		else
		{
			defender(state, 3);
		}

		goalkeeper(state, 0);
		centreBack(state, 4);
		//defender(state, 3);
		//print("%d %d", state->ballPos.x, state->ballPos.y);
	}
}