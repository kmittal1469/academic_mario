#pragma once
#include "misc.h"
#include "MarioEvents.h" //includes  a number of events such as death taking damage and so on
#include "Enemies.h"

Enemies enemy;

class mapHandling
{
public:

void mapHandling::playSounds()
{
	if(amIAlive)
	{
		//if checkpoint sound is on then reduce main song volume
		if(dbSoundPlaying(ScheckPoint))dbSetSoundVolume(SmainTheme, 80);
		else dbSetSoundVolume(SmainTheme, 100); 
		//make sure the music keeps repeating until the level is over
		if(dbSoundPlaying(SmainTheme)==0 && levelOver == 0)dbPlaySound(SmainTheme);
	}
}

void mapHandling::displayInformation()
{
	dbSetTextSize(30);
	//displays points
	char points[100];
	sprintf_s ( points, 200, "Score \n %d", score);
	dbText (50, 50, points);	

	//displays coins
	char coinNum[100];
	sprintf_s ( coinNum, 200, "Coins \n %d", coins);
	dbText (150, 50, coinNum);	

	//displays level number
	char levelbeingPlayed[100];
	sprintf_s ( levelbeingPlayed, 200, "Level \n %d", level);
	dbText (300, 50, levelbeingPlayed);	

	//displays lifes number
	char Lifes[100];
	sprintf_s ( Lifes, 200, "Lifes \n %d", lifes);
	dbText (400, 50, Lifes);

	//displays time 
	char timeLeft[100];
	sprintf_s ( timeLeft, 200, "Time \n %d", time);
	dbText (500, 50, timeLeft);	
}


//used to paste the tiles and handle any animations necessary
void mapHandling::pasteTiles(int x, int tilenumx,int y,int tilenumy, int tempx, int tempy)
{
	//question box
	if(map[x + tilenumx][y + tilenumy] == qC || map[x + tilenumx][y + tilenumy] == qF)
	{ 
		if(dbTimer() - questionBoxTimer > 75) //animation frames change every 75 ms
		{
			questionBoxTimer = dbTimer();
			qBoxAnim++;
			if(qBoxAnim == 26) qBoxAnim = 0;
		}
		dbPasteImage( q + qBoxAnim, ( x * tilesizex ) - tempx, ( y * tilesizey ) - tempy );
	}
	//coins
	else if(map[x + tilenumx][y + tilenumy] == C)
	{ 
		if(dbTimer() - coinTimer > 100) //animation frames change every 75 ms
		{
			coinTimer = dbTimer();
			coinAnim++;
			if(coinAnim == 6) coinAnim = 0;
		}
		dbPasteImage( map[x + tilenumx][y + tilenumy]+ coinAnim, ( x * tilesizex ) - tempx, ( y * tilesizey ) - tempy );
	}
	//Enemy piranha plant LEFT TILE
	else if(map[x + tilenumx][y + tilenumy] == EPl)
	{ 
		for(int i = 0; i < maxPiranhas; i ++)
		{ 
			//if it finds the exact reference then we paste the sprite and images in the right location
			if(piranhaPlants[i].ReferenceJ == x + tilenumx && piranhaPlants[i].ReferenceI == y + tilenumy)
			{
				if(dbSpriteVisible(piranhaPlants[i].id)==0)
				{
					dbShowSprite(piranhaPlants[i].id);
				}
				dbPasteImage( map[x + tilenumx][y + tilenumy] + piranhaPlants[i+1].plantAnim, ( x * tilesizex ) - tempx, ( y * tilesizey ) - tempy );
				dbSprite(piranhaPlants[i].id, ( x * tilesizex ) - tempx, ( y * tilesizey ) - tempy, map[x + tilenumx][y + tilenumy] + piranhaPlants[i+1].plantAnim);
				//dbSprite is only used so plants positions can be checked and stop the plant at certain 
				//situations, e.g. when mario is 2 close to them, because GDK doesnt have dbImageX, to check where images are positioned
				break; //leave the loop as soon as its found the matching reference
			}
		}
	}
	//Enemy piranha plant Right TILE (handles all timing and animations)
	else if(map[x + tilenumx][y + tilenumy] == EPr)
	{ 
		for(int i = 0; i < maxPiranhas; i ++)
		{
			//if it finds the exact reference then we paste the sprite and images in the right location
			if(piranhaPlants[i].ReferenceJ == x + tilenumx && piranhaPlants[i].ReferenceI == y + tilenumy)
			{
				if(dbSpriteVisible(piranhaPlants[i].id)==0)
				{
					dbShowSprite(piranhaPlants[i].id);
				}
				if(dbTimer() - piranhaPlants[i].plantTimer > 100 && dbTimer() - piranhaPlants[i].plantLoopTimer > 1400) //animation frames change every 100 ms
				{
					piranhaPlants[i].plantTimer = dbTimer();
					//check if player is very close to RIGHT plant, if so then keep it down once it finishes anim
					if(piranhaPlants[i].tooClose == true && piranhaPlants[i].plantAnim == 0)
					{
						piranhaPlants[i].plantLoopTimer = dbTimer();
						//if mario is too close to the plant then stop it from rising again until hes at a specific distance
					}
					//check if player is very close to left plant, if so then keep it down once it finishes anim
					else if(piranhaPlants[i-1].tooClose == true && piranhaPlants[i].plantAnim == 0)
					{
						piranhaPlants[i].plantLoopTimer = dbTimer();
						//if mario is too close to the plant then stop it from rising again until hes at a specific distance
					}
					else 
					{
						piranhaPlants[i].plantAnim++;
						//plays the crunching sound of the piranha om noming if its closing its jaws
						if(piranhaPlants[i].plantAnim == 5 || piranhaPlants[i].plantAnim == 10 || piranhaPlants[i].plantAnim == 15 || piranhaPlants[i].plantAnim == 25 )
						{
							//only play the sound if mario is fairly close to the plant, to avoid spam on the sounds
							if(piranhaPlants[i].distance < 500)
							{
								dbPlaySound(SplantCrunch);
							}
						}
					}
					if(piranhaPlants[i].plantAnim == 30)
					{
						piranhaPlants[i].plantAnim = 0;
						piranhaPlants[i].plantLoopTimer = dbTimer();
					}
				}
				dbPasteImage( map[x + tilenumx][y + tilenumy] + piranhaPlants[i].plantAnim, ( x * tilesizex ) - tempx, ( y * tilesizey ) - tempy );
				dbSprite(piranhaPlants[i].id, ( x * tilesizex ) - tempx, ( y * tilesizey ) - tempy, map[x + tilenumx][y + tilenumy] + piranhaPlants[i].plantAnim);
				//dbSprite is only used so plants positions can be checked and stop the plant at certain 
				//situations, e.g. when mario is 2 close to them, because GDK doesnt have dbImageX, to check where images are positioned
				break; //leave the loop as soon as its found the matching reference
			}

		}
	}
	//fire flower
	else if(map[x + tilenumx][y + tilenumy] == f)
	{ 
		dbPasteImage( map[x + tilenumx][y + tilenumy], ( x * tilesizex ) - tempx, ( y * tilesizey ) - tempy );
	}
	//Displays all kinds of tile based animations
	else if(map[x + tilenumx][y + tilenumy] == SA)
	{
		bool foundRightElement = false; // jumps off the array as soon as its found the right id element
		// check which element is in anim mode
		for(int i = 0; i < maxAnimations && foundRightElement == false; i++)
		{
			if(anims[i].busy == true)
			{
				if(anims[i].typeOf == IMAGE)
				{
					//if id matches the element within the 2d array
					if(anims[i].id == map[x + tilenumx][y + tilenumy]/*Makes sure that tiles arent overwritten when there are multiple anims*/ && anims[i].x == x + tilenumx && anims[i].y == y + tilenumy)
					{
						foundRightElement = true;
						//1000 score animation
						if(dbTimer() - anims[i].timer > 80) //animation frames change every 75 ms
						{
							anims[i].timer = dbTimer();
							anims[i].frames++;
										
							if(anims[i].frames == anims[i].HighestFrame)
							{
								anims[i].busy = false;
								//turn that into an air tile or an object such as 1up mushroom
								map[x + tilenumx][y + tilenumy] = anims[i].FinalFrame;
							}  
						}
						dbPasteImage( anims[i].SetImage + anims[i].frames, ( x * tilesizex ) - tempx,  ( y * tilesizey ) - tempy );
					}
				}
			}
		}

	}
	//GOOMBAS before first spawn
	else if(map[x + tilenumx][y + tilenumy] == G)
	{ 
		map[x + tilenumx][y + tilenumy] = a;
		//if user is trying to spawn more than one mario then create an air tile instead
		enemy.createEnemy((( x * tilesizex ) - tempx),  (y * tilesizey ) - tempy);
	}
	//mario spawn spot, if any more than 1 are found they are converted into air tiles
	else if(map[x + tilenumx][y + tilenumy] == M)
	{ 
		map[x + tilenumx][y + tilenumy] = a;
		//if user is trying to spawn more than one mario then create an air tile instead
		if(marioSpawned == false)
		{
			marioSpawned = true;
			myEvents.createPlayer((( x * tilesizex ) - tempx),  (y * tilesizey ) - tempy);
		}
	}
	//1up box before being seen
	else if(map[x + tilenumx][y + tilenumy] == L)
	{ 
	   dbPasteImage( map[x + tilenumx][y + tilenumy], ( x * tilesizex ) - tempx, ( y * tilesizey ) - tempy );
	}
	//Green mushroom +1 life
	else if(map[x + tilenumx][y + tilenumy] == gM)
	{ 
	   dbPasteImage( _1up_1+16, ( x * tilesizex ) - tempx, ( y * tilesizey ) - tempy );
	}
	else// displays a normal tile(without any animations)
    {
	   dbPasteImage( map[x + tilenumx][y + tilenumy], ( x * tilesizex ) - tempx, ( y * tilesizey ) - tempy );
	}
}

void mapHandling::displayLevel()
{
    //works out the tile number within array to start displaying tiles at
   int tilenumx = mapX / numoftilesx;
   int tilenumy = mapY / numoftilesy;
   
   //cache calculation to tempX and TempY variables for a minor speed increase
   //this calculation works out how many pixels to offset the position where the tile
   //images should be plaaced.
   int tempx = mapX - ( tilenumx * tilesizex );
   int tempy = mapY - ( tilenumy * tilesizey );
   
   //this pastes the images to screen in the correct order by working out where to start
   //pasting the images from in the array, then displaying the images at the correct
   //screen coordinates
   for (int y = 0; y <= 12; y++ ) //because we have 12 rows and 15 because we display 15 columns each time
   {
      for (int x = 0; x <= 15; x++ ) 
	  {     
		  pasteTiles(x, tilenumx, y, tilenumy, tempx, tempy);
      }
   }
}










};