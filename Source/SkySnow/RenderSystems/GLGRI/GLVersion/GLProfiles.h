//
// Copyright(c) 2020 - 2022 the SkySnowEngine project.
// Open source is written by liuqian(SkySnow),zhangshuangxue(Calence)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright noticeand this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
/*
    WindowOS  : Import GLFunction Self,Include ThiryParty/Khronos/OpenGL.
                    Use DLL Pointer Address Import
                    Use wglGetPropAddress Import
                        GL Common Function Pointer
                        GL Option Function Pointer
    MacOS     : Not Import GLFunction Self,Include OS GL Header,And MacOS Use GL version below 4.x(<GL4.x).
                MacOS10.14 stop OpenGL Interface,so OpenGL Interface Support Simple
    LinuxOS   : Not Support OS.
    AndroidOS : Not Import GLFunction,Include OS GL Header,But Check Expansion String.
    IosOS     : Not Import GLFunction,Include OS GL Header,But Check Expansion String.
 */
#pragma once
#include "PlatformProfiles.h"
#include "GRICommons.h"
#if PLATFORM == PLATFORM_ANDROID
#	include <GLES3/gl3.h>
#	include <GLES3/gl3ext.h>
#elif PLATFORM == PLATFORM_IOS
#	include <OpenGLES/ES3/gl.h>
#	include <OpenGLES/ES3/glext.h>
	//GPU Simd
#	if __has_include(<simd/simd.h>)
#		ifndef WBSIMD
#			define WBSIMD
#		endif
#	endif
#elif PLATFORM == PLATFORM_WINDOW || PLATFORM == PLATFORM_MAC
#	define GLFW_INCLUDE_NONE
#	include <stdarg.h>
#	include <stdio.h>
#	include <GLFW/glfw3.h>
#   if PLATFORM == PLATFORM_WINDOW
#       define GLFW_EXPOSE_NATIVE_WIN32
#       define GLFW_EXPOSE_NATIVE_WGL
#       include <GL/glcorearb.h>
#       include <GL/glext.h>
#       include <GL/wglext.h>
#       define USE_GL4  1
#   elif PLATFORM == PLATFORM_MAC
#       define GLFW_EXPOSE_NATIVE_COCOA
#       define GLFW_EXPOSE_NATIVE_NSGL
#       define GL_SILENCE_DEPRECATION
#       include <OpenGL/OpenGL.h>
#       include <OpenGL/gl3.h>
#       include <OpenGL/gl3ext.h>
#       define USE_GL4  0
#   endif
#   include <GLFW/glfw3native.h>
#endif // 0
//This is Not good idea,so delete this class
class GLContext
{
public:
    GLContext(){};
    
    virtual ~GLContext(){};
    
    virtual void CreateGLContext() = 0;
    
    virtual void DestroyGLContext() = 0;
    
    virtual void MakeCurrContext() = 0;
    
};
namespace SkySnow
{
    void PlatformDeviceContextInit();
}
//About OS Platform Context:Example GLContext
struct PlatformDeviceContext;
//About OS Platform Device:Example Window for Window(OSWindow) for window(WindowHandle) for Android(NativeWindow)
struct PlatformDeviceInit;

