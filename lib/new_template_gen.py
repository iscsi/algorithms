import distutils
from distutils import dir_util
import sys
import os
import subprocess
from shutil import copyfile
import string

if len(sys.argv) == 2:
	newProject = int(sys.argv[2])
	newProjectLower = newProject.lower()
	newProjectUpper = newProject.upper()
	dir_util.copy_tree("template",newProjectLower)
	
	#rename files template -> newProjectLower

	#replace all files
	#template -> newProjectLower
	#Template -> newProject
	#TEMPLATE -> newProjectUpper

	#add newProject to the ../CMakeLists.txt
	#add_subdirectory(lib/newProjectLower/test)

else:
	print("Error: wrong number of arguments")