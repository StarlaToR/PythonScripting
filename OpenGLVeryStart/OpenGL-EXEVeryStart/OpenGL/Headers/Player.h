#pragma once
#include<GameObject.h>
#include<Physics.h>
#include<Maths.h>
#include<Light.h>
#include <pybind11/pybind11.h>

namespace Platformer
{
	class Player : public GameObject
	{
	private:

		LowRenderer::SpotLight* shadow = new LowRenderer::SpotLight(Vec3(0, -1, 0),
			Vec3(0,5,0),
			Vec3(-1, -1, -1),
			1.0,	0.0014,	0.000007,
			M_PI / 3.2f);


	public:
		bool affectedByGravity = true;
		bool canJump = true;
		bool isJumping = false;
		bool isGrounded = false;

		GameObject* collideWith = nullptr;

		Vec3 velocity;
		Vec3 direction;
		float heightLimit = -100;

		int pv=3;

		Player()
		{

		};

		Player(LowRenderer::Mesh* mesh, Vec3 pos, Vec3 rot, Vec3 sca, Vec3 dir, float* s)
		{
			SetMesh(mesh);
			transform->SetPosition(pos);
			transform->SetRotation(rot);
			transform->SetScale(sca);
			direction = dir;
			scale = s;
		};

		void MovePlayer(Vec3 _direction, Vec3 camForward);
		void Jump();
		void Update();

		void AddVelocity(Vec3 _velocity);
		void callPython();
		void ReactionToCollision(GameObject* gameObject);
		LowRenderer::SpotLight* GetShadow() { return shadow; };
		pybind11::object player_pyt;

	};

} 