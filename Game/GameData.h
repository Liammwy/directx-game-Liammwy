#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_

//=================================================================
//Data to be passed by game to all Game Objects via Tick
//=================================================================

#include "GameState.h"
#include "Keyboard.h"
#include "Mouse.h"

using namespace DirectX;

struct GameData
{
	float m_dt;  //time step since last frame
	GameState m_GameState; //global GameState

	//player input
	Keyboard::State m_KeyboardState;
	Mouse::State m_MouseState;
	Keyboard::KeyboardStateTracker m_KBS_tracker;
};
#endif
