include ${ROOT}/config/config.freebsd.Mk
include ${ROOT}/config/config.Mk

_BINDIR=${ROOT}/bin
_BIN=${LOCAL_BIN}

_LIBDIR=${ROOT}/lib
_LIB=${LOCAL_LIB}

_CPP=$(shell find . -name '*.cpp')
_OBJ=$(_CPP:.cpp=.o)

.SUFFIXES: .o .cpp

all: ${_LIB} ${_BIN}

${_LIB}: ${_OBJ}
	mkdir -p ${_LIBDIR}
	${AR} rcs ${_LIB} ${_OBJ}

${_BIN}: ${_OBJ}
	mkdir -p ${_BINDIR}
	${CXX} -o ${_BIN} ${_OBJ} ${LOCAL_LDFLAGS} ${LDFLAGS}

.cpp.o:
	${CXX} -c ${LOCAL_CXXFLAGS} ${CXXFLAGS} -o $@ $<

clean:
	rm -f ${_OBJ}
	rm -f ${_BIN}
	rm -r -f ${_BINDIR}
	rm -f ${_LIB}
	rm -r -f ${_LIBDIR}

