#ifndef __ELEMENT_DEFINES_H
#define __ELEMENT_DEFINES_H

#include <Windows.h>

#pragma once

//------------------------------------------------------------------
//
// Definition Type: Declare Base And Sub Procs
//
//------------------------------------------------------------------

//Makes The Typedef For The BaseClass
#define Proc_DeclareBaseClass(baseclassname)											\
typedef baseclassname BaseClass;														\
public:

//Makes The Base Proc For Like Windows
#define Proc_DeclareBase(classname)														\
static LRESULT CALLBACK ElementProcBase(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)		\
{																						\
	classname* element = (classname*)(GET_ELEMENT_USERDATA(hwnd));						\
	if (!element)																		\
		return DefWindowProc(hwnd, msg, wp, lp);										\
																						\
	return element->ElementProc(hwnd, msg, wp, lp);										\
}

//Makes An Empty Base Proc
#define Proc_DeclareBaseEmpty()															\
static LRESULT CALLBACK ElementProcBase(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)		\
{																						\
	return DefWindowProc(hwnd, msg, wp, lp);											\
}

//Makes The Subproc For Like Buttons Or Other Elements
#define Proc_DeclareSub(classname)														\
static LRESULT CALLBACK ElementSubprocBase(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)	\
{																						\
	classname* element = (classname*)(GET_ELEMENT_USERDATA(hwnd));						\
	if (!element)																		\
		return 0;																		\
																						\
	return element->ElementSubproc(hwnd, msg, wp, lp);									\
}

//Makes An Empty Subproc
#define Proc_DeclareSubEmpty()															\
static LRESULT CALLBACK ElementSubprocBase(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)	\
{																						\
	return 0;																			\
}

//Makes The Subproc For Dialog Procs
#define Proc_DeclareDlg(classname)														\
static BOOL CALLBACK ElementDialogBase(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)		\
{																						\
	classname* element = (classname*)(GET_ELEMENT_USERDATA(hwnd));						\
	if (!element)																		\
		return FALSE;																	\
																						\
	return element->ElementDialogProc(hwnd, msg, wp, lp);								\
}

#define Proc_DeclareDlgDifferent(classname)												\
static BOOL CALLBACK ElementDialogDiffBase(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)	\
{																						\
	SubDialog* pThis = nullptr;															\
																						\
	if (msg == WM_INITDIALOG)															\
	{																					\
		pThis = (SubDialog*)lp;															\
																						\
		if (!pThis)																		\
			return FALSE;																\
																						\
		pThis->m_Hwnd = hwnd;															\
		SET_ELEMENT_USERDATA(hwnd, pThis);												\
	}																					\
	else																				\
	{																					\
		pThis = (SubDialog*)GET_ELEMENT_USERDATA(hwnd);									\
																						\
		if (!pThis)																		\
			return FALSE;																\
	}																					\
																						\
	return pThis->ElementDiffDialogProc(hwnd, msg, wp, lp);								\
}

//------------------------------------------------------------------
//
// Definition Type: Declaring Elements
//
//------------------------------------------------------------------

//Declare An Element With Both Base And Subclass Proc
#define DECLARE_ELEMENT(classname, baseclass)											\
Proc_DeclareBaseClass(baseclass)														\
Proc_DeclareBase(classname)																\
Proc_DeclareSub(classname);

//Defines An Element With A Base Proc But No Subproc
#define DECLARE_ELEMENT_NOSUBPROC(classname, baseclass)									\
Proc_DeclareBaseClass(baseclass)														\
Proc_DeclareBase(classname)																\
Proc_DeclareSubEmpty()

//Defines An Element With A Subproc But No Base Proc
#define DECLARE_ELEMENT_NOBASEPROC(classname, baseclass)								\
Proc_DeclareBaseClass(baseclass)														\
Proc_DeclareBaseEmpty()																	\
Proc_DeclareSub(classname)

//Defines An Element With No Proc
#define DECLARE_ELEMENT_NOPROC(classname, baseclass)									\
Proc_DeclareBaseClass(baseclass)														\
Proc_DeclareBaseEmpty()																	\
Proc_DeclareSubEmpty()

//Defines An Element With A Dialog Proc
#define DECLARE_ELEMENT_DIALOG(classname, baseclass)									\
Proc_DeclareBaseClass(baseclass)														\
Proc_DeclareDlg(classname)

