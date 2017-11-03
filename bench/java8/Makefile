JAVA=/usr/bin/java
JAVAC=/usr/bin/javac

all : bin/Shapes.class

bin/Shapes.class : src/Shapes.java
	$(JAVAC) -d bin -s src src/Shapes.java

run : bin/Shapes.class
	$(JAVA) -cp bin Shapes
