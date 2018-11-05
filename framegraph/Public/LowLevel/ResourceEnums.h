// Copyright (c) 2018,  Zhirnov Andrey. For more information see 'LICENSE'

#pragma once

#include "framegraph/Public/LowLevel/Types.h"

namespace FG
{

	enum class EMemoryType : uint
	{
		Default			= 0,			// local in GPU
		HostRead		= 1 << 0,
		HostWrite		= 1 << 1,
		Dedicated		= 1 << 2,		// force to use dedicated allocation
		AllowAliasing	= 1 << 3,		// 
		Sparse			= 1 << 4,
		_Last,
	};
	FG_BIT_OPERATORS( EMemoryType );


	enum class EBufferUsage : uint
	{								//	cpu read  |  cpu write  |  shader read  |  shader write  |
		TransferSrc		= 1 << 0,	//            |             |      no       |      no        |
		TransferDst		= 1 << 1,	//            |             |      no       |      no        |  
		UniformTexel	= 1 << 2,	//            |             |      yes      |      no        |
		StorageTexel	= 1 << 3,	//            |             |      yes      |      no        |
		Uniform			= 1 << 4,	//            |             |      fast     |      no        |
		Storage			= 1 << 5,	//            |             |      yes      |      yes       |
		Index			= 1 << 6,	//            |             |      no       |      no        |
		Vertex			= 1 << 7,	//            |             |      no       |      no        |
		Indirect		= 1 << 8,	//            |             |      no       |      no        |
		_Last,
		
		All				= ((_Last-1) << 1) - 1,
		Transfer		= TransferDst | TransferSrc,
		Unknown			= 0,
	};
	FG_BIT_OPERATORS( EBufferUsage );


	enum class EImage : uint
	{
		Tex1D		= 0,
		Tex1DArray,
		Tex2D,
		Tex2DArray,
		Tex2DMS,
		Tex2DMSArray,
		TexCube,
		TexCubeArray,
		Tex3D,
		Buffer,
		Unknown		= ~0u,
	};


	enum class EImageUsage : uint
	{
		TransferSrc				= 1 << 0,		// for all copy operations
		TransferDst				= 1 << 1,		// for all copy operations
		Sampled					= 1 << 2,		// access in shader as texture
		Storage					= 1 << 3,		// access in shader as image
		ColorAttachment			= 1 << 4,		// color or resolve attachment
		DepthStencilAttachment	= 1 << 5,		// depth/stencil attachment
		TransientAttachment		= 1 << 6,		// color, resolve, depth/stencil, input attachment
		InputAttachment			= 1 << 7,		// input attachment in fb and shader
		_Last,

		All						= ((_Last-1) << 1) - 1,
		Transfer				= TransferSrc | TransferDst,
		Unknown					= 0,
	};
	FG_BIT_OPERATORS( EImageUsage );


	enum class EImageAspect : uint
	{
		Color			= 1 << 0,
		Depth			= 1 << 1,
		Stencil			= 1 << 2,
		Metadata		= 1 << 3,
		_Last,

		DepthStencil	= Depth | Stencil,
		Auto			= ~0u,
	};
	FG_BIT_OPERATORS( EImageAspect );
	
	
	enum class EAttachmentLoadOp : uint
	{
		Invalidate,
		Load,
		Clear,
	};


	enum class EAttachmentStoreOp : uint
	{
		Invalidate,
		Store,
	};


	enum class EPixelFormat : uint
	{
		// signed normalized
		RGBA16_SNorm,
		RGBA8_SNorm,
		RGB16_SNorm,
		RGB8_SNorm,
		RG16_SNorm,
		RG8_SNorm,
		R16_SNorm,
		R8_SNorm,
			
