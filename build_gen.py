import sys
import os
import subprocess
from shutil import copyfile


if not os.path.exists("build"):
    os.makedirs("build")

os.chdir("build")
subprocess.call('cmake -G "Visual Studio 15 2017 Win64" ..\\')