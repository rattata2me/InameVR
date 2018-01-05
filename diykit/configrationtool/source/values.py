



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
	

cameras = []
