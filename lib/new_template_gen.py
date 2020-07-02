import distutils
from distutils import dir_util
import sys
import os
import subprocess
from shutil import copyfile
import string

def replaceFileNames(folder_path, old, new):
    for path, subdirs, files in os.walk(folder_path):
        for name in files:
            if(old.lower() in name.lower()):
                file_path = os.path.join(path,name)
                new_name = os.path.join(path,name.lower().replace(old,new))
                os.rename(file_path, new_name)

def replaceInFilesRecursievely(folder_path, old, new):
	for dname, dirs, files in os.walk(folder_path):
	    for fname in files:
	        fpath = os.path.join(dname, fname)
	        with open(fpath) as f:
	            s = f.read()
	        s = s.replace(old, new)
	        with open(fpath, "w") as f:
	            f.write(s)

def to_camel_case(snake_str):
    components = snake_str.split('_')
    # We capitalize the first letter of each component except the first one
    # with the 'title' method and join them together.
    return components[0] + ''.join(x.title() for x in components[1:])

def to_camel_case_Test(snake_str):
    snake_str = snake_str + "_test"
    components = snake_str.split('_')
    return ''.join(x.title() for x in components)

if len(sys.argv) == 2:
	newProject = sys.argv[1]
	newProjectLower = newProject.lower()
	newProjectUpper = newProject.upper()
	newProjectTest = to_camel_case_Test(newProjectLower)
	dir_util.copy_tree("template",newProjectLower)
	
	#rename files template -> newProjectLower
	replaceFileNames(newProjectLower, "template", newProjectLower)

	#replace all pattern in files
	replaceInFilesRecursievely(newProjectLower, "template", newProjectLower)
	replaceInFilesRecursievely(newProjectLower, "TemplateTest", newProjectTest)
	replaceInFilesRecursievely(newProjectLower, "Template", newProject)
	replaceInFilesRecursievely(newProjectLower, "TEMPLATE", newProjectUpper)
	
	#add newProject to the ../CMakeLists.txt

	cmakeFile = "../CMakeLists.txt"

	with open(cmakeFile) as f:
		content = f.read()
	
	#insert before all test

	newTest = "add_subdirectory(lib/{}/test/)".format(newProjectLower)
	allTest = "add_subdirectory(lib/all_test/)"

	content = content.replace(allTest, newTest + '\n' + allTest)
	
	with open(cmakeFile, "w") as f:
	    f.write(content)

else:
	print("Error: wrong number of arguments")
