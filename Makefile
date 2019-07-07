CC				:= g++
SRCDIR		:= src
BUILDDIR	:= build
TARGET		:= dist/pizza

CFLAGS		:= -std=c++11 -g

SRCEXT		:= cpp
SOURCES 	:= $(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS		:= $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))
# LIB 		:= -L lib
# INC		:= -I include

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo " Building..."
	@mkdir -p $(BUILDDIR)
	# @echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@echo " $(CC) $(CFLAGS) -c -o $@ $<"; $(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@mkdir -p dist
	# @echo " $(CC) $(CFLAGS) $(LIB) -o $@ $^"; $(CC) $(CFLAGS) $(LIB) -o $@ $^
	@echo " $(CC) $(CFLAGS) -o $@ $^"; $(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	@echo " Cleaning..."
	@echo " $(RM) -r $(BUILDDIR) $(OBJECTS)"; $(RM) -r $(BUILDDIR) $(OBJECTS)
