#include <Player.h>
#include <PythonBinder.h>


Vec3 ConvertAngleToDirection(float angle)
{
	return Vec3(cos(angle), 0, sin(angle));
}

void Platformer::Player::callPython()
{
	player_pyt = pybind11::module::import("Script.PlayerPy");
}

void Platformer::Player::MovePlayer(Vec3 _direction, Vec3 camForward)
{
	try {
		auto player_Move = player_pyt.attr("MovePlayer");
		player_Move(_direction, camForward, this);
	}
	catch (pybind11::error_already_set error) {
		printf("%s\n", error.what());
	}
}
 
void Platformer::Player::Jump()
{
	try {
		auto player_Jump = player_pyt.attr("Jump");
		player_Jump(this);
	}
	catch (pybind11::error_already_set error) {
		printf("%s\n", error.what());
	}
}

void Platformer::Player::AddVelocity(Vec3 _velocity)
{
	try {
		auto player_Velocity = player_pyt.attr("AddVelocity");
		player_Velocity(&_velocity, this);
	}
	catch (pybind11::error_already_set error) {
		printf("%s\n", error.what());
	}

}

void Platformer::Player::Update()
{
	callPython();
	//printf("%f\n", transform->GetPosition().y);
	if (transform->GetPosition().y < -20)
		transform->SetPosition(Vec3(0, 0, 0));
	//Gravity
	if (transform->GetPosition().y > heightLimit && affectedByGravity)
		AddVelocity(Vec3(0, -GRAVITY, 0));

	if (collideWith == nullptr)
	{
		affectedByGravity = true;
	}
	else
	{
		canJump = true;
		if (velocity.y < 0.1 && velocity.y > -0.1)
		{
			isGrounded = true;
			affectedByGravity = false;
		}
		else
		{
			ReactionToCollision(collideWith);
		}
	}


	transform->SetPosition(transform->GetPosition()+velocity);
	transform->SetRotation(Vec3(0, GetAngleBetweenVectors(direction, Vec3(0,0,1)),0));

	shadow->position = Vec3(transform->GetPosition().x, transform->GetPosition().y - 1, transform->GetPosition().z);

	velocity = Vec3(0,velocity.y * 0.99, 0);

	collider->scale = Vec3(1, 1, 1);
	collider->position.y += 1;
	
}

void Platformer::Player::ReactionToCollision(GameObject* gameObject)
{
	Mat4 rotationMat = CreateTransformMatrix(Vec3(), gameObject->collider->rotation, Vec3(1, 1, 1));
	Mat4 halfSizeRotated;
	for (int j = 0; j < 3; j++)
	{
		halfSizeRotated.tab[0][j] = rotationMat.tab[0][j] * gameObject->collider->scale.x;
		halfSizeRotated.tab[1][j] = rotationMat.tab[1][j] * gameObject->collider->scale.y;
		halfSizeRotated.tab[2][j] = rotationMat.tab[2][j] * gameObject->collider->scale.z;
	}

	Vec3 vec1 = Vec3(rotationMat.tab[1][0], rotationMat.tab[1][1], rotationMat.tab[1][2]);
	vec1.Normalize();
	Vec3 vec2 = Vec3(collider->position - gameObject->collider->position);
	vec2.Normalize();

	float up = GetDotProduct(vec1,vec2);
	float forward = GetDotProduct(Vec3(rotationMat.tab[2][0], rotationMat.tab[2][1], rotationMat.tab[2][2]),vec2);
	float right = GetDotProduct(Vec3(rotationMat.tab[0][0], rotationMat.tab[0][1], rotationMat.tab[0][2]), vec2);

	Vec4 centerFaceX;
	Vec4 centerFaceY;
	Vec4 centerFaceZ;

	if (up >= 0)
		centerFaceY = Vec3(0, gameObject->collider->scale.y, 0) * rotationMat + gameObject->collider->position;
	else
		centerFaceY = Vec3(0, - gameObject->collider->scale.y, 0) * rotationMat + gameObject->collider->position;

	if (right >= 0)
		centerFaceX = Vec3(gameObject->collider->scale.x, 0, 0) * rotationMat + gameObject->collider->position;
	else
		centerFaceX = Vec3(-gameObject->collider->scale.x, 0, 0) * rotationMat + gameObject->collider->position;

	if (forward >= 0)
		centerFaceZ = Vec3(0, 0, gameObject->collider->scale.z) * rotationMat + gameObject->collider->position;
	else
		centerFaceZ = Vec3(0, 0, -gameObject->collider->scale.z) * rotationMat + gameObject->collider->position;

	Vec3 directionX = Vec3(centerFaceX.x, centerFaceX.y, centerFaceX.z) - gameObject->collider->position;
	Vec3 directionY = Vec3(centerFaceY.x, centerFaceY.y, centerFaceY.z) - gameObject->collider->position;
	Vec3 directionZ = Vec3(centerFaceZ.x, centerFaceZ.y, centerFaceZ.z) - gameObject->collider->position;

	float newUp = GetDotProduct(vec2, directionY);
	float newForward = GetDotProduct(vec2, directionZ);
	float newRight = GetDotProduct(vec2, directionX);

	bool isInsideX = !(newRight >= 0);
	bool isInsideY = !(newUp >= 0);
	bool isInsideZ = !(newForward >= 0);

	if (isInsideX && isInsideY && isInsideZ)
	{
		AddVelocity(directionY.GetNormalizedVector() * 2);
		printf("inside");
	}
	else
	{
		if (!isInsideY)
		{
			if (up >= 0)
			{
				isGrounded = true;
				velocity.y = 0;
			}
			AddVelocity(directionY * 0.1f);

		}
		else if (!isInsideX)
		{
			AddVelocity(directionX * 0.1f);
			printf("on the side x");
		}
		else
		{
			AddVelocity(directionZ * 0.1f);
			printf("on the side z");

		}
	}
	
}