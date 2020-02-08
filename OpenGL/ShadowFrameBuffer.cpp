#include "ShadowFrameBuffer.h"
#include <glm.hpp>
#include "glad.h"
#include "TheScreen.h"


ShadowFrameBuffer::ShadowFrameBuffer()
{
}

ShadowFrameBuffer::ShadowFrameBuffer(int width, int height)
{
	WIDTH = width;
	HEIGHT = height;
	initialiseFrameBuffer();
}

void ShadowFrameBuffer::cleanUp()
{
}

void ShadowFrameBuffer::bindFrameBuffer()
{
	bindFrameBuffer(fbo, WIDTH, HEIGHT);
}

void ShadowFrameBuffer::unbindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	int w;
	int h;
	TheScreen::Instance()->GetScreenSize(w, h);

	glViewport(0, 0, w, h);
}

int ShadowFrameBuffer::getShadowMap()
{
	return ShadowMap;
}

void ShadowFrameBuffer::initialiseFrameBuffer()
{
	fbo = createFrameBuffer();
	ShadowMap = createDepthBufferAttachment(WIDTH, HEIGHT);
	unbindFrameBuffer();
}

void ShadowFrameBuffer::bindFrameBuffer(int frameBuffer, int width, int height)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);
	glViewport(0, 0, width, height);
}

int ShadowFrameBuffer::createFrameBuffer()
{
	 glGenFramebuffers(1, &depthMapFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	return depthMapFBO;
}

int ShadowFrameBuffer::createDepthBufferAttachment(int width, int height)
{
	return 0;
}
