#pragma once

//Handles loading of all images and files
class loader
{
public:
	void loadCurrentLevel(int level);
	void loadImages();
	void loadSounds();
};
miscelaneous misc;

void loader::loadSounds()
{
	dbLoadSound("Sounds//Main Theme.wav", SmainTheme);
	dbLoadSound("Sounds//coin.wav", ScoinPickup);
	dbLoadSound("Sounds//Flower appear.wav", SFlowerAppear);
	dbLoadSound("Sounds//jump.wav", Sjump);
	dbLoadSound("Sounds//Death.wav", Sdeath);
	dbLoadSound("Sounds//break block.wav", Sbrick);
	dbLoadSound("Sounds//bump.wav", Sbump);
	dbLoadSound("Sounds//FlowerPickup.wav", SFlowerPickup);
	dbLoadSound("Sounds//checkpoint 1.wav", ScheckPoint);
	dbLoadSound("Sounds//life.wav", SnewLife);
	dbLoadSound("Sounds//Flag pole.wav", SendLevel);
	dbLoadSound("Sounds//Time warning.wav", StimeWarning);
	dbLoadSound("Sounds//clear level.wav", SlevelClear);
	dbLoadSound("Sounds//Pick up powerup.wav", Spowerup);
	dbLoadSound("Sounds//plant crunch.wav", SplantCrunch);
	dbLoadSound("Sounds//EnemyStomp.wav", Sstomp);
	dbLoadSound("Sounds//PipeAndDamage.wav", SPipeAndDamage);
}