//Defines An Element With A Dialog Proc that uses DialogBox instead of CreateDialog so only this window will work instead
//of the main window and other SubDialogs and this all at the same time
#define DECLARE_ELEMENT_DIALOG_DIFFERENT(classname, baseclass)							\
Proc_DeclareBaseClass(baseclass)														\
Proc_DeclareDlgDifferent(classname)

#define DECLARE_ELEMENT_DIALOG_BOTH(classname, baseclass)							    \
Proc_DeclareBaseClass(baseclass)														\
Proc_DeclareDlgDifferent(classname)														\
Proc_DeclareDlg(classname)

//------------------------------------------------------------------
//
// Definition Type: Declaring The Procs For The Element
//
//------------------------------------------------------------------

//Declares The Element Proc. Used For Like Windows
#define DECLARE_ELEMENT_PROC()															\
virtual LRESULT CALLBACK ElementProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

//Same As DECLARE_ELEMENT_PROC But This Is Used Inside The Actual Class Declartion
#define DECLARE_ELEMENT_PROC_INTERNAL()													\
LRESULT CALLBACK ElementProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)					\
{																						\
	int notificationCode = HIWORD(wp);													\
	switch (msg)

//Declares The Element Subproc. Used For Like Buttons, Sliders etc..
#define DECLARE_ELEMENT_SUBPROC()														\
virtual LRESULT CALLBACK ElementSubproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

//Same As DECLARE_ELEMENT_SUBPROC But This Is Used Inside The Actual Class Declartion
#define DECLARE_ELEMENT_SUBPROC_INTERNAL()												\
LRESULT CALLBACK ElementSubproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)				\
{																						\
	int notificationCode = HIWORD(wp);													\
	switch (msg)

//Declares The dialog proc. Used For SubDialog class
#define DECLARE_ELEMENT_DLGPROC()														\
virtual BOOL CALLBACK ElementDialogProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

//Same As DECLARE_ELEMENT_DLGPROC But This Is Used Inside The Actual Class Declartion
#define DECLARE_ELEMENT_DLGPROC_INTERNAL()												\
BOOL CALLBACK ElementDialogProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)				\
{																						\
	int notificationCode = HIWORD(wp);													\
	switch (msg)

//Declares The dialog proc. Used For SubDialog class
#define DECLARE_ELEMENT_DLGPROC_DIFFERENT()												\
virtual BOOL CALLBACK ElementDiffDialogProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

//Same As DECLARE_ELEMENT_DLGPROC But This Is Used Inside The Actual Class Declartion
#define DECLARE_ELEMENT_DLGPROC_DIFFERENT_INTERNAL()									\
BOOL CALLBACK ElementDiffDialogProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)			\
{																						\
	int notificationCode = HIWORD(wp);													\
	switch (msg)

//------------------------------------------------------------------
//
// Definition Type: Starting/Ending The Element Proc's Outside The Class. Used For The Cpp File Of The Class
//
//------------------------------------------------------------------

//Starts The Base Proc Function For The Desired Classname
#define START_ELEMENT_PROC(classname)													\
LRESULT CALLBACK classname::ElementProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)		\
{																						\
	int notificationCode = HIWORD(wp);													\
	switch (msg)																		\
	{

//Starts The Base Proc But Doesnt Start With The switch(msg) Thing
#define START_ELEMENT_PROC_NOSWITCH(classname)											\
LRESULT CALLBACK classname::ElementProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)		\
{																						\
	int notificationCode = HIWORD(wp);

//Starts The Sub Proc Function For The Desired Classname
#define START_ELEMENT_SUBPROC(classname)												\
LRESULT CALLBACK classname::ElementSubproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)	\
{																						\
	int notificationCode = HIWORD(wp);													\
	switch (msg)																		\
	{

//Starts The Sub Proc But Doesnt Start With The switch(msg) Thing
#define START_ELEMENT_SUBPROC_NOSWITCH(classname)										\
BOOL CALLBACK classname::ElementSubproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)	    \
{																						\
	int notificationCode = HIWORD(wp);

//Starts The Base Proc Function For The Desired Classname
#define START_ELEMENT_DLGPROC(classname)												\
BOOL CALLBACK classname::ElementDialogProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)	\
{																						\
	int notificationCode = HIWORD(wp);													\
	switch (msg)																		\
	{

//Starts The Base Proc But Doesnt Start With The switch(msg) Thing
#define START_ELEMENT_DLGPROC_NOSWITCH(classname)										\
BOOL CALLBACK classname::ElementDialogProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)	\
{																						\
	int notificationCode = HIWORD(wp);

//Starts The Base Proc Function For The Desired Classname
#define START_ELEMENT_DLGPROC_DIFFERENT(classname)										\
BOOL CALLBACK classname::ElementDiffDialogProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)\
{																						\
	int notificationCode = HIWORD(wp);													\
	switch (msg)																		\
	{

//Starts The Base Proc But Doesnt Start With The switch(msg) Thing
#define START_ELEMENT_DLGPROC_DIFFERENT_NOSWITCH(classname)								\
BOOL CALLBACK classname::ElementDiffDialogProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)\
{																						\
	int notificationCode = HIWORD(wp);

//Ends The Proc For Both START_ELEMENT_PROC and START_ELEMENT_SUBPROC
#define END_ELEMENT_PROC(ret)															\
	}																					\
	return ret;																			\
}

//Ends The Proc For Both START_ELEMENT_PROC_NOSWITCH and START_ELEMENT_SUBPROC_NOSWITCH
#define END_ELEMENT_PROC_NO_SWITCH(ret)													\
	return ret;																			\
}

//------------------------------------------------------------------
//
// Definition Type: Definitions For Defining/Starting case Statements For Procs
//
//------------------------------------------------------------------

//QUICK NOTE:
//if using WM_PAINT then remember to not use DEFINE_ELEMENT_PROC_RETURN and use DEFINE_ELEMENT_PROC
//instead otherwise some stuff like the rich edit will not work correctly

//Defines A Switch Statement. Uses message As The Case Message And func As The Funcion To Execute
//If The Case Is true. Breaks After Calling The Function
#define DEFINE_ELEMENT_PROC(message, func)												\
case message:																			\
{																						\
	func(hwnd, msg, wp, lp);															\
	break;																				\
}

//Defines A Switch Statement. Uses message As The Case Message, func As The Funcion To Execute
//If The Case Is true. And ret As The Value To Return After Calling The Function
#define DEFINE_ELEMENT_PROC_RETURN(message, func, ret)									\
case message:																			\
{																						\
	func(hwnd, msg, wp, lp);															\
	return ret;																			\
}

//Defines The Default Statement. Uses func As The Funcion To Execute If This Gets Hit
#define DEFAULT_ELEMENT_PROC(func)														\
default:																				\
{																						\
	func(hwnd, msg, wp, lp);															\
	break;																				\
}

//Defines The Default Statement. Uses func As The Funcion To Execute If This Gets Hit
//And ret As The Value To Return After Calling The Function
#define DEFAULT_ELEMENT_PROC_RETURN(func, ret)											\
default:																				\
{																						\
	func(hwnd, msg, wp, lp);															\
	return ret;																			\
}

//Defines A Subproc For Inside A Proc. Uses message As The Message For The Case Statement And type
//For The Type It Will Use For The Switch Statement Inside The case message: Use Something Like
//WM_COMMAND and LOWORD(wp) For Command Types
#define DEFINE_ELEMENT_SUBPROC(message, type)											\
case message:																			\
{																						\
	switch (type)																		\
	{

//Defines A Subproc For Inside A Proc. Uses message As The Message For The Case Statement.
//This One Doesnt Start The Nested Switch Statement So You Can Do Whatever In Here
#define DEFINE_ELEMENT_SUBPROC_NOSWITCH(message)										\
case message:																			\
{

//Defines A Subproc For Inside A Subproc That Uses A Notification Code From HIWORD(wp).
//Uses code As The Code That Will Compare Against HIWORD(wp) And Type Is Used
//For The Type It Will Use For The Switch Statement Inside The if (noticode == code). Use Something Like
//BN_CLICKED and LOWORD(wp) For Inside Something Like DEFINE_ELEMENT_SUBPROC_NOSWITCH(WM_COMMAND)
#define DEFINE_ELEMENT_SUBPROC_NOTI(code, type)											\
if (notificationCode == code)															\
{																						\
	switch (type)																		\
	{

#define DEFINE_ELEMENT_SUBPROC_IFSTATEMENT(condition, type)								\
if (condition)																			\
{																						\
	switch (type)																		\
	{

//------------------------------------------------------------------
//
// Definition Type: Definitions For Ending case Statements For Procs
//
//------------------------------------------------------------------

//Used To End Notification Subprocs Created With DEFINE_ELEMENT_SUBPROC_NOTI. This Breakes
//The Main Switch Statement
#define END_ELEMENT_SUBPROC_NOTI()														\
	}																					\
	break;																				\
}

//Used To End Notification Subprocs Created With DEFINE_ELEMENT_SUBPROC_NOTI. This Returns
//The ret Value
#define END_ELEMENT_SUBPROC_NOTI_RETURN(ret)											\
	}																					\
	return ret;																			\
}

//Ends An Element Subproc Made With DEFINE_ELEMENT_SUBPROC
#define END_ELEMENT_SUBPROC()															\
	}																					\
	break;																				\
}

//Ends An Element Subproc Made With DEFINE_ELEMENT_SUBPROC But Returns The
//Ret Value
#define END_ELEMENT_SUBPROC_RETURN(ret)													\
	}																					\
	return ret;																			\
}

//Ends A Subproc That Is Made With DEFINE_ELEMENT_SUBPROC_NOSWITCH
#define END_ELEMENT_SUBPROC_NOSWITCH()													\
	break;																				\
}

