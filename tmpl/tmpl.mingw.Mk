include ${ROOT}\config\config.mingw.Mk
include ${ROOT}\config\config.Mk

_LIBDIR=${ROOT}\lib
_LIB=${LOCAL_LIB}

_BINDIR=${ROOT}\bin
_BIN=${LOCAL_BIN}

_CPP=$(shell dir *.cpp /b /s)
_OBJ=$(_CPP:.cpp=.o)

.SUFFIXES: .o .cpp

all: ${_LIB} ${_BIN}

${_LIB}: ${_OBJ}
	-mkdir ${_LIBDIR}
	${AR} rcs ${_LIB} ${_OBJ}

${_BIN}: ${_OBJ}
	-mkdir ${_BINDIR}
	${CXX} -o ${_BIN} ${_OBJ} ${LOCAL_LDFLAGS} ${LDFLAGS}

.cpp.o:
	${CXX} -c ${LOCAL_CXXFLAGS} ${CXXFLAGS} -o $@ $<

clean:
	-del /Q ${_OBJ} 2>nul
	-del /Q ${_LIB} 2>nul
	-rmdir /Q ${_LIBDIR} 2>nul
	-del /Q ${_BIN} 2>nul
	-rmdir /Q ${_BINDIR} 2>nul
