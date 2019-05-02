#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(std::string &fileName) : Entity(fileName)
{
	mAlive = true;
	mSide = eSide::ePlayer;
}

PlayerEntity::~PlayerEntity()
{
}

void PlayerEntity::AddMoney(int amount) 
{ 
	mMoneyAmount += amount; 
	if (mMoneyAmount < 0) // checks if the player has lost more money than they have left and if so marks them as bankrupt
	{
		mBankrupt = true;
	}
}

void PlayerEntity::AddLGAmmo(int amount)
{
	mLGAmmo += amount;
	if (mLGAmmo > mLGMaxAmmo) // if the ammo total reaches a number above capacity it is set back to capacity
	{
		mLGAmmo = mLGMaxAmmo;
	}

	if (mLGAmmo < 0) // makes sure the player cannot have negative ammo
	{
		mLGAmmo = 0;
	}
}

void PlayerEntity::ShootLG()
{
	// SHOOTING ANIMATION HERE
	// PROJECTILE SHOOTING HERE
	bool bulletSpawned = false;
	for (int i = 0; i < 10 && bulletSpawned == false; i++)
	{
		if (!mBullets[i]->IsAlive())
		{
			mBullets[i]->SetAliveStatus(true);
			mBullets[i]->setPosition((VectorF(sprite->GetTransformComp().GetPosition().x + 5, sprite->GetTransformComp().GetPosition().y)));

			mBullets[i]->SetDirection(GetDirection());
			AddLGAmmo(-1);
			bulletSpawned = true;
		}
	}
}

void PlayerEntity::Update()
{
	const HAPISPACE::KeyboardData &mKeyboardInput = HAPI_Sprites.GetKeyboardData();

	PlayerMovementCollision();

	//SHOOT
	if (mKeyboardInput.scanCode['F'] && mLGAmmo > 0 && updatesSinceLGlastFired >= LGCooldownUpdates)// Couldn't come up with a key so press f to shoot respect
	{
		HAPI_Sprites.PlaySound((std::string)"Data//Sounds//LoveGun.wav");
		ShootLG();
		updatesSinceLGlastFired = 0;
	}

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
	if (mAlive)
	{
		sprite->Render(SCREEN_SURFACE);
	}
	HAPI_Sprites.RenderText(20, 25, Colour255(34, 85, 0), "Ammo : " + std::to_string(mLGAmmo), 25);
	HAPI_Sprites.RenderText(575, 25, Colour255(34, 85, 0), "Babies : " + std::to_string(mMoneyAmount), 25);
	HAPI_Sprites.RenderText(1150, 25,  Colour255(34, 85, 0), "Key : " + std::to_string(mHasKey), 25);
}

