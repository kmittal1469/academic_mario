#pragma once

marioEvents myEvents; // general mario events death, taking damage etc


//Handles loading of all images and files
class Enemies
{
	public:
	void Enemies::createEnemy(int initial_X, int initial_Y)
	{

		walkers[currentWalker].id = misc.findFreeSprite();
		dbSprite( walkers[currentWalker].id, initial_X, initial_Y, G );
		// initial_X PLUS mapX IS VERY IMPORTANT because of the way we display the map
		//if were half way through the map and we want to spawn an enemy 
		//this will make sure the enemy is spawned exactly where we told him to !!
	    walkers[currentWalker].x = initial_X+mapX; //used to fix where the enemies were spawning
	    walkers[currentWalker].y = initial_Y;
		walkers[currentWalker].ASleep = true;
		currentWalker++; 

		
	}

	//spawns enemies if mario is closed to them
	// this is used so enemies at the end of the map dont get spawned early and
	//start walking towards a cliff for example
	void Enemies::AwakeEnemies()
	{
		int distance; 
		for(int i = 0; i < maxWalkers; i ++)
		{
			if(dbSpriteExist(walkers[i].id))
			{
				//check if mario is close enough to a sleeping walker and if so we drop the walker and enable them e.g. allow them walk and interact
				if(walkers[i].ASleep)
				{
					//get the distance between mario and the enemy, if the enemy is fairly close
					//then we spawn them
				   distance = misc.get2dDistance(dbSpriteX(mario), 
								dbSpriteY(mario), dbSpriteX(walkers[i].id), 
									dbSpriteY(walkers[i].id));

				  //mario is close enough now allow the enemy to be spawned
				   //keeps the enemies spawning along with mario
				   if(distance < 1500)
				   {
					   walkers[i].ASleep = false;
					   walkers[i].isAlive = true;
					   walkers[i].walking = true;
					   walkers[i].touchingGround = false;
					   walkers[i].isDying = false;
					   walkers[i].typeOf = GOOMBA;
					   walkers[i].walkingDirection = LEFT;
					   //by default always send the goombas to the left
					   //change direction on collision
			
				   }
				   
				}
			}
		}		
	}

	void Enemies::piranhaCollision(int arrX, int arrY, int typeOfCollision)
	{
		//touch plant piranha
		//if mario collides with either left side or right side of the plant whislt the plant is out
		//do some damage
		if(map[arrX][arrY] == EPl || map[arrX][arrY] == EPr)
		{
			for(int i = 0; i < maxPiranhas; i++)
			{
				//if it finds the exact reference then we paste the sprite and images in the right location
				if(piranhaPlants[i].ReferenceJ == arrX && piranhaPlants[i].ReferenceI == arrY)
				{
					//only do damage if the plant is out of the pipe
					//not the best collision method but it works
					//another way of getting this perfect would be to use
					//pixel perfect collision but that is demanding as hell
					if(piranhaPlants[i].plantAnim > 0 && piranhaPlants[i].plantAnim < 28)
					{
						myEvents.takeDamage();
					}
					break; //leave the loop as soon as its found the matching reference
				}
			}
		}
	}

	//handles if mario is too close to the plant then keeps the plant down
	void Enemies::piranhaAI()
	{
		for(int i = 0; i < maxPiranhas; i++)
		{
			if(piranhaPlants[i].isAlive)
			{
				if(piranhaPlants[i].typeOf == EPl)
				{
					piranhaPlants[i].distance = misc.get2dDistance(dbSpriteX(mario), 
							dbSpriteY(mario), dbSpriteX(piranhaPlants[i].id), 
								dbSpriteY(piranhaPlants[i].id));
					if(piranhaPlants[i].distance < 225)
					{
						piranhaPlants[i].tooClose = true;
					}
					else piranhaPlants[i].tooClose = false;
				}
				else if(piranhaPlants[i].typeOf == EPr)
				{
					piranhaPlants[i].distance = misc.get2dDistance(dbSpriteX(mario), 
							dbSpriteY(mario), dbSpriteX(piranhaPlants[i].id), 
								dbSpriteY(piranhaPlants[i].id));
					if(piranhaPlants[i].distance < 225)
					{
						piranhaPlants[i].tooClose = true;
					}
					else piranhaPlants[i].tooClose = false;
				}
			}
		}
	}
};