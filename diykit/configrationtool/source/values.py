import json
import os
import os.path

class Camera(object):
	
	def __init__(self, index, colors=[0]*6):
		self.index = index
		self.colors = colors

	def setGreen(self, upper, lower):
		self.colors[0] = upper
		self.colors[1] = lower
	
	def setRed(self, upper, lower):
		self.colors[2] = upper
		self.colors[3] = lower

	def setRed(self, upper, lower):
		self.colors[4] = upper
		self.colors[5] = lower
	

cameras = [Camera(0)]


def to_json():
	a = {}
	camdic = []
	for camera in cameras:
		camidic = {}
		camidic["colors"] = camera.colors
		camidic["name"] = camera.index
		camdic.append(camidic)
	a["cameras"] = camdic
	out = json.dumps(a, sort_keys=True, indent=4)
	if os.path.exists("settings.iname"):	
		os.remove("settings.iname")
	sett = open("settings.iname", "w")
	sett.write(out)
	sett.close()