#if PLATFORM == PLATFORM_WINDOW
#define GL_APIENTRYPOINTER_DLL(Macro)\
		Macro(PFNGLBINDTEXTUREPROC,glBindTexture) \
		Macro(PFNGLBLENDFUNCPROC,glBlendFunc) \
		Macro(PFNGLCOLORMASKPROC,glColorMask) \
		Macro(PFNGLCOPYTEXIMAGE1DPROC,glCopyTexImage1D) \
		Macro(PFNGLCOPYTEXIMAGE2DPROC,glCopyTexImage2D) \
		Macro(PFNGLCOPYTEXSUBIMAGE1DPROC,glCopyTexSubImage1D) \
		Macro(PFNGLCOPYTEXSUBIMAGE2DPROC,glCopyTexSubImage2D) \
		Macro(PFNGLCULLFACEPROC,glCullFace) \
		Macro(PFNGLDELETETEXTURESPROC,glDeleteTextures) \
		Macro(PFNGLDEPTHFUNCPROC,glDepthFunc) \
		Macro(PFNGLDEPTHMASKPROC,glDepthMask) \
		Macro(PFNGLDEPTHRANGEPROC,glDepthRange) \
		Macro(PFNGLDISABLEPROC,glDisable) \
		Macro(PFNGLDRAWARRAYSPROC,glDrawArrays) \
		Macro(PFNGLDRAWBUFFERPROC,glDrawBuffer) \
		Macro(PFNGLDRAWELEMENTSPROC,glDrawElements) \
		Macro(PFNGLENABLEPROC,glEnable) \
		Macro(PFNGLFINISHPROC,glFinish) \
		Macro(PFNGLFLUSHPROC,glFlush) \
		Macro(PFNGLFRONTFACEPROC,glFrontFace) \
		Macro(PFNGLGENTEXTURESPROC,glGenTextures) \
		Macro(PFNGLGETBOOLEANVPROC,glGetBooleanv) \
		Macro(PFNGLGETDOUBLEVPROC,glGetDoublev) \
		Macro(PFNGLGETERRORPROC,glGetError) \
		Macro(PFNGLGETFLOATVPROC,glGetFloatv) \
		Macro(PFNGLGETINTEGERVPROC,glGetIntegerv) \
		Macro(PFNGLGETPOINTERVPROC,glGetPointerv) \
		Macro(PFNGLGETSTRINGPROC,glGetString) \
		Macro(PFNGLGETTEXIMAGEPROC,glGetTexImage) \
		Macro(PFNGLGETTEXLEVELPARAMETERFVPROC,glGetTexLevelParameterfv) \
		Macro(PFNGLGETTEXLEVELPARAMETERIVPROC,glGetTexLevelParameteriv) \
		Macro(PFNGLGETTEXPARAMETERFVPROC,glGetTexParameterfv) \
		Macro(PFNGLGETTEXPARAMETERIVPROC,glGetTexParameteriv) \
		Macro(PFNGLHINTPROC,glHint) \
		Macro(PFNGLISENABLEDPROC,glIsEnabled) \
		Macro(PFNGLISTEXTUREPROC,glIsTexture) \
		Macro(PFNGLLINEWIDTHPROC,glLineWidth) \
		Macro(PFNGLLOGICOPPROC,glLogicOp) \
		Macro(PFNGLPIXELSTOREFPROC,glPixelStoref) \
		Macro(PFNGLPIXELSTOREIPROC,glPixelStorei) \
		Macro(PFNGLPOINTSIZEPROC,glPointSize) \
		Macro(PFNGLPOLYGONMODEPROC,glPolygonMode) \
		Macro(PFNGLPOLYGONOFFSETPROC,glPolygonOffset) \
		Macro(PFNGLREADBUFFERPROC,glReadBuffer) \
		Macro(PFNGLREADPIXELSPROC,glReadPixels) \
		Macro(PFNGLSCISSORPROC,glScissor) \
		Macro(PFNGLCLEARDEPTHPROC,glClearDepth) \
		Macro(PFNGLCLEARCOLORPROC,glClearColor) \
		Macro(PFNGLCLEARSTENCILPROC,glClearStencil) \
		Macro(PFNGLCLEARPROC,glClear) \
		Macro(PFNGLSTENCILFUNCPROC,glStencilFunc) \
		Macro(PFNGLSTENCILMASKPROC,glStencilMask) \
		Macro(PFNGLSTENCILOPPROC,glStencilOp) \
		Macro(PFNGLTEXIMAGE1DPROC,glTexImage1D) \
		Macro(PFNGLTEXIMAGE2DPROC,glTexImage2D) \
		Macro(PFNGLTEXPARAMETERFPROC,glTexParameterf) \
		Macro(PFNGLTEXPARAMETERFVPROC,glTexParameterfv) \
		Macro(PFNGLTEXPARAMETERIPROC,glTexParameteri) \
		Macro(PFNGLTEXPARAMETERIVPROC,glTexParameteriv) \
		Macro(PFNGLTEXSUBIMAGE1DPROC,glTexSubImage1D) \
		Macro(PFNGLTEXSUBIMAGE2DPROC,glTexSubImage2D) \
		Macro(PFNGLVIEWPORTPROC,glViewport)

