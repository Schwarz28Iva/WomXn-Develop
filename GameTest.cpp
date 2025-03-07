//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include<cstdlib>
//------------------------------------------------------------------------
#include "app\app.h"


#include <iostream>
using std::cerr;
using std::endl;
#include <fstream>
using std::ofstream;
#include <cstdlib> // for exit function
#include <time.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

//#include "Entities.h"
//------------------------------------------------------------------------
typedef struct JUMP_STATE {
	bool inJump;
	int jump_dur;
	int jump_restriction;
} jump_state;

CSimpleSprite* testSprite;
CSimpleSprite* healthSprite = nullptr;
CSimpleSprite* nohealthSprite;
CSimpleSprite* backgroundSprite1;
CSimpleSprite* backgroundSprite2;
CSimpleSprite* groundSprite;
CSimpleSprite* groundSprite2;
CSimpleSprite* animal_attackSprite;
CSimpleSprite* animal_attackSprite2;
CSimpleSprite* startmenuSprite;
CSimpleSprite* mythmenuSprite;
CSimpleSprite* storymenuSprite;
CSimpleSprite* leadermenuSprite;
CSimpleSprite* guidemenuSprite;
CSimpleSprite* mythSprite;
CSimpleSprite* storySprite;
CSimpleSprite* leaderSprite;
CSimpleSprite* guideSprite;
CSimpleSprite* resumeSprite;
CSimpleSprite* restartSprite;
CSimpleSprite* apolloSprite;
CSimpleSprite* aresSprite;
CSimpleSprite* objects[10];
CSimpleSprite* monsters[10];
CSimpleSprite* shadows[30];
CSimpleSprite* apollo_avSprite;
CSimpleSprite* ares_avSprite;
CSimpleSprite* sunSprite;
CSimpleSprite* swordSprite;
CSimpleSprite* heartSprite;

int objectsCounter = 0;
int shadow1Counter = 0, shadow2Counter = 10, shadow3Counter = 20;
int damageTimer = 30;
int monsterCounter = 0;
int j, j2, j3;
int aresFlag = 0;
int aresCounter = 0;
float xa, ya = 200;
int congratflag = 0;
float xo, yo;
float xb1, yb1, xb2, yb2, xg1, yg1, xg2, yg2;

enum
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
	ANIM_HEALTH6,
	ANIM_HEALTH5,
	ANIM_HEALTH4,
	ANIM_HEALTH3,
	ANIM_HEALTH2,
	ANIM_HEALTH1,
	ANIM_ANIMAL,
	ANIM_ANIMALATTACK,
	ANIM_SUN
};
enum GameState
{
	inMenu,
	inGame,
	inMyth,
	inStory,
	inLeader,
	inGuide,
	pause
};

enum inMenuOp
{
	start,
	myth,
	story,
	leaderboard,
	guide
};

jump_state state, kick;
bool obstacleFlag = 0;
int obstacleCounter = 0;
bool obstacleSpawned = 0;
int nr_hearts = 6;
GameState gs = inMenu;
inMenuOp imo = start;
int nr_imo = 0;
int nr_imo2 = 0;
bool k2 = 0;
bool k = 0;
float xc, yc;
int powerup_Ares = 0;
int powerup_Apollo = 0;
int game_time = 0;
int game_score = 0;
int suntimer = 0;
int leaderflag = 0;
int game_time_seconds = 0;
int score[5], aux;
int heartFlag = 0, heartCounter;
int heartCollided = 0;
float customScore = 0;

void updateLeaderBoard()
{
	congratflag = 0;
	leaderflag = 0;
	if (score[0] < (int)customScore)
	{
		score[0] = (int)customScore;
		congratflag = 1;
	}
	else
		if (score[1] < (int)customScore)
		{
			score[1] = (int)customScore;
			congratflag = 1;
		}
		else
			if (score[2] < (int)customScore)
			{
				score[2] = (int)customScore;
				congratflag = 1;
			}
			else
				if (score[3] < (int)customScore)
				{
					score[3] = (int)customScore;
					congratflag = 1;
				}
				else
					if (score[4] < (int)customScore)
					{
						score[4] = (int)customScore;
						congratflag = 1;
					}

	for (int i = 0; i < 5; i++)
		for (int j = i; j < 5; j++)
		{
			if (score[i] > score[j])
			{
				aux = score[i];
				score[i] = score[j];
				score[j] = aux;
			}
		}
	ofstream fout("leaderfile.txt");
	for (int i = 0; i < 5; i++)
	{
		fout << score[i] << endl;
	}
}

