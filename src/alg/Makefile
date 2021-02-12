PROJECT = alg
VISSRCPATH = ..
BINDINGS = lua/algtolua5.cpp lua/algtolua5.h
include $(VISSRCPATH)/../xp/MakefileLib

%.c: %.lua 
	$(LUAC5) -o temp.l $<
	$(BIN2C5) temp.l > $@
	rm -f temp.l

lua/algtolua5.cpp lua/algtolua5.h: lua/alg.pkg
	$(TOLUA5) -o lua/algtolua5.cpp -H lua/algtolua5.h -n alg $<
