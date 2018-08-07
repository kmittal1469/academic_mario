#pragma once

#include "loader.h"//used to load images and other files
#include "mapHandlingDetails.h"
loader load;
mapHandlingDetails mHandling;

class marioEvents
{
	public:
	void marioEvents::resetEverything()
	{
		checkPlayerX = playerX;
		checkPlayerY = playerY;
		time = 400;
		lifes = 3;
		score = 0;
		amIAlive = true;
	}
	//handles any timer actions
	void marioEvents::tickTock()
	{
		if(levelOver == 0)
		{
			if(dbTimer() - gameTimer > 1000)
			{
				gameTimer = dbTimer();
				if(time > 0) time--;
				else killMario();

				if(time == 200)
				{
					dbPlaySound(StimeWarning);
				}
			}
		}
	}

	void marioEvents::endLevel()
	{
		//if the final flag has been touched then stop the main theme
		if(levelOver != 0)
		{
			if(dbSoundPlaying(SmainTheme)) dbStopSound(SmainTheme);//stop main theme sound
		}
		if(levelOver == 1)
		{
			//wait until he touches the ground to start the new sound
			if(touchingGround)
			{
				levelOver = 2;
			} 
		}
		if(levelOver == 2)
		{
			//flag sound is over play level clear sound
			dbPlaySound(SlevelClear);
			levelOver = 3;
		}
		//touched ground walk towards the end of the level
		if(levelOver == 3)
		{
			walkingRight = true;
			playerX = playerX + speedx/2;
			EndGame = true;
			dbSetTextSize(30);
		}

		//TELLS the player the game is over
		if(EndGame)
		{
			dbText(screenCenterX/2, screenCenterY, "Game demo is over,\n Press any key to exit");
			if(dbScanCode() > 0)   
			{
				exit(0); // exit is used because dbEnd doesnt work most of the times
			}
		}
	}


	void marioEvents::coinPickedUp()
	{
		coins++; 
		dbPlaySound(ScoinPickup);
		score += 200;
		if(coins >= 100)
		{
			coins = 0;
			lifes ++;
			dbPlaySound(SnewLife);
		}
	}


