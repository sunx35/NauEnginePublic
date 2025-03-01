// Copyright 2024 N-GINN LLC. All rights reserved.

// Copyright (C) 2024  Gaijin Games KFT.  All rights reserved
#pragma once

// stream number: specify ALL stream regs after it, because this stream number
// can't be used again in this declaration
#define VSD_STREAM(n)                   (VSDOP_STREAM | (n) | ((n) == 0 ? 0 : VSDS_PER_INSTANCE_DATA)) // For compatibility.
#define VSD_STREAM_PER_VERTEX_DATA(n)   (VSDOP_STREAM | (n))
#define VSD_STREAM_PER_INSTANCE_DATA(n) (VSDOP_STREAM | (n) | VSDS_PER_INSTANCE_DATA)

// map data of type t to input register n (0..15); n must be a pre-defined
// constant when using standard vertex program (see below)
#define VSD_REG(n, t) (VSDOP_INPUT | (t) | (n))

// skip n 32-bit words of input stream data (0..15)
#define VSD_SKIP(n) (VSDOP_INPUT | VSD_SKIPFLG | ((n) << 16))

// types of input data:
enum VSDT
{
// 1d float: x => (x,0,0,1)
VSDT_FLOAT1 = (0x00 << 16),
// 2d float: x,y => (x,y,0,1)
VSDT_FLOAT2 = (0x01 << 16),
// 3d float: x,y,z => (x,y,z,1)
VSDT_FLOAT3 = (0x02 << 16),
// 4d float: x,y,z,w => (x,y,z,w)
VSDT_FLOAT4 = (0x03 << 16),
// 4-byte B,G,R,A color (E3DCOLOR type) => (R,G,B,A) (0..1 range)
VSDT_E3DCOLOR = (0x04 << 16),
// 4d uint8_t x,y,z,w => (x,y,z,w)
VSDT_UBYTE4 = (0x05 << 16),
// 2d signed short: x,y => (x,y,0,1)
VSDT_SHORT2 = (0x06 << 16),
// 4d signed short: x,y,z,w => (x,y,z,w)
VSDT_SHORT4 = (0x07 << 16),

// 2D signed short normalized (v[0]/32767.0,v[1]/32767.0,0,1)
VSDT_SHORT2N = (9 << 16),
// 4D signed short normalized (v[0]/32767.0,v[1]/32767.0,0,1)
VSDT_SHORT4N = (10 << 16),
// 2D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,0,1)
VSDT_USHORT2N = (11 << 16),
// 4D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,v[2]/65535.0,v[3]/65535.0)
VSDT_USHORT4N = (12 << 16),

// 3D unsigned 10 10 10 format expanded to (value, value, value, 1)
VSDT_UDEC3 = (13 << 16),
// 3D signed 10 10 10 format normalized and expanded to (v[0]/511.0, v[1]/511.0, v[2]/511.0, 1)
VSDT_DEC3N = (14 << 16),

// Two 16-bit floating point values, expanded to (value, value, 0, 1)
VSDT_HALF2 = (15 << 16),
// Four 16-bit floating point values
VSDT_HALF4 = (16 << 16),

VSDT_INT1 = (17 << 16),
VSDT_INT2 = (18 << 16),
VSDT_INT3 = (19 << 16),
VSDT_INT4 = (20 << 16),

VSDT_UINT1 = (21 << 16),
VSDT_UINT2 = (22 << 16),
VSDT_UINT3 = (23 << 16),
VSDT_UINT4 = (24 << 16)
};
// register numbers for standard vertex program
enum VSDR
{
VSDR_POS  = 0,
VSDR_BLENDW  = 1,
VSDR_BLENDIND  = 2,
VSDR_NORM  = 3,
VSDR_TANGENT = 4,
VSDR_PSIZE  = 5,
VSDR_DIFF  = 6,
VSDR_SPEC  = 7,
VSDR_TEXC0  = 8,
VSDR_TEXC1  = 9,
VSDR_TEXC2  = 10,
VSDR_TEXC3  = 11,
VSDR_TEXC4  = 12,
VSDR_TEXC5  = 13,
VSDR_TEXC6  = 14,
VSDR_TEXC7 = 15,
VSDR_POS2 = 16,
VSDR_NORM2 = 17,
VSDR_TEXC15 = 18,
VSDR_TEXC8 = 19
// Note: before adding new entry ensure you don't overflow locationSourceStream (64 bits)
};

