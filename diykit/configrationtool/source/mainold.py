# Something fast and usable, why not python, however TODO write this in opengl, pygame sucks
import pygame
from pygame.locals import *
import cv2
import numpy as np
import sys

"< My keyboard does not have >"

#Suport classes

class Rect:
	
	def __init__(self, x, y, width, height):
		self.x = x
		self.y = y
		self.width = width
		self.height = height

	def collide_with(self, x, y):
		if self.x < x and (self.x+self.width) > x and self.y < y and (self.y+self.height) > y:
			return True
		else:
			return False
			
	



class Application:
	
	def __init__(self, window_size):
		pygame.init()
		pygame.display.set_caption("HUEHUE")
		self.screen = pygame.display.set_mode(window_size)
		self.running = False
		self.screenman = None		
			
	def start(self):
		self.running = True
		self.loop()		
	
	def stop(self):
		self.running = False

	def render(self):
		if self.screenman != None:
			self.screenman.draw()

	def loop(self):
		
		while self.running:
			self.render()

	def set_screenman(self, screen):
		self.screenman = screen


# I do not really know how to use pygame, so, using generic methods here

class Screen(object):

	def __init__(self, screen):
		self.screen = screen

	def draw(self):
		pass


class Camerasetcolors(Screen):
	
	def __init__(self, screen):
		super(Camerasetcolors, self).__init__(screen)
		self.camera = cv2.VideoCapture(0)
		self.frameobj = ScreenObject(self, Rect(0, 0, 320, 258))	
		self.maskobj = ScreenObject(self, Rect(320, 0, 320, 258))
		self.lowerGreen = (16, 80, 80)
		self.upperGreen = (100, 255, 255)
		self.lowerRed = (0,86,6)
		self.upperRed = (50,255,255)
		self.lowerBlue = (0,86,6)
		self.upperBlue = (50,255,255)

	def draw(self):

		self.update_input()

		grabbed, frame = self.camera.read()
		
		#Clean screen 
		self.screen.fill([0,255,0])
		if not grabbed:
			print("dude there is an error here")
			
		frame = cv2.flip(frame, -1)
		#Tracking mask		
		hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
		
		mask = cv2.inRange(hsv, self.upperGreen, self.lowerGreen)
	
		mask = cv2.erode(mask, None, iterations=2)
		mask = cv2.dilate(mask, None, iterations=2)
		
		show_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
		show_mask = mask
		show_frame = np.rot90(show_frame)
		show_mask = np.rot90(show_mask)
		
		#Update both surfaces
		self.frameobj.surface = pygame.surfarray.make_surface(show_frame)
		self.maskobj.surface = pygame.surfarray.make_surface(show_mask)
		
		#Draw objects
		self.frameobj.draw()
		self.maskobj.draw()
		

		pygame.display.update()
		
		

	def update_input(self):
		lclick = pygame.mouse.get_pressed()[0]
		mx, my = pygame.mouse.get_pos()

		if lclick == 1 and self.frameobj.rect.collide_with(mx, my):
			print "yes"		
	
		for event in pygame.event.get():
			if event.type == pygame.QUIT: sys.exit()

class ScreenObject(object):
	
	def __init__(self, screenman, rect=Rect(0,0,0,0), surface=None):
		self.screenman = screenman
		self.rect = rect
		self.surface = surface

	def draw(self):
		self.screenman.screen.blit(pygame.transform.scale(self.surface, (self.rect.width, self.rect.height)), (self.rect.x, self.rect.y))	
		
		


app = Application([1280, 720])
app.set_screenman(Camerasetcolors(app.screen))
app.start()
