#pragma once

class variables
{
public:
};

#define normalMario 1
#define FireMario 2
#define bottom 1 //used to define the type of collision
#define top 2
#define M 0 //THIS IS THE SPOT positioned on the map where mario initially spawns YOU CANT HAVE 2 OF THEM(
//any other M's found after the first one are converted into AIR TiLeS)
#define a 1 //air tile
//tiles with value above 10 are used for collisions (you can walk through them)
#define r 10 //restriction tile
#define g 11 //ground tile TOP
#define B 12 //ground tile Bottom
#define p1 13 //pipe tile top right
#define p2 14 //pipe tile top left
#define p3 15 //pipe tile bottom right
#define p4 16 //pipe tile bottom left
//tiles above 20 are used for collision and interaction, e.g. ? boxes bricks, enemies
#define b 20 //brick tile
//over 100 because we dont want collision to push away mario
#define fr 150
#define fl 151
#define P1 152
#define P2 153
#define P3 154
#define P4 155
#define P5 156
#define P5l 157
#define P6 158
#define q 40 //question brick, these animations go from 40 to 67 
#define qC 32 // q coins 
#define qF 33 // q flower 
#define e 34 // empty block, what ? boxes are turned into
#define k 35 // other blocks scattered around level
#define d 70 //d means death used to check if player fell in any of the holes in the map, if so then handle mario's death
#define c 9 //clouds
#define L 99 // used for 1up boxes
#define C 100 //coins
#define SA 105 //special tileset based anim
#define f 300  // used for fire flower 12 for the anims
#define fB 115 // used for checkpoint flag bottom
#define fT 116 // used for checkpoint flag top
#define gM 117 // green mushroom
#define maxAnimations 20 // limits the maximum number of special anims(e.g. coin above question box etc)
//Enemies vars
#define EPl 170 // enemies plant LEFT (because it takes up 2 tiles) 30 images
#define EPr 200 // enemies plant rIGHT
#define maxPiranhas 10 // limits the maximum number of plants allowed in the map
#define maxWalkers 30 // limits the maximum number of walkers and turtles allowed in the map 
#define G 230 //walkers GOOMBA
#define GOOMBA 1
#define TURTLE 2
#define LEFT 1 //used to change enemies directions 
#define RIGHT 2//based on collisions
//USED FOR THE ANIMATIONS
#define SPRITE 1
#define IMAGE 2
int currentWalker = 1; //used to create new walkers and set id's
int speedxEN = 2; //speed at which enemies move
//Enemies vars end
int numoftilesx = 65;
int numoftilesy = 65;
int tilesizex = 65;
int tilesizey = 65;
int speedx = 5;
int speedy = 5; 
int screenCenterX = 380;
int screenCenterY = 280;
int playerX = screenCenterX;
int playerY = screenCenterY;
int mapX = 0;
int mapY = 0;
int oldmapX = 0;
int oldmapY = 0;
int oldx1 = 0;
int oldy1 = 0;
const int COLS = 170; //very high because the map is mostly columns
const int ROWS = 12;
int level = 1; //used to load the right map depending on the level

//mario vars
int mario = 2; 
int marioWalk = 3; 
int marioJump = 4;
//mario flower anims
int FireMarioStill = 5;
int FireMarioWalk = 6; 
int FireMarioJump = 7;

int walkingTimer = dbTimer(); //used to play walking animations
int jumpStartTimer = dbTimer(); // used to stop colliding issues
const float GRAVITY = 0.2;// needs to be an even number. as screen coordinates can only be whole numbers
bool jumping = false;
bool falling = false; //used to show falling animations when coming down
bool touchingGround = false;
int touchingGroundTimer = dbTimer(); //used to play certain animation e,g. falling
int currentMario; //used to know which mario is in action, small big or fire one
bool walkingRight = false; //used to walk to the end of the map in certain levels
bool walkingLeft = false;
bool takingDamage = false; //turns mario invisible during damage taking
bool marioSpawned = false; //restricts mario spawns to only 1
bool CheckPointReached = false;
bool TEMPGombaSpawned = false;
//completes the final steps of the game
bool EndGame = false;
int speedTimer = dbTimer();
//COLUMN IS THE SHELF
//ROW IS THE DRAWER

//animation based vars
int qBoxAnim = 0; //increment Question boxes animation
int questionBoxTimer = dbTimer(); //handles how often question box animations are cycled

int coinAnim = 0; //increment coin tiles animation
int coinTimer = dbTimer(); //handles how often coins animations are cycled

//the main map is stored here
bool spaceKeyPressed = false;//stops jump from repeating if space is held
int map[COLS][ROWS];

