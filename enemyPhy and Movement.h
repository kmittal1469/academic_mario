//Handles physics movement and certain events functions
#pragma once

class EnemyPhyAndMovement
{
	public:
	void EnemyPhyAndMovement::changeDirection(int element)
	{
		if(walkers[element].walkingDirection == LEFT)
		{
			walkers[element].walkingDirection = RIGHT;
		}
		else
		{
			walkers[element].walkingDirection = LEFT;
		}
	}

	int EnemyPhyAndMovement::collidingWithWalker(int element)
	{	
		//check if a 'walker' has collided with another
		//if so change both of their directions :)
		for(int i = 0; i < maxWalkers; i ++)
		{
			//make sure we dont check collision between 
			//the same sprite otherwise it always returns true
			//freezing it
			if(dbSpriteExist(walkers[i].id) && walkers[i].id != walkers[element].id)
			{
				if(walkers[i].isAlive)
				{
					if(dbSpriteCollision(walkers[element].id, walkers[i].id))
					{
						return i; //return the walker he collided against
					}
				}
			}
		}
		//array can never be negative
		return -1;
	}

	void EnemyPhyAndMovement::FlashMe(int TimeToFlash, int CharacterToFlash)
	{
		if(TimeToFlash > 200 && TimeToFlash < 300)
		{
			dbHideSprite(CharacterToFlash); // fully hide them
		}
		else if(TimeToFlash > 300 && TimeToFlash < 400)
		{
			dbShowSprite(CharacterToFlash); // fully hide them
		}
		else if(TimeToFlash > 400 && TimeToFlash < 500)
		{
			dbHideSprite(CharacterToFlash); // fully hide them
		}
		else if(TimeToFlash > 500 && TimeToFlash < 600)
		{
			dbShowSprite(CharacterToFlash); // fully hide them
		}
		else if(TimeToFlash > 600 && TimeToFlash < 700)
		{
			dbHideSprite(CharacterToFlash); // fully hide them
		}
		else if(TimeToFlash > 700 && TimeToFlash < 800)
		{
			dbShowSprite(CharacterToFlash); // fully hide them
		}
		else if(TimeToFlash > 800 && TimeToFlash < 900)
		{
			dbHideSprite(CharacterToFlash); // fully hide them
		}
		else if(TimeToFlash > 900 && TimeToFlash < 1000)
		{
			dbShowSprite(CharacterToFlash); // fully hide them
		}
	}

	//makes sure the right animations are shown when the player presses the key
	void EnemyPhyAndMovement::goombaAnim()
	{
		for(int i = 0; i < maxWalkers; i ++)
		{
			if(dbSpriteExist(walkers[i].id))
			{
				if(walkers[i].isAlive)
				{
					dbSprite(walkers[i].id, walkers[i].x - mapX, walkers[i].y, G + walkers[i].currentFrame);
					if(walkers[i].walking)
					{
						if(dbTimer() - walkers[i].walkingTimer > 90 )
						{
							walkers[i].walkingTimer = dbTimer();
							//only show him walking if the goomba is touching the ground
							//makes sure it plays the walking animation between two diff images
							
							//once it reaches the last animation then reset it
							if(walkers[i].currentFrame > 5)
							{
								walkers[i].currentFrame = 0;
							}
							walkers[i].currentFrame++;
						}
					}
				}
				//if enemy is dying we display a death animation
				else if(walkers[i].isDying)
				{
					dbSprite(walkers[i].id, walkers[i].x - mapX, walkers[i].y - mapY, G + 7);
					//wait until the enemy is shown dead for x milliseconds then remove them
					int TimeToFlash = dbTimer() - walkers[i].walkingTimer;

					//used to flash the enemy during death
					FlashMe(TimeToFlash, walkers[i].id);
					
					if(TimeToFlash > 1150 )
					{
						walkers[i].isDying = false;
						dbHideSprite(walkers[i].id); // fully hide them
					}

				}
			}
		}
	}




	void EnemyPhyAndMovement::gravity()
	{
	  // char collidedWith[100];
	 //  sprintf_s ( collidedWith, 200, "Touchin ground", lovemakingCounter);			
	 //  dbText(100, i*80 , collidedWith);

		for(int i = 0; i < maxWalkers; i ++)
		{
			if(walkers[i].isAlive)
			{
				if(!walkers[i].touchingGround) 
				{
					walkers[i].oldy = walkers[i].y; 
					//store speed incase EN collides against something on his way down
 					walkers[i].y = walkers[i].y + speedy;
					wasThereAnEnCollision(i); //return him into place if a collision was found
				}
			}
		}
	}

