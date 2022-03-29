//CHARACTER CPP

#include "pch.hpp"

/************************************************************
*			GLOBAL DECLARATIONS
************************************************************/


namespace Characters
{
	/******************************************************
	*
	* PLAYER NAMESPACE
	*
	*******************************************************/
	namespace Character
	{
		
		/************************************************************
		*			CHARACTER NAMESPACE DECLARATIONS
		************************************************************/
		AEGfxVertexList* Player1Grid = 0;	//ORIGN
		AEGfxVertexList* Player2Grid = 0;	//TOP
		AEGfxVertexList* Player3Grid = 0;	//BACK
		AEGfxVertexList* Player4Grid = 0;	//BOTTOM
		AEGfxVertexList* Player5Grid = 0;	//ATTACK
		AEGfxVertexList* PlayerMesh = 0;

		AEGfxVertexList* playermaxhealth = 0;	//PLAYER HEALTH MESH
		AEGfxVertexList* playercurrhealth = 0;	//PLAYER HEALTH MESH
		AEGfxVertexList* playerstamina = 0;		//PLAYER STAMINA MESH
		int counter{ 21 };

		void CombatMesh(int RGBcounter)
		{
			FreePlayerMeshOnUpdate();

			AEGfxMeshStart();

			AEGfxVertexAdd(-240.0f, -160.0f, RGBcounter, 1.0f, 1.0f);
			AEGfxVertexAdd(-140.0f, -160.0f, RGBcounter, 1.0f, 1.0f);
			AEGfxVertexAdd(-140.0f, -60.0f, RGBcounter, 1.0f, 1.0f);			//PLAYERGRID 4 BOTTOM
			AEGfxVertexAdd(-240.0f, -60.0f, RGBcounter, 1.0f, 1.0f);
			AEGfxVertexAdd(-240.0f, -160.0f, RGBcounter, 1.0f, 1.0f);

			Player4Grid = AEGfxMeshEnd();
			AE_ASSERT_MESG(Player4Grid, "Failed to create playermesh4!!");

			//

			AEGfxMeshStart();

			AEGfxVertexAdd(-350.0f, -50.0f, RGBcounter, 0.0f, 1.0f);
			AEGfxVertexAdd(-250.0f, -50.0f, RGBcounter, 1.0f, 1.0f);
			AEGfxVertexAdd(-250.0f, 50.0f, RGBcounter, 0.0f, 0.0f);				//PLAYERGRID 3 BACK
			AEGfxVertexAdd(-350.0f, 50.0f, RGBcounter, 1.0f, 0.0f);
			AEGfxVertexAdd(-350.0f, -50.0f, RGBcounter, 0.0f, 1.0f);

			Player3Grid = AEGfxMeshEnd();
			AE_ASSERT_MESG(Player3Grid, "Failed to create playermesh3!!");

			// 

			AEGfxMeshStart();

			AEGfxVertexAdd(-240.0f, 160.0f, RGBcounter, 0.0f, 1.0f);
			AEGfxVertexAdd(-140.0f, 160.0f, RGBcounter, 1.0f, 1.0f);
			AEGfxVertexAdd(-140.0f, 60.0f, RGBcounter, 0.0f, 0.0f);				//PLAYERGRID 2 TOP
			AEGfxVertexAdd(-240.0f, 60.0f, RGBcounter, 1.0f, 0.0f);
			AEGfxVertexAdd(-240.0f, 160.0f, RGBcounter, 0.0f, 1.0f);

			Player2Grid = AEGfxMeshEnd();
			AE_ASSERT_MESG(Player2Grid, "Failed to create playermesh2!!");

			//

			AEGfxMeshStart();

			AEGfxVertexAdd(-240.0f, -50.0f, RGBcounter, 0.0f, 1.0f);
			AEGfxVertexAdd(-140.0f, -50.0f, RGBcounter, 1.0f, 1.0f);
			AEGfxVertexAdd(-140.0f, 50.0f, RGBcounter, 0.0f, 0.0f);                //PLAYERGRID 1 MIDDLE
			AEGfxVertexAdd(-240.0f, 50.0f, RGBcounter, 1.0f, 0.0f);
			AEGfxVertexAdd(-240.0f, -50.0f, RGBcounter, 0.0f, 1.0f);

			Player1Grid = AEGfxMeshEnd();
			AE_ASSERT_MESG(Player1Grid, "Failed to create playermesh1!!");

			//

			AEGfxMeshStart();

			AEGfxVertexAdd(0.0f, -50.0f, RGBcounter, 0.0f, 1.0f);
			AEGfxVertexAdd(-100.0f, -50.0f, RGBcounter, 1.0f, 1.0f);
			AEGfxVertexAdd(-100.0f, 50.0f, RGBcounter, 0.0f, 0.0f);				//PLAYERGRID 5 ATTACK
			AEGfxVertexAdd(0.0f, 50.0f, RGBcounter, 1.0f, 0.0f);
			AEGfxVertexAdd(0.0f, -50.0f, RGBcounter, 0.0f, 1.0f);

			Player5Grid = AEGfxMeshEnd();
			AE_ASSERT_MESG(Player2Grid, "Failed to create playermesh2!!");
		}


