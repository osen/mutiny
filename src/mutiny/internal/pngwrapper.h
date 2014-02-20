#ifdef USE_LIBPNG

#ifndef WRAPPER_PNGWRAPPER_H
#define WRAPPER_PNGWRAPPER_H

#include <GL/glew.h>

#include <string>

int pngwrapper_load(std::string path);
void pngwrapper_unload(int id);
int pngwrapper_width(int id);
int pngwrapper_height(int id);
void pngwrapper_texture(int id);

#endif

#endif