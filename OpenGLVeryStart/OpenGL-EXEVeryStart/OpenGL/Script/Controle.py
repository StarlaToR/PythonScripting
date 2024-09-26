print ("Controle.py loaded")

import Worker
import importlib

def Reload():
	importlib.reload(Worker)
	print("Reload")