	bool EnemyPhyAndMovement::wasThereAnEnCollision(int element)
	{
	   int collidedWithX = 0; //used to find out what mario collided with map[] 
	   int collidedWithY = 0; //used to find out what mario collided with map[][]

	   //the following 8 lines of code stores the old and new left,right,top,bottom edges of
	   //the sprite in the respective variables
	   
	   //gets which tiles the current left and right co-ordinates of the player are on
	   int lefttilenum = int( walkers[element].x / tilesizex );
	   int righttilenum = int( ( walkers[element].x + ( tilesizex - 1 ) ) / tilesizex );
	   //gets which tiles the current top and bottom co-ordinates of the player are on
	   int toptilenum = int( walkers[element].y / tilesizey );
	   int bottomtilenum = int( ( walkers[element].y + ( tilesizey - 1 ) ) / (tilesizey) );
	   
	   //gets which tiles the old left and right co-ordinates of the player are on
	   int oldlefttilenum = int( walkers[element].oldx / tilesizex );
	   int oldrighttilenum = int( ( walkers[element].oldx + ( tilesizex - 1 ) ) / tilesizex );
	   //gets which tiles the old top and bottom co-ordinates of the player are on
	   int oldtoptilenum = int( walkers[element].oldy / tilesizey );
	   int oldbottomtilenum = int( ( walkers[element].oldy + ( tilesizey - 1 ) ) / (tilesizey) );
	   
	   //this is where we check for those 4 collision points; if the collision point is on a
	   //tile you are not able to pass through (in our case a tile that has an image number
	   //of 10 or greater), then the old coordinates of the sprite are restored.
	   //Note: to have sliding collision we must check the the current x tile against the
	   //old y tile and vice versa.
	   bool wasThereACollision = false;

	   //checks for top-left collision point
	   if ( map[lefttilenum][oldtoptilenum] >= 10) 
	   {
		  if(map[lefttilenum][oldtoptilenum] < 100)
		  {
			  walkers[element].x = walkers[element].oldx;
			  wasThereACollision = true;
		  }
		  collidedWithX = lefttilenum;
		  collidedWithY = oldtoptilenum;
	   }
	   
	   if ( map[oldlefttilenum][toptilenum] >= 10)
	   {
		  if(map[oldlefttilenum][toptilenum] < 100)
		  {
			  walkers[element].y = walkers[element].oldy;
			  wasThereACollision = true;
			  //colliding below something 1/2
		  }
		  collidedWithX = oldlefttilenum;
		  collidedWithY = toptilenum;
	   }
	   //checks for top-right collision point
	   if ( map[righttilenum][oldtoptilenum] >= 10) 
	   {
		  if(map[righttilenum][oldtoptilenum] < 100)
		  {
			  walkers[element].x = walkers[element].oldx;
			  wasThereACollision = true;
		  }
		  collidedWithX = righttilenum;
		  collidedWithY = oldtoptilenum;
	   }
	   
	   if ( map[oldrighttilenum][toptilenum] >= 10) 
	   {
		  if(map[oldrighttilenum][toptilenum] < 100)
		  {
			  walkers[element].y = walkers[element].oldy;
			  wasThereACollision = true;
		  }
		  collidedWithX = oldrighttilenum;
		  collidedWithY = toptilenum;
		  //colliding below something 2/2
	   }
	   
	   //checks for bottom-left collision point
	   if ( map[lefttilenum][oldbottomtilenum] >= 10) 
	   {
		  if(map[lefttilenum][oldbottomtilenum] < 100)
		  {
			  walkers[element].x = walkers[element].oldx;
			  wasThereACollision = true;
		  }
		  collidedWithX = lefttilenum;
		  collidedWithY = oldbottomtilenum;
	   }
	   
	   if ( map[oldlefttilenum][bottomtilenum] >= 10) 
	   {
		  if(map[oldlefttilenum][bottomtilenum] < 100)
		  {
			   //STANDING ABOVE TILE 1/2
			  walkers[element].touchingGround = true;
			  walkers[element].y = walkers[element].oldy;
			  wasThereACollision = true; 
		  }
		  collidedWithX = oldlefttilenum;
		  collidedWithY = bottomtilenum;
	   }
	   
	   //checks for bottom-right collision point
	   if ( map[righttilenum][oldbottomtilenum] >= 10)
	   {
		  if(map[righttilenum][oldbottomtilenum] < 100)
		  {
			  walkers[element].x = walkers[element].oldx;
			  wasThereACollision = true;
		  }
		  collidedWithX = righttilenum;
		  collidedWithY = oldbottomtilenum;
	   }
	   
	   if ( map[oldrighttilenum][bottomtilenum] >= 10) 
	   {
		  if(map[oldrighttilenum][bottomtilenum] < 100)
		  {
			  //STANDING ABOVE TILE 2/2
			  walkers[element].touchingGround = true;
			  walkers[element].y = walkers[element].oldy;
			  wasThereACollision = true;
		  }
		  collidedWithX = oldrighttilenum;
		  collidedWithY = bottomtilenum;
	   }

	   //check if player is touching the ground or NOT, if hes colliding with an air tile then hes not touching the ground
	   if ( map[oldrighttilenum][bottomtilenum] < 10 && map[oldlefttilenum][bottomtilenum] < 10) 
	   {
		  walkers[element].touchingGround = false;
	   }
		
		if(wasThereACollision)
		{
			collisionEvents(collidedWithX, collidedWithY, element);
			return true;
		}
		//no collision found meaning we return false
		return false;
	}


