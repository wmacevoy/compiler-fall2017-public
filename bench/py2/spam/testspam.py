import sys
import os
from glob import glob

thisdir=os.path.abspath(os.path.dirname(sys.argv[0]))
builddir=thisdir + "/build"

# dynamically add lib folders with shared objects
for root, dirs, files in os.walk(builddir):
    for dir in dirs:
        if dir.startswith("lib."):
            for subroot,subdirs,subfiles in os.walk(builddir + "/" + dir):
                for subfile in subfiles:
                    if (subfile.endswith(".so")):
                        buildsodir=builddir + "/" + dir
                        sys.path.append(buildsodir)
             
import spam

spam.system('echo ok')
