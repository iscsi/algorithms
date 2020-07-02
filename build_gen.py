import sys
import os
import subprocess
from shutil import copyfile
import string
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("-w", "--work", help = "visual studio 2015", action='store_true')
args = parser.parse_args()

if args.work:
	cmakeCommand = 'cmake -G "Visual Studio 14 2015 Win64" ..\\'
else:
	cmakeCommand = 'cmake -G "Visual Studio 15 2017 Win64" ..\\'

if not os.path.exists("build"):
    os.makedirs("build")
    	
os.chdir("build")
subprocess.call(cmakeCommand)