import sys
import os

# dynamically include local libraries
thisdir=os.path.abspath(os.path.dirname(sys.argv[0]))
libdir=os.path.abspath(thisdir + "/../lib")

for root, dirs, files in os.walk(libdir):
    for dir in dirs:
        if dir.startswith("lib."):
            for subroot,subdirs,subfiles in os.walk(libdir + "/" + dir):
                for subfile in subfiles:
                    if (subfile.endswith(".so")):
                        libsodir=libdir + "/" + dir
                        sys.path.append(libsodir)

import rand

rand.srand()

if (rand.rand(2) == 0):
    print "heads"
else:
    print "tails"
