#ifdef ANDROID_ES
#include <GLES3/gl32.h>
#else
#define GLEW_STATIC	
#include <GL/gl3w.h>
#endif