	void EnemyPhyAndMovement::controlAI()
	{
		//declared here to avoid declaration on loop
		bool thereWasACollision = false;// used to apply changes if a collision happened between enemies
		for(int i = 0; i < maxWalkers; i++)
		{
			if(dbSpriteExist(walkers[i].id))
			{
				if(walkers[i].isAlive)
				{
					//only move him if hes touching the ground
					if(walkers[i].touchingGround)
					{
						//store the x and y coordinates of the 
						//player into the variables walkers[i].oldx
						//and walkers[i].oldy incase he collides then we bring him back
						//so they dont go through it
						
						walkers[i].oldx = walkers[i].x;

						if(walkers[i].walkingDirection == LEFT)
						{
							//makes sure he is facing the right way
							if(dbSpriteMirrored(walkers[i].id)==0) dbMirrorSprite(walkers[i].id);
							walkers[i].x -= speedxEN;
						}
						else if(walkers[i].walkingDirection == RIGHT)
						{
							//makes sure he is facing the right way
							if(dbSpriteMirrored(walkers[i].id)==1) dbMirrorSprite(walkers[i].id);
							walkers[i].x += speedxEN;
						}

						//check for any collisions
						//and move them back if so
						if(wasThereAnEnCollision(i))
						{
							walkers[i].x = walkers[i].oldx;
							changeDirection(i);
						}
						
						int collidedAgainstSomeone = collidingWithWalker(i);
						if(collidedAgainstSomeone != -1)
						{
							//20 milliseconds because it is just enough time for the two Walkers to stop colliding against each other
							if(dbTimer() - walkers[i].CollisionTimer < 20)
							{
								if(walkers[collidedAgainstSomeone].id == walkers[i].LastEnemyCollided)
								{
									//its bumping against its last collision therefore 
									//ignore that and let them move apart before allowing them to collide again
									thereWasACollision = false;
								}
							}
							else
							{
								thereWasACollision = true;
							}
							
							if(thereWasACollision)
							{
								//two walker sprites bumped against each other therefore
								//we position them in their old spot
								//and change their directions
								//we reset their collision timer and we tell them program 
								//to stop any collision between for the next x milliseconds
								//mainly because sprite collision isnt great on dark gdk

								walkers[i].x = walkers[i].oldx;
								changeDirection(i);	
								changeDirection(collidedAgainstSomeone);
								//store the last collision and give them time to move apart
								walkers[i].LastEnemyCollided = walkers[collidedAgainstSomeone].id;
								walkers[i].CollisionTimer = dbTimer(); //reset the timer
								walkers[collidedAgainstSomeone].LastEnemyCollided = walkers[i].id;
								walkers[collidedAgainstSomeone].CollisionTimer = dbTimer(); //reset the timer
							}
						}
					}
			   }
			}
		}
	}


	//used to activate specific animations and events
	void EnemyPhyAndMovement::collisionEvents(int arrX, int arrY, int id)
	{
		//id within the type of enemy array
		//type OfEnemy = 0 means Goomba
		//		   	     1 means turtle
		//enemy touches death ground
		if(map[arrX][arrY] == d)
		{
			//kill the enemies
			//GOOMBA
			if(walkers[id].typeOf == GOOMBA)
			{
				walkers[id].isAlive = false;
				walkers[id].walking = false;
				dbHideSprite(walkers[id].id);
			}
			else if(walkers[id].typeOf == TURTLE)
			{


			}
		}
	}



	//used to kill the designated enemy
	void EnemyPhyAndMovement::KillMe(int ElementToKill)
	{
		walkers[ElementToKill].isAlive = false;
		walkers[ElementToKill].walking = false;
		walkers[ElementToKill].isDying = true;
		walkers[ElementToKill].walkingTimer = dbTimer(); // reset the timer so dying animations show at the right time
		
	}

};
