#include "pch.h"
#include "Player.h"
#include <dinput.h>
#include "GameData.h"
#include <iostream>

Player::Player(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF) : CMOGO(_fileName, _pd3dDevice, _EF)
{
	//any special set up for Player goes here
	m_fudge = Matrix::CreateRotationY(XM_PI);

	m_pos.y = 10.0f;

	SetDrag(0.7);
	SetPhysicsOn(false);
}

Player::~Player()
{
	//tidy up anything I've created
}


void Player::Tick(GameData* _GameData)
{
	switch (_GameData->m_GameState)
	{
	case GS_PLAY_MAIN_CAM:
	{
		{
			//MOUSE CONTROL SCHEME HERE
			float speed = 10.0f;
			m_acc.x += speed * _GameData->m_MouseState.x;
			m_acc.z += speed * _GameData->m_MouseState.y;
			break;
		}
	}
	case GS_PLAY_TPS_CAM:
	{
		//TURN AND FORWARD CONTROL HERE
		Vector3 forwardMove = 40.0f * Vector3::Forward;
		Matrix rotMove = Matrix::CreateRotationY(m_yaw);
		forwardMove = Vector3::Transform(forwardMove, rotMove);

		if (_GameData->m_KeyboardState.W)
		{
			m_acc += forwardMove;
		}
		if (_GameData->m_KeyboardState.S)
		{
			m_acc -= forwardMove;
		}

		// up down pitch
		// left right yaw

		break;
	}
	}

	//change orinetation of player
	float rotSpeed = 2.0f * _GameData->m_dt;

	// Camera movement via mouse input.
	m_pitch += (_GameData->m_MouseState.y * rotSpeed / 2) * -1;
	m_yaw += (_GameData->m_MouseState.x * rotSpeed / 2) * -1;

	if (m_pitch > XMConvertToRadians(60)) m_pitch = XMConvertToRadians(60);
	if (m_pitch < -XMConvertToRadians(60)) m_pitch = -XMConvertToRadians(-60);

	Vector3 sideMove = 40.0f * Vector3::Left;
	Matrix rotMove = Matrix::CreateRotationY(m_yaw);
	sideMove = Vector3::Transform(sideMove, rotMove);

	if (_GameData->m_KeyboardState.A)
	{
		m_acc += sideMove;
	}
	if (_GameData->m_KeyboardState.D)
	{
		m_acc -= sideMove;
	}

	//move player up and down
	if (_GameData->m_KeyboardState.Space)
	{
		m_acc.y += 40.0f;
	}

	if (_GameData->m_KeyboardState.LeftShift)
	{
		m_acc.y -= 40.0f;
	}

	//limit motion of the player
	float length = m_pos.Length();
	float maxLength = 500.0f;
	if (length > maxLength)
	{
		m_pos.Normalize();
		m_pos *= maxLength;
		m_vel *= -0.9; //VERY simple bounce back
	}

	//apply my base behaviour
	CMOGO::Tick(_GameData);
}