import kivy
from kivy.uix.screenmanager import Screen
from kivy.lang import Builder
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.image import Image
from kivy.clock import Clock
from kivy.graphics.texture import Texture
import cv2
import numpy as np

Builder.load_string("""
#:import hex kivy.utils.get_color_from_hex

<CamerasLayout>

<CameraScreen1>:
	FloatLayout:
		canvas.before:

			Color:
				rgba: hex("#43A635")

			Rectangle:
				pos: self.pos
				size: self.size

		BoxLayout:
			orientation: "vertical"	
	
			Label:
				font_size: dp(50)
				text: "Step 1"
				size_hint: (1, .2)

			Label:
				font_size: dp(30)
				text: "Prepare the mask"
				size_hint: (1, .05)

			CamerasLayout:
				id: "cameras"
				


		
""")

class CameraScreen1(Screen):
	pass


class CamerasLayout(BoxLayout):

	def __init__(self, **kwargs):
		super(CamerasLayout, self).__init__(**kwargs)
		self.capture = cv2.VideoCapture(0)
		self.frame = Image()
		self.add_widget(self.frame)
		self.mask = Image()
		self.add_widget(self.mask)
		Clock.schedule_interval(self.update, 1.0/60) #30 fps
		self.lowerGreen = (29, 86, 6)
		self.upperGreen = (64, 255, 255)
		self.lowerRed = (0,86,6)
		self.upperRed = (50,255,255)
		self.lowerBlue = (0,86,6)
		self.upperBlue = (50,255,255)
	
	def update(self, something):
		
		ret, frame = self.capture.read()
		
		if ret is False:
			return



		#Tracking mask		
		hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
		
		mask = cv2.inRange(hsv, self.lowerGreen, self.upperGreen)
	
		mask = cv2.erode(mask, None, iterations=2)
		mask = cv2.dilate(mask, None, iterations=2)

		#Mask
		blank_image = np.zeros((frame.shape[0], frame.shape[1],3), np.uint8)
		blank_image[:,:] = (255,255,255)
		blank_imager = cv2.bitwise_and(blank_image, blank_image, mask=mask)
		buf2 = blank_imager.tostring()
		texture_mask = Texture.create(size=(frame.shape[1], frame.shape[0]))
		texture_mask.blit_buffer(buf2)
		self.mask.texture = texture_mask

		#Frame
		buf = frame.tostring()
		texture_frame = Texture.create(size=(frame.shape[1], frame.shape[0]), colorfmt='bgr')
		texture_frame.blit_buffer(buf, colorfmt='bgr', bufferfmt='ubyte')
		self.frame.texture = texture_frame

		