void environmentMovement()
{
	animal_attackSprite2->GetPosition(xo, yo);
	xo = xo - 7;
	animal_attackSprite2->SetPosition(xo, yo);
	animal_attackSprite->GetPosition(xo, yo);
	xo = xo - 7;
	animal_attackSprite->SetPosition(xo, yo);
	if (powerup_Ares == 10)
	{
		ares_avSprite->SetPosition(180.0f, 650.0f);
		aresSprite->SetPosition(-500.0f, 650.0f);
	}
	if (aresFlag == 1)
	{
		swordSprite->GetPosition(xa, ya);
		if (ya > 200)
		{
			swordSprite->GetPosition(xa, ya);
			ya = ya - 5;
			swordSprite->SetPosition(xa, ya);
		}
	}
	backgroundSprite1->GetPosition(xb1, yb1);
	xb1 -= 3.0f;
	backgroundSprite2->GetPosition(xb2, yb2);
	xb2 -= 3.0f;
	groundSprite->GetPosition(xg1, yg1);
	groundSprite2->GetPosition(xg2, yg2);
	xg1 -= 3.0f;
	xg2 -= 3.0f;
	groundSprite->SetPosition(xg1, yg1);
	groundSprite2->SetPosition(xg2, yg2);
	backgroundSprite2->SetPosition(xb2, yb2);
	backgroundSprite1->SetPosition(xb1, yb1);
	if (xg1 <= -509.0f)
	{
		groundSprite->SetPosition(1536.0f, 100.0f);
		groundSprite2->SetPosition(512.0f, 100.0f);
	}
	if (xg2 <= -509.0f)
	{
		groundSprite2->SetPosition(1536.0f, 100.0f);
		groundSprite->SetPosition(512.0f, 100.0f);
	}
	if (xb1 <= -509.0f)
	{
		backgroundSprite1->SetPosition(1536.0f, 483.5f);
		backgroundSprite2->SetPosition(512.0f, 483.5f);
	}
	if (xb2 <= -509.0f)
	{
		backgroundSprite2->SetPosition(1536.0f, 483.5f);
		backgroundSprite1->SetPosition(512.0f, 483.5f);
	}
}

void healthDropEvent(int al)
{
	if (al == 0)
		nr_hearts--;
	else
		if(nr_hearts<=5 && al==1)
			nr_hearts++;
	switch (nr_hearts)
	{
	case 6:	healthSprite->SetAnimation(ANIM_HEALTH6);
		break;
	case 5: healthSprite->SetAnimation(ANIM_HEALTH5);
		break;
	case 4: healthSprite->SetAnimation(ANIM_HEALTH4);
		break;
	case 3: healthSprite->SetAnimation(ANIM_HEALTH3);
		break;
	case 2: healthSprite->SetAnimation(ANIM_HEALTH2);
		break;
	case 1: healthSprite->SetAnimation(ANIM_HEALTH1);
		break;
	case 0:
	{
		delete healthSprite;
		nohealthSprite->SetPosition(105.0f, 735.0f);
		gs = inLeader;
		leaderflag = 1;
		break;
	}
	default: //nohealthSprite->SetPosition(105.0f, 735.0f);
		break;
	}
}

void heartCollision()
{
	heartSprite->GetPosition(xo, yo);
	testSprite->GetPosition(xc, yc);
	if (xc - xo <50 && xc-xo>-50 && yc - yo <50 && yc - yo>-50 && heartCollided==0)
	{
		healthDropEvent(1);
		heartCollided = 1;
		heartSprite->SetPosition(-500, -500);
	}
}

void rockCollision()
{
	for (int i = 0; i < 10; i++)
	{
		objects[i]->GetPosition(xo, yo);
		if (xo > 70 && xo < 170 && yc - yo < 50 && k == 0)
		{

			testSprite->SetAnimation(ANIM_BACKWARDS);
			//App::PlaySound(".\\TestData\\hurt_avatar.wav");
			k = 1;
			healthDropEvent(0);

		}

	}
}

void monsterCollision()
{
	for (int i = 0; i < 10; i++)
	{
		monsters[i]->GetPosition(xo, yo);
		if (xo > 80 && xo < 150 && k2 == 0 && kick.inJump == 0)
		{

			testSprite->SetAnimation(ANIM_BACKWARDS);
			//App::PlaySound(".\\TestData\\hurt_avatar.wav");
			k2 = 1;
			animal_attackSprite2->SetPosition(xo, yo);
			healthDropEvent(0);

		}
		else
		{
			if (xo > 80 && xo < 150 && k2 == 0 && kick.inJump == 1)
			{
				customScore = customScore + 5;
				monsters[i]->SetPosition(-500, 0);
				animal_attackSprite->SetPosition(xo, yo);
				//App::PlaySound(".\\TestData\\hurt_cerberus.wav");
				if (powerup_Ares < 10)
					powerup_Ares++;
			}
		}
	}
}

bool damageCooldown(bool damageFlag)
{
	if (damageFlag == 1)
	{
		damageTimer--;
	}
	if (damageTimer == 0)
	{
		damageTimer = 30;
		damageFlag = 0;
	}
	return damageFlag;
}

void kickF()
{
	kick.jump_dur++;
	testSprite->SetAngle(testSprite->GetAngle() - 0.25132f);
	if (kick.jump_dur == 25) // k e cat de mult dureaza saritura
	{
		kick.jump_dur = 0;
		kick.jump_restriction = 5; //k2 intervalul dintre doua sarituri
	}
}

void jumpF()
{
	state.jump_dur++;
	float x, y;
	testSprite->GetPosition(x, y);
	if (state.jump_dur > 20)
		y = y - 10;//+-10 este in ex asta cat de mult se sare
	else
		y = y + 10;
	testSprite->SetPosition(x, y);
	if (state.jump_dur == 40) // k e cat de mult dureaza saritura
	{
		state.jump_dur = 0;
		state.jump_restriction = 5; //k2 intervalul dintre doua sarituri
	}
}