		// the meshes that i only want to initialise once
		void MeshInit() {

			// THE MAX PLAYER HEALTH
			AEGfxMeshStart();
			AEGfxVertexAdd(-390.0f, -290.0f, 0xFFFFFFFF, 0.0f, 1.0f);
			AEGfxVertexAdd(-230.0f, -290.0f, 0xFFFFFFFF, 0.0f, 1.0f);
			AEGfxVertexAdd(-230.0f, -265.0f, 0xFFFFFFFF, 0.0f, 1.0f);
			AEGfxVertexAdd(-390.0f, -265.0f, 0xFFFFFFFF, 0.0f, 1.0f);
			AEGfxVertexAdd(-390.0f, -290.0f, 0xFFFFFFFF, 0.0f, 1.0f);

			playermaxhealth = AEGfxMeshEnd();
			AE_ASSERT_MESG(playermaxhealth, "Failed to create playerhealth!!");

			//

			//CHARACTER OBJECT
			AEGfxMeshStart();
			AEGfxTriAdd(
				-220.0f, -30.0f, 0x00FF00FF, 0.0f, 1.0f,
				-160.0f, -30.0f, 0x00FFFF00, 1.0f, 1.0f,
				-220.0f, 30.0f, 0x0000FFFF, 0.0f, 0.0f);
			AEGfxTriAdd(
				-160.0f, -30.0f, 0x00FFFFFF, 1.0f, 1.0f,
				-160.0f, 30.0f, 0x00FFFFFF, 1.0f, 0.0f,
				-220.0f, 30.0f, 0x00FFFFFF, 0.0f, 0.0f);

			PlayerMesh = AEGfxMeshEnd();
			AE_ASSERT_MESG(PlayerMesh, "Failed to create character!!");

			//

			AEGfxMeshStart();
			AEGfxTriAdd(
				-20.0f, -20.0f, 0x00FF00FF, 0.0f, 1.0f,
				20.0f, -20.0f, 0x00FFFF00, 1.0f, 1.0f,
				20.0f, 20.0f, 0x0000FFFF, 1.0f, 0.0f);

			AEGfxTriAdd(
				-20.0f, -20.0f, 0x00FFFFFF, 0.0f, 1.0f,
				-20.0f, 20.0f, 0x00FFFFFF, 0.0f, 0.0f,
				20.0f, 20.0f, 0x00FFFFFF, 1.0f, 0.0f);

			playerstamina = AEGfxMeshEnd();
			AE_ASSERT_MESG(playerstamina, "Failed to create stamina mesh!!");
		}


		void StaminaLogic(int const& keypressed)
		{

			//std::cout << playerstats->staminacount << "\n";
			//static int flagset = 0;

			if (playerstats->staminacount < playerstats->staminamax) {
				playerstats->staminaCD -= DT;

				if (playerstats->staminaCD < 0) {

					if (playerstats->status == FROSTED)
					{
						playerstats->staminaCD = 1.25f;
					}
					else
					{
						playerstats->staminaCD = 1.0f;	// resets the playerCD
					}
					++playerstats->staminacount;
				}
			}

			if (keypressed == 1) {
				--playerstats->staminacount;
			}
		}


