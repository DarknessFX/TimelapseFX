#pragma once

#include <windows.h>
#include <string>

#ifdef TIMELAPSEFX_HELPER_EXPORTS
#define TIMELAPSEFX_HELPER_API __declspec(dllexport)
#else
#define TIMELAPSEFX_HELPER_API __declspec(dllimport)
#endif

extern "C" TIMELAPSEFX_HELPER_API void CaptureFromDLL(HWND hTargetWnd, std::string sFile);
