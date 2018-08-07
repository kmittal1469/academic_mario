//Handles physics movement and certain events functions
#pragma once

#include "Enemies.h" //includes  a number of events such as death taking damage and so on
#include "enemyPhy and Movement.h"
#include "mapHandlingDetails.h"

Enemies enemies;
EnemyPhyAndMovement enPhy; //			//			// for the enemy
mapHandling mapping;

class phyAndMovement
{
public:

//checks the title
void phyAndMovement::playerJump()
{
	if(dbSpaceKey() && spaceKeyPressed == false)
	{
		if(!jumping && touchingGround)
		{
			dbPlaySound(Sjump);
			spaceKeyPressed = true;
			touchingGround = false;
			jumpStartTimer = dbTimer(); //makes sure the initial gravity doesnt stick the player to the ground he is already standing on
			jumping = true;
		}
	}
	if (jumping) 
	{
		if(dbTimer() - jumpStartTimer < 650)
		{
			playerY = playerY - speedy;
		}
		if(dbTimer() - jumpStartTimer > 720)
		{
			jumping = false;
		}
	}
	if(dbSpaceKey()==0)spaceKeyPressed = false;

}

void phyAndMovement::gravity()
{
	if(amIAlive == true /* && stopMovement == false*/)
	{
		if(!touchingGround)
		{
			if(jumping == false)
			{
				if(dbTimer() - touchingGroundTimer > 150)
				{
					falling = true;
				}
				playerY = playerY + speedy;
			}
		}
		if(touchingGround)
		{	
			if(jumping)jumping = false; 
			if(falling)falling = false;
		}
	}
}

int phyAndMovement::MarioWalkerCollision()
{	
	//check if a 'walker' has collided with another
	//if so change both of their directions :)
	for(int i = 0; i < maxWalkers; i ++)
	{
		//find out who mario collided against
		if(dbSpriteExist(walkers[i].id))
		{
			if(walkers[i].isAlive) 
			{
				if(dbSpriteCollision(mario, walkers[i].id))
				{
					return i; //return the walker he collided against
				}
			}
		}
	}
	//returns a -1 because the walker isnt found or there was no collision
	return -1;
}


/*Checks if mario collides with any of the enemies and if so
check if mario collided from above or any other side 
then either do damage to mario or his enemy*/
void phyAndMovement::AiPlayerCollisions()
{
	int didMarioCollide = MarioWalkerCollision();
	
	if(didMarioCollide != -1 && amIAlive == true)//to avoid double triggers, e.g. goomba kills mario and then mario kills goomba
	{
		/*If mario is a certain height above the enemy we will kill or damage them, otherwise
		mario takes the damage because he didnt hit from above*/
		
		//enemies height minus Mario's height, if that > or equals 60 
		//then mario is right above them
		if(dbSpriteY(walkers[didMarioCollide].id) - dbSpriteY(mario) >= 55 && !walkers[didMarioCollide].isDying) //to avoid double triggers, e.g. mario kills goomba and then goomba kills mario
		{
			//iF THE PLAYER does collide but is too much to either side then we count that as a bad jump and the walker does damage to mario
			//if he is within a certain space then he damages them e.g. too much on edges will get mario killed
			if(dbSpriteX(mario) > dbSpriteX(walkers[didMarioCollide].id) + 55 || dbSpriteX(mario) < dbSpriteX(walkers[didMarioCollide].id) - 55)
			{
				myEvents.takeDamage();
			}
			//Otherwise mario is the one causing the damage
			else
			{
				if(walkers[didMarioCollide].typeOf == GOOMBA)
				{
					playerY = playerY - (speedy*5); //Improve this
					dbPlaySound(Sstomp); 

					// kills the goomba stamped on
					enPhy.KillMe(didMarioCollide);
					//plays score animation above goombas head
					mHandling.startAnimation(score100_1, SPRITE, dbSpriteX(walkers[didMarioCollide].id), dbSpriteY(walkers[didMarioCollide].id)-65, 9, a, 80);
				}
			}
		}
		//mario collided anywhere but the top therefore we do damage to him
		else
		{
			myEvents.takeDamage();
		}
	}
}


void phyAndMovement::StaticPlayerCollisions()
{
   //NOTE : you may have noticed the player sticking to the blocks, to stop this make the
   //       collision area of the player smaller and edit the players image to the same
   //       same size (so it doesn't look weird). You have to make the change in the
   //       players x and y sizes greater or equal to their speed or you wont notice a
   //       difference.
   
   
   //the following 8 lines of code stores the old and new left,right,top,bottom edges of
   //the sprite in the respective variables
   
   //gets which tiles the current left and right co-ordinates of the player are on
   int lefttilenum = int( playerX / tilesizex );
   int righttilenum = int( ( playerX + ( tilesizex - 1 ) ) / tilesizex );
   //gets which tiles the current top and bottom co-ordinates of the player are on
   int toptilenum = int( playerY / tilesizey );
   int bottomtilenum = int( ( playerY + ( tilesizey - 1 ) ) / (tilesizey) );
   
   //gets which tiles the old left and right co-ordinates of the player are on
   int oldlefttilenum = int( oldx1 / tilesizex );
   int oldrighttilenum = int( ( oldx1 + ( tilesizex - 1 ) ) / tilesizex );
   //gets which tiles the old top and bottom co-ordinates of the player are on
   int oldtoptilenum = int( oldy1 / tilesizey );
   int oldbottomtilenum = int( ( oldy1 + ( tilesizey - 1 ) ) / (tilesizey) );
   
   
   //this is where we check for those 4 collision points; if the collision point is on a
   //tile you are not able to pass through (in our case a tile that has an image number
   //of 10 or greater), then the old coordinates of the sprite are restored.
   //Note: to have sliding collision we must check the the current x tile against the
   //old y tile and vice versa.
   
   bool collidedWithSomething = false;//was there a collision?
   int typeOfCollision = 0;

   //if so do something about it
   int collidedWithX = 0; //used to find out what mario collided with map[] 
   int collidedWithY = 0; //used to find out what mario collided with map[][]

   //checks for top-left collision point
   if ( map[lefttilenum][oldtoptilenum] >= 10) 
   {
	  if(map[lefttilenum][oldtoptilenum] < 100)
	  {
		  playerX = oldx1;
		  mapX = oldmapX;
	  }
	  collidedWithSomething = true;
	  collidedWithX = lefttilenum;
	  collidedWithY = oldtoptilenum;
   }
   
   if ( map[oldlefttilenum][toptilenum] >= 10)
   {
	  if(map[oldlefttilenum][toptilenum] < 100)
	  {
		  playerY = oldy1;
		//  mapY = oldmapY;
		  if(jumping == true)jumping = false; // if player was jumping he hit his head on something meaning the jump is over
		  //colliding below something 1/2
	  }
	  typeOfCollision = bottom;
	  collidedWithSomething = true;
	  collidedWithX = oldlefttilenum;
	  collidedWithY = toptilenum;
   }
   //checks for top-right collision point
   if ( map[righttilenum][oldtoptilenum] >= 10) 
   {
	  if(map[righttilenum][oldtoptilenum] < 100)
	  {
		  playerX = oldx1;
		  mapX = oldmapX;
	  }
	  collidedWithSomething = true;
	  collidedWithX = righttilenum;
	  collidedWithY = oldtoptilenum;
   }
   
   if ( map[oldrighttilenum][toptilenum] >= 10) 
   {
	  if(map[oldrighttilenum][toptilenum] < 100)
	  {
		  playerY = oldy1;
		//  mapY = oldmapY;
		  if(jumping == true)jumping = false; // if player was jumping he hit his head on something meaning the jump is over
	  }
	  typeOfCollision = bottom;
	  collidedWithSomething = true;
	  collidedWithX = oldrighttilenum;
	  collidedWithY = toptilenum;
	  //colliding below something 2/2
   }
   
   //checks for bottom-left collision point
   if ( map[lefttilenum][oldbottomtilenum] >= 10) 
   {
	  if(map[lefttilenum][oldbottomtilenum] < 100)
	  {
		  playerX = oldx1;
		  mapX = oldmapX;
	  }
	  collidedWithSomething = true;
	  collidedWithX = lefttilenum;
	  collidedWithY = oldbottomtilenum;
   }
   
   if ( map[oldlefttilenum][bottomtilenum] >= 10) 
   {
	  if(map[oldlefttilenum][bottomtilenum] < 100)
	  {
		   //STANDING ABOVE TILE 1/2
		  if(jumping == true)jumping = false;
		  touchingGround = true;
		  touchingGroundTimer = dbTimer(); // used so falling animation only trigger after 150ms
		  playerY = oldy1;
		 // mapY = oldmapY;
	  }
	  typeOfCollision = top;
	  collidedWithSomething = true;
	  collidedWithX = oldlefttilenum;
	  collidedWithY = bottomtilenum;
   }
   
   
   //checks for bottom-right collision point
   if ( map[righttilenum][oldbottomtilenum] >= 10)
   {
      if(map[righttilenum][oldbottomtilenum] < 100)
	  {
		  playerX = oldx1;
		  mapX = oldmapX;
	  }
	  collidedWithSomething = true;
	  collidedWithX = righttilenum;
	  collidedWithY = oldbottomtilenum;
   }
   
   if ( map[oldrighttilenum][bottomtilenum] >= 10) 
   {
	  if(map[oldrighttilenum][bottomtilenum] < 100)
	  {
		  //STANDING ABOVE TILE 2/2
		  touchingGround = true;
		  touchingGroundTimer = dbTimer(); // used so falling animation only trigger after 150ms
		  if(jumping == true)jumping = false;
		  playerY = oldy1;
		//  mapY = oldmapY;
	  }
	  typeOfCollision = top;
	  collidedWithSomething = true;
	  collidedWithX = oldrighttilenum;
	  collidedWithY = bottomtilenum;
   }

   //keeps the map in place
   if ( mapX < 60 ) 
   {
      mapX = 60;
   }
   
   //check if player is touching the ground or NOT, if hes colliding with an air tile then hes not touching the ground
   if ( map[oldrighttilenum][bottomtilenum] < 10 && map[oldlefttilenum][bottomtilenum] < 10) 
   {
	  touchingGround = false;
   }
   
   //---------------EXTRA COLLISIONS------------------
   // e.g. coins, mushrooms question boxes
   //	hittin below

   //handles items pickup and specific animations
   myEvents.pickupItems(collidedWithX, collidedWithY, typeOfCollision); 

   enemies.piranhaCollision(collidedWithX, collidedWithY, typeOfCollision);
}


void phyAndMovement::controlCharacter()
{
   if(amIAlive == true) 
   {
		// in case moving mario causes a goomba to collide with something
	    //we can move them back
		for(int i = 0; i < maxWalkers; i ++)
		{
			if(walkers[i].isAlive)
			{
				if(amIAlive == true) 
				{
					//store the map's x and y coordinates into the variables OldmapX and OldmapY
				   
					//store the x and y coordinates of the player into the variables walkers[i].oldx and walkers[i].oldy
					walkers[i].oldx = walkers[i].x;
					walkers[i].oldy = walkers[i].y;
			   }
		   }
		}

	   //store the map's x and y coordinates into the variables OldmapX and OldmapY
	   oldmapX = mapX;
	   oldmapY = mapY;
	   
	   //store the x and y coordinates of the player into the variables oldX1 and oldY1
	   oldx1 = playerX;
	   oldy1 = playerY;
	   
	   //makes the player move by altering the sprites coordinates
	   //makes the map move by altering the maps coordinates, if the player is roughly at the
	   //centre of the screen
	   if(stopMovement == false)
	   {
		   if ( dbLeftKey() == 1) 
		   {
			   //slows the player down before moving
			   //to a new direction
			  if(walkingRight == true && speedx > 0)
			  {
				speedx = 0;
				walkingRight = false;
			  }
		      else if(dbTimer() - speedTimer > 150)
			  {
				speedTimer = dbTimer();
				if(speedx < 5)speedx++;
				walkingLeft = true;
			  }
		   }
		   if ( dbRightKey() == 1) 
		   {
			   //slows the player down before moving
			   //to a new direction
			  if(walkingLeft == true && speedx > 0)
			  {
				speedx = 0;
				walkingLeft = false;
			  }
		      else if(dbTimer() - speedTimer > 150)
			  {
				speedTimer = dbTimer();
				if(speedx < 5)speedx++;
				walkingRight = true;
			  }
		   }
		   if(walkingRight == true)
		   {
			  if ( mapX < playerX - ( screenCenterX - 5 ) && mapX > playerX - ( screenCenterX + 5 ) ) 
			  {
				 mapX = mapX + speedx;
				 //move any walkers  when the map is moved also
				 for(int i = 0; i < maxWalkers; i ++)
				 {
				 	 if(dbSpriteExist(walkers[i].id))
					 {
						 if(walkers[i].isAlive)
						 {  
							//stores the walkers pos before moving him 
							//incase they collide with something
						//walkers[i].oldx = walkers[i].x;
						//walkers[i].x = walkers[i].x - speedx/2;
						//enPhy.EnemyCollisions(i);
							//wen we move the map we have to move all enemies
							//after moving them we need to check if they collided
							//against anything, if so we imediately move the back to 
							//their old position without any graphical changes
							//and to stop them going through physical 'objects'
						 }
					 }
				 }
			  }
			  playerX = playerX + speedx;
		   }

		   if(walkingLeft == true)
		   {
			  if ( mapX < playerX - ( screenCenterX - 5 ) && mapX > playerX - ( screenCenterX + 5 ) ) 
			  {
				 mapX = mapX - speedx;
				 //move any walkers  when the map is moved also
				 for(int i = 0; i < maxWalkers; i ++)
				 {
				 	 if(dbSpriteExist(walkers[i].id))
					 {
						 if(walkers[i].isAlive)
						 {  
							//stores the walkers pos before moving him 
							//incase they collide with something
						//walkers[i].oldx = walkers[i].x;
						//walkers[i].x = walkers[i].x + speedx/2;
						//enPhy.EnemyCollisions(i);
							//wen we move the map we have to move all enemies
							//after moving them we need to check if they collided
							//against anything, if so we imediately move the back to 
							//their old position without any graphical changes
							//and to stop them going through physical 'objects'
						 }
					 }
				 }
			  }
			  playerX = playerX - speedx;
		   }
		   if(dbLeftKey() == 0)
		   {
			  if(walkingLeft == true && speedx > 0)
			  {
				if(dbTimer() - speedTimer > 150)
				{
					speedTimer = dbTimer();
					if(speedx > 0)speedx--;
				}
				if(speedx == 0) walkingLeft = false;
			  }
		   }
		   //reset the speed to it is slowly increment when left or right are held
		   if(dbRightKey() == 0)
		   {
			  if(walkingRight == true && speedx > 0)
			  {
				if(dbTimer() - speedTimer > 150)
				{
					speedTimer = dbTimer();
					if(speedx > 0)speedx--;
				}
				if(speedx == 0) walkingRight = false;
			  }
		   }
		   if(dbRightKey() && dbLeftKey())
		   {
			  walkingRight = false;
			  walkingLeft = false;
		   }

		   //increase speed if shift is pressed
		   if(dbShiftKey() /*&& falling == false && jumping == false*/)
		   {
			   //only start sprinting once speed has developed
			  if(speedx > 4)
			  {
				  if(dbRightKey() || dbLeftKey())
				  {
					  //only allow him to sprint if hes touching the ground
					  if(touchingGround)
					  {
						  speedx += 1;
					  }
				  }
			  } 
		   }
		   else 
		   {
			  if(speedx > 4)speedx -= 1;
		   }
		   if(speedx > 6)speedx = 6;// limits the sprint speed
	   }
   }
   
}

};