void checkAresPowerup()
{
	if (powerup_Ares == 10)
	{
		ares_avSprite->SetPosition(180.0f, 650.0f);
		aresSprite->SetPosition(-500.0f, 650.0f);
	}

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_RIGHT_SHOULDER, true) && powerup_Ares == 10)
	{
		powerup_Ares = 0;
		aresSprite->SetPosition(180.0f, 650.0f);
		ares_avSprite->SetPosition(-500.0f, 650.0f);
		aresFlag = 1;
		swordSprite->SetPosition(500, 500);
		aresCounter = 600;
		customScore = customScore + 30;
	}
	if (aresFlag == 1)
	{
		swordSprite->GetPosition(xa, ya);
		if (ya > 200)
		{
			swordSprite->GetPosition(xa, ya);
			ya = ya - 5;
			swordSprite->SetPosition(xa, ya);
		}
	}
	if (aresFlag == 1 && aresCounter >= 0 && ya <= 200)
	{
		aresCounter = aresCounter - 1;
		for (int i = 0; i < 10; i++)
		{
			monsters[i]->GetPosition(xo, yo);
			if (xo <= 500)
			{
				monsters[i]->SetPosition(-500, -500);
			}
			objects[i]->GetPosition(xo, yo);
			if (xo <= 500)
			{
				objects[i]->SetPosition(-500, -500);
			}
		}
		for (int i = 0; i < 30; i++)
		{
			shadows[i]->GetPosition(xo, yo);
			if (xo <= 500)
			{
				shadows[i]->SetPosition(-500, -500);
			}
		}

	}
	else
	{
		if (aresCounter < 0)
		{
			aresFlag = 0;
			swordSprite->SetPosition(-500, -500);
		}
	}
	if (aresFlag == 1 && aresCounter >= 0 && ya <= 200)
	{
		aresCounter = aresCounter - 1;
		for (int i = 0; i < 10; i++)
		{
			monsters[i]->GetPosition(xo, yo);
			if (xo <= 500)
			{
				monsters[i]->SetPosition(-500, -500);
			}
			objects[i]->GetPosition(xo, yo);
			if (xo <= 500)
			{
				objects[i]->SetPosition(-500, -500);
			}
		}
		for (int i = 0; i < 30; i++)
		{
			shadows[i]->GetPosition(xo, yo);
			if (xo <= 500)
			{
				shadows[i]->SetPosition(-500, -500);
			}
		}

	}
	else
	{
		if (aresCounter < 0)
		{
			aresFlag = 0;
			swordSprite->SetPosition(-500, -500);
		}
	}


}

void checkApolloPowerup()
{
	if (powerup_Apollo == 10)
	{
		apollo_avSprite->SetPosition(85.0f, 650.0f);
		apolloSprite->SetPosition(-500.0f, 650.0f);
	}

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_LEFT_SHOULDER, true) && powerup_Apollo == 10)
	{
		powerup_Apollo = 0;
		apolloSprite->SetPosition(85.0f, 650.0f);
		apollo_avSprite->SetPosition(-500.0f, 650.0f);
		suntimer = 500;
		sunSprite->SetPosition(-50, 530.0f);
		customScore = customScore + 30;
	}

	sunSprite->GetPosition(xo, yo);
	if (suntimer != 0)
		suntimer = suntimer - 1;
	else sunSprite->SetPosition(-500.0f, 530.0f);
	if (suntimer > 0 && suntimer % 5 == 0)
	{
		sunSprite->GetPosition(xb1, yb1);
		if (suntimer > 250)
			xb1 = xb1 + 5;
		else
			xb1 = xb1 - 5;
		sunSprite->SetPosition(xb1, 530.0f);
	}

}

void teleport()
{

	int min = 3000;

	int moveBy;

	float x1, y1, x2, y2;

		for (int i = 0; i < 30; i++)
		{
			shadows[i]->GetPosition(x1, y1);
			if (x1 > 100 && x1 < min)
			{
				min = x1;
				j = i;
			}
		}
		j2 = -1;
		j3 = -1;
		shadows[j]->GetPosition(x1, y1);
		for (int i = 0; i < 10; i++)
		{
			monsters[i]->GetPosition(x2, y2);
			if (x2 == x1)
			{
				j2 = i;
				break;
			}
			objects[i]->GetPosition(x2, y2);
			if (x2 == x1)
			{
				j3 = i;
				break;
			}
		}
		if (j3 == -1) //umbra e sub monstru
		{
			if (j >= 0 && j < 10)
			{
				moveBy = x1 - 70;
			}
			if (j >= 10 && j < 20)
			{
				moveBy = x1 - 91;
			}
			if (j >= 20 && j < 30)
			{
				moveBy = x1 - 200;
			}
		}
		else //umbra e sub piatra
		{
			if (j >= 0 && j < 10)
			{
				moveBy = x1 - 70;
			}
			if (j >= 10 && j < 20)
			{
				moveBy = x1 + 100;
			}
			if (j >= 20 && j < 30)
			{
				moveBy = x1 - 90;
			}
		}
		if (moveBy < 10 || moveBy>1000)
			moveBy = 0;
		if (powerup_Apollo < 10 && moveBy != 0)
			powerup_Apollo++;
		if (moveBy != 0)
			customScore = customScore + 10;
		for (int i = 0; i < 10; i++)
		{
			objects[i]->GetPosition(x2, y2);
			objects[i]->SetPosition(x2 - moveBy, y2);
		}
		for (int i = 0; i < 10; i++)
		{
			monsters[i]->GetPosition(x2, y2);
			monsters[i]->SetPosition(x2 - moveBy, y2);
		}
		for (int i = 0; i < 30; i++)
		{
			shadows[i]->GetPosition(x2, y2);
			shadows[i]->SetPosition(x2 - moveBy, y2);
		}

		backgroundSprite1->GetPosition(x2, y2);
		backgroundSprite2->GetPosition(x1, y1);
		if (x2 > x1)
		{
			if (moveBy >= 509.0f + x1)
			{
				backgroundSprite1->SetPosition(x2 - 509.0f - x1, y2);
				backgroundSprite2->SetPosition(-509.0f, y1);
			}
			else {
				backgroundSprite1->SetPosition(x2 - moveBy, y2);
				backgroundSprite2->SetPosition(x1 - moveBy, y1);
			}
		}
		else {

			if (moveBy >= 509.0f + x2)
			{
				backgroundSprite1->SetPosition(-509.0f, yc);
				backgroundSprite2->SetPosition(xo - 509.0f - x2, y1);
			}
			else {
				backgroundSprite1->SetPosition(x2 - moveBy, y2);
				backgroundSprite2->SetPosition(x1 - moveBy, y1);
			}
		}

	

}

