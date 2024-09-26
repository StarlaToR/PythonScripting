print ("Camera.py loaded")

import Worker
import math

def MouseDirection(xpos : float, ypos : float, camera : Worker.Camera):
	if camera.firstMouse == True:
		camera.lastX = xpos
		camera.lastY = ypos
		camera.firstMouse = False

	xoffset : float = xpos - camera.lastX
	yoffset : float = camera.lastY - ypos
	camera.lastX = xpos
	camera.lastY = ypos
	
	sensitivity : float = 0.2
	xoffset *= sensitivity
	yoffset *= sensitivity

	camera.yaw += xoffset
	camera.pitch += yoffset

	if camera.pitch > 89.0:
		camera.pitch = 89.0
	if camera.pitch < -89.0:
		camera.pitch = -89.0

	direc = [math.cos(camera.yaw * math.pi / 180) * math.cos(camera.pitch * math.pi / 180), -math.sin(camera.pitch), math.sin(camera.yaw * math.pi / 180) * math.cos(camera.pitch * math.pi / 180)]
		
	camera.camForward = direc.GetNormalizedVector
	camera.oldDirection = camera.camForward