//sound vars S starting to indentify them as sound
int SmainTheme = 1;
int ScoinPickup = 2;
int SFlowerAppear = 3;
int Sjump = 4;
int Sdeath = 5;
int Sbrick = 6;
int Sbump = 7;
int SFlowerPickup = 8;
int SnewLife = 11;
int SendLevel = 12;
int StimeWarning = 13;
int SlevelClear = 14;
int Spowerup = 15; // used for 1up
int SplantCrunch = 16; // used for 1up
int ScheckPoint = 93;
int Sstomp = 17; //stomping on enemies sound
int SPipeAndDamage = 18; //used for when turning from fire to normal or going through a plant

//image used for the score animations
int score200_1 = 71;// 71 to 81
int score100_1 = 270;// 270 to 279 // used for when killing enemies
int score1000_1 = 82;// 82 to 93
int check_1 = 120; // checkpoint images 13 of them
int dust_1 = 133; // dust images 8 of them
int _1up_1 = 245; // 14 up images for the animation
int _1upText_1 = 280;

//display variables, e.g. time, coins
int coins = 0;
int time;
int gameTimer = dbTimer();
int score;
int lifes;
int checkPointX;
int checkPointY;
int checkPlayerX;
int checkPlayerY;
int levelOver = 0;
bool stopMovement = false;

//death vars
int deathFlash; // decides which way mario spins when he dies
int damageFlashes;//counts number of spins
bool amIAlive = false;
bool dying = false;
int flashTimer = dbTimer();

//handles things like the coin above a ? box or the flower above the ? box,
// struct is used because multiple animation may be required
typedef struct extraAnimations 
{
	bool busy; // is there something happening on the current element of the struct, if so skip to the one ahead
	int SetImage; //used to find which image is the one to follow e.g. 100 score, 200 score
	int frames; //stores the sprites image ID
	int timer; //stores the sprites ID
	int id; // used to store the 2d and 1d element
	int typeOf; // used to figure out if the animation is sprite based or image based
	//y and x are used for animations of sprites
	int y;
	int x;
	int HighestFrame; //because different animations have different frame limits
    //used so we can calculate the distance between the time when mario triggered the animation
	//and where he moved to, this allows us to keep the animation in the correct place even after mapX moves
	int OriginalMapX;
	int FinalFrame; //is used for animations in which after the animation a change is required e.g. 1 up mushroom
	int animDelay; //used to specify what delay between animation each image has
} extraAnimations;

//used for all the plants actions
typedef struct piranhaAI 
{
	int id;//image and sprite id
	int typeOf; //used to define if it is the left half or the right one
	bool tooClose; //if so then stop plant from rising
	bool isAlive; // defines whether the plant is alive or not
	int plantTimer; //handles plants animation speed
	int plantLoopTimer; //how long it waits until it comes back up again
	int plantAnim; //stores current anim on the plant
	int distance;  //how far is the plant from mario
	//these variables are used to indentify exact where in the map[][]
	//the plants are located, this way we can see which plant is being called on the map handler
	//and handle the exactly correct sprite and animation
	//simply it allows plants to function independently e.g. different animation can be found in different plants
	int ReferenceJ;
	int ReferenceI; 

} piranhaAI;

//used for all walkers animations
typedef struct walkingEN 
{
	int id;//image and sprite id
	int typeOf; //used to see which type of enemy this is GOOMBA or Turtle
	bool isAlive; // defines whether the plant is alive or not
	bool touchingGround; //used for gravity if not bring them down
	bool walking; //is he walking or not, will almost always be true
	bool isDying; //if the enemy is dying we initiate a death animation
	int walkingDirection; // which direction are we setting the walker towards, change on collision
	int walkingTimer; // used to change walking anims
	int x; // walkers xpos
	int y; // walkers ypos
	int oldx; // walkers old xpos(to reverse to if a collision occurs)
	int oldy; // walkers old ypos	
	int currentFrame; //used to play with animations
	int CollisionTimer; // used to keep enemies away from each other on collision
	int LastEnemyCollided; //stores the last enemy bumped against used to unstick Ai
	bool ASleep; // used to keep enemies still once spawned and frees them once mario is close to them(prevent deaths to walkers and helps with the stupid tilling system)

} walkingEN;

walkingEN walkers[maxWalkers]; //makes the array to store all walking enemies walkers, turtles

piranhaAI piranhaPlants[maxPiranhas*2]; // because each stores 1 plant e.g. left side or right

extraAnimations anims[maxAnimations]; // allows up to X animations at the same time


