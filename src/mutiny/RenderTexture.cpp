#include "RenderTexture.h"
#include "Color.h"
#include "Application.h"
#include "Screen.h"
#include "Debug.h"

#include <GL/glew.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
//#include <SDL/SDL_rotozoom.h>

#include <memory>
#include <functional>
#include <vector>
#include <iostream>

namespace mutiny
{

namespace engine
{

RenderTexture::RenderTexture(int width, int height)
{
  this->width = width;
  this->height = height;

  glGenFramebuffers(1, &nativeFrameBuffer);
  _nativeFrameBuffer.reset(&nativeFrameBuffer, std::bind(deleteFramebuffer, nativeFrameBuffer));
  glBindFramebuffer(GL_FRAMEBUFFER, nativeFrameBuffer);

  if(nativeTexture == -1)
  {
    glGenTextures(1, &nativeTexture);
    _nativeTexture.reset(&nativeTexture, std::bind(deleteTexture, nativeTexture));
  }

  glBindTexture(GL_TEXTURE_2D, nativeTexture);

  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

  //glGenerateMipmapEXT(GL_TEXTURE_2D);

  glGenRenderbuffers(1, &nativeRenderBuffer);
  _nativeRenderBuffer.reset(&nativeRenderBuffer, std::bind(deleteRenderbuffer, nativeRenderBuffer));
  glBindRenderbuffer(GL_RENDERBUFFER, nativeRenderBuffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, nativeRenderBuffer);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, nativeTexture, 0);

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
  {
    Debug::logWarning("Failed to create FBO configuration");
  }

  glBindTexture(GL_TEXTURE_2D, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

RenderTexture::~RenderTexture()
{

}

void RenderTexture::disable()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glViewport(0, 0, Screen::getWidth(), Screen::getHeight());
}

void RenderTexture::setEnabled(bool enabled)
{
  if(enabled == true)
  {
    glBindFramebuffer(GL_FRAMEBUFFER, nativeFrameBuffer);
    glViewport(0, 0, width, height);
  }
  else
  {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Screen::getWidth(), Screen::getHeight());
  }
}

}

}