		void StaminaRender(AEGfxTexture* staminapotion)
		{
			for (int i{ 0 }; i < playerstats->staminacount; ++i) {

				AEGfxSetBlendMode(AE_GFX_BM_BLEND);
				AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
				AEGfxSetPosition(playerstats->staminaX + (i * 30), -270.0f);
				AEGfxTextureSet(staminapotion, 0, 0);
				AEGfxSetTintColor(1, 1, 1, 1);
				AEGfxSetTransparency(1);
				AEGfxMeshDraw(playerstamina, AE_GFX_MDM_TRIANGLES);
			}
		}

		void RenderPlayerGrid(AEGfxVertexList* PlayerMesh)
		{
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxSetPosition(0.0f, 0.0f);
			AEGfxTextureSet(NULL, 0, 0);

			AEGfxMeshDraw(PlayerMesh, AE_GFX_MDM_LINES_STRIP);
		}


		// this one frees it before it draws every mesh. to prevent memoryleak
		void FreePlayerMeshOnUpdate() {

			if (Player1Grid != nullptr) {
				AEGfxMeshFree(Player1Grid);
				Player1Grid = nullptr;
			}

			if (Player2Grid != nullptr) {
				AEGfxMeshFree(Player2Grid);
				Player2Grid = nullptr;
			}

			if (Player3Grid != nullptr) {
				AEGfxMeshFree(Player3Grid);
				Player3Grid = nullptr;
			}

			if (Player4Grid != nullptr) {
				AEGfxMeshFree(Player4Grid);
				Player4Grid = nullptr;
			}

			if (Player5Grid != nullptr) {
				AEGfxMeshFree(Player5Grid);
				Player5Grid = nullptr;
			}
		}

		void FreePlayerMesh()
		{
			if (PlayerMesh != nullptr) {
				AEGfxMeshFree(PlayerMesh);
				PlayerMesh = nullptr;
			}

			if (playermaxhealth != nullptr) {
				AEGfxMeshFree(playermaxhealth);
				playermaxhealth = nullptr;
			}

			if (playercurrhealth != nullptr) {
				AEGfxMeshFree(playercurrhealth);
				playercurrhealth = nullptr;
			}

			if (playerstamina != nullptr) {
				AEGfxMeshFree(playerstamina);
				playerstamina = nullptr;
			}

			if (Player1Grid != nullptr) {
				AEGfxMeshFree(Player1Grid);
				Player1Grid = nullptr;
			}

			if (Player2Grid != nullptr) {
				AEGfxMeshFree(Player2Grid);
				Player2Grid = nullptr;
			}

			if (Player3Grid != nullptr) {
				AEGfxMeshFree(Player3Grid);
				Player3Grid = nullptr;
			}

			if (Player4Grid != nullptr) {
				AEGfxMeshFree(Player4Grid);
				Player4Grid = nullptr;
			}

			if (Player5Grid != nullptr) {
				AEGfxMeshFree(Player5Grid);
				Player5Grid = nullptr;
			}

		}

		// returns an int. any movement sets the int flag to 1

		void PlayerMovement(int& x, int& keypressed) {

			x = 0;

			if (playerstats->staminacount > 0 && playerstats->status != FROZEN)
			{
				AEInputCheckTriggered(AEVK_W) ? x = TOP : x = x;	//ID Should be 1
				AEInputCheckTriggered(AEVK_A) ? x = BACK : x = x;	//ID Should be 2
				AEInputCheckTriggered(AEVK_S) ? x = DOWN : x = x;	//ID Should be 3
				AEInputCheckTriggered(AEVK_D) ? x = ATTACK : x = x;	//ID Should be 4

				playerstats->movementdt = 0.5f;

				switch (x) {

				case ATTACK:	//ATTACK GRID
					playerstats->positionID = ATTACK;
					playerstats->positionX = 145.0f;
					playerstats->positionY = 0.0f;
					playerstats->is_attacking = true;
					keypressed = 1;
					break;

				case TOP:
					playerstats->positionID = TOP;
					playerstats->positionX = 0.0f;
					playerstats->positionY = 110.0f;
					playerstats->is_attacking = false;
					keypressed = 1;
					break;

				case BACK:
					playerstats->positionID = BACK;
					playerstats->positionX = -110.0f;
					playerstats->positionY = 0.8f;
					playerstats->is_attacking = false;
					keypressed = 1;
					break;

				case DOWN:
					playerstats->positionID = DOWN;
					playerstats->positionX = 0.0f;
					playerstats->positionY = -110.0f;
					playerstats->is_attacking = false;
					keypressed = 1;
					break;
				}
			}
			if (playerstats->status == FROZEN)
			{
				if (counter == 0)
				{
					playerstats->status = NEUTRAL;
				}
				else
				{
					if (AEInputCheckTriggered(AEVK_A) || AEInputCheckTriggered(AEVK_D))
					{
						--counter;
						//std::cout << counter << "\n";
					}
				}
			}

			if (playerstats->positionX == 0.0f && playerstats->positionY == 0.0f) {
				playerstats->positionID = ORIGIN;
				playerstats->is_attacking = false;
			}
		}