void obstacleSpawner()
{
	int shadowType, objectType;
	if (objectsCounter == 10)
		objectsCounter = 0;
	if (monsterCounter == 10)
		monsterCounter = 0;
	if (shadow1Counter == 10)
		shadow1Counter = 0;
	if (shadow2Counter == 20)
		shadow2Counter = 10;
	if (shadow3Counter == 30)
		shadow3Counter = 20;
	if (heartFlag == 0) 
	{
		heartCounter = rand() % 1000 + 800;
		heartFlag = 1;
	}
	if (heartFlag == 1)
	{
		if (heartCounter > 0)
			heartCounter--;
		else
		{
			heartFlag = 0;
			heartSprite->SetPosition(1500.0f, 400.0f);
			heartCollided = 0;
		}
	}
	if (obstacleFlag == 0) //obstacleFlag =1 daca s a pornit counterul de spawn
	{
		obstacleCounter = rand() % 200 + 30;
		obstacleFlag = 1;
	}
	if (obstacleFlag == 1)
	{
		if (obstacleCounter > 0)
			obstacleCounter--;
		else
		{
			obstacleFlag = 0;
			objectType = rand() % 2;
			switch (objectType)
			{
			case 0:
				objects[objectsCounter]->SetPosition(1500.0f, 230.0f);
				objectsCounter++;
				break;
			case 1:
				monsters[monsterCounter]->SetPosition(1500.0f, 230.0f);
				monsterCounter++;
				break;
			}
			shadowType = rand() % 3;
			if (suntimer > 0)
				shadowType = 0;
			switch (shadowType)
			{
			case 0:
				shadows[shadow1Counter]->SetPosition(1500.0f, 150.0f);
				shadow1Counter++;
				break;
			case 1:
				shadows[shadow2Counter]->SetPosition(1500.0f, 150.0f);
				shadow2Counter++;
				break;
			case 2:
				shadows[shadow3Counter]->SetPosition(1500.0f, 150.0f);
				shadow3Counter++;
				break;
			}
			obstacleSpawned = 1;//flag for if object is spawned

		}
	}
	for (int i = 0; i < 10; i++)
	{
		objects[i]->GetPosition(xo, yo);
		xo -= 7.0f;
		objects[i]->SetPosition(xo, yo);
		monsters[i]->GetPosition(xo, yo);
		xo -= 7.0f;
		monsters[i]->SetPosition(xo, yo);
	}
	for (int i = 0; i < 30; i++)
	{
		shadows[i]->GetPosition(xo, yo);
		xo -= 7.0f;
		shadows[i]->SetPosition(xo, yo);
	}
	heartSprite->GetPosition(xo, yo);
	xo -= 7.0f;
	heartSprite->SetPosition(xo, yo);
}

