#include <Scene.h>
#include <Camera.h>
#include <SceneManager.h>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

using namespace Platformer;
using namespace LowRenderer;

PYBIND11_MODULE(Worker, module)
{
	module.doc() = "PybindTest";

	//Player
	py::class_<Player, std::shared_ptr<Player>>(module, "Player")
		.def("MovePlayer", &Player::MovePlayer)
		.def("AddVelocity", &Player::AddVelocity)
		.def("Jump", &Player::Jump)
		.def_readwrite("velocity", &Player::velocity)
		.def_readwrite("direction", &Player::direction)
		.def_readwrite("affectedByGravity", &Player::affectedByGravity)
		.def_readwrite("canJump", &Player::canJump)
		.def_readwrite("isJumping", &Player::isJumping)
		.def_readwrite("isGrounded", &Player::isGrounded)
		;

	//Vector3
	py::class_<Vec3, std::shared_ptr<Vec3>>(module, "Vec3")
		.def(py::init<float, float, float>())
		.def("GetNormalizedVector", &Vec3::GetNormalizedVector)
		.def_readwrite("x", &Vec3::x)
		.def_readwrite("y", &Vec3::y)
		.def_readwrite("z", &Vec3::z)
		.def(py::self + py::self)
		.def(py::self += py::self)
		.def(py::self == py::self)
		.def(py::self * float())
		;

	py::class_<SceneManager, std::shared_ptr<SceneManager>>(module, "SceneManager")
		.def_readwrite("forwardKey", &SceneManager::forwardKey)
		.def_readwrite("backKey", &SceneManager::backKey)
		.def_readwrite("leftKey", &SceneManager::leftKey)
		.def_readwrite("rightKey", &SceneManager::rightKey)
		.def_readwrite("camForwardKey", &SceneManager::camForwardKey)
		.def_readwrite("camBackKey", &SceneManager::camBackKey)
		.def_readwrite("camLeftKey", &SceneManager::camLeftKey)
		.def_readwrite("camRightKey", &SceneManager::camRightKey)
		.def_readwrite("currentScene", &SceneManager::currentScene)
		.def_readwrite("scenes", &SceneManager::scenes)
		;

	//Camera
	py::class_<Camera, std::shared_ptr<Camera>>(module, "Camera")
		.def("Mouse Direction", &Camera::MouseDirection)
		.def_readwrite("lastX", &Camera::lastX)
		.def_readwrite("lastY", &Camera::lastY)
		.def_readwrite("yaw", &Camera::yaw)
		.def_readwrite("pitch", &Camera::pitch)
		.def_readwrite("camForward", &Camera::camForward)
		.def_readwrite("camRight", &Camera::camRight)
		.def_readwrite("camUp", &Camera::camUp)
		.def_readwrite("firstMouse", &Camera::firstMouse)
		.def_readwrite("oldDirection", &Camera::oldDirection)
		.def_readwrite("position", &Camera::position)
		;	

	module.attr("GRAVITY") = GRAVITY;
	module.attr("PLAYER_VERTICAL_ACCELERATION") = PLAYER_VERTICAL_ACCELERATION;
	module.attr("PLAYER_MAX_VERTICAL_SPEED") = PLAYER_MAX_VERTICAL_SPEED;
	module.attr("PLAYER_HORIZONTAL_ACCELERATION") = PLAYER_HORIZONTAL_ACCELERATION;
	module.attr("PLAYER_MAX_HORIZONTAL_SPEED") = PLAYER_MAX_HORIZONTAL_SPEED;
	module.attr("CAMERA_SPEED") = CAMERA_SPEED;
}