	//used to activate specific animations
	void marioEvents::pickupItems(int arrX, int arrY, int typeOfCollision)
	{
		//pickup coin
		if(map[arrX][arrY] == C)
		{
			//turn the coin tile into an air tile
			map[arrX][arrY] = a; 	
			coinPickedUp();
		}
	   //pickup fire plant 
		else if(map[arrX][arrY] == f+11)
		{
			//turn the coin tile into an air tile
			if(currentMario == normalMario)currentMario = FireMario;
			score += 1000;
			// if mario is already on fire then inc their score by 1000
			dbPlaySound(SFlowerPickup);
			mHandling.startAnimation(score1000_1, IMAGE, arrX, arrY-1, 10, a , 80);

			//turn that box empty
			map[arrX][arrY] = a; 
		}

		//break brick
		else if(map[arrX][arrY] == b)
		{
			if(typeOfCollision == bottom)
			{
				//turn the brick into dust then nothing	
				dbPlaySound(Sbrick);
				mHandling.startAnimation(dust_1, IMAGE, arrX, arrY, 8, a, 80);
			}
		}
		//hit 1UP box turn it into a cube
		else if(map[arrX][arrY] == L)
		{
			if(typeOfCollision == bottom)
			{
				//turn the brick into dust then nothing	
				dbPlaySound(SFlowerAppear);//plays the flower found sound
				mHandling.startAnimation(_1up_1, IMAGE, arrX, arrY-1, 16, gM, 100 );
				//turn that box empty
				map[arrX][arrY] = e; 
			}
		}
		//hit empty block
		else if(map[arrX][arrY] == e || map[arrX][arrY] == k)
		{
			if(typeOfCollision == bottom)
			{
				dbPlaySound(Sbump);
			}
		}
		//bump question box Coin
		else if(map[arrX][arrY] == qC)
		{
			if(typeOfCollision == bottom)
			{
				mHandling.startAnimation(C, IMAGE, arrX, arrY-1, 6, a, 120);
				//turn the ? boxes into an empty block
				map[arrX][arrY] = e; 
				coinPickedUp();
			}
		}

		//bump question box fireflower
		else if(map[arrX][arrY] == qF)
		{
			if(typeOfCollision == bottom)
			{
				//turn the ? boxes into an empty block
				map[arrX][arrY] = e; 

				//turn the brick into dust then nothing	
				dbPlaySound(SFlowerAppear);//plays the flower found sound
				mHandling.startAnimation(f, IMAGE, arrX, arrY-1, 11, f+11, 100 );//small F means fire plant and 11 is the last animation of the flowers
				//turn that box empty
			} 
		}
		//touch death ground, kill mario
		else if(map[arrX][arrY] == d) 
		{	
			killMario();
		}
		//touch check point flag
		else if(map[arrX][arrY] == fB || map[arrX][arrY] == fT)
		{
			//if that checkpoint hasnt been reached then 
			//add it
			if(CheckPointReached == false)
			{
				CheckPointReached = true;
				checkPointX = mapX;
				checkPointY = mapY;
				checkPlayerX = playerX;
				checkPlayerY = playerY;

				//turn the coin tile into an air tile
				score += 500;
				dbPlaySound(ScheckPoint);

				//DISPLAY THE "Checkpoint text"
				mHandling.startAnimation(check_1, SPRITE, dbSpriteX(mario), dbSpriteY(mario)-100/*About a tile and a half*/, 8, a, 150);
			}
		}
		//Green mushroom +1 life
		else if(map[arrX][arrY] == gM)
		{
			map[arrX][arrY] = a;
			lifes ++;
			dbPlaySound(Spowerup);
			//show the "1 up" animation
			mHandling.startAnimation(_1upText_1, IMAGE, arrX, arrY-1, 6, a, 100 );
		}
	   //Touch end flag
		//Flag is divided into many tiles hence the check
		else if(map[arrX][arrY] == fl || map[arrX][arrY] == P1 ||
			map[arrX][arrY] == P2 || map[arrX][arrY] == P3 ||
			map[arrX][arrY] == P4 || map[arrX][arrY] == P5 ||
			map[arrX][arrY] == P5l || map[arrX][arrY] == P6)
		{
			
			//ending the game is made up of three stages 
			//stage 1
			// hit the flag play flag sound,
			if(levelOver == 0)
			{
				stopMovement = true;
				dbPlaySound(SendLevel);
				levelOver = 1;
			}

		}
	}


	//makes sure the right animations are shown when the player presses the key
	void marioEvents::playerAnimations()
	{ 
		//incase player forgets to add mario onto the designed level
		if(dbSpriteExist(mario))
		{
			if(marioSpawned) //only show all the animations if mario has spawned
			{
				if(amIAlive == true)
				{
					if(misc.noEssentialKeyBeingPressed() && dbTimer() - walkingTimer > 120 && jumping == false && falling == false) //if hes not pressing anything show him still
					{
						walkingTimer = dbTimer();
						if(currentMario == normalMario)
						{
							dbSprite( mario, playerX - mapX, playerY - mapY, mario );
						}
						else if (currentMario == FireMario)
						{
							dbSprite( mario, playerX - mapX, playerY - mapY, FireMarioStill );
						}
					}
					else if(jumping == true || falling == true)
					{
						if(currentMario == normalMario)
						{
							dbSprite( mario, playerX - mapX, playerY - mapY, marioJump );
						}
						else if (currentMario == FireMario)
						{
							dbSprite( mario, playerX - mapX, playerY - mapY, FireMarioJump );
						}
					}
					if(/*dbRightKey() && dbLeftKey()==0 ||*/ walkingRight == true)
					{
						if(dbSpriteMirrored(mario))
						{
							dbMirrorSprite(mario); //if mario is facing left then mirror him to the right
						}
						if(dbTimer() - walkingTimer > 100)
						{
							walkingTimer = dbTimer();
							if(currentMario == normalMario && jumping == false && falling == false)
							{
								//running animation
								if(dbSpriteImage(mario)==mario)
								{
									dbSprite( mario, playerX - mapX, playerY - mapY, marioWalk );
								}
								else
								{
									dbSprite( mario, playerX - mapX, playerY - mapY, mario );
								}
							}
							else if(currentMario == FireMario && jumping == false && falling == false)
							{
								//running animation
								if(dbSpriteImage(mario)==FireMarioStill)
								{
									dbSprite( mario, playerX - mapX, playerY - mapY, FireMarioWalk );
								}
								else
								{
									dbSprite( mario, playerX - mapX, playerY - mapY, FireMarioStill );
								}
							}
						}		
					}
					if(walkingLeft == true)
					{
						if(dbSpriteMirrored(mario)==0)
						{
							dbMirrorSprite(mario); //if mario is facing right then mirror him to the left
						}
						if(dbTimer() - walkingTimer > 100)
						{
							walkingTimer = dbTimer();
							if(currentMario == normalMario && jumping == false && falling == false)
							{
								//running animation
								if(dbSpriteImage(mario)==mario)
								{
									dbSprite( mario, playerX - mapX, playerY - mapY, marioWalk );
								}
								else
								{
									dbSprite( mario, playerX - mapX, playerY - mapY, mario );
								}
							}
							else if(currentMario == FireMario && jumping == false && falling == false)
							{
								//running animation
								if(dbSpriteImage(mario)==FireMarioStill)
								{
									dbSprite( mario, playerX - mapX, playerY - mapY, FireMarioWalk );
								}
								else
								{
									dbSprite( mario, playerX - mapX, playerY - mapY, FireMarioStill );
								}
							}
						}		
					}
				}
			}
		}
	}