void Init()
{
	customScore = 0;
	srand(time(NULL));
	obstacleFlag = 0;
	obstacleCounter = 0;
	obstacleSpawned = 0;
	nr_hearts = 6;
	GameState gs = inMenu;
	inMenuOp imo = start;
	int nr_imo = 0;
	bool k2 = 0;
	bool k = 0;
	objectsCounter = 0;
	shadow1Counter = 0;
	shadow2Counter = 10;
	shadow3Counter = 20;
	damageTimer = 30;
	monsterCounter = 0;
	state.inJump = 0;
	state.jump_dur = 0;
	state.jump_restriction = 0;
	kick.inJump = 0;
	kick.jump_dur = 0;
	kick.jump_restriction = 0;

	powerup_Ares = 0;
	powerup_Apollo = 0;
	game_time = 0;
	game_score = 0;
	suntimer = 0;

	testSprite = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4);
	testSprite->SetPosition(100.0f, 250.0f);

	for (int i = 0; i < 30; i++)
	{
		if (i >= 0 && i < 10)
			shadows[i] = App::CreateSprite(".\\TestData\\shadow1.bmp", 1, 1);
		if (i >= 10 && i < 20)
			shadows[i] = App::CreateSprite(".\\TestData\\shadow2.bmp", 1, 1);
		if (i >= 20 && i < 30)
			shadows[i] = App::CreateSprite(".\\TestData\\shadow3.bmp", 1, 1);
		shadows[i]->SetScale(0.5f);
		shadows[i]->SetPosition(-500.0f, 350.0f);
	}

	animal_attackSprite2 = App::CreateSprite(".\\TestData\\cerberus_attack.bmp", 7, 1);
	animal_attackSprite2->SetPosition(-500.0f, 350.0f);
	float speed5 = 1.0f / 5.0f;
	animal_attackSprite2->CreateAnimation(ANIM_ANIMALATTACK, speed5, { 6,5,4,3,2,1,0,1,2,3,4,5,6 });
	animal_attackSprite2->SetScale(2.0f);
	
	animal_attackSprite = App::CreateSprite(".\\TestData\\cerberus_dies.bmp", 5, 1);
	animal_attackSprite->SetPosition(-500.0f, 350.0f);
	animal_attackSprite->CreateAnimation(ANIM_ANIMALATTACK, speed5, { 4,3,2,1,0,1,2,3,4 });
	animal_attackSprite->SetScale(2.0f);

	healthSprite = App::CreateSprite(".\\TestData\\health.bmp", 1, 6);
	healthSprite->SetPosition(105.0f, 735.0f);
	healthSprite->SetScale(0.5f);
	float speed2 = 1.0f / 15.0f;
	healthSprite->CreateAnimation(ANIM_HEALTH6, speed2, { 5 });
	healthSprite->CreateAnimation(ANIM_HEALTH5, speed2, { 4 });
	healthSprite->CreateAnimation(ANIM_HEALTH4, speed2, { 3 });
	healthSprite->CreateAnimation(ANIM_HEALTH3, speed2, { 2 });
	healthSprite->CreateAnimation(ANIM_HEALTH2, speed2, { 1 });
	healthSprite->CreateAnimation(ANIM_HEALTH1, speed2, { 0 });
	healthSprite->SetAnimation(ANIM_HEALTH6);

	nohealthSprite = App::CreateSprite(".\\TestData\\nohealth.bmp", 1, 1);
	nohealthSprite->SetScale(0.5f);
	nohealthSprite->SetPosition(-105.0f, 705.0f);

	apolloSprite = App::CreateSprite(".\\TestData\\apollo_unav.bmp", 1, 1);
	apolloSprite->SetPosition(85.0f, 650.0f);
	apolloSprite->SetScale(0.4f);

	aresSprite = App::CreateSprite(".\\TestData\\ares_unav.bmp", 1, 1);
	aresSprite->SetPosition(180.0f, 650.0f);
	aresSprite->SetScale(0.4f);

	apollo_avSprite = App::CreateSprite(".\\TestData\\apollo_av.bmp", 1, 1);
	apollo_avSprite->SetPosition(-500.0f, 650.0f);
	apollo_avSprite->SetScale(0.4f);

	sunSprite = App::CreateSprite(".\\TestData\\sun.bmp", 2, 1);
	float speed4 = 1.0f / 15.0f;
	sunSprite->CreateAnimation(ANIM_SUN, speed4, { 0,1 });
	sunSprite->SetPosition(-500.0f, 530.0f);
	sunSprite->SetScale(0.45f);

	swordSprite = App::CreateSprite(".\\TestData\\sword.bmp", 1, 1);
	swordSprite->SetPosition(-680.0f, 630.0f);
	swordSprite->SetScale(0.4f);

	ares_avSprite = App::CreateSprite(".\\TestData\\ares_av.bmp", 1, 1);
	ares_avSprite->SetPosition(-500.0f, 650.0f);
	ares_avSprite->SetScale(0.4f);

	heartSprite = App::CreateSprite(".\\TestData\\heart.bmp", 1, 1);
	heartSprite->SetPosition(-500.0f, 650.0f);
	heartSprite->SetScale(0.2f);

	for (int i = 0; i < 10; i++)
	{
		objects[i] = App::CreateSprite(".\\TestData\\rock.bmp", 1, 1);
		objects[i]->SetScale(0.5f);
		objects[i]->SetPosition(-500.0f, 350.0f);
	}
	for (int i = 0; i < 10; i++)
	{
		monsters[i] = App::CreateSprite(".\\TestData\\cerberus_waiting.bmp", 6, 1);
		monsters[i]->SetPosition(-400.0f, 350.0f);
		float speed3 = 1.0f / 8.0f;
		monsters[i]->CreateAnimation(ANIM_ANIMAL, speed3, { 5,4,3,2,1,0,1,2,3,4,5 });
		monsters[i]->SetScale(2.0f);
	}
	groundSprite = App::CreateSprite(".\\TestData\\groundresized3.bmp", 1, 1);
	groundSprite->SetPosition(512.0f, 100.0f);
	groundSprite->SetScale(2.0f);
	groundSprite2 = App::CreateSprite(".\\TestData\\groundresized3.bmp", 1, 1);
	groundSprite2->SetPosition(1536.0f, 100.0f);
	groundSprite2->SetScale(2.0f);

	backgroundSprite1 = App::CreateSprite(".\\TestData\\background1resized2.bmp", 1, 1);
	backgroundSprite1->SetPosition(512.0f, 483.5f);
	backgroundSprite1->SetScale(2.0f);
	backgroundSprite2 = App::CreateSprite(".\\TestData\\background2resized2.bmp", 1, 1);
	backgroundSprite2->SetPosition(1536.0f, 483.5f);
	backgroundSprite2->SetScale(2.0f);

	startmenuSprite = App::CreateSprite(".\\TestData\\startmenu_start.bmp", 1, 1);
	startmenuSprite->SetPosition(512.0f, 384.0f);
	startmenuSprite->SetScale(2.0f);

	mythmenuSprite = App::CreateSprite(".\\TestData\\startmenu_myth.bmp", 1, 1);
	mythmenuSprite->SetPosition(512.0f, 384.0f);
	mythmenuSprite->SetScale(2.0f);

	storymenuSprite = App::CreateSprite(".\\TestData\\startmenu_story.bmp", 1, 1);
	storymenuSprite->SetPosition(512.0f, 384.0f);
	storymenuSprite->SetScale(2.0f);

	leadermenuSprite = App::CreateSprite(".\\TestData\\startmenu_leader.bmp", 1, 1);
	leadermenuSprite->SetPosition(512.0f, 384.0f);
	leadermenuSprite->SetScale(2.0f);

	guidemenuSprite = App::CreateSprite(".\\TestData\\startmenu_guide.bmp", 1, 1);
	guidemenuSprite->SetPosition(512.0f, 384.0f);
	guidemenuSprite->SetScale(2.0f);

	mythSprite = App::CreateSprite(".\\TestData\\myth.bmp", 1, 1);
	mythSprite->SetPosition(-512.0f, 384.0f);
	mythSprite->SetScale(2.0f);

	storySprite = App::CreateSprite(".\\TestData\\story.bmp", 1, 1);
	storySprite->SetPosition(-512.0f, 384.0f);
	storySprite->SetScale(2.0f);

	leaderSprite = App::CreateSprite(".\\TestData\\leader.bmp", 1, 1);
	leaderSprite->SetPosition(-512.0f, 384.0f);
	leaderSprite->SetScale(2.0f);

	guideSprite = App::CreateSprite(".\\TestData\\controller.bmp", 1, 1);
	guideSprite->SetPosition(-512.0f, 384.0f);
	guideSprite->SetScale(2.0f);

	resumeSprite = App::CreateSprite(".\\TestData\\resume.bmp", 1, 1);
	resumeSprite->SetPosition(-512.0f, 384.0f);
	resumeSprite->SetScale(2.0f);

	restartSprite = App::CreateSprite(".\\TestData\\restart.bmp", 1, 1);
	restartSprite->SetPosition(-512.0f, 384.0f);
	restartSprite->SetScale(2.0f);

	float speed = 1.0f / 15.0f;
	testSprite->CreateAnimation(ANIM_BACKWARDS, speed, { 0,1,2,3,4,5,6,7 });
	testSprite->CreateAnimation(ANIM_RIGHT, speed, { 16,17,18,19,20,21,22,23 });
	testSprite->SetScale(2.0f);

}

