CC := g++
SRCDIR := src
RM := rm
BUILDDIR := build
TARGET := bin/main
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -std=c++1z -g -Wall
LIB := -L lib/ -L /usr/local/opt/botan/lib/ $(shell pkg-config --libs opencv)
INC := -I include/ $(shell pkg-config --cflags opencv) -I /usr/local/opt/botan/include/botan-2/

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -L $(LIB) -o $(TARGET)"; $(CC) $^ $(LIB) $(INC) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(shell dirname $@)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR)/* $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
test:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester
