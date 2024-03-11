#pragma once

#ifdef SOUL_GAME_ENGINE_DLL_EXPORTS
#define SOUL_ENGNIE_API __declspec(dllexport)
#else
#define SOUL_ENGNIE_API __declspec(dllimport)
#endif

#ifdef SOUL_GAME_ENGINE_DLL_EXPORTS
#define SOUL_ENGNIE_TEMPLATE_API __declspec(dllexport)
#else
#define SOUL_ENGNIE_TEMPLATE_API __declspec(dllimport)
#endif