void loader::loadCurrentLevel(int level)
{
	if(level == 1)
	{
		//current level is made the opposite of the 2d array map, ROWS first instead of columns
		int currentLevel[ROWS][COLS] = 
		{
			//RESET MAP ON DEATH
			{r ,r ,r , r , r , r , r , r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r,},
			{r ,a ,a ,a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, qC, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a,},
			{r, a, c, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, c, a, a, a, a, a, a, a, a, a, a, a, a, c, a, a, a, a, a, c, a, a, a, a, a, a, a, a, a, a, a, a, a, c, a, a, a, a, G, a, a, a, c, a, a, a, a, a, a, c, a, a, a, a, a, a, a, a, c, a, a, a, a, a, a, c, a, a, a, a, a, a, a, c, C, C, C, C, a, a, a, a, a, c, a, a, a, a, a, a, a, c, qF, a, a, a, a, a, a, a, a, a, a, a, a, a, c, a, a, a, a, a, a, c, a, a, a, a, a, a, a, a, a, a, a, a, c, a, a, a, a, a, a, c, a, a, a, a, a, P6, a, a, a, c, a, a, r},
			{r, a, a, M, a, a, c, a, a, a, a, a, b, qC, b, a, c, a, a, a, c, a, a, a, a, a, a, c, C, C, a, a, a, a, c, a, a, a, a, a, a, a, a, C, C, a, a, a, a, a, a, a, c, a, a, a, a, C, C, C, C, b, b, b, C, a, a, a, a, a, a, a, a, a, a, a, a, c, a, a, a, a, a, a, c, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, c, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, c, a, a, a, a, a, a, a, c, a, a, a, a, a, a, a, a, a, a, a, G, a, G, a, a, G, a, a, a, a, a, a, a, a, a, a, P5l, P5, a, a, a, a, a, a, r},
			{r, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, C, C, a, a, a, a, a, a, a, a, a, a, a, a, a, a, C, a, a, a, a, a, a, a, a, G, a, G, a, a, a, a, a, a, a, a, a, a, a, C, a, a, a, a, a, a, a, G, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, P4, a, a, a, a, a, a, r},
			{r, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, G, a, C, C, a, a, a, a, a, a, a, a, a, a, L, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, G, G, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, C, a, a, qC, qC, qC, qC, a, a, a, a, a, EPl, EPr, a, a, a, a, a, a, a, a, a, k, a, a, a, a, a, a, a, a, a, EPl, EPr, a, a, a, a, a, a, a, a, a, a, b, b, b, b, qC, qC, qC, b, a, a, a, EPl, EPr, a, a, a, a, a, a, a, a, a, a, P3, a, a, a, a, a, a, r},
			{r, a, a, a, a, a, a, a, a, a, a, b, qC, b, qF, b, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, G, a, G, p1, p2, a, a, a, a, a, a, a, a, a, a, a, a, b, b, qC, b, b, qC, b, b, a, a, a, a, a, a, a, a, a, a, a, a, a, EPl, EPr, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, p1, p2, a, a, a, a, a, a, a, C, a, a, a, a, a, a, a, a, a, a, a, p1, p2, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, p1, p2, a, a, a, a, a, a, a, a, a, a, P2, a, a, a, a, a, a, r},//HERE
			{r, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, p1, p2, a, a, a, a, a, a, a, a, a, a, a, a, a, p3, p4, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, G, a, G, p1, p2, a, a, fT, a, a, a, k, a, a, a, k, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, p3, p4, a, p1, p2, a, a, a, a, k, a, a, a, a, a, a, a, a, a, a, a, p3, p4, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, p3, p4, a, a, a, a, a, a, a, a, a, a, P1, a, a, a, a, a, a, r},
			{r, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, p3, p4, a, a, a, a, a, p1, p2, a, a, a, a, a, a, p3, p4, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, p3, p4, a, a, fB, a, a, k, k, a, a, a, k, k, a, a, a, a, a, a, a, a, a, a, a, a, a, a, p3, p4, a, p3, p4, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, p3, p4, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, p3, p4, a, a, a, a, a, a, a, a, a, fl, fr, a, a, a, a, a, a, r},
			{g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, a, a, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, a, a, a, g, g, g, g, g, g, g, g, g, g, g, g, g, a, a, a, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, a, a, a, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, a, a, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g},
			{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, a, a, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, a, a, a, B, B, B, B, B, B, B, B, B, B, B, B, B, a, a, a, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, a, a, a, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, a, a, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
			{d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d}//DEATH GROUND touch it = death
			//MAP END
		};

		//copy level to the map array
		//and store any enemies on the level into their respective arrays
		int enemyRecorder;
		int x = 0;
		for(int i = 0; i < ROWS; i++)
		{
			for(int j = 0; j < COLS; j++)
			{
				map[j][i] = currentLevel[i][j];
			
				//store left piranha as a reference to check distances later
				if(map[j][i] == EPl)
				{ 
					enemyRecorder = misc.findFreeSprite();
					piranhaPlants[x].id = enemyRecorder;
					//so we know exactly which plant we are handling in the map
					piranhaPlants[x].ReferenceJ = j;
					piranhaPlants[x].ReferenceI = i;
					dbSprite(piranhaPlants[x].id, 100, 100, EPl);
					dbHideSprite(piranhaPlants[x].id);
					piranhaPlants[x].typeOf = map[j][i];//left side or right side
					piranhaPlants[x].isAlive = true;
					x++;
				}
				else if(map[j][i] == EPr)
				{
					enemyRecorder= misc.findFreeSprite();
					piranhaPlants[x].id = enemyRecorder;
					//so we know exactly which plant we are handling in the map
					piranhaPlants[x].ReferenceJ = j;
					piranhaPlants[x].ReferenceI = i;
					dbSprite(piranhaPlants[x].id, 100, 100, EPr);
					dbHideSprite(piranhaPlants[x].id);
					piranhaPlants[x].typeOf = map[j][i];//left side or right side
					piranhaPlants[x].isAlive = true;
					x++;
				}
			}
		}
	}
}

void loader::loadImages()
{
	// load mario
	dbLoadImage("mario//still.png", mario, 1);
	dbLoadImage("mario//walk.png", marioWalk, 1);
	dbLoadImage("mario//jump.png", marioJump, 1);
	dbLoadImage("mario//stillFire.png", FireMarioStill, 1);
	dbLoadImage("mario//walkFire.png", FireMarioWalk, 1);
	dbLoadImage("mario//JumpFire.png", FireMarioJump, 1);

	//load environmnet tiles
	dbLoadImage("environment//Physics//Brick.png", b);
	dbLoadImage("environment//airTile.png", a);// turns the air tiles into restriction tiles also
	dbLoadImage("environment//airTile.png", r);//and also death tiles, put below the map to check if player falls down any holes
	dbLoadImage("environment//airTile.png", d);
	dbLoadImage("environment//airTile.png", L);//show the hidden 1up box as an air tile, player bumps into it then turn into a block and give green mushroom

	dbLoadImage("environment//cloud.png", c);
    dbLoadImage("environment//Physics//GroundTop.png", g); //used as a boundry to stop player moving that way
    dbLoadImage("environment//Physics//GroundBottom.png", B);
    dbLoadImage("environment//PipeULeft.png", p1);
    dbLoadImage("environment//PipeURight.png", p2);
    dbLoadImage("environment//PipeDleft.png", p3);
    dbLoadImage("environment//PipeDright.png", p4);

   //load question blocks all animations
   dbLoadImage("environment//Blocks//Question block frames//Question block001.png", q);
   dbLoadImage("environment//Blocks//Question block frames//Question block003.png", q+1);
   dbLoadImage("environment//Blocks//Question block frames//Question block005.png", q+2);
   dbLoadImage("environment//Blocks//Question block frames//Question block007.png", q+3);
   dbLoadImage("environment//Blocks//Question block frames//Question block009.png", q+4);
   dbLoadImage("environment//Blocks//Question block frames//Question block011.png", q+5);
   dbLoadImage("environment//Blocks//Question block frames//Question block013.png", q+6);
   dbLoadImage("environment//Blocks//Question block frames//Question block015.png", q+7);
   dbLoadImage("environment//Blocks//Question block frames//Question block017.png", q+8);
   dbLoadImage("environment//Blocks//Question block frames//Question block019.png", q+9);
   dbLoadImage("environment//Blocks//Question block frames//Question block021.png", q+10);
   dbLoadImage("environment//Blocks//Question block frames//Question block023.png", q+11);
   dbLoadImage("environment//Blocks//Question block frames//Question block025.png", q+12);
   dbLoadImage("environment//Blocks//Question block frames//Question block027.png", q+13);
   dbLoadImage("environment//Blocks//Question block frames//Question block029.png", q+14);
   dbLoadImage("environment//Blocks//Question block frames//Question block031.png", q+15);
   dbLoadImage("environment//Blocks//Question block frames//Question block033.png", q+16);
   dbLoadImage("environment//Blocks//Question block frames//Question block035.png", q+17);
   dbLoadImage("environment//Blocks//Question block frames//Question block037.png", q+18);
   dbLoadImage("environment//Blocks//Question block frames//Question block039.png", q+19);
   dbLoadImage("environment//Blocks//Question block frames//Question block041.png", q+20);
   dbLoadImage("environment//Blocks//Question block frames//Question block043.png", q+21);
   dbLoadImage("environment//Blocks//Question block frames//Question block045.png", q+22);
   dbLoadImage("environment//Blocks//Question block frames//Question block047.png", q+23);
   dbLoadImage("environment//Blocks//Question block frames//Question block049.png", q+24);
   dbLoadImage("environment//Blocks//Question block frames//Question block051.png", q+25);
   dbLoadImage("environment//Blocks//Question block frames//Question block053.png", q+26);
  
   dbLoadImage("environment//Blocks//solid block.png", k);
   dbLoadImage("environment//Blocks//empty block.png", e);

   dbLoadImage("environment//Flag pole//FlagBottomRight.png", fr);
   dbLoadImage("environment//Flag pole//FlagBottomLeft.png", fl);
   dbLoadImage("environment//Flag pole//pole1.png", P1);
   dbLoadImage("environment//Flag pole//pole2.png", P2);
   dbLoadImage("environment//Flag pole//pole3.png", P3);
   dbLoadImage("environment//Flag pole//pole4.png", P4);
   dbLoadImage("environment//Flag pole//pole5.png", P5);
   dbLoadImage("environment//Flag pole//pole5Left.png", P5l);
   dbLoadImage("environment//Flag pole//pole6.png", P6);
   dbLoadImage("environment//Flag pole//midwayFlagBottom.png", fB);
   dbLoadImage("environment//Flag pole//midwayFlagTop.png", fT);


   //load coin and all anims
   dbLoadImage("environment//Rewards//coin001.png", C);
   dbLoadImage("environment//Rewards//coin002.png", C+1);
   dbLoadImage("environment//Rewards//coin003.png", C+2);
   dbLoadImage("environment//Rewards//coin004.png", C+3);
   dbLoadImage("environment//Rewards//coin005.png", C+4);
   dbLoadImage("environment//Rewards//coin006.png", C+5);
   dbLoadImage("environment//Rewards//coin001.png", C+6); // used for special animations

   //load fire flower and its anims
	dbLoadImage("environment//Rewards//FireFlower1.png", f);
	dbLoadImage("environment//Rewards//FireFlower2.png", f+1);
	dbLoadImage("environment//Rewards//FireFlower3.png", f+2);
	dbLoadImage("environment//Rewards//FireFlower4.png", f+3);
	dbLoadImage("environment//Rewards//FireFlower5.png", f+4);
	dbLoadImage("environment//Rewards//FireFlower6.png", f+5);
	dbLoadImage("environment//Rewards//FireFlower7.png", f+6);
	dbLoadImage("environment//Rewards//FireFlower8.png", f+7);
	dbLoadImage("environment//Rewards//FireFlower9.png", f+8);
	dbLoadImage("environment//Rewards//FireFlower10.png", f+9);
	dbLoadImage("environment//Rewards//FireFlower11.png", f+10);
	dbLoadImage("environment//Rewards//FireFlower12.png", f+11);



	//load score images 100
	dbLoadImage("environment//score//100_1.png", score100_1);
	dbLoadImage("environment//score//100_2.png", score100_1+1);
	dbLoadImage("environment//score//100_3.png", score100_1+2);
	dbLoadImage("environment//score//100_4.png", score100_1+3);
	dbLoadImage("environment//score//100_5.png", score100_1+4);
	dbLoadImage("environment//score//100_6.png", score100_1+5);
	dbLoadImage("environment//score//100_7.png", score100_1+6);
	dbLoadImage("environment//score//100_8.png", score100_1+7);
	dbLoadImage("environment//score//100_9.png", score100_1+8);

	//load score images 200
	dbLoadImage("environment//score//200_1.png", score200_1);
	dbLoadImage("environment//score//200_2.png", score200_1+1);
	dbLoadImage("environment//score//200_3.png", score200_1+2);
	dbLoadImage("environment//score//200_4.png", score200_1+3);
	dbLoadImage("environment//score//200_5.png", score200_1+4);
	dbLoadImage("environment//score//200_6.png", score200_1+5);
	dbLoadImage("environment//score//200_7.png", score200_1+6);
	dbLoadImage("environment//score//200_8.png", score200_1+7);
	dbLoadImage("environment//score//200_9.png", score200_1+8);
	dbLoadImage("environment//score//200_10.png",score200_1+9);
	dbLoadImage("environment//score//200_11.png",score200_1+10);

	// load score 1000
	dbLoadImage("environment//score//1000_1.png", score1000_1);
	dbLoadImage("environment//score//1000_2.png", score1000_1+1);
	dbLoadImage("environment//score//1000_3.png", score1000_1+2);
	dbLoadImage("environment//score//1000_4.png", score1000_1+3);
	dbLoadImage("environment//score//1000_5.png", score1000_1+4);
	dbLoadImage("environment//score//1000_6.png", score1000_1+5);
	dbLoadImage("environment//score//1000_7.png", score1000_1+6);
	dbLoadImage("environment//score//1000_8.png", score1000_1+7);
	dbLoadImage("environment//score//1000_9.png", score1000_1+8);
	dbLoadImage("environment//score//1000_10.png", score1000_1+9);
	dbLoadImage("environment//score//1000_11.png", score1000_1+10);

	// loads checkpoint anim
	dbLoadImage("environment//score//check_1.png", check_1);
	dbLoadImage("environment//score//check_2.png", check_1+1);
	dbLoadImage("environment//score//check_3.png", check_1+2);
	dbLoadImage("environment//score//check_4.png", check_1+3);
	dbLoadImage("environment//score//check_5.png", check_1+4);
	dbLoadImage("environment//score//check_6.png", check_1+5);
	dbLoadImage("environment//score//check_7.png", check_1+6);
	dbLoadImage("environment//score//check_8.png", check_1+7);

	//load dust animations
	dbLoadImage("environment//Blocks//Dust//dust1.png", dust_1);
	dbLoadImage("environment//Blocks//Dust//dust2.png", dust_1+1);
	dbLoadImage("environment//Blocks//Dust//dust3.png", dust_1+2);
	dbLoadImage("environment//Blocks//Dust//dust4.png", dust_1+3);
	dbLoadImage("environment//Blocks//Dust//dust5.png", dust_1+4);
	dbLoadImage("environment//Blocks//Dust//dust6.png", dust_1+5);
	dbLoadImage("environment//Blocks//Dust//dust7.png", dust_1+6);
	dbLoadImage("environment//Blocks//Dust//dust8.png", dust_1+7);
	dbLoadImage("environment//Blocks//Dust//dust9.png", dust_1+8);

	//load up 1up anims
	dbLoadImage("environment//1up//1up_1.png", _1up_1);
	dbLoadImage("environment//1up//1up_2.png", _1up_1+1);
	dbLoadImage("environment//1up//1up_3.png", _1up_1+2);
	dbLoadImage("environment//1up//1up_4.png", _1up_1+3);
	dbLoadImage("environment//1up//1up_5.png", _1up_1+4);
	dbLoadImage("environment//1up//1up_6.png", _1up_1+5);
	dbLoadImage("environment//1up//1up_7.png", _1up_1+6);
	dbLoadImage("environment//1up//1up_8.png", _1up_1+7);
	dbLoadImage("environment//1up//1up_9.png", _1up_1+8);
	dbLoadImage("environment//1up//1up_10.png", _1up_1+9);
	dbLoadImage("environment//1up//1up_11.png", _1up_1+10);
	dbLoadImage("environment//1up//1up_12.png", _1up_1+11);
	dbLoadImage("environment//1up//1up_13.png", _1up_1+12);
	dbLoadImage("environment//1up//1up_14.png", _1up_1+13);
	dbLoadImage("environment//1up//1up_15.png", _1up_1+14);
	dbLoadImage("environment//1up//1up_16.png", _1up_1+15);
	dbLoadImage("environment//1up//1up_17.png", _1up_1+16);
	

	
	//load up 1up TEXT anims
	dbLoadImage("environment//1up//1upText_1.png", _1upText_1);
	dbLoadImage("environment//1up//1upText_2.png", _1upText_1+1);
	dbLoadImage("environment//1up//1upText_3.png", _1upText_1+2);
	dbLoadImage("environment//1up//1upText_4.png", _1upText_1+3);
	dbLoadImage("environment//1up//1upText_5.png", _1upText_1+4);
	dbLoadImage("environment//1up//1upText_6.png", _1upText_1+5);
	dbLoadImage("environment//1up//1upText_7.png", _1upText_1+6);


	//Enemies images
		//Plant left tile
	dbLoadImage("Enemies//plantL1.png", EPl);
	dbLoadImage("Enemies//plantL2.png", EPl+1);
	dbLoadImage("Enemies//plantL3.png", EPl+2);
	dbLoadImage("Enemies//plantL4.png", EPl+3);
	dbLoadImage("Enemies//plantL5.png", EPl+4);
	dbLoadImage("Enemies//plantL6.png", EPl+5);
	dbLoadImage("Enemies//plantL7.png", EPl+6);
	dbLoadImage("Enemies//plantL8.png", EPl+7);
	dbLoadImage("Enemies//plantL9.png", EPl+8);
	dbLoadImage("Enemies//plantL10.png", EPl+9);
	dbLoadImage("Enemies//plantL11.png", EPl+10);
	dbLoadImage("Enemies//plantL12.png", EPl+11);
	dbLoadImage("Enemies//plantL12x1.png", EPl+12);
	dbLoadImage("Enemies//plantL12x2.png", EPl+13);
	dbLoadImage("Enemies//plantL12x3.png", EPl+14);
	dbLoadImage("Enemies//plantL12x4.png", EPl+15);
	dbLoadImage("Enemies//plantL12x5.png", EPl+16);
	dbLoadImage("Enemies//plantL12x6.png", EPl+17);
	dbLoadImage("Enemies//plantL12x7.png", EPl+18);
	dbLoadImage("Enemies//plantL12x8.png", EPl+19);
	dbLoadImage("Enemies//plantL12x9.png", EPl+20);
	dbLoadImage("Enemies//plantL13.png", EPl+21);
	dbLoadImage("Enemies//plantL14.png", EPl+22);
	dbLoadImage("Enemies//plantL15.png", EPl+23);
	dbLoadImage("Enemies//plantL16.png", EPl+24);
	dbLoadImage("Enemies//plantL17.png", EPl+25);
	dbLoadImage("Enemies//plantL18.png", EPl+26);
	dbLoadImage("Enemies//plantL19.png", EPl+27);
	dbLoadImage("Enemies//plantL20.png", EPl+28);
	dbLoadImage("Enemies//plantL21.png", EPl+29);
	dbLoadImage("Enemies//plantL22.png", EPl+30);

		//Plant right tiles
	dbLoadImage("Enemies//plantR1.png", EPr);
	dbLoadImage("Enemies//plantR2.png", EPr+1);
	dbLoadImage("Enemies//plantR3.png", EPr+2);
	dbLoadImage("Enemies//plantR4.png", EPr+3);
	dbLoadImage("Enemies//plantR5.png", EPr+4);
	dbLoadImage("Enemies//plantR6.png", EPr+5);
	dbLoadImage("Enemies//plantR7.png", EPr+6);
	dbLoadImage("Enemies//plantR8.png", EPr+7);
	dbLoadImage("Enemies//plantR9.png", EPr+8);
	dbLoadImage("Enemies//plantR10.png", EPr+9);
	dbLoadImage("Enemies//plantR11.png", EPr+10);
	dbLoadImage("Enemies//plantR12.png", EPr+11);
	dbLoadImage("Enemies//plantR12x1.png", EPr+12);
	dbLoadImage("Enemies//plantR12x2.png", EPr+13);
	dbLoadImage("Enemies//plantR12x3.png", EPr+14);
	dbLoadImage("Enemies//plantR12x4.png", EPr+15);
	dbLoadImage("Enemies//plantR12x5.png", EPr+16);
	dbLoadImage("Enemies//plantR12x6.png", EPr+17);
	dbLoadImage("Enemies//plantR12x7.png", EPr+18);
	dbLoadImage("Enemies//plantR12x8.png", EPr+19);
	dbLoadImage("Enemies//plantR12x9.png", EPr+20);
	dbLoadImage("Enemies//plantR13.png", EPr+21);
	dbLoadImage("Enemies//plantR14.png", EPr+22);
	dbLoadImage("Enemies//plantR15.png", EPr+23);
	dbLoadImage("Enemies//plantR16.png", EPr+24);
	dbLoadImage("Enemies//plantR17.png", EPr+25);
	dbLoadImage("Enemies//plantR18.png", EPr+26);
	dbLoadImage("Enemies//plantR19.png", EPr+27);
	dbLoadImage("Enemies//plantR20.png", EPr+28);
	dbLoadImage("Enemies//plantR21.png", EPr+29);
	dbLoadImage("Enemies//plantR22.png", EPr+30);

	dbLoadImage("Enemies//Goomba//goomba1.png", G);
	dbLoadImage("Enemies//Goomba//goomba2.png", G+1);
	dbLoadImage("Enemies//Goomba//goomba3.png", G+2);
	dbLoadImage("Enemies//Goomba//goomba4.png", G+3);
	dbLoadImage("Enemies//Goomba//goomba5.png", G+4);
	dbLoadImage("Enemies//Goomba//goomba6.png", G+5);
	dbLoadImage("Enemies//Goomba//goomba7.png", G+6);
	dbLoadImage("Enemies//Goomba//GoombaDeath1.png", G+7);
}