		bool PlayerLevelUp()
		{
			if (playerstats->PlayerXP >= 100)
			{
				return true;
			}
			return false;
		}

		void RGBloop(int& RGBcounter) {
			if (RGBcounter <= 16777215)
			{
				RGBcounter += 500;
				(RGBcounter > 16766215) ? RGBcounter = 16384000 : RGBcounter = RGBcounter;
			}
		}

		void playerrender(AEGfxTexture* playertexture, AEGfxVertexList* playermesh) {

			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			// Set position for object 1
			AEGfxSetPosition(playerstats->positionX, playerstats->positionY);
			AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
			AEGfxTextureSet(playertexture, 1.0f, 1.0f);

			AEGfxMeshDraw(playermesh, AE_GFX_MDM_TRIANGLES);
		}

		void GridCheck(bool EnemyAttackState, float timer, int& x) {

			if (EnemyAttackState == true && timer <= 0.60f) {

				switch (x) // Check for the Safety Grids
				{

				case 1:
					//SAFEGRID (TOP SAFE)
					Character::RenderPlayerGrid(Character::Player1Grid);
					Character::RenderPlayerGrid(Character::Player3Grid);
					Character::RenderPlayerGrid(Character::Player4Grid);
					Character::RenderPlayerGrid(Character::Player5Grid);
					break;

				case 2:
					//SAFEGRID (BACK SAFE)
					Character::RenderPlayerGrid(Character::Player1Grid);
					Character::RenderPlayerGrid(Character::Player2Grid);
					Character::RenderPlayerGrid(Character::Player4Grid);
					Character::RenderPlayerGrid(Character::Player5Grid);
					break;

				case 3:
					//SAFEGRID (BOTTOM SAFE)
					Character::RenderPlayerGrid(Character::Player1Grid);
					Character::RenderPlayerGrid(Character::Player2Grid);
					Character::RenderPlayerGrid(Character::Player3Grid);
					Character::RenderPlayerGrid(Character::Player5Grid);
					break;
				}
			}
		}

		void RenderPlayerHealth()
		{
			char strBufferHealth[100];
			char strBuffer[100];
			memset(strBufferHealth, 0, 100 * sizeof(char));
			sprintf_s(strBufferHealth, "Player Health:  %d", playerstats->health);

			char strBufferLevel[100];
			memset(strBufferLevel, 0, 100 * sizeof(char));
			sprintf_s(strBufferLevel, "Level: %d", playerstats->PlayerLevel);

			char strBufferStatus[100];
			memset(strBufferStatus, 0, 100 * sizeof(char));

			switch (playerstats->status)
			{
			case FROSTED:
				sprintf_s(strBufferStatus, "Status: Frosted");
				break;
			case FROZEN:
				sprintf_s(strBufferStatus, "Status: Frozen");
				break;
			case NEUTRAL:
				sprintf_s(strBufferStatus, "Status: Normal");
				break;
			}

			if (playercurrhealth != nullptr) {
				AEGfxMeshFree(playercurrhealth);
				playercurrhealth = nullptr;
			}

			float healthscale = (float)playerstats->health / playerstats->maxhealth;

			AEGfxMeshStart();

			AEGfxTriAdd(
				-390.0f, -290.0f, 0xFFFFFFFF, 0.0f, 1.0f,
				-390.0f, -265.0f, 0xFFFFFFFF, 0.0f, 1.0f,
				-390.0f + 160 * healthscale, -265.0f, 0xFFFFFFFF, 0.0f, 1.0f);

			AEGfxTriAdd(
				-390.0f + 160 * healthscale, -265.0f, 0xFFFFFFFF, 0.0f, 1.0f,
				-390.0f + 160 * healthscale, -290.0f, 0xFFFFFFFF, 0.0f, 1.0f,
				-390.0f, -290.0f, 0xFFFFFFFF, 0.0f, 1.0f);

			playercurrhealth = AEGfxMeshEnd();
			AE_ASSERT_MESG(playercurrhealth, "Failed to create playercurrhealth!!");

			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxSetTintColor(0.9f, 0.0f, 0.0f, 1.0f);
			AEGfxSetPosition(0.0f, 0.0f);
			AEGfxTextureSet(NULL, 0, 0);
			AEGfxMeshDraw(playercurrhealth, AE_GFX_MDM_TRIANGLES);
			AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxPrint(fontId, strBufferHealth, -0.95f, -0.95f, 1.0f, 1.f, 1.f, 1.f);
			AEGfxPrint(fontId, strBufferLevel, -0.95f, -0.85f, 1.0f, 1.f, 1.f, 1.f);
			AEGfxPrint(fontId, strBufferStatus, -0.95f, -0.75f, 1.0f, 1.f, 1.f, 1.f);
			sprintf_s(strBuffer, "Stamina: %d", playerstats->staminacount);
			AEGfxPrint(fontId, strBuffer, -0.10f, -0.80f, 1.14f, 1.0f, 1.0f, 1.0f);
			AEGfxSetBlendMode(AE_GFX_BM_NONE);

		}
	}

