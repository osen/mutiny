include ${ROOT}/config/config.openbsd.Mk
include ${ROOT}/config/config.Mk

_BINDIR=${ROOT}/bin
_BIN=${_BINDIR}/${LOCAL_BIN}

_CPP=$(shell find . -name '*.cpp')
_OBJ=$(_CPP:.cpp=.o)

.SUFFIXES: .o .cpp

all: ${_BIN}

${_BINDIR}:
	mkdir -p ${_BINDIR}

${_BIN}: ${_BINDIR} ${_OBJ}
	${CXX} -o ${_BIN} ${_OBJ} ${LOCAL_LDFLAGS} ${LDFLAGS}

.cpp.o:
	${CXX} -c ${LOCAL_CXXFLAGS} ${CXXFLAGS} -o $@ $<

clean:
	rm -f ${_OBJ}
	rm -f ${_BIN}
	rm -r -f ${_BINDIR}