#define GL_APIENTRYPOINTER(Macro)\
		Macro(PFNGLBINDSAMPLERPROC,glBindSampler) \
		Macro(PFNGLDELETESAMPLERSPROC,glDeleteSamplers) \
		Macro(PFNGLGENSAMPLERSPROC,glGenSamplers) \
		Macro(PFNGLSAMPLERPARAMETERIPROC,glSamplerParameteri) \
		Macro(PFNGLCLEARBUFFERFVPROC,glClearBufferfv) \
		Macro(PFNGLCLEARBUFFERIVPROC,glClearBufferiv) \
		Macro(PFNGLCLEARBUFFERUIVPROC,glClearBufferuiv) \
		Macro(PFNGLCLEARBUFFERFIPROC,glClearBufferfi) \
		Macro(PFNGLCOLORMASKIPROC,glColorMaski) \
		Macro(PFNGLDISABLEIPROC,glDisablei) \
		Macro(PFNGLENABLEIPROC,glEnablei) \
		Macro(PFNGLGETBOOLEANI_VPROC,glGetBooleani_v) \
		Macro(PFNGLGETINTEGERI_VPROC,glGetIntegeri_v) \
		Macro(PFNGLISENABLEDIPROC,glIsEnabledi) \
		Macro(PFNGLBLENDCOLORPROC,glBlendColor) \
		Macro(PFNGLBLENDEQUATIONPROC,glBlendEquation) \
		Macro(PFNGLDRAWRANGEELEMENTSPROC,glDrawRangeElements) \
		Macro(PFNGLTEXIMAGE3DPROC,glTexImage3D) \
		Macro(PFNGLTEXSUBIMAGE3DPROC,glTexSubImage3D) \
		Macro(PFNGLCOPYTEXSUBIMAGE3DPROC,glCopyTexSubImage3D) \
		Macro(PFNGLACTIVETEXTUREPROC,glActiveTexture) \
		Macro(PFNGLSAMPLECOVERAGEPROC,glSampleCoverage) \
		Macro(PFNGLCOMPRESSEDTEXIMAGE3DPROC,glCompressedTexImage3D) \
		Macro(PFNGLCOMPRESSEDTEXIMAGE2DPROC,glCompressedTexImage2D) \
		Macro(PFNGLCOMPRESSEDTEXIMAGE1DPROC,glCompressedTexImage1D) \
		Macro(PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC,glCompressedTexSubImage3D) \
		Macro(PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC,glCompressedTexSubImage2D) \
		Macro(PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC,glCompressedTexSubImage1D) \
		Macro(PFNGLGETCOMPRESSEDTEXIMAGEPROC,glGetCompressedTexImage) \
		Macro(PFNGLBLENDFUNCSEPARATEPROC,glBlendFuncSeparate) \
		Macro(PFNGLMULTIDRAWARRAYSPROC,glMultiDrawArrays) \
		Macro(PFNGLMULTIDRAWELEMENTSPROC,glMultiDrawElements) \
		Macro(PFNGLPOINTPARAMETERFPROC,glPointParameterf) \
		Macro(PFNGLPOINTPARAMETERFVPROC,glPointParameterfv) \
		Macro(PFNGLPOINTPARAMETERIPROC,glPointParameteri) \
		Macro(PFNGLPOINTPARAMETERIVPROC,glPointParameteriv) \
		Macro(PFNGLGENQUERIESPROC,glGenQueries) \
		Macro(PFNGLDELETEQUERIESPROC,glDeleteQueries) \
		Macro(PFNGLISQUERYPROC,glIsQuery) \
		Macro(PFNGLBEGINQUERYPROC,glBeginQuery) \
		Macro(PFNGLENDQUERYPROC,glEndQuery) \
		Macro(PFNGLGETQUERYIVPROC,glGetQueryiv) \
		Macro(PFNGLGETQUERYOBJECTIVPROC,glGetQueryObjectiv) \
		Macro(PFNGLGETQUERYOBJECTUIVPROC,glGetQueryObjectuiv) \
		Macro(PFNGLBINDBUFFERPROC,glBindBuffer) \
		Macro(PFNGLBINDBUFFERBASEPROC,glBindBufferBase) \
		Macro(PFNGLDELETEBUFFERSPROC,glDeleteBuffers) \
		Macro(PFNGLGENBUFFERSPROC,glGenBuffers) \
		Macro(PFNGLISBUFFERPROC,glIsBuffer) \
		Macro(PFNGLBUFFERDATAPROC,glBufferData) \
		Macro(PFNGLBUFFERSUBDATAPROC,glBufferSubData) \
		Macro(PFNGLGETBUFFERSUBDATAPROC,glGetBufferSubData) \
		Macro(PFNGLMAPBUFFERPROC,glMapBuffer) \
		Macro(PFNGLUNMAPBUFFERPROC,glUnmapBuffer) \
		Macro(PFNGLGETBUFFERPARAMETERIVPROC,glGetBufferParameteriv) \
		Macro(PFNGLGETBUFFERPOINTERVPROC,glGetBufferPointerv) \
		Macro(PFNGLBLENDEQUATIONSEPARATEPROC,glBlendEquationSeparate) \
		Macro(PFNGLDRAWBUFFERSPROC,glDrawBuffers) \
		Macro(PFNGLSTENCILOPSEPARATEPROC,glStencilOpSeparate) \
		Macro(PFNGLSTENCILFUNCSEPARATEPROC,glStencilFuncSeparate) \
		Macro(PFNGLSTENCILMASKSEPARATEPROC,glStencilMaskSeparate) \
		Macro(PFNGLATTACHSHADERPROC,glAttachShader) \
		Macro(PFNGLBINDATTRIBLOCATIONPROC,glBindAttribLocation) \
		Macro(PFNGLBINDFRAGDATALOCATIONPROC,glBindFragDataLocation) \
		Macro(PFNGLCOMPILESHADERPROC,glCompileShader) \
		Macro(PFNGLCREATEPROGRAMPROC,glCreateProgram) \
		Macro(PFNGLCREATESHADERPROC,glCreateShader) \
		Macro(PFNGLDELETEPROGRAMPROC,glDeleteProgram) \
		Macro(PFNGLDELETESHADERPROC,glDeleteShader) \
		Macro(PFNGLDETACHSHADERPROC,glDetachShader) \
		Macro(PFNGLDISABLEVERTEXATTRIBARRAYPROC,glDisableVertexAttribArray) \
		Macro(PFNGLENABLEVERTEXATTRIBARRAYPROC,glEnableVertexAttribArray) \
		Macro(PFNGLGETACTIVEATTRIBPROC,glGetActiveAttrib) \
		Macro(PFNGLGETACTIVEUNIFORMPROC,glGetActiveUniform) \
		Macro(PFNGLGETATTACHEDSHADERSPROC,glGetAttachedShaders) \
		Macro(PFNGLGETATTRIBLOCATIONPROC,glGetAttribLocation) \
		Macro(PFNGLGETPROGRAMIVPROC,glGetProgramiv) \
		Macro(PFNGLGETPROGRAMINFOLOGPROC,glGetProgramInfoLog) \
		Macro(PFNGLGETSHADERIVPROC,glGetShaderiv) \
		Macro(PFNGLGETSHADERINFOLOGPROC,glGetShaderInfoLog) \
		Macro(PFNGLGETSHADERSOURCEPROC,glGetShaderSource) \
		Macro(PFNGLGETUNIFORMLOCATIONPROC,glGetUniformLocation) \
		Macro(PFNGLGETUNIFORMBLOCKINDEXPROC,glGetUniformBlockIndex) \
		Macro(PFNGLGETUNIFORMFVPROC,glGetUniformfv) \
		Macro(PFNGLGETUNIFORMIVPROC,glGetUniformiv) \
		Macro(PFNGLGETVERTEXATTRIBDVPROC,glGetVertexAttribdv) \
		Macro(PFNGLGETVERTEXATTRIBFVPROC,glGetVertexAttribfv) \
		Macro(PFNGLGETVERTEXATTRIBIVPROC,glGetVertexAttribiv) \
		Macro(PFNGLGETVERTEXATTRIBPOINTERVPROC,glGetVertexAttribPointerv) \
		Macro(PFNGLISPROGRAMPROC,glIsProgram) \
		Macro(PFNGLISSHADERPROC,glIsShader) \
		Macro(PFNGLLINKPROGRAMPROC,glLinkProgram) \
		Macro(PFNGLSHADERSOURCEPROC,glShaderSource) \
		Macro(PFNGLUSEPROGRAMPROC,glUseProgram) \
		Macro(PFNGLUNIFORM1FPROC,glUniform1f) \
		Macro(PFNGLUNIFORM2FPROC,glUniform2f) \
		Macro(PFNGLUNIFORM3FPROC,glUniform3f) \
		Macro(PFNGLUNIFORM4FPROC,glUniform4f) \
		Macro(PFNGLUNIFORM1IPROC,glUniform1i) \
		Macro(PFNGLUNIFORM2IPROC,glUniform2i) \
		Macro(PFNGLUNIFORM3IPROC,glUniform3i) \
		Macro(PFNGLUNIFORM4IPROC,glUniform4i) \
		Macro(PFNGLUNIFORM1FVPROC,glUniform1fv) \
		Macro(PFNGLUNIFORM2FVPROC,glUniform2fv) \
		Macro(PFNGLUNIFORM3FVPROC,glUniform3fv) \
		Macro(PFNGLUNIFORM4FVPROC,glUniform4fv) \
		Macro(PFNGLUNIFORM1IVPROC,glUniform1iv) \
		Macro(PFNGLUNIFORM2IVPROC,glUniform2iv) \
		Macro(PFNGLUNIFORM3IVPROC,glUniform3iv) \
		Macro(PFNGLUNIFORM4IVPROC,glUniform4iv) \
		Macro(PFNGLUNIFORM1UIVPROC,glUniform1uiv) \
		Macro(PFNGLUNIFORM2UIVPROC,glUniform2uiv) \
		Macro(PFNGLUNIFORM3UIVPROC,glUniform3uiv) \
		Macro(PFNGLUNIFORM4UIVPROC,glUniform4uiv) \
		Macro(PFNGLUNIFORMBLOCKBINDINGPROC,glUniformBlockBinding) \
		Macro(PFNGLUNIFORMMATRIX2FVPROC,glUniformMatrix2fv) \
		Macro(PFNGLUNIFORMMATRIX3FVPROC,glUniformMatrix3fv) \
		Macro(PFNGLUNIFORMMATRIX4FVPROC,glUniformMatrix4fv) \
		Macro(PFNGLVALIDATEPROGRAMPROC,glValidateProgram) \
		Macro(PFNGLVERTEXATTRIB1DPROC,glVertexAttrib1d) \
		Macro(PFNGLVERTEXATTRIB1DVPROC,glVertexAttrib1dv) \
		Macro(PFNGLVERTEXATTRIB1FPROC,glVertexAttrib1f) \
		Macro(PFNGLVERTEXATTRIB1FVPROC,glVertexAttrib1fv) \
		Macro(PFNGLVERTEXATTRIB1SPROC,glVertexAttrib1s) \
		Macro(PFNGLVERTEXATTRIB1SVPROC,glVertexAttrib1sv) \
		Macro(PFNGLVERTEXATTRIB2DPROC,glVertexAttrib2d) \
		Macro(PFNGLVERTEXATTRIB2DVPROC,glVertexAttrib2dv) \
		Macro(PFNGLVERTEXATTRIB2FPROC,glVertexAttrib2f) \
		Macro(PFNGLVERTEXATTRIB2FVPROC,glVertexAttrib2fv) \
		Macro(PFNGLVERTEXATTRIB2SPROC,glVertexAttrib2s) \
		Macro(PFNGLVERTEXATTRIB2SVPROC,glVertexAttrib2sv) \
		Macro(PFNGLVERTEXATTRIB3DPROC,glVertexAttrib3d) \
		Macro(PFNGLVERTEXATTRIB3DVPROC,glVertexAttrib3dv) \
		Macro(PFNGLVERTEXATTRIB3FPROC,glVertexAttrib3f) \
		Macro(PFNGLVERTEXATTRIB3FVPROC,glVertexAttrib3fv) \
		Macro(PFNGLVERTEXATTRIB3SPROC,glVertexAttrib3s) \
		Macro(PFNGLVERTEXATTRIB3SVPROC,glVertexAttrib3sv) \
		Macro(PFNGLVERTEXATTRIB4NBVPROC,glVertexAttrib4Nbv) \
		Macro(PFNGLVERTEXATTRIB4NIVPROC,glVertexAttrib4Niv) \
		Macro(PFNGLVERTEXATTRIB4NSVPROC,glVertexAttrib4Nsv) \
		Macro(PFNGLVERTEXATTRIB4NUBPROC,glVertexAttrib4Nub) \
		Macro(PFNGLVERTEXATTRIB4NUBVPROC,glVertexAttrib4Nubv) \
		Macro(PFNGLVERTEXATTRIB4NUIVPROC,glVertexAttrib4Nuiv) \
		Macro(PFNGLVERTEXATTRIB4NUSVPROC,glVertexAttrib4Nusv) \
		Macro(PFNGLVERTEXATTRIB4BVPROC,glVertexAttrib4bv) \
		Macro(PFNGLVERTEXATTRIB4DPROC,glVertexAttrib4d) \
		Macro(PFNGLVERTEXATTRIB4DVPROC,glVertexAttrib4dv) \
		Macro(PFNGLVERTEXATTRIB4FPROC,glVertexAttrib4f) \
		Macro(PFNGLVERTEXATTRIB4FVPROC,glVertexAttrib4fv) \
		Macro(PFNGLVERTEXATTRIB4IVPROC,glVertexAttrib4iv) \
		Macro(PFNGLVERTEXATTRIB4SPROC,glVertexAttrib4s) \
		Macro(PFNGLVERTEXATTRIB4SVPROC,glVertexAttrib4sv) \
		Macro(PFNGLVERTEXATTRIB4UBVPROC,glVertexAttrib4ubv) \
		Macro(PFNGLVERTEXATTRIB4UIVPROC,glVertexAttrib4uiv) \
		Macro(PFNGLVERTEXATTRIB4USVPROC,glVertexAttrib4usv) \
		Macro(PFNGLVERTEXATTRIBI4IVPROC,glVertexAttribI4iv) \
		Macro(PFNGLVERTEXATTRIBI4UIVPROC,glVertexAttribI4uiv) \
		Macro(PFNGLVERTEXATTRIBI4SVPROC,glVertexAttribI4sv) \
		Macro(PFNGLVERTEXATTRIBI4USVPROC,glVertexAttribI4usv) \
		Macro(PFNGLVERTEXATTRIBI4BVPROC,glVertexAttribI4bv) \
		Macro(PFNGLVERTEXATTRIBI4UBVPROC,glVertexAttribI4ubv) \
		Macro(PFNGLVERTEXATTRIBPOINTERPROC,glVertexAttribPointer) \
		Macro(PFNGLVERTEXATTRIBIPOINTERPROC,glVertexAttribIPointer) \
		Macro(PFNGLUNIFORMMATRIX2X3FVPROC,glUniformMatrix2x3fv) \
		Macro(PFNGLUNIFORMMATRIX3X2FVPROC,glUniformMatrix3x2fv) \
		Macro(PFNGLUNIFORMMATRIX2X4FVPROC,glUniformMatrix2x4fv) \
		Macro(PFNGLUNIFORMMATRIX4X2FVPROC,glUniformMatrix4x2fv) \
		Macro(PFNGLUNIFORMMATRIX3X4FVPROC,glUniformMatrix3x4fv) \
		Macro(PFNGLUNIFORMMATRIX4X3FVPROC,glUniformMatrix4x3fv) \
		Macro(PFNGLISRENDERBUFFERPROC,glIsRenderbuffer) \
		Macro(PFNGLBINDRENDERBUFFERPROC,glBindRenderbuffer) \
		Macro(PFNGLDELETERENDERBUFFERSPROC,glDeleteRenderbuffers) \
		Macro(PFNGLGENRENDERBUFFERSPROC,glGenRenderbuffers) \
		Macro(PFNGLRENDERBUFFERSTORAGEPROC,glRenderbufferStorage) \
		Macro(PFNGLGETRENDERBUFFERPARAMETERIVPROC,glGetRenderbufferParameteriv) \
		Macro(PFNGLISFRAMEBUFFERPROC,glIsFramebuffer) \
		Macro(PFNGLBINDFRAMEBUFFERPROC,glBindFramebuffer) \
		Macro(PFNGLDELETEFRAMEBUFFERSPROC,glDeleteFramebuffers) \
		Macro(PFNGLGENFRAMEBUFFERSPROC,glGenFramebuffers) \
		Macro(PFNGLCHECKFRAMEBUFFERSTATUSPROC,glCheckFramebufferStatus) \
		Macro(PFNGLFRAMEBUFFERTEXTURE1DPROC,glFramebufferTexture1D) \
		Macro(PFNGLFRAMEBUFFERTEXTURE2DPROC,glFramebufferTexture2D) \
		Macro(PFNGLFRAMEBUFFERTEXTURE3DPROC,glFramebufferTexture3D) \
		Macro(PFNGLFRAMEBUFFERTEXTUREPROC,glFramebufferTexture) \
		Macro(PFNGLFRAMEBUFFERRENDERBUFFERPROC,glFramebufferRenderbuffer) \
		Macro(PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC,glGetFramebufferAttachmentParameteriv) \
		Macro(PFNGLGENERATEMIPMAPPROC,glGenerateMipmap) \
		Macro(PFNGLBLITFRAMEBUFFERPROC,glBlitFramebuffer) \
		Macro(PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC,glRenderbufferStorageMultisample) \
		Macro(PFNGLFRAMEBUFFERTEXTURELAYERPROC,glFramebufferTextureLayer) \
		Macro(PFNGLMAPBUFFERRANGEPROC,glMapBufferRange) \
		Macro(PFNGLFLUSHMAPPEDBUFFERRANGEPROC,glFlushMappedBufferRange) \
		Macro(PFNGLVERTEXATTRIBDIVISORPROC,glVertexAttribDivisor) \
		Macro(PFNGLDRAWARRAYSINSTANCEDPROC,glDrawArraysInstanced) \
		Macro(PFNGLDRAWELEMENTSINSTANCEDPROC,glDrawElementsInstanced) \
		Macro(PFNGLGETSTRINGIPROC,glGetStringi) \
		Macro(PFNGLGENVERTEXARRAYSPROC,glGenVertexArrays) \
		Macro(PFNGLDELETEVERTEXARRAYSPROC,glDeleteVertexArrays) \
		Macro(PFNGLBINDVERTEXARRAYPROC,glBindVertexArray) \
		Macro(PFNGLCOPYBUFFERSUBDATAPROC,glCopyBufferSubData) \
		Macro(PFNGLTEXBUFFERPROC,glTexBuffer) \
		Macro(PFNGLTEXIMAGE2DMULTISAMPLEPROC,glTexImage2DMultisample) \
		Macro(PFNGLQUERYCOUNTERPROC, glQueryCounter)\
		Macro(PFNGLISSYNCPROC, glIsSync)\
		Macro(PFNGLDELETESYNCPROC, glDeleteSync)\
		Macro(PFNGLGETQUERYOBJECTUI64VPROC, glGetQueryObjectui64v)\
		Macro(PFNGLFENCESYNCPROC, glFenceSync)\
		Macro(PFNGLGETSYNCIVPROC, glGetSynciv)\
		Macro(PFNGLCLIENTWAITSYNCPROC, glClientWaitSync)\
		Macro(PFNGLBINDBUFFERRANGEPROC, glBindBufferRange)

