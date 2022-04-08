//COMBAT.CPP

#include "pch.hpp"

/*****************************************************************
				GLOBAL DECLARATIONS
*****************************************************************/

int		RGB{ 16384000 };
int		&RGBcounter{ RGB };

int		switchvalue{ 0 },
		keyvalue{ 0 },
		counter{ 0 },
		SAFEGRID{ 1 },
		gridcounter{ 0 },
		gr{ 0 };

int		&keypressed{ keyvalue },
		showgridcounter{ gridcounter },
		choosegrid{ gr };

int		&x{ switchvalue }, y{};

float	movementdt;

AEGfxTexture* playertexture;
AEGfxTexture* enemytexture;
AEGfxTexture* enemytexturefire;
AEGfxTexture* enemytexturefrost;
AEGfxTexture* staminapotion;


/*****************************************************************
				USING NAMESPACES
*****************************************************************/
using namespace Characters;
using namespace Characters::Enemies;
using namespace Characters::Character;


/*
	Loads all assets in Level1. It should only be called once before the start of the level.
	Opens and reads required files, and assigns values to necessary variables.
*/
void Combat_Load()
{
	std::cout << "Combat:Load" << std::endl;
	//playertexture = AEGfxTextureLoad("ducky.jpg");
	playertexture = AEGfxTextureLoad("Images/Fighting duck.png");
	AE_ASSERT_MESG(playertexture, "cant create duck texture\n");

	enemytexture = AEGfxTextureLoad("Images/Angry turtle.png");
	AE_ASSERT_MESG(enemytexture, "cant create turtle texture\n");

	staminapotion = AEGfxTextureLoad("Images/staminapotion.png");
	AE_ASSERT_MESG(staminapotion, "cant create stamina potion texture\n");

	enemytexturefrost = AEGfxTextureLoad("Images/Frost turtle.png");
	AE_ASSERT_MESG(enemytexturefrost, "cant create enemy texture frost\n");

	enemytexturefire = AEGfxTextureLoad("Images/Fire turtle.png");
	AE_ASSERT_MESG(enemytexturefire, "cant create enemy texture fire\n");

}


/*
	Initializes and sets the starting values of level1.
	Ensures the input file stream opens correctly, and the values
	are assigned accordingly to the variables.
*/
void Combat_Initialize()
{
	stop_Audio();	//JN: new code
	combat_background_Audio();
	//initialise_pausemenu();
	if (enemystats->EnemyType != ENEMYBOSS)
	{
		ChoosingEnemyType((f32)((rand() % 3) + 0));
	}
	else
	{
		SpawnBossEnemy();
	}
	MeshInit();		// Single init for the meshes that only need to be created once (NON RGB MESHES)
	AEToogleFullScreen(systemsettings.fullscreen); // R: added
}


/*
	In charge of checking and updating the program.
	Updates every frame. Part of the actual game loop for level1.
	Contols the logic to end or restart the program.
*/
void Combat_Update()
{
	Audio_Update();
	increase_bgm_fader();	//JN: new code
	decrease_bgm_fader();	//JN: new code
	increase_sfx_fader();	//JN: new code
	decrease_sfx_fader();	//JN: new code
	mute_master_fader();	//JN: new code
	unmute_master_fader();	//JN: new code

	if (AEInputCheckTriggered(AEVK_ESCAPE) && systemsettings.paused == 0) {
		systemsettings.paused = 1;
	} 

	else if (AEInputCheckTriggered(AEVK_ESCAPE) && systemsettings.paused == 1) {
		systemsettings.paused = 0;
	}

	// if not paused
	if (systemsettings.paused == 0)
	{
		RGBloop(RGBcounter);
		CombatMesh(RGBcounter);
		EnemyCombatMesh();
		inventorylogic();
		CheckandUpdatePlayerStatus();
		godmode();

		playerstats->is_dmgtaken -= DT;

		if (enemystats->health <= 0)
		{
			std::cout << "You Won!\n";
			enemystats->health = 0;
			enemystats->EnemyType = 0;
			playerstats->debuffcounter = 0.0f;
			playerstats->PlayerXP += enemystats->EnemyXP;
			if (PlayerLevelUp())
			{
				playerstats->PlayerLevel += 1;
				playerstats->PlayerXP = 0;
				next = LEVELUP;
			}
			else
			{
				next = MAZE;
				maze_init_flag = 1;
				std::cout << "return to maze\n";
			}
		}

		else if (playerstats->health <= 0) {
		  std::cout << "You Died!\n";
		  playerstats->health = 0;
		  next = GAMEOVER;
		  maze_init_flag = 0;
		}
  
		if (keypressed == 0) {											// so i cant move whilst cooldown active
			PlayerMovement(x, keypressed);								// character movement	
			StaminaLogic(keypressed);
		}

		if (keypressed == 1) {
			playerstats->movementdt -= DT;
			if (playerstats->movementdt <= 0.0f) {
				playerstats->positionX = 0.0f;
				playerstats->positionY = 0.0f;
				playerstats->positionID = 1;
				playerstats->is_attacking = false;
				keypressed = 0;
			}
		}

		UpdateEnemyState();
	}

	// else paused
	else {
		//render pause menu here
		logicpausemenu();
		renderpausemenu();
		}	
  
  }


/*
	Updates every frame together with the update function.
	Draws the updated logic from the update function.
*/
void Combat_Draw()
{
	StaminaRender(staminapotion);
	inventoryrender();
	RenderEnemyHealth();
	RenderPlayerHealth();
	GridCheck(enemystats->is_attacking, enemystats->AttackCD, playerstats->SAFEGRID);
	playerrender(playertexture, Character::PlayerMesh);

	if (enemystats->AttackCD <= 0.60f)
	{
		RenderEnemyGrid(EnemyGridAttack);
	}

	if (enemystats->EnemyType == ICE)
	{
		RenderEnemy(enemytexturefrost, EnemyMesh);
	}
	if (enemystats->EnemyType == FIRE)
	{
		RenderEnemy(enemytexturefire, EnemyMesh);
	}
	if (enemystats->EnemyType == NORMAL) {
		RenderEnemy(enemytexture, EnemyMesh);
	}
	if (enemystats->EnemyType == ENEMYBOSS)
	{
		RenderEnemy(enemytexture, EnemyMesh);
	}


}


/*
	Cleans game object instances. will be run in restart
*/
void Combat_Free()
{
	std::cout << "Combat:Free" << std::endl;
	FreePlayerMesh();
	FreeEnemyMesh();
	//unloadpausemenu();
}


/*
	Unload game assets. Frees and releases memory, wont be run in restart
*/
void Combat_Unload()
{
	unloadtextures();
	AEGfxTextureUnload(playertexture);
	AEGfxTextureUnload(enemytexture);
	AEGfxTextureUnload(staminapotion);
	AEGfxTextureUnload(enemytexturefrost);
	AEGfxTextureUnload(enemytexturefire);
}