	/******************************************************
	*
	* ENEMY NAMESPACE
	*
	*******************************************************/
	namespace Enemies
	{

		AEGfxVertexList* EnemyGridIdle = 0;
		AEGfxVertexList* EnemyGridAttack = 0;
		AEGfxVertexList* EnemyMesh = 0;
		AEGfxVertexList* Enemymaxhealth = 0;
		AEGfxVertexList* Enemycurrhealth = 0;

		enum EnemyPos { IDLE, ATTACKING };
		enum ENEMY_TYPE { NORMAL, ICE, FIRE };


		namespace
		{


			void EnemyTypeCheckToApplyPlayerDebuff()
			{

				switch (enemystats->EnemyType)
				{
				case ICE:
					++enemystats->DebuffCounter;
					if (playerstats->status != Character::FROZEN)
					{
						playerstats->status = Character::FROSTED;
					}
					if (enemystats->DebuffCounter == 3 && playerstats->status == Character::FROSTED)
					{
						playerstats->status = Character::FROZEN;
						Character::counter = 21;
						enemystats->DebuffCounter = 0;
					}
					break;
				case NORMAL:
					break;
				}
			}

			void EnemyAttackState()
			{
				playerstats->SAFEGRID = enemystats->EnemyGrid;
				enemystats->EnemyState = ATTACKING;
				enemystats->is_attacking = true;

				//Movement to Attack Grid
				if (enemystats->positionX != 150.0f)
				{
					enemystats->positionX += 10.0f;
				}
				if (enemystats->EnemyState == ATTACKING && enemystats->is_attacking == true)
				{
					//Delay before enemy attack
					enemystats->AttackCD -= DT;
					if (enemystats->AttackCD <= 0.0f)
					{
						if (playerstats->positionID != playerstats->SAFEGRID)
						{
							playerstats->health -= enemystats->damage;
							EnemyTypeCheckToApplyPlayerDebuff();
						}

						//Resets Everything such as Enemy Cooldown while in idle
						//Sets the AttackCD for the next attack phase
						//Sets the next safe grid for next attack
						enemystats->AttackCD = 0.60f;
						enemystats->EnemyCD = static_cast<float>((rand() % 4) + 1);
						enemystats->EnemyGrid = (rand() % 3) + 1;
						enemystats->DamageCD = 1.0f;
					}
				}
			}

