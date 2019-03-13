#include "ProgramRenderer.h"

ProgramRenderer::ProgramRenderer(const char * vPathRender, const char * fPathRender) :
	program(vPathRender, fPathRender)
{
	createUniforms();
}

ProgramRenderer::~ProgramRenderer()
{
}
