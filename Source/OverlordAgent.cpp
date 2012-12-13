#include "OverlordAgent.h"
#include "PFManager.h"
#include "Commander.h"
#include "AgentManager.h"
//Added by Bulten
#include <stdlib.h>
#include <time.h>


OverlordAgent::OverlordAgent(Unit* mUnit)
{
	unit = mUnit;
	type = unit->getType();
	unitID = unit->getID();
	agentType = "OverlordAgent";
	Broodwar->printf("OverlordAgent created (%s)", unit->getType().getName().c_str());
	
	lastUpdateFrame = Broodwar->getFrameCount();
	
	srand(time(NULL));
	goal = TilePosition(rand(), rand());
	//goal = 
	updateGoal();
}

void OverlordAgent::updateGoal()
{
	BaseAgent* agent = AgentManager::getInstance()->getClosestBase(unit->getTilePosition());
	if (agent != NULL)
	{
		goal = agent->getUnit()->getTilePosition();
		lastUpdateFrame = Broodwar->getFrameCount();
	}
}

void OverlordAgent::computeActions()
{
	if (squadID == -1)
	{
		if (Broodwar->getFrameCount() - lastUpdateFrame > 100)
		{
			updateGoal();
		}
	}
	if(unit->isUnderAttack())
	{
		goal = TilePosition(-1, -1);
	}

	PFManager::getInstance()->computeAttackingUnitActions(this, goal, true);
}