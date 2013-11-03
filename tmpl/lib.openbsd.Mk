include ${ROOT}/config/config.openbsd.Mk
include ${ROOT}/config/config.Mk

_LIBDIR=${ROOT}/lib
_LIB=${_LIBDIR}/${LOCAL_LIB}

_CPP=$(shell find . -name '*.cpp')
_OBJ=$(_CPP:.cpp=.o)

.SUFFIXES: .o .cpp

all: ${_LIB}

${_LIBDIR}:
	mkdir -p ${_LIBDIR}

${_LIB}: ${_LIBDIR} ${_OBJ}
	${AR} rcs ${_LIB} ${_OBJ}

.cpp.o:
	${CXX} -c ${LOCAL_CXXFLAGS} ${CXXFLAGS} -o $@ $<

clean:
	rm -f ${_OBJ}
	rm -f ${_LIB}
	rm -r -f ${_LIBDIR}

