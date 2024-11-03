#ifndef __CRASHHANDLER_H
#define __CRASHHANDLER_H

#include "Window.h"

#pragma once

#define MAKE_CRASH_HANDLER(funcname) LONG WINAPI funcname(EXCEPTION_POINTERS* exceptionInfo)
#define SET_CRASH_HANDLER(funcname) SetUnhandledExceptionFilter(funcname)

#endif