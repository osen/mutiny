#include "RenderTexture.h"
#include "Color.h"
#include "Application.h"
#include "Screen.h"
#include "Debug.h"

#include <GL/glew.h>

#include <memory>
#include <functional>
#include <vector>
#include <iostream>

namespace mutiny
{

namespace engine
{

shared<RenderTexture> RenderTexture::create(int width, int height)
{
  shared<RenderTexture> rtn(new RenderTexture());
  rtn->width = width;
  rtn->height = height;

  rtn->nativeFrameBuffer = gl::Uint::genFramebuffer();
  glBindFramebuffer(GL_FRAMEBUFFER, rtn->nativeFrameBuffer->getGLuint());

  if(rtn->nativeTexture.get() == NULL)
  {
    rtn->nativeTexture = gl::Uint::genTexture();
  }

  glBindTexture(GL_TEXTURE_2D, rtn->nativeTexture->getGLuint());

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

  rtn->nativeRenderBuffer = gl::Uint::genRenderbuffer();
  glBindRenderbuffer(GL_RENDERBUFFER, rtn->nativeRenderBuffer->getGLuint());
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rtn->nativeRenderBuffer->getGLuint());

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rtn->nativeTexture->getGLuint(), 0);

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
  {
    Debug::logWarning("Failed to create FBO configuration");
  }

  glBindTexture(GL_TEXTURE_2D, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);

  return rtn;
}

RenderTexture::~RenderTexture()
{

}

void RenderTexture::setActive(ref<RenderTexture> renderTexture)
{
  if(Application::context->active.try_get() == renderTexture.try_get())
  {
    return;
  }

  if(renderTexture.valid())
  {
    glBindFramebuffer(GL_FRAMEBUFFER, renderTexture->nativeFrameBuffer->getGLuint());
    glViewport(0, 0, renderTexture->width, renderTexture->height);
  }
  else
  {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Screen::getWidth(), Screen::getHeight());
  }

  Application::context->active = renderTexture;
}

ref<RenderTexture> RenderTexture::getActive()
{
  return Application::context->active;
}

}

}

