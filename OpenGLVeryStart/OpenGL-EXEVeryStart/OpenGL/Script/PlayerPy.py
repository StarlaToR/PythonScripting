print ("PlayerPy.py loaded")

#Module
import Worker

def AddVelocity(_velocity : Worker.Vec3, player : Worker.Player):
	player.velocity = _velocity + player.velocity

	if player.velocity.y > Worker.PLAYER_MAX_VERTICAL_SPEED:
		player.velocity.y = Worker.PLAYER_MAX_VERTICAL_SPEED
	if player.velocity.y < -Worker.PLAYER_MAX_VERTICAL_SPEED:
		player.velocity.y = -Worker.PLAYER_MAX_VERTICAL_SPEED

def Jump(player : Worker.Player):
	AddVelocity(Worker.Vec3(0, Worker.PLAYER_VERTICAL_ACCELERATION, 0), player);		
	player.canJump = False
	player.isGrounded = False
	player.affectedByGravity = True

def MovePlayer(_direction : Worker.Vec3, camForward : Worker.Vec3,  player : Worker.Player):
	if _direction == Worker.Vec3(0, 0, 1):
		player.direction = Worker.Vec3(camForward.x, 0, camForward.z)

	elif _direction == Worker.Vec3(0, 0, -1):
		player.direction = Worker.Vec3(-camForward.x, 0, -camForward.z)

	elif _direction == Worker.Vec3(1, 0, 0):
		player.direction = Worker.Vec3(-camForward.z, 0, camForward.x)

	elif _direction == Worker.Vec3(-1, 0, 0):
		player.direction = Worker.Vec3(camForward.z, 0, -camForward.x)
	
	AddVelocity(player.direction.GetNormalizedVector() * Worker.PLAYER_HORIZONTAL_ACCELERATION, player)
	

