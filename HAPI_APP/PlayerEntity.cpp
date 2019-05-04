#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(std::string &fileName) : Entity(fileName)
{
	mAlive = true;
	mSide = eSide::ePlayer;
}

PlayerEntity::~PlayerEntity()
{
}

//MONEY HAS BEEN REPLACED WITH BABIES
void PlayerEntity::AddMoney(int amount) 
{ 
	//Add score to the player
	mMoneyAmount += amount; 
}

void PlayerEntity::AddLGAmmo(int amount)
{
	mLGAmmo += amount;

	//Make sure player can not have more than the max ammo limit
	if (mLGAmmo > mLGMaxAmmo)
	{
		mLGAmmo = mLGMaxAmmo;
	}

	//Make sure the player does not have a negative ammo count
	if (mLGAmmo < 0)
	{
		mLGAmmo = 0;
	}
}

void PlayerEntity::ShootLG()
{
	bool bulletSpawned = false;

	//Set bullet to alive and move when the gun is fired
	for (int i = 0; i < 10 && bulletSpawned == false; i++)
	{
		if (!mBullets[i]->IsAlive())
		{
			mBullets[i]->SetAliveStatus(true);
			mBullets[i]->setPosition((VectorF(sprite->GetTransformComp().GetPosition().x + 5, sprite->GetTransformComp().GetPosition().y)));

			mBullets[i]->SetDirection(GetDirection());

			//Reduce ammo count
			AddLGAmmo(-1);

			bulletSpawned = true;
		}
	}
}

void PlayerEntity::Update()
{
	const HAPISPACE::KeyboardData &mKeyboardInput = HAPI_Sprites.GetKeyboardData();

	//Check for the player moving or colliding
	PlayerMovementCollision();

	//Fire the love gun
	if (mKeyboardInput.scanCode['F'] && mLGAmmo > 0 && updatesSinceLGlastFired >= LGCooldownUpdates)
	{
		HAPI_Sprites.PlaySound((std::string)"Data//Sounds//LoveGun.wav");
		ShootLG();
		updatesSinceLGlastFired = 0;
	}

	//Limit the fire rate of the love gun
	if (updatesSinceLGlastFired < LGCooldownUpdates)
	{
		updatesSinceLGlastFired++;
		if (mKeyboardInput.scanCode['F'] && mLGAmmo < 1)
		{
			HAPI_Sprites.PlaySound((std::string)"Data//Sounds//ErrorSound.wav");
		}
	}
}

void PlayerEntity::Render()
{
	//Render the player and in game text
	if (mAlive)
	{
		sprite->Render(SCREEN_SURFACE);
	}

	HAPI_Sprites.RenderText(20, 25, Colour255(34, 85, 0), "Ammo : " + std::to_string(mLGAmmo), 25);
	HAPI_Sprites.RenderText(575, 25, Colour255(34, 85, 0), "Babies : " + std::to_string(mMoneyAmount), 25);
	HAPI_Sprites.RenderText(1150, 25,  Colour255(34, 85, 0), "Key : " + std::to_string(mHasKey), 25);
}

