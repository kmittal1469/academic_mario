#include "DarkGDK.h"
#include "variables.h"
#include "mapHandling.h"
#include "Phy and movement.h" //used to load many things
#include "globstruct.h" //USED FOR MESSAGE box and other methods

phyAndMovement phy;// allows us to call Physics and movement functions

void MarioPhysics()
{
	phy.controlCharacter();
	phy.gravity();
	phy.StaticPlayerCollisions();
	phy.AiPlayerCollisions();
	phy.playerJump();
}

void EnemyPhysics()
{
	enPhy.controlAI();
	enPhy.gravity();
	enPhy.goombaAnim();
}

void MarioEvents()
{
	myEvents.playerAnimations();
	myEvents.tickTock();
	myEvents.handleDeath();
	myEvents.handleDamage();
	myEvents.endLevel();
}

void EnemyAnim()
{
	enemy.AwakeEnemies();
	enemy.piranhaAI();
}

void DarkGDK() 
{
    dbSyncOn();
    dbSyncRate(60);
	dbSetDisplayMode(800, 600, 32);
	dbMaximizeWindow();
	dbBackdropOn();
	dbBackdropColor(dbRGB(0, 255, 0));
	load.loadImages();
	load.loadCurrentLevel(level);
	load.loadSounds();
	myEvents.resetEverything();

    while (LoopGDK())
	{
		mapping.playSounds();
		mapping.displayLevel();
		mHandling.LevelAnimations();
		EnemyAnim();
		mapping.displayInformation();
		MarioPhysics();
		MarioEvents();
		EnemyPhysics();
		dbSync();
	}
    return;
}