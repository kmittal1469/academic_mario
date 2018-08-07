#pragma once

class miscelaneous
{
	public:

	int miscelaneous::findFreeSprite()
	{
		//start from 10 to make sure no sprite is overwritten
		int i = 10;
		while(dbSpriteExist(i))
		{
			i++;
		}
		return i;
	}

	bool miscelaneous::noEssentialKeyBeingPressed()
	{
		if(!dbUpKey() && !dbLeftKey() && !dbRightKey() && !dbSpaceKey())
		{
			return true;
		}
		return false;
	}

	//used to find a free anim, for coin, score animation ...
	int miscelaneous::findFreeAnimation()
	{
		for(int i = 0; i < maxAnimations; i ++)
		{
			if(anims[i].busy == false)
			{
				return i;
			}
		}
		return 0;
	}

	//hides all enemies so they dont overwrite other tiles 
	//when mario is respawned
	//------------RESETS EVERYTHING REQUIRED FOR when a life is lost and a restart is required------------------
	void miscelaneous::cleanupEnemies()
	{
		for(int i = 0; i < maxPiranhas; i ++)
		{
			if(dbSpriteExist(piranhaPlants[i].id))
			{
				dbDeleteSprite(piranhaPlants[i].id);
				piranhaPlants[i].isAlive = false;
				piranhaPlants[i].tooClose = false;
				piranhaPlants[i].ReferenceI = 0;
				piranhaPlants[i].ReferenceJ = 0;
				piranhaPlants[i].plantAnim = 0;
				piranhaPlants[i].id = 0;
			}
		}
		//get rid of any walkers and turtles about 
		for(int i = 0; i < maxWalkers; i++)
		{
			if(dbSpriteExist(walkers[i].id))
			{
				dbDeleteSprite(walkers[i].id);
				//turn that box into an air tile and spawn the goomba here
				walkers[i].isAlive = false;
				walkers[i].walking = false;
				walkers[i].touchingGround = false;
				walkers[i].x = 0; //used to fix where the enemies were spawning
				walkers[i].y = 0;
				walkers[i].typeOf = 0;
				//reset any deaths
				walkers[i].isDying = false;
				walkers[i].id = 0;
			}
		}
		currentWalker = 1; //sets the goomba counter to 0
	}

	//finds the distance between two images, usually two sprites
	float miscelaneous::get2dDistance(int x1, int y1, int x2, int y2)
	{
		return dbSqrt(((x2-x1)*(x2-x1)) + ((y2-y1)*(y2-y1)));
	}


};