		// unsigned normalized
		RGBA16_UNorm,
		RGBA8_UNorm,
		RGB16_UNorm,
		RGB8_UNorm,
		RG16_UNorm,
		RG8_UNorm,
		R16_UNorm,
		R8_UNorm,
		RGB10_A2_UNorm,
		RGBA4_UNorm,
		RGB5_A1_UNorm,
		RGB_5_6_5_UNorm,

		// BGRA
		BGR8_UNorm,
		BGRA8_UNorm,
			
		// sRGB
		sRGB8,
		sRGB8_A8,
		//sBGR8,
		//sBGR8_A8,

		// signed integer
		R8I,
		RG8I,
		RGB8I,
		RGBA8I,
		R16I,
		RG16I,
		RGB16I,
		RGBA16I,
		R32I,
		RG32I,
		RGB32I,
		RGBA32I,
			
		// unsigned integer
		R8U,
		RG8U,
		RGB8U,
		RGBA8U,
		R16U,
		RG16U,
		RGB16U,
		RGBA16U,
		R32U,
		RG32U,
		RGB32U,
		RGBA32U,
		RGB10_A2U,
			
		// float
		R16F,
		RG16F,
		RGB16F,
		RGBA16F,
		R32F,
		RG32F,
		RGB32F,
		RGBA32F,
		RGB_11_11_10F,

		// depth stencil
		Depth16,
		Depth24,
		//Depth32,
		Depth32F,
		Depth16_Stencil8,
		Depth24_Stencil8,
		Depth32F_Stencil8,
			
		// compressed
		BC1_RGB8_UNorm,
		BC1_RGB8_A1_UNorm,
		BC2_RGBA8_UNorm,
		BC3_RGBA8_UNorm,
		BC4_RED8_SNorm,
		BC4_RED8_UNorm,
		BC5_RG8_SNorm,
		BC5_RG8_UNorm,
		BC7_RGBA8_UNorm,
		BC7_SRGB8_A8_UNorm,
		BC6H_RGB16F,
		BC6H_RGB16F_Unsigned,
		ETC2_RGB8_UNorm,
		ECT2_SRGB8_UNorm,
		ETC2_RGB8_A1_UNorm,
		ETC2_SRGB8_A1_UNorm,
		ETC2_RGBA8_UNorm,
		ETC2_SRGB8_A8_UNorm,
		EAC_R11_SNorm,
		EAC_R11_UNorm,
		EAC_RG11_SNorm,
		EAC_RG11_UNorm,
		ASTC_RGBA_4x4,
		ASTC_RGBA_5x4,
		ASTC_RGBA_5x5,
		ASTC_RGBA_6x5,
		ASTC_RGBA_6x6,
		ASTC_RGBA_8x5,
		ASTC_RGBA_8x6,
		ASTC_RGBA_8x8,
		ASTC_RGBA_10x5,
		ASTC_RGBA_10x6,
		ASTC_RGBA_10x8,
		ASTC_RGBA_10x10,
		ASTC_RGBA_12x10,
		ASTC_RGBA_12x12,
		ASTC_SRGB8_A8_4x4,
		ASTC_SRGB8_A8_5x4,
		ASTC_SRGB8_A8_5x5,
		ASTC_SRGB8_A8_6x5,
		ASTC_SRGB8_A8_6x6,
		ASTC_SRGB8_A8_8x5,
		ASTC_SRGB8_A8_8x6,
		ASTC_SRGB8_A8_8x8,
		ASTC_SRGB8_A8_10x5,
		ASTC_SRGB8_A8_10x6,
		ASTC_SRGB8_A8_10x8,
		ASTC_SRGB8_A8_10x10,
		ASTC_SRGB8_A8_12x10,
		ASTC_SRGB8_A8_12x12,

		Unknown					= ~0u,
	};
	

	enum class EFragOutput : uint
	{
		Unknown		= 0,
		Int4		= uint( EPixelFormat::RGBA32I ),
		UInt4		= uint( EPixelFormat::RGBA32U ),
		Float4		= uint( EPixelFormat::RGBA32F ),
	};


}	// FG