			void EnemyIdleState()
			{
				//Idle state and reducing of enemyCD to next attack
				//DamageCD is for frames where player cannot attack the enemy as enemy
				//is returning to idle state
				enemystats->EnemyState = IDLE;
				enemystats->is_attacking = false;
				enemystats->positionX = 0.0f;
				enemystats->positionY = 0.0f;
				enemystats->EnemyCD -= DT;
				enemystats->DamageCD -= DT;
				if (enemystats->EnemyState == IDLE && enemystats->is_attacking == false)
				{
					//Check for Player Damage
					if (playerstats->is_attacking == true && enemystats->DamageCD <= 0.0f)
					{
						enemystats->health -= playerstats->damage;
						playerstats->is_attacking = false;
					}
				}
			}
		}
			void ChoosingEnemyType(float RNG) {

				switch ((int)RNG)
				{
				case 0:
					enemystats->EnemyType = NORMAL;
					enemystats->health = 40;
					enemystats->maxhealth = 40;
					enemystats->damage = 10;
					enemystats->EnemyCD = 3.0f;				//Cooldown till next enemy attack
					enemystats->EnemyXP = 20;
					break;
				case 1:
					enemystats->EnemyType = ICE;
					enemystats->health = 50;
					enemystats->maxhealth = 50;
					enemystats->damage = 35;
					enemystats->EnemyCD = 3.0f;				//Cooldown till next enemy attack
					enemystats->DebuffCounter = 0;
					enemystats->EnemyXP = 50;
					break;
				}
			}

		//Main Update loop for Idle and Attack States of Enemy
		void UpdateEnemyState()
		{
			if (enemystats->EnemyCD <= 0.0f)
			{
				EnemyAttackState();
			}
			else
			{
				EnemyIdleState();
			}
		}

		void EnemyCombatMesh()
		{
			FreeEnemyMesh();													//deletes old mesh

			AEGfxMeshStart();

			AEGfxVertexAdd(50.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);
			AEGfxVertexAdd(150.0f, -50.0f, 0xFFFFFF, 1.0f, 1.0f);
			AEGfxVertexAdd(150.0f, 50.0f, 0xFF0000, 0.0f, 0.0f);				//ENEMYGRID IDLE
			AEGfxVertexAdd(50.0f, 50.0f, 0xFFFFFF, 1.0f, 0.0f);
			AEGfxVertexAdd(50.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);

			EnemyGridIdle = AEGfxMeshEnd();
			AE_ASSERT_MESG(EnemyGridIdle, "Failed to create enemygrididle!!");


			AEGfxMeshStart();

			AEGfxVertexAdd(200.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);
			AEGfxVertexAdd(300.0f, -50.0f, 0xFFFFFF, 1.0f, 1.0f);
			AEGfxVertexAdd(300.0f, 50.0f, 0xFF0000, 0.0f, 0.0f);				//ENEMYGRID ATTACK
			AEGfxVertexAdd(200.0f, 50.0f, 0xFFFFFF, 1.0f, 0.0f);
			AEGfxVertexAdd(200.0f, -50.0f, 0xFF0000, 0.0f, 1.0f);

			EnemyGridAttack = AEGfxMeshEnd();
			AE_ASSERT_MESG(EnemyGridAttack, "Failed to create enemygridattack!!");

			//AEGfxVertexAdd(75.0f, -25.0f, 0xFFFFFF, 0.0f, 1.0f);
			//AEGfxVertexAdd(125.0f, -25.0f, 0xFFFFFF, 1.0f, 1.0f);
			//AEGfxVertexAdd(125.0f, 25.0f, 0xFFFFFF, 0.0f, 0.0f);				//ENEMY MESH
			//AEGfxVertexAdd(75.0f, 25.0f, 0xFFFFFF, 1.0f, 0.0f);
			//AEGfxVertexAdd(75.0f, -25.0f, 0xFFFFFF, 0.0f, 1.0f);

			AEGfxMeshStart();

			AEGfxTriAdd(
				70.0f, -30.0f, 0x00FF00FF, 0.0f, 1.0f,
				130.0f, -30.0f, 0x00FFFF00, 1.0f, 1.0f,
				70.0f, 30.0f, 0x0000FFFF, 0.0f, 0.0f);
			//x,y,colour,u,v

			AEGfxTriAdd(
				130.0f, -30.0f, 0x00FFFFFF, 1.0f, 1.0f,
				130.0f, 30.0f, 0x00FFFFFF, 1.0f, 0.0f,
				70.0f, 30.0f, 0x00FFFFFF, 0.0f, 0.0f);

			EnemyMesh = AEGfxMeshEnd();
			AE_ASSERT_MESG(EnemyMesh, "Failed to create enemyMesh!!");
		}

