import distutils
from distutils import dir_util
import sys
import os
import subprocess
from shutil import copyfile
import string

def replace(folder_path, old, new):
    for path, subdirs, files in os.walk(folder_path):
        for name in files:
            if(old.lower() in name.lower()):
                file_path = os.path.join(path,name)
                new_name = os.path.join(path,name.lower().replace(old,new))
                os.rename(file_path, new_name)

if len(sys.argv) == 2:
	newProject = sys.argv[1]
	newProjectLower = newProject.lower()
	newProjectUpper = newProject.upper()
	dir_util.copy_tree("template",newProjectLower)
	
	#rename files template -> newProjectLower
	replace(newProjectLower, "template", newProjectLower)

	#replace all files
	#template -> newProjectLower
	#Template -> newProject
	#TEMPLATE -> newProjectUpper

	#add newProject to the ../CMakeLists.txt
	#add_subdirectory(lib/newProjectLower/test)

else:
	print("Error: wrong number of arguments")
