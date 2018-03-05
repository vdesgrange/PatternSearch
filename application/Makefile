CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := bin/main
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -std=c++1z -g -Wall
LIB := -L lib/ $(pkg-config --libs opencv)
INC := -I include/ $(pkg-config --cflags opencv)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ $(LIB) -o $(TARGET)"; $(CC) $^ $(LIB) $(INC) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR)/% $(TARGET)"; $(RM) -r $(BUILDDIR)/% $(TARGET)

# Tests
test:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester
