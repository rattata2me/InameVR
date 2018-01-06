import kivy
from kivy.uix.screenmanager import Screen
from kivy.lang import Builder
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.image import Image
from kivy.clock import Clock
from kivy.graphics.texture import Texture
import cv2
import numpy as np
import values

Builder.load_string("""
#:import hex kivy.utils.get_color_from_hex
<ColorPick>
	size_hint: 1,1
	orientation: "vertical"
	BoxLayout:
		Label:
			text: "H"
		TextInput:
			id: hvalue
			size_hint: .3,1
			multiline: False
			input_type: "number"
			on_text: root.proccessChange("h", self.text)
		Slider:
			id: hslider
			min: 0
			max: 0x100
			on_value_pos: root.ids["hvalue"].text = str(int(self.value))
	BoxLayout:
		Label:
			text: "S"
		TextInput:
			id: svalue
			size_hint: .3,1
			multiline: False
			input_type: "number"
			on_text: root.proccessChange("s", self.text)
		Slider:
			id: sslider
			min: 0
			max: 0x100
			on_value_pos: root.ids["svalue"].text = str(int(self.value))
	BoxLayout:
		Label:
			text: "V"
		TextInput:
			id: vvalue
			size_hint: .3,1
			multiline: False
			input_type: "number"
			on_text: root.proccessChange("v", self.text)
		Slider:
			id: vslider
			min: 0
			max: 0x100
			on_value_pos: root.ids["vvalue"].text = str(int(self.value))
				
			
			
<ChooseColor@BoxLayout>
	padding: 10,10,10, self.height*0.2
	orientation: "vertical"
	Label:
		text:"Upper Color"
	
	ColorPick:
		id: upper
	
	Label:
		text:"Lower Color"

	ColorPick:
		id: lower

<CamerasLayout>:
	padding: 20,20,40,40
	Image:
		id: frame_camera
		on_touch_down: root.touch_on_picture(args[1])
				
	Image:
		id: mask_camera
	
	TabbedPanel:
		id: tabbedpanel
		size_hint_y: .9
		do_default_tab: False			
				
		TabbedPanelItem:
			id: layout_controller1
			background_color: hex("#00FFA0")			
			text: "Controller 1"
			ChooseColor:

		TabbedPanelItem:
			id: layout_controller2
			background_color: hex("#AE0000")
			text: "Controller 2"
			ChooseColor:

		TabbedPanelItem:
			id: layout_controller3
			background_color: hex("#00A0FF")			
			text: "Controller 3"
			ChooseColor:

			
<CameraScreen1>:
	RelativeLayout:
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
				id: cameraslayout
		Button:
			text: "Save settings"
			size_hint: .09, .05
			pos_hint: {"x": .88, "y": .05}
			on_press: root.ids["cameraslayout"].save_colors()
				
""")

#It works... TODO implement this nicely
index = 0

class CameraScreen1(Screen):
	
	def __init__(self, i, **kwargs):
		super(CameraScreen1, self).__init__(**kwargs)
		index = i
class ColorPick(BoxLayout):
	
	def __init__(self, **kwargs):
		super(ColorPick, self).__init__(**kwargs)
		
		self.color = [0,0,0]

	def proccessChange(self, valueindx, value):
		if str.isdigit(str(value)):
			if valueindx is "h":
				self.color[0] = int(value)
			if valueindx is "s":
				self.color[1] = int(value)
			if valueindx is "v":
				self.color[2] = int(value)
			self.ids[valueindx+"slider"].value = int(value)

class CamerasLayout(BoxLayout): #TODO support more controllers

	def __init__(self, **kwargs):
		super(CamerasLayout, self).__init__(**kwargs)	
		self.capture = cv2.VideoCapture(0)				
		Clock.schedule_interval(self.update, 1.0/60) #60 fps
		self.started = False	
		self.hsv = None	
		self.camera_dimensions = [0,0]
	
	def start(self):
		self.frame = self.ids.frame_camera
		self.mask = self.ids.mask_camera				

	def set_color_of_current_widget(self, upper, lower):
		upperw = self.ids["tabbedpanel"].content.children[0].ids["upper"]
		upperw.ids["hvalue"].text = str(upper[0])
		upperw.ids["svalue"].text = str(upper[1])
		upperw.ids["vvalue"].text = str(upper[2])
		
		lowerw = self.ids["tabbedpanel"].content.children[0].ids["lower"]
		lowerw.ids["hvalue"].text = str(lower[0])
		lowerw.ids["svalue"].text = str(lower[1])
		lowerw.ids["vvalue"].text = str(lower[2])
		
	def save_colors(self):
		cam = values.cameras[index]
		
		colorsg = self.get_color_array(self.ids["tabbedpanel"]._tab_strip.children[0].content) #Color array should not need arguments TODO
		colorsr = self.get_color_array(self.ids["tabbedpanel"]._tab_strip.children[1].content)	
		colorsb = self.get_color_array(self.ids["tabbedpanel"]._tab_strip.children[2].content)	
		colorsall = colorsb + colorsr + colorsg
		for j in range(2):
			for i in range(3):
				values.cameras[index].colors[i*2+j] = colorsall[(i*6+j*3):(i*6+j*3+3)]
		values.to_json()		

	def touch_on_picture(self, touch):
		if self.frame.collide_point(touch.x, touch.y):
			
			if self.hsv is not None:
				x = (touch.x/self.frame.width)*self.camera_dimensions[0]
				y = (touch.y/self.frame.height)*self.camera_dimensions[1]
				
				#Limitations for weird moments
				if x >= self.camera_dimensions[0]:
					x = self.camera_dimensions[0]-1
				if y >= self.camera_dimensions[1]:
					y = self.camera_dimensions[1]-1	
				#TODO implement a more intelligent way		
				upper = self.hsv[x, y] + (20,255,90)
				lower = upper - (40,60,40)
				self.set_color_of_current_widget(lower, upper)
			
	def get_color_array(self, index):
		upper = index.ids["upper"].color
		lower = index.ids["lower"].color
		return (upper+lower)

	def update(self, something):

		if len(self.ids) < 3:
			return
		elif not self.started:
			self.start()		
			self.started = True

		ret, frame = self.capture.read()
		
		if ret is False:
			return

		self.camera_dimensions = [frame.shape[0], frame.shape[1]] # TODO update all references to frame.shape[0] and [1]

		#Tracking mask	
		
		#Get colors

		colors = np.array(self.get_color_array(self.ids["tabbedpanel"].content.children[0]))

		self.hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
		
		mask = cv2.inRange(self.hsv, colors[0:3], colors[3:6])
	
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

		
