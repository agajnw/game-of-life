CXX = @g++
RESULT = zycie
FILES = gra gui osobniki main

CXXFLAGS = -ggdb
LDFLAGS = -g -lncurses -lpthread

OBJDIR = obj
SRCDIR = src
INCDIR = include

SOURCES = ${FILES:%=${SRCDIR}/%.c}
OBJECTS = ${FILES:%=${OBJDIR}/%.o}

CXXFLAGS += -I${INCDIR} -I/usr/local/include -Wall

all: ${RESULT}
	@echo ""
	@echo ""
	@echo "Kompilacja zakonczona pomyslnie!"
	@echo ""

${RESULT}: ${OBJECTS}
	@echo ""
	@echo ""
	@echo ""
	@echo -n "\033[01;37mLinkowanie...\033[00m					"
	${CXX} ${LDFLAGS} -o ${RESULT} ${OBJECTS}
	@echo "[\033[01;32mOK\033[00m]"

${OBJDIR}/%.o: ${SRCDIR}/%.c
	@echo ""
	@echo -n "Kompiluje \033[01;37m$<\033[00m...				"
	$(CXX) ${CXXFLAGS} -c -o $@ $<
	@echo -n "[\033[01;32mOK\033[00m]"

clean:
	@echo ""
	@echo -n "\033[01;37mUsuwanie...\033[00m					"
	@rm -rf ${OBJECTS} ${RESULTS}
	@echo "[\033[01;32mOK\033[00m]"
	@echo ""
	@echo "Skompilowana gra zostala usunieta."
	@echo ""
