# Makefile for project file_structures 
	

#
# My first generic Makefile

CC := g++ # Main compiler
# CC := clang --analyze # Other compiler, Very good Clang XD 
#SRCDIR := src 
#BUILDDIR := build
#TARGET := bin/runner
SRCEXT := cc
#SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
#OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -Wall -g
#LIB := -pthread -L lib -lboost_thread-mt -lboost_filesystem-mt -lboost_system-mt # libs bootst
INC := -I include # add Include for my project

mainmake: main.cc 
	@echo ":::::  Project File Structures ::::: "
	@echo ""
	@echo ":: wait a moment, please,  Compiling [entity] .......... Ok "
	@g++ -c entity.cc
	@echo ":: wait a moment, please,  Compiling [attribute] .......... Ok "
	@g++ -c attribute.cc
	@echo ":: wait a moment, please,  Compiling [data_dictionary_file] .......... Ok "
	@g++ -c data_dictionary_file.cc
	@echo ":: wait a moment, please,  Compiling [view] .......... Ok "
	@g++ -c view.cc
	@echo ":: wait a moment, please,  Linking [all project] .......... Ok "
	@g++ -o app main.cc entity.o attribute.o data_dictionary_file.o view.o

#$(TARGET): $(OBJECTS)
#  @echo " =======> Linking ... ";
#  @echo " =======> $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

#$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
#  @mkdir -p $(BUILDDIR)
#  @echo " =======> $(CC) $(CFLAGS) $(INC) -c -o $@ $&lt;"; $(CC) $(CFLAGS) $(INC) -c -o $@ $&lt;

#clean:
#	@echo " =======> Cleaning ..."; 
#	@echo " =======> $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
#tester:
#	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester
#
#.PHONY: clean

