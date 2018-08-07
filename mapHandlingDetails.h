#pragma once

class mapHandlingDetails
{
public:
/*TEMPORARY CLASS RE-WRITE ALL CLASSES BEFORE YOUTUBE TUTORIAL*/


//starts an animation rolling, whether its a 100 score display or 
void mapHandlingDetails::startAnimation(int scoreToDisplay, int typeOfScore, int x, int y, int topFrame, int solidFrame, int delay)
{
	//only mess with the array if it is an IMAGE and not a SPRITE(avoid any chance of array overflow)
	if(typeOfScore == IMAGE) map[x][y] = SA;

	int i = misc.findFreeAnimation();
	if(anims[i].busy == false)
	{
		if(typeOfScore == IMAGE) anims[i].id = map[x][y];
		anims[i].animDelay = delay;
		anims[i].SetImage = scoreToDisplay;
		anims[i].HighestFrame = topFrame;
		anims[i].x = x;
		anims[i].y = y;
		anims[i].busy = true;
		anims[i].timer = dbTimer();
		anims[i].frames = 0; 
		anims[i].typeOf = typeOfScore;
		anims[i].OriginalMapX = mapX; //stores the map x so we can keep the image in its exact place during animation
		//solid frame is used for animations that required a final tile replacement
		anims[i].FinalFrame = solidFrame;
	}
}

//displays all kinds of animations, from score graphics display to checkpoint text, triggered by "startAnimation method"
void mapHandlingDetails::LevelAnimations()
{
	for(int i = 0;i < maxAnimations; i++)
	{
		if(anims[i].busy == true)
		{
			if(dbTimer() - anims[i].timer > anims[i].animDelay) //animation frames change every 80 ms
			{
				anims[i].timer = dbTimer();
				anims[i].frames++;
					
				if(anims[i].frames == anims[i].HighestFrame)
				{
					anims[i].busy = false;
					//solid frame is used for animations that required a final tile replacement
				}
			}
			//IF THE Animation was triggered from a sprite e.g. a goomba then we paste it based on the location of the sprite
			if(anims[i].typeOf == SPRITE)
			{
				dbPasteImage( anims[i].SetImage + anims[i].frames, anims[i].x + (anims[i].OriginalMapX - mapX), anims[i].y);//Keeps the animation beautifully still
			}
		}
	}
}
























};
