include ${ROOT}\config\config.mingw.Mk
include ${ROOT}\config\config.Mk

_BINDIR=${ROOT}\bin
_BIN=${_BINDIR}\${LOCAL_BIN}

_CPP=$(shell dir *.cpp /b /s)
_OBJ=$(_CPP:.cpp=.o)

.SUFFIXES: .o .cpp

all: ${_BIN}

${_BINDIR}:
	mkdir ${_BINDIR}

${_BIN}: ${_BINDIR} ${_OBJ}
	${CXX} -o ${_BIN} ${_OBJ} ${LOCAL_LDFLAGS} ${LDFLAGS}

.cpp.o:
	${CXX} -c ${LOCAL_CXXFLAGS} ${CXXFLAGS} -o $@ $<

clean:
	-del /Q ${_OBJ} 2>nul
	-del /Q ${_BIN} 2>nul
	-rmdir /Q ${_BINDIR} 2>nul