		void RenderEnemyGrid(AEGfxVertexList* EnemyMesh)
		{
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			// Set position for object 1
			AEGfxSetPosition(0.0f, 0.0f);
			// No texture for object 1
			AEGfxTextureSet(NULL, 0, 0);

			AEGfxMeshDraw(EnemyMesh, AE_GFX_MDM_LINES_STRIP);
		}

		void FreeEnemyMesh()
		{

			if (EnemyGridIdle != nullptr) {
				AEGfxMeshFree(EnemyGridIdle);
				EnemyGridIdle = nullptr;
			}

			if (EnemyGridAttack != nullptr) {
				AEGfxMeshFree(EnemyGridAttack);
				EnemyGridAttack = nullptr;
			}

			if (EnemyMesh != nullptr) {
				AEGfxMeshFree(EnemyMesh);
				EnemyMesh = nullptr;
			}

			if (Enemycurrhealth != nullptr) {
				AEGfxMeshFree(Enemycurrhealth);
				Enemycurrhealth = nullptr;
			}
		}


		void RenderEnemy(AEGfxTexture* enemytexture, AEGfxVertexList* EnemyMesh)
		{
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			// Set position for object 1
			AEGfxSetPosition(enemystats->positionX, enemystats->positionY);
			AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
			// No texture for object 1;
			AEGfxTextureSet(enemytexture, 1.0f, 1.0f);
			AEGfxMeshDraw(EnemyMesh, AE_GFX_MDM_TRIANGLES);
		}

		void RenderEnemyHealth()
		{
			char strBufferHealth[100];
			//char strBuffer[100];
			memset(strBufferHealth, 0, 100 * sizeof(char));
			sprintf_s(strBufferHealth, "Enemy Health:  %d", enemystats->health);

			char strBufferLevel[100];
			memset(strBufferLevel, 0, 100 * sizeof(char));
			sprintf_s(strBufferLevel, "Level: %d", enemystats->EnemyLevel);

			char strBufferType[100];
			memset(strBufferType, 0, 100 * sizeof(char));
			switch (enemystats->EnemyType)
			{
			case NORMAL:
				sprintf_s(strBufferType, "Enemy Type: Normal");
				break;
			case ICE:
				sprintf_s(strBufferType, "Enemy Type: Frost");
				break;
			}

		float healthscale = (float)enemystats->health / enemystats->maxhealth;


			if (Enemycurrhealth != nullptr) {
				AEGfxMeshFree(Enemycurrhealth);
				Enemycurrhealth = nullptr;
			}

		AEGfxMeshStart();
		AEGfxTriAdd(
			230.0f, -290.0f, 0xFFFFFFFF, 0.0f, 1.0f,
			230.0f, -265.0f, 0xFFFFFFFF, 0.0f, 1.0f,
			230.0f + 160 * healthscale, -265.0f, 0xFFFFFFFF, 0.0f, 1.0f);

		AEGfxTriAdd(
			230.0f + 160 * healthscale, -265.0f, 0xFFFFFFFF, 0.0f, 1.0f,
			230.0f + 160 * healthscale, -290.0f, 0xFFFFFFFF, 0.0f, 1.0f,
			230.0f, -290.0f, 0xFFFFFFFF, 0.0f, 1.0f);

			Enemycurrhealth = AEGfxMeshEnd();
			AE_ASSERT_MESG(Enemycurrhealth, "Failed to create Enemycurrhealth!!");

			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
			AEGfxSetTintColor(0.9f, 0.0f, 0.0f, 1.0f);
			AEGfxSetPosition(0.0f, 0.0f);
			AEGfxTextureSet(NULL, 0, 0);
			AEGfxMeshDraw(Enemycurrhealth, AE_GFX_MDM_TRIANGLES);
			AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
      
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxPrint(fontId, strBufferHealth, 0.60f, -0.95f, 1.0f, 1.f, 1.f, 1.f);
			AEGfxPrint(fontId, strBufferLevel, 0.60f, -0.85f, 1.0f, 1.f, 1.f, 1.f);
			AEGfxPrint(fontId, strBufferType, 0.60f, -0.75f, 1.0f, 1.f, 1.f, 1.f);
			AEGfxSetBlendMode(AE_GFX_BM_NONE);
		}
	}
}