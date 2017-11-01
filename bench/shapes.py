from sets import Set
import numpy

class Shape:
    def __init__(self,name):
        self.name=name
    def draw(self):
        print "drawing: " + self.name

class Circle(Shape):
    def __init__(self,name,radius):
        Shape.__init__(self,name)
        self.radius = radius
    def draw(self):
        print "drawing circle: " + self.name + " r=" + str(self.radius) 

class Square(Shape):
    def __init__(self,name,side):
        Shape.__init__(self,name)
        self.side = side
    def draw(self):
        print "drawing square: " + self.name + " s=" + str(self.side) 

c=0
rng=numpy.random.rand(1000)

def rand(n):
    global c
    global rng
    if (c >= 1000):
        rng=numpy.random.rand(1000)
        c=1
    else:
        c=c + 1
    return rng[c-1]

def mkShapes(n):
    shapes = list([])
    nrng = numpy.random.randint(1,100,n)
    for i in xrange(n):
        name = str(nrng[i]) + "(" + str(i) + ")";
        if (i%10) <= 5:
            shapes.append(Circle("circle # " + name,rand(100)))
        else:
            shapes.append(Square("shape # " +name,rand(100)))
    return shapes

def drawShapes(shapes):
    for shape in shapes:
        shape.draw()

n = 1000000
# n = 100
shapes=mkShapes(n)
sortedShapes = sorted(shapes,key = lambda shape: shape.name)

# drawShapes(sortedShapes)
    
