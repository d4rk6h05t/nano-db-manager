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
	@echo "wait a moment, please ..."
	@echo ":: Compiling [entity] ........................ Ok "
	@g++ -c entity.cc
	@echo ":: Compiling [attribute] ..................... Ok "
	@g++ -c attribute.cc
	@echo ":: Compiling [data_dictionary_file] .......... Ok "
	@g++ -c data_dictionary_file.cc
	@echo ":: Compiling [view] .......................... Ok "
	@g++ -c view.cc
	@echo ":: Linking [all project] ..................... Ok "
	@g++ -o app main.cc entity.o attribute.o data_dictionary_file.o view.o

clean:
	@echo ":::::  Project File Structures ::::: "
	@echo "wait a moment, please ..."
	
	@echo ":: Remove from project [app] ................... Ok "
	@rm -f app || true 
	@echo ":: Remove from project [*.o] ................... Ok "
	@rm  -f *.o || true 
	@echo ":: Remove from project [*.dat] ................. Ok "
	@rm -f *.dat || true
	
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