enum
{
  VBLOCK_READONLY = 0x02,
  VBLOCK_WRITEONLY = 0x04,
  VBLOCK_NOSYSLOCK = 0x08,  // for debugging
  VBLOCK_DISCARD = 0x10,    // discard buffer contents - they won't be read
  VBLOCK_NOOVERWRITE = 0x20 // no drawn vertexes will be overwritten
};

enum PRIM
{
  PRIM_POINTLIST = 1,
  PRIM_LINELIST = 2,
  PRIM_LINESTRIP = 3,
  PRIM_TRILIST = 4,
  PRIM_TRISTRIP = 5,
  PRIM_TRIFAN = 6,
#if _TARGET_XBOX
  PRIM_QUADLIST = 7, // D3D_PRIMITIVE_TOPOLOGY_QUADLIST = 19, Xbox extension.
#endif
  PRIM_4_CONTROL_POINTS = 8, // Quads for heightmap hardware tesselation
  PRIM_3_CONTROL_POINTS = 35,
  PRIM_COUNT,
};


enum
{
  TM_WORLD = 0,
  TM_VIEW = 1,
  TM_PROJ = 2,

  TM_LOCAL2VIEW = 3,
  TM_VIEW2LOCAL = 4,
  TM_GLOBAL = 5,
  TM__NUM
};

enum
{
  CLEAR_TARGET = 1,
  CLEAR_ZBUFFER = 2,
  CLEAR_STENCIL = 4,
  CLEAR_DISCARD_TARGET = 8, // Indicates the initial RT content will be completely overwritten and doesn't matter - optimization in
                            // some APIs
  CLEAR_DISCARD_ZBUFFER = 16,
  CLEAR_DISCARD_STENCIL = 32,
  CLEAR_DISCARD = CLEAR_DISCARD_TARGET | CLEAR_DISCARD_ZBUFFER | CLEAR_DISCARD_STENCIL
};

enum D3D_BLEND
{
  BLEND_ZERO = 1,
  BLEND_ONE = 2,
  BLEND_SRCCOLOR = 3,
  BLEND_INVSRCCOLOR = 4,
  BLEND_SRCALPHA = 5,
  BLEND_INVSRCALPHA = 6,
  BLEND_DESTALPHA = 7,
  BLEND_INVDESTALPHA = 8,
  BLEND_DESTCOLOR = 9,
  BLEND_INVDESTCOLOR = 10,
  BLEND_SRCALPHASAT = 11,
  BLEND_BOTHINVSRCALPHA = 13,
  BLEND_BLENDFACTOR = 14,
  BLEND_INVBLENDFACTOR = 15
};

enum D3D_BLENDOP
{
  BLENDOP_ADD = 1,
  BLENDOP_SUBTRACT = 2,
  BLENDOP_REVSUBTRACT = 3,
  BLENDOP_MIN = 4,
  BLENDOP_MAX = 5,
};

enum D3D_CMPF
{
  CMPF_NEVER = 1,
  CMPF_LESS = 2,
  CMPF_EQUAL = 3,
  CMPF_LESSEQUAL = 4,
  CMPF_GREATER = 5,
  CMPF_NOTEQUAL = 6,
  CMPF_GREATEREQUAL = 7,
  CMPF_ALWAYS = 8
};

enum D3D_CULL
{
  CULL_NONE = 1,
  CULL_CW,
  CULL_CCW
};

enum D3D_STNCLOP
{
  STNCLOP_KEEP = 1,
  STNCLOP_ZERO = 2,
  STNCLOP_REPLACE = 3,
  STNCLOP_INCRSAT = 4,
  STNCLOP_DECRSAT = 5,
  STNCLOP_INVERT = 6,
  STNCLOP_INCR = 7,
  STNCLOP_DECR = 8
};

enum
{
  TEXADDR_WRAP = 1,
  TEXADDR_MIRROR = 2,
  TEXADDR_CLAMP = 3,
  TEXADDR_BORDER = 4,
  TEXADDR_MIRRORONCE = 5, // dx9 extension
};

enum
{
  TEXFILTER_DEFAULT = 0, // driver default

  TEXFILTER_POINT = 1,
  TEXFILTER_SMOOTH = 2,  // bilinear
  TEXFILTER_BEST = 3,    // anisotropic and similar, if available
  TEXFILTER_COMPARE = 4, // point comparasion for using in pcf
  TEXFILTER_NONE = 5,
};
static constexpr int MAX_SURVEY_INDEX = 0;
