#!/usr/bin/python
# -*- coding: utf-8 -*-

from ScriptingBridge import *
import fnmatch, os

# vars. depends on your environments and goal.
WORK_DIR = "/Users/tani/Desktop"
EXTS = ["*.aif", "*.wav", "*.m4a"]


# 1. list all finderitem with desktop position.
finder = SBApplication.applicationWithBundleIdentifier_("com.apple.finder")

def tissue_box():
	a = finder.items()	
	for i in a:
		p = i.desktopPosition()
		yield [i.name(), int(p.x), int(p.y)]


# 2-1. make a finder-item-list which has a given extension.
resultlist = []
for pattern in EXTS :
	resultlist.extend( fnmatch.filter(os.listdir(WORK_DIR), pattern) )

# 2-2. extends with folders.
resultlist.extend([f.name() for f in finder.folders()])

# 3. std out
cnt = 1
for i in resultlist:  # matched list
	for e in tissue_box():  # every entry
		if i == e[0]:
			#print e[0], e[1], e[2]
			print "/dump", cnt, e[0], e[1], e[2]
			cnt += 1
			break



