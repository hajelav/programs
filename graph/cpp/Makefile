# project name (generate executable with this name)
TARGET   = graph

CC       = g++
# compiling flags here
CFLAGS   = -g -Wall -I. -std=c++11

LINKER   = g++ -g -o
# linking flags here
LFLAGS   = -Wall -I. -lm

LDFLAGS  = -pthread

# change these to set the proper directories where each files should be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm        = rm -f


$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(LDFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"

.PHONY: count
count:
	find . -type f -name "*.h"|xargs wc -l
	find . -type f -name "*.cpp"|xargs wc -l
	@echo "Lines of code counted!"


