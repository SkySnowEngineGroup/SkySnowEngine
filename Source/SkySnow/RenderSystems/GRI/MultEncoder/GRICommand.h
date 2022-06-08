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
#pragma once
//Commandbuffer encoding render commands are encoded in units of one pipeline and submitted in units of one pipeline 
//Command commit to CommandBuffers,CommandBuffer commit to CommandQueue
//CommandBufferPool alloc CommandBuffer
//Commandbuffers are synchronized through events or memory barriers
//Commandqueues are synchronized between semaphores
//The CPU and GPU are synchronized through a fence
//If the same thread has more than one encoder encoding it can have a CommandBufferPool of its own
class GRICommand
{

};

//command encoder
class GRICommandBuffers
{

};
//Alloc CommandBuffers
class GRICommandBufferPool
{

};
//CommandBuufer commit command to commandQueue
//Abstract a set of such concepts for OpengL, and some encapsulation for OpengL,
//so that in the future compatible with Vulkan and Metal, also easier 
//
class GRICommandQueue
{

};