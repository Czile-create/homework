import os, sys
path = "/home/czile/work/LinuxProgram/python/picHash.py/3"
with open("pattern3.mdb") as f:
    filelist = f.read().split('\n')
    for filename in filelist:
        os.system("cp {} {}".format(filename, path))