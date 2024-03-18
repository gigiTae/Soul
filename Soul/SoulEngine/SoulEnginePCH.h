#ifndef SOUL_ENGINE_PCH_H
#define SOUL_ENGINE_PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

#include <memory>

#include "../SoulGraphics/SoulGraphicsHeaderh.h"

#include "InputEnum.h"

#endif //PCH_H
