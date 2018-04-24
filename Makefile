# Micaelan Eger
# mte160230@utdallas.edu
# CS3377.002

CXX=g++
CXXFLAGS=-Wall -g 
CPPFLAGS=-I/scratch/perkins/include
LDFLAGS=-L/scratch/perkins/lib
LDLIBS=-lcdk -lcurses 

EXECFILE = cdkproj

OBJS = cdkproj.o


all:$(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*


$(EXECFILE):$(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename "'pwd'"))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo	
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME) 2> /dev/null
	@echo 600 $(MKBKUPNAME)
	@echo
	@echo Done!