//Ends A Subproc That Is Made With DEFINE_ELEMENT_SUBPROC_NOSWITCH But Returns
//The Ret Value
#define END_ELEMENT_SUBPROC_NOSWITCH_RETURN(ret)										\
	return ret;																			\
}


//------------------------------------------------------------------
//
// Definition Type: Calling The Procs
//
//------------------------------------------------------------------

//Calls The Default subclass proc with the input of m_DefaultProc, ELEMENT_ITEMS
#define CALL_DEF_SUBPROC()																\
CallWindowProc(m_DefaultProc, hwnd, msg, wp, lp)

//Calls The Default WindowProc with the input of ELEMENT_ITEMS
#define CALL_DEF_WINDPROC()																\
DefWindowProc(hwnd, msg, wp, lp)

// //------------------------------------------------------------------
//
// Definition Type: Hwnd Long Pointer Changing
//
//------------------------------------------------------------------

//Sets The Userdata Of A Hwnd
#define SET_ELEMENT_USERDATA(hwnd, udata)												\
SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG)udata)

//Get The Userdata Of A Hwnd
#define GET_ELEMENT_USERDATA(hwnd)														\
GetWindowLongPtr(hwnd, GWLP_USERDATA)

//Set The Flags/Style Of A Hwnd
#define SET_ELEMENT_FLAGS(hwnd, flags)													\
SetWindowLongPtr(hwnd, GWL_STYLE, flags);												\
SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

