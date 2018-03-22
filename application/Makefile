CC := g++
SRCDIR := src
TESTDIR := test
RM := rm
BUILDDIR := build
BIN := bin
TARGET := main
TESTER := tester
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
SOURCESWITHOUTMAIN := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT) | grep -v "main.cpp")
SOURCESTEST := $(shell find $(TESTDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
OBJECTSTEST := $(patsubst $(TESTDIR)/%,$(BUILDDIR)/%,$(SOURCESTEST:.$(SRCEXT)=.o))
CFLAGS := -std=c++1z -g -Wall -fstack-protector -m64 -stdlib=libc++
LIB := -L lib/ -lpthread -lbotan-2 -L/usr/local/lib $(shell pkg-config --libs cppunit)
INC := -I include/ -I/usr/local/include/botan-2 $(shell pkg-config --cflags cppunit)


$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@mkdir -p $(BIN)
	@echo " $(CC) $(CFLAGS) $^ -o $(target)"; $(CC) $(CFLAGS) $^ $(LIB) $(INC) -o $(BIN)/$(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(shell dirname $@)
	@echo " $(CC) $(CFLAGS) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)/%.o: $(TESTDIR)/%.$(SRCEXT)
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

all: $(TARGET)

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR)/* $(TARGET)"; $(RM) -r $(BUILDDIR) $(BIN)

# Tests
test: $(OBJECTSTEST) $(OBJECTS)
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(INC) $(LIB) $(SOURCESTEST) $(SOURCESWITHOUTMAIN) -o bin/tester