#define GL_APIENTRYPOINTS_OPTIONAL(Macro)\
		Macro(PFNGLCLIPCONTROLPROC,glClipControl) \
		Macro(PFNGLDEBUGMESSAGECALLBACKARBPROC,glDebugMessageCallbackARB) \
		Macro(PFNGLDEBUGMESSAGECONTROLARBPROC,glDebugMessageControlARB) \
		Macro(PFNGLDEBUGMESSAGECALLBACKAMDPROC,glDebugMessageCallbackAMD) \
		Macro(PFNGLDEBUGMESSAGEENABLEAMDPROC,glDebugMessageEnableAMD) \
		Macro(PFNGLGETACTIVEUNIFORMSIVPROC,glGetActiveUniformsiv) \
		Macro(PFNGLGETVERTEXATTRIBIUIVPROC,glGetVertexAttribIuiv) \
		Macro(PFNGLGETACTIVEUNIFORMNAMEPROC,glGetActiveUniformName) \
		Macro(PFNGLGETUNIFORMUIVPROC,glGetUniformuiv) \
		Macro(PFNGLGETACTIVEUNIFORMBLOCKIVPROC,glGetActiveUniformBlockiv) \
		Macro(PFNGLGETBUFFERPARAMETERI64VPROC,glGetBufferParameteri64v) \
		Macro(PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC,glGetActiveUniformBlockName) \
		Macro(PFNGLGETSAMPLERPARAMETERFVPROC,glGetSamplerParameterfv) \
		Macro(PFNGLGETSAMPLERPARAMETERIVPROC,glGetSamplerParameteriv) \
		Macro(PFNGLDISPATCHCOMPUTEPROC, glDispatchCompute) \
		Macro(PFNGLDISPATCHCOMPUTEINDIRECTPROC, glDispatchComputeIndirect) \
		Macro(PFNGLBINDIMAGETEXTUREPROC, glBindImageTexture) \
		Macro(PFNGLMEMORYBARRIERPROC, glMemoryBarrier) \
		Macro(PFNGLBLENDEQUATIONIPROC, glBlendEquationi) \
		Macro(PFNGLBLENDEQUATIONSEPARATEIPROC, glBlendEquationSeparatei) \
		Macro(PFNGLBLENDFUNCIPROC, glBlendFunci) \
		Macro(PFNGLBLENDFUNCSEPARATEIPROC, glBlendFuncSeparatei)\
		Macro(PFNGLBLENDEQUATIONSEPARATEIARBPROC,glBlendEquationSeparateiARB)\
		Macro(PFNGLBLENDEQUATIONIARBPROC,glBlendEquationiARB)\
		Macro(PFNGLBLENDFUNCSEPARATEIARBPROC,glBlendFuncSeparateiARB)\
		Macro(PFNGLBLENDFUNCIARBPROC,glBlendFunciARB)\
		Macro(PFNGLCLEARBUFFERDATAPROC, glClearBufferData)\
		Macro(PFNGLCLEARBUFFERSUBDATAPROC, glClearBufferSubData)\
		Macro(PFNGLPUSHDEBUGGROUPPROC, glPushDebugGroup)\
		Macro(PFNGLPOPDEBUGGROUPPROC, glPopDebugGroup)\
		Macro(PFNGLOBJECTLABELPROC, glObjectLabel)\
		Macro(PFNGLOBJECTLABELPROC, glObjectPtrLabel)\
		Macro(PFNGLPATCHPARAMETERIPROC, glPatchParameteri)\
		Macro(PFNGLBINDVERTEXBUFFERPROC, glBindVertexBuffer)\
		Macro(PFNGLVERTEXATTRIBFORMATPROC, glVertexAttribFormat)\
		Macro(PFNGLVERTEXATTRIBIFORMATPROC, glVertexAttribIFormat)\
		Macro(PFNGLVERTEXATTRIBBINDINGPROC, glVertexAttribBinding)\
		Macro(PFNGLVERTEXBINDINGDIVISORPROC, glVertexBindingDivisor)\
		Macro(PFNGLCOPYIMAGESUBDATAPROC, glCopyImageSubData)\
		Macro(PFNGLTEXSTORAGE1DPROC, glTexStorage1D)\
		Macro(PFNGLTEXSTORAGE2DPROC, glTexStorage2D)\
		Macro(PFNGLTEXSTORAGE3DPROC, glTexStorage3D)\
		Macro(PFNGLBUFFERSTORAGEPROC, glBufferStorage)\
		Macro(PFNGLTEXTUREVIEWPROC, glTextureView)\
		Macro(PFNGLTEXSTORAGE2DMULTISAMPLEPROC, glTexStorage2DMultisample)\
		Macro(PFNGLDRAWELEMENTSINDIRECTPROC, glDrawElementsIndirect)\
		Macro(PFNGLDRAWARRAYSINDIRECTPROC, glDrawArraysIndirect)\
		Macro(PFNGLDEPTHBOUNDSEXTPROC, glDepthBoundsEXT)\
		Macro(PFNGLGETTEXTUREHANDLENVPROC, glGetTextureHandleARB)\
		Macro(PFNGLGETTEXTURESAMPLERHANDLENVPROC, glGetTextureSamplerHandleARB)\
		Macro(PFNGLMAKETEXTUREHANDLERESIDENTNVPROC, glMakeTextureHandleResidentARB)\
		Macro(PFNGLUNIFORMHANDLEUI64NVPROC, glUniformHandleui64ARB)\
		Macro(PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC, glMakeTextureHandleNonResidentARB)\
		Macro(PFNGLPUSHDEBUGGROUPPROC, glPushDebugGroupKHR)\
		Macro(PFNGLPOPDEBUGGROUPPROC, glPopDebugGroupKHR)\
		Macro(PFNGLOBJECTLABELPROC, glObjectLabelKHR)\
		Macro(PFNGLOBJECTLABELPROC, glObjectPtrLabelKHR)\
		Macro(PFNGLDEBUGMESSAGECALLBACKARBPROC,glDebugMessageCallbackKHR) \
		Macro(PFNGLDEBUGMESSAGECONTROLARBPROC,glDebugMessageControlKHR) \
		Macro(PFNGLPATCHPARAMETERIPROC, glPatchParameteriEXT)\
		Macro(PFNGLTEXTUREVIEWPROC, glTextureViewEXT)\
		Macro(PFNGLBLENDEQUATIONIPROC, glBlendEquationiEXT) \
		Macro(PFNGLBLENDEQUATIONSEPARATEIPROC, glBlendEquationSeparateiEXT) \
		Macro(PFNGLBLENDFUNCIPROC, glBlendFunciEXT) \
		Macro(PFNGLBLENDFUNCSEPARATEIPROC, glBlendFuncSeparateiEXT)\
		Macro(PFNGLCOLORMASKIPROC,glColorMaskiEXT) \
		Macro(PFNGLDISABLEIPROC,glDisableiEXT) \
		Macro(PFNGLENABLEIPROC,glEnableiEXT) \
		Macro(PFNGLFRAMEBUFFERTEXTUREPROC,glFramebufferTextureEXT) \
		Macro(PFNGLCOPYIMAGESUBDATAPROC, glCopyImageSubDataEXT) \
		Macro(PFNGLTEXBUFFERPROC,glTexBufferEXT) \
		Macro(PFNGLDEPTHRANGEFPROC,glDepthRangef) \
		Macro(PFNGLCLEARDEPTHFPROC,glClearDepthf) \
		Macro(PFNGLGETSHADERPRECISIONFORMATPROC, glGetShaderPrecisionFormat) \
		Macro(PFNGLPROGRAMPARAMETERIPROC, glProgramParameteri) \
		Macro(PFNGLUSEPROGRAMSTAGESPROC, glUseProgramStages) \
		Macro(PFNGLBINDPROGRAMPIPELINEPROC, glBindProgramPipeline) \
		Macro(PFNGLDELETEPROGRAMPIPELINESPROC, glDeleteProgramPipelines) \
		Macro(PFNGLGENPROGRAMPIPELINESPROC, glGenProgramPipelines) \
		Macro(PFNGLPROGRAMUNIFORM1IPROC, glProgramUniform1i) \
		Macro(PFNGLPROGRAMUNIFORM4IVPROC, glProgramUniform4iv) \
		Macro(PFNGLPROGRAMUNIFORM4FVPROC, glProgramUniform4fv) \
		Macro(PFNGLPROGRAMUNIFORM4UIVPROC, glProgramUniform4uiv) \
		Macro(PFNGLGETPROGRAMPIPELINEIVPROC, glGetProgramPipelineiv) \
		Macro(PFNGLVALIDATEPROGRAMPIPELINEPROC, glValidateProgramPipeline) \
		Macro(PFNGLGETPROGRAMPIPELINEINFOLOGPROC, glGetProgramPipelineInfoLog) \
		Macro(PFNGLISPROGRAMPIPELINEPROC, glIsProgramPipeline) \
		Macro(PFNGLGETPROGRAMBINARYPROC, glGetProgramBinary) \
		Macro(PFNGLPROGRAMBINARYPROC, glProgramBinary)

#define DECLARE_GL_APIENTRYPOINTS(FunType,Fun) extern FunType __declspec(dllexport) Fun;
		GL_APIENTRYPOINTER_DLL(DECLARE_GL_APIENTRYPOINTS);
		GL_APIENTRYPOINTER(DECLARE_GL_APIENTRYPOINTS);
		GL_APIENTRYPOINTS_OPTIONAL(DECLARE_GL_APIENTRYPOINTS);
#undef DECLARE_GL_APIENTRYPOINTS
#endif // PLATFORM == PLATFORM_WINDOW
