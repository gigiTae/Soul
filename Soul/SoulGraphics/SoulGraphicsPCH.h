#ifndef SOUL_GRAPHICS_PCH_H
#define SOUL_GRAPHICS_PCH_H


// 여기에 미리 컴파일하려는 헤더 추가
#define WIN32_LEAN_AND_MEAN
	
#include <memory>

// d3d11
#include <d3d11.h>
#include <DirectXMath.h>
#include <directxtk/simplemath.h>
#include <Directxtk/DDSTextureLoader.h>
#include <Directxtk/WICTextureLoader.h>

//assimp
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

//stl 
#include <array>
#include <vector>
#include <unordered_map>
#include <filesystem>

// rtti
#include <typeinfo>
#include <typeindex>
#include <tuple>

#include "InitializeInfomation.h"
#include "Helper.h"

#endif //SOUL_GRAPHICS_PCH_H
