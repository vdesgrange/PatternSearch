CC := g++
SRCDIR := src
RM := rm
BUILDDIR := build
TARGET := bin/main
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -std=c++1z -g -Wall -fstack-protector -m64 -stdlib=libc++
LIB := -L lib/ -lpthread -lbotan-2 -L/usr/local/lib $(shell pkg-config --libs opencv)
INC := -I include/ -I/usr/local/include/botan-2 $(shell pkg-config --cflags opencv)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(target)"; $(CC) $^ $(LIB) $(INC) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(shell dirname $@)
	@echo " $(CC) $(CFLAGS) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR)/* $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
test:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester
