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
             
import rand

a=0
b=0
n=1000

rand.srand()

for i in xrange(n):
    r=rand.rand(2)
    if r == 0:
        a = a + 1
    if r == 1:
        b = b + 1

print "a=" + str(a) + " b=" + str(b) + " miss=" + str(n-(a+b))