	void marioEvents::createPlayer(int initial_X, int initial_Y)
	{
		playerX = initial_X;
		playerY = initial_Y;
		currentMario = normalMario; // start without any special stuff
		dbSprite(mario, playerX, playerY, mario);
		dbSetSprite(mario, 0, 1);
		dbSetSpritePriority(mario, 1);
	}


	void marioEvents::takeDamage()
	{
		if(currentMario == FireMario)
		{
			takingDamage = true;
			currentMario = normalMario;
			dbPlaySound(SPipeAndDamage);
		}
		//he has no powerup kill him
		else killMario();

	}


	void marioEvents::respawnMario()
	{

		misc.cleanupEnemies();
		load.loadCurrentLevel(level);
		currentMario = normalMario; // remove fire if he had it
		dying = false;
		amIAlive = true;
		damageFlashes = 0;
		playerX = checkPlayerX;
		playerY = checkPlayerY;
		mapX = checkPointX; 
		mapY = 0;// HAS TO BE DONE or map gets repositioned on the Y AXIS and screws all AI physics
		time = 400; //reset time

	}

	void marioEvents::handleDamage()
	{
		if(dying == false && amIAlive == true && takingDamage == true)
		{
			//show mario spinning when he dies
			if(dbTimer() - flashTimer > 40)
			{
				damageFlashes ++;
				flashTimer = dbTimer();
				if(deathFlash == 1)dbHideSprite(mario), deathFlash = 0;
				else dbShowSprite(mario), deathFlash = 1;
				if(damageFlashes == 25) // flash 20 fast times before returning mario to normal
				{
					damageFlashes = 0;
					takingDamage = false, dbShowSprite(mario);//turns mario invis for a few secs when taken damage
				}
			}
		}	
	}

	void marioEvents::handleDeath()
	{
		if(dying == true && amIAlive == false)
		{
			//show mario flashing when he dies
			if(dbTimer() - flashTimer > 40)
			{
				playerY = playerY - 3.0;
				damageFlashes ++;
				flashTimer = dbTimer();
				if(deathFlash == 1)dbHideSprite(mario), deathFlash = 0;
				else dbShowSprite(mario), deathFlash = 1;
				if(damageFlashes == 50)
				{
					//make sure mario is redisplayed after after doing the death flash
					dbShowSprite(mario);
					if(lifes > 0)
					{
						respawnMario();
					}
					//all his lifes have been used therefore call game over
					else
					{
						dying = false;
						EndGame = true;
					}
					
				}
			}
			dbSprite( mario, playerX - mapX, playerY - mapY, mario );
		}	
	}


	//used to get rid of mario on certain situations(time up, fall through hole)
	void marioEvents::killMario()
	{
		if(amIAlive == true && dying == false && takingDamage == false)
		{
			dying = true;
			lifes --;
			amIAlive = false;
			dbPlaySound(Sdeath);
			deathFlash = dbRnd(1);
			if(dbSoundPlaying(SmainTheme)) dbStopSound(SmainTheme);
		}
	}

};
