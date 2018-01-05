#!/usr/bin/env python
# -*- coding: utf-8 -*-

import kivy

from kivy.app import App
from kivy.uix.screenmanager import ScreenManager, SlideTransition
from camerascreen import CameraScreen1
from kivy.config import Config

VERSION = 0.1


Config.set('graphics', 'width', '1280')
Config.set('graphics', 'height', '720')
Config.set('graphics', 'resizable', False)
Config.write()

class ConfigApp(App):
	
	def build(self):
		sm = ScreenManager()
		sm.add_widget(CameraScreen1(name="CameraScreen1", transition=SlideTransition()))
		return sm


if __name__ == "__main__":
	
	ConfigApp().run()