//Get The Flags/Style Of A Hwnd
#define GET_ELEMENT_FLAGS(hwnd)															\
GetWindowLongPtr(hwnd, GWL_STYLE)

//Set The EX Flags/Style Of A Hwnd
#define SET_ELEMENT_EX_FLAGS(hwnd, flags)												\
SetWindowLongPtr(hwnd, GWL_EXSTYLE, flags);												\
SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

//Get The Flags/Style Of A Hwnd
#define GET_ELEMENT_EX_FLAGS(hwnd)														\
GetWindowLongPtr(hwnd, GWL_EXSTYLE)

//------------------------------------------------------------------
//
// Definition Type: Proc Items For The ElementProc's
//
//------------------------------------------------------------------

//Declares The Proc Items For An ElementProc And ElementSubProc So You Dont Need To
#define ELEMENT_PROC_ITEMS																\
HWND hwnd, UINT msg, WPARAM wp, LPARAM lp

//Used To Input Into Functions That Have ELEMENT_PROC_ITEMS As Its Input
#define ELEMENT_ITEMS																	\
hwnd, msg, wp, lp

//An Empty Proc Made For DEFINE_ELEMENT_*
#define NO_PROC \
EmptyProc

//------------------------------------------------------------------
//
// Definition Type: Entry Point Definitions
//
//------------------------------------------------------------------

//A Macro For The Entry Point
#define ENTRY_POINT()																	\
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)

//------------------------------------------------------------------
//
// Definition Type: helper functions for inside functios for ELEMENT_PROC's
//
//------------------------------------------------------------------

//get the notification thing for the WM_NOTIFY
#define GUI_NOTIFICATION_GET()															\
LPNMHDR noticode = (LPNMHDR)lp;

#endif