void Update(float deltaTime)
{

	switch (gs)
	{
	case 0: 
	{

		Init();

		if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, true))
		{
			if (nr_imo == 0)
				nr_imo = 5;
			if (nr_imo > 0)
				nr_imo--;
		}

		if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, true))
		{
			if (nr_imo == 4)
				nr_imo = -1;
			if (nr_imo < 4)
				nr_imo++;
		}

		if (nr_imo == 0)
			imo = start;
		if (nr_imo == 1)
			imo = myth;
		if (nr_imo == 2)
			imo = story;
		if (nr_imo == 3)
			imo = leaderboard;
		if (nr_imo == 4)
			imo = guide;

		switch (imo)
		{
		case 0:
			if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
			{
				gs = inGame;
				startmenuSprite->Update(deltaTime);
				delete startmenuSprite;
				delete mythmenuSprite;
				delete storymenuSprite;
				delete leadermenuSprite;
				delete guidemenuSprite;
			}
			break;

		case 1:
			if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
			{
				gs = inMyth;
				startmenuSprite->Update(deltaTime);
				delete startmenuSprite;
				delete mythmenuSprite;
				delete storymenuSprite;
				delete leadermenuSprite;
				delete guidemenuSprite;
			}
			break;

		case 2:
			if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
			{
				gs = inStory;
				startmenuSprite->Update(deltaTime);
				delete startmenuSprite;
				delete mythmenuSprite;
				delete storymenuSprite;
				delete leadermenuSprite;
				delete guidemenuSprite;
			}
			break;

		case 3:
			if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
			{
				gs = inLeader;
				startmenuSprite->Update(deltaTime);
				delete startmenuSprite;
				delete mythmenuSprite;
				delete storymenuSprite;
				delete leadermenuSprite;
				delete guidemenuSprite;
			}
			break;

		case 4:
			if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
			{
				gs = inGuide;
				startmenuSprite->Update(deltaTime);
				delete startmenuSprite;
				delete mythmenuSprite;
				delete storymenuSprite;
				delete leadermenuSprite;
				delete guidemenuSprite;
			}
			break;

		default: break;

		}
		break;
	}
	case 1: 
	{
		testSprite->Update(deltaTime);
		healthSprite->Update(deltaTime);
		nohealthSprite->Update(deltaTime);
		apolloSprite->Update(deltaTime);
		aresSprite->Update(deltaTime);
		sunSprite->Update(deltaTime);
		swordSprite->Update(deltaTime);
		backgroundSprite1->Update(deltaTime);
		backgroundSprite2->Update(deltaTime);
		groundSprite->Update(deltaTime);
		groundSprite2->Update(deltaTime);
		testSprite->SetAnimation(ANIM_RIGHT);
		sunSprite->SetAnimation(ANIM_SUN);
		heartSprite->Update(deltaTime);
		animal_attackSprite2->Update(deltaTime);
		animal_attackSprite2->SetAnimation(ANIM_ANIMALATTACK);
		animal_attackSprite->Update(deltaTime);
		animal_attackSprite->SetAnimation(ANIM_ANIMALATTACK);

		game_time = game_time + deltaTime;
		customScore = customScore + deltaTime / 1000;

		for (int i = 0; i < 10; i++)
			objects[i]->Update(deltaTime);
		for (int i = 0; i < 30; i++)
			shadows[i]->Update(deltaTime);
		for (int i = 0; i < 10; i++)
		{
			monsters[i]->Update(deltaTime);
			monsters[i]->SetAnimation(ANIM_ANIMAL);
		}


		if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
		{
			teleport();
		}

		checkApolloPowerup();

		checkAresPowerup();

		obstacleSpawner();

		heartCollision();

		if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false) && state.inJump == 0 && state.jump_restriction == 0)
		{
			state.inJump = 1;
		}

		if (state.inJump == 1) //flag=1 rezulta suntem in timpul unei sarituri
		{
			jumpF();
		}

		if (state.inJump == 1 && state.jump_dur == 0)
		{
			state.inJump = 0;
		}

		if (state.jump_restriction > 0)
		{
			state.jump_restriction--;
		}


		if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true) && kick.inJump == 0 && kick.jump_restriction == 0)
		{
			kick.inJump = 1;
		}

		if (kick.inJump == 1) //flag=1 rezulta suntem in timpul unei sarituri
		{
			kickF();
		}

		if (kick.inJump == 1 && kick.jump_dur == 0)
		{
			kick.inJump = 0;
		}

		if (kick.jump_restriction > 0)
		{
			kick.jump_restriction--;
		}


		//Collision event
		testSprite->GetPosition(xc, yc);

		k = damageCooldown(k);

		rockCollision();

		k2 = damageCooldown(k2);

		monsterCollision();

		if (App::GetController().CheckButton(XINPUT_GAMEPAD_RIGHT_SHOULDER, true) && powerup_Ares == 10)
		{
			powerup_Ares = 0;
			aresSprite->SetPosition(180.0f, 650.0f);
			ares_avSprite->SetPosition(-500.0f, 650.0f);
			aresFlag = 1;
			swordSprite->SetPosition(500, 500);
			aresCounter = 600;
		}

		environmentMovement();

		//------------------------------------------------------------------------
		// Sample Sound.
		//------------------------------------------------------------------------
		/*
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
		{
			App::PlaySound(".\\TestData\\Test.wav");
		}*/
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
		{
			gs = pause;
			resumeSprite->SetPosition(512, 384);
		}

		break;
	}
	case 2:
	{
		Init();
		mythSprite->SetPosition(512, 384);
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
		{
			gs = inMenu;
			delete mythSprite;
		}
		break;
	}
	case 3:
	{
		Init();
		storySprite->SetPosition(512, 384);
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
		{
			gs = inMenu;
			delete storySprite;
		}
		break;
	}
	case 4:
	{
		Init();
		leaderSprite->SetPosition(512, 384);
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
		{
			gs = inMenu;
			delete leaderSprite;
		}
		break;
	}
	case 5:
	{
		Init();
		guideSprite->SetPosition(512, 384);
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
		{
			gs = inMenu;
			delete guideSprite;
		}
		break;
	}
	case 6:
	{

		if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, true))
		{
			if (nr_imo2 == 0)
				nr_imo2 = 2;
			if (nr_imo2 > 0)
				nr_imo2--;
		}
		restartSprite->SetPosition(-512.0f, 384.0f);
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, true))
		{
			if (nr_imo2 == 1)
				nr_imo2 = -1;
			if (nr_imo2 < 1)
				nr_imo2++;
		}
		switch (nr_imo2)
		{
		case 0:
			resumeSprite->SetPosition(512.0f, 384.0f);
			restartSprite->SetPosition(-512.0f, 384.0f);
			break;
		case 1:
			resumeSprite->SetPosition(-512.0f, 384.0f);
			restartSprite->SetPosition(512.0f, 384.0f);
			break;
		default:
			resumeSprite->SetPosition(512.0f, 384.0f);
			restartSprite->SetPosition(-512.0f, 384.0f);
			break;
		}
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true) && nr_imo2 == 0)
		{
			gs = inGame;
		}
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true) && nr_imo2 == 1)
		{
			Init();
			gs = inGame;
		}
		break;
	}
	default: {
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
		{
			gs = inGame;
			startmenuSprite->Update(deltaTime);
			delete startmenuSprite;
		}
	}
	}
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{

	switch (gs)
	{
	case 0: {
		switch (imo)
		{
		case 0:
		{
			startmenuSprite->Draw();
			break;
		}
		case 1:
			mythmenuSprite->Draw();
			break;
		case 2: storymenuSprite->Draw();
			break;
		case 3: leadermenuSprite->Draw();
			break;
		case 4: guidemenuSprite->Draw();
			break;
		default: startmenuSprite->Draw();
			break;
		}
	}
		  break;

	case 1: 
	{
		float r2 = 1.0f;
		float g2 = 1.0f;
		float b2 = 1.0f;

		float sx = 0;
		float sy = 200;
		float ex = 1024;
		float ey = 200;
		App::DrawLine(sx, sy, ex, ey, r2, g2, b2);

		backgroundSprite1->Draw();
		backgroundSprite2->Draw();
		groundSprite->Draw();
		groundSprite2->Draw();
		testSprite->Draw();
		healthSprite->Draw();
		nohealthSprite->Draw();
		apolloSprite->Draw();
		aresSprite->Draw();
		apollo_avSprite->Draw();
		ares_avSprite->Draw();
		sunSprite->Draw();
		swordSprite->Draw();
		heartSprite->Draw();
		animal_attackSprite->Draw();
		animal_attackSprite2->Draw();
		for (int i = 0; i < 30; i++)
			shadows[i]->Draw();
		for (int i = 0; i < 10; i++)
			objects[i]->Draw();
		for (int i = 0; i < 10; i++)
			monsters[i]->Draw();

		std::string sa = std::to_string(powerup_Apollo);
		char const* apollo_pchar = sa.c_str();

		if (powerup_Apollo != 10)
			App::Print(75, 595, apollo_pchar, 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18);
		else  App::Print(75, 595, "", 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18);

		std::string s = std::to_string(powerup_Ares);
		char const* pchar = s.c_str();
		if (powerup_Ares != 10)
			App::Print(170, 595, pchar, 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18);
		else  App::Print(170, 595, "", 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18);
		game_time_seconds = game_time / 1000;
		std::string st = std::to_string(game_time_seconds);
		char const* time_pchar = st.c_str();
		App::Print(800, 730, "Game time: ", 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18);
		App::Print(895, 730, time_pchar, 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18); 

		std::string cs = std::to_string((int)customScore);
		char const* custom_pchar = cs.c_str();
		App::Print(835, 710, "Score: ", 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18);
		App::Print(895, 710, custom_pchar, 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18);
		leaderflag = 1;

		break;
	}
	case 2:
		mythSprite->Draw();
		App::Print(750, 20, "Press B to go back to Menu ");
		break;

	case 3:
		storySprite->Draw();
		App::Print(750, 20, "Press B to go back to Menu ");
		break;

	case 4:
	{
		leaderSprite->Draw();
		std::string ld = std::to_string((int)customScore);
		char const* leader_pchar = ld.c_str();
		App::Print(430, 395, "Ai terminat cu scorul: ", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_12);
		App::Print(550, 395, leader_pchar, 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_12);
		ifstream fin("leaderfile.txt");
		for (int i = 0; i < 5; i++)
		{
			fin >> score[i];
		}
		if (leaderflag == 1 )
		{
			updateLeaderBoard();
		}
		if(congratflag == 1)
			App::Print(420, 330, "Felicitari, ai ajuns in leaderboard!", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_12);

		for (int i = 0; i < 5; i++)
		{
			std::string ld = std::to_string(score[i]);
			char const* leader_pchar = ld.c_str();
			App::Print(490, i * 50 + 100, "Locul", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
			//std::string ldi = std::to_string(i);
			//char const* i_pchar = ldi.c_str();
			//App::Print(540, i * 50 + 100, i_pchar, 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
			App::Print(512, i * 50 + 80, leader_pchar, 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
		}
		int kx = 1;
		for (int i = 4; i >= 0; i--)
		{

			std::string ldi = std::to_string(kx);
			char const* i_pchar = ldi.c_str();
			App::Print(540, i * 50 + 100, i_pchar, 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
			kx++;
		}
		App::Print(425, 50, "Press A to reset the leaderboard", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_12);
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
		{
			for (int i = 0; i < 5; i++)
			{
				score[i] = 0;
				ofstream fout("leaderfile.txt");
				for (int i = 0; i < 5; i++)
				{
					fout << score[i] << endl;
				}
			}
		}
		App::Print(750, 20, "Press B to go back to Menu ");
		break;
	}
	case 5:
		guideSprite->Draw();
		App::Print(750, 20, "Press B to go back to Menu ");
		break;
	case 6:
		resumeSprite->Draw();
		restartSprite->Draw();
		break;
	default: startmenuSprite->Draw();
		break;
	}

}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
	//------------------------------------------------------------------------
	// Example Sprite Code....
	delete testSprite;
	delete nohealthSprite;
	delete backgroundSprite1;
	delete backgroundSprite2;
	delete groundSprite;
	delete groundSprite2;
	delete heartSprite;
	delete animal_attackSprite2;
	delete animal_attackSprite;
	for (int i = 0; i < 10; i++)
		delete objects[i];
	for (int i = 0; i < 10; i++)
		delete monsters[i];
	for (int i = 0; i < 30; i++)
		delete shadows[i];
	delete resumeSprite;
	delete restartSprite;
	delete apolloSprite;
	delete aresSprite;
	delete apollo_avSprite;
	delete ares_avSprite;
	delete sunSprite;
	delete swordSprite;


	//------------------------------------------------------------------------
}