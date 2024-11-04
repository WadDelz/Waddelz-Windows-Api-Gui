#ifndef __ELEMENT_H
#define __ELEMENT_H

#define _CRT_SECURE_NO_WARNINGS

#include "ElementDefines.h"
#include <vector>

#pragma once

namespace gui
{
	enum class FileDialogType
	{
		FILE_OPEN_DIALOG,
		FILE_OPEN_SHELL,
		FOLDER_OPEN_DIALOG,
		FOLDER_OPEN_NORMAL_DIALOG,
		FILE_SAVE_DIALOG
	};

	class PropertyPage;
	class ToolTip;
	class ToolBar;

	class Element
	{
	public:
		Element();
		
		virtual void SetName(const char* name);

		virtual int GetX();
		virtual int GetY();
		virtual int GetWide();
		virtual int GetTall();
		virtual void GetPos(int* x, int* y);
		virtual void GetSize(int* wide, int* tall);
		virtual void GetBounds(int* x, int* y, int* wide, int* tall);

		virtual void SetPos(const int& x, const int& y);
		virtual void SetX(const int& x);
		virtual void SetY(const int& y);
		virtual void SetSize(const int& wide, const int& tall);
		virtual void SetWide(const int& wide);
		virtual void SetTall(const int& tall);
		virtual void SetBounds(const int& x, const int& y, const int& wide, const int& tall);

		virtual void SetIcon(HICON icon, bool big = false);

		//called when the deconstructor is called
		virtual void OnDeconstructor();

		virtual const char* GetName();
		virtual const char* GetClassname();

		virtual Element* GetParent();

		virtual bool IsVisible();
		virtual void SetVisible(const bool& visible);

		virtual bool IsEnabled();
		virtual void SetEnabled(const bool& enabled);

		virtual void AddChild(Element* child);
		virtual void DeleteChild(Element* child);
		virtual void RemoveChild(Element* child);
		virtual void SetParent(Element* parent);

		//DONT CALL DELETE THIS UNLESS IS IN DECONSTRUCTOR
		virtual void DeleteThis();

		virtual int GetCommand();

		virtual unsigned int GetFlags();
		virtual void SetFlags(unsigned int flags);
		
		virtual unsigned int GetExtendedFlags();
		virtual void SetExtendedFlags(unsigned int flags);

		virtual void SetText(const char* text);
		virtual void GetText(char* buf, int len);

		virtual void SetSubproc(WNDPROC proc);
		virtual void SetFocusToThis();

		virtual HWND GetHandle();

		virtual POINT ClientFromScreen(POINT pt);
		virtual POINT ClientFromScreen(Element* element, POINT pt);

		virtual void Redraw(bool repaint = true, Element* item = nullptr, const RECT* rect = nullptr);

		virtual std::vector<Element*> GetChildren();
		virtual std::vector<ToolTip*> GetToolTips();

		static int EmptyMessageBox(int flags, const char* title, const char* text, ...);
		virtual int ShowMessageBox(int flags, const char* title, const char* text, ...);

		virtual void OnFileSelected(int id, const char* file, FileDialogType type);

		virtual void SetPropertyPage(PropertyPage* page);
		virtual PropertyPage* GetPropertyPage();

		virtual void DeleteToolTip(ToolTip* tip);
		virtual void RemoveToolTip(ToolTip* tip);

		//only 1 sound can play at a time
		static void EmitSound(const char* filename, unsigned long flags, HMODULE hmod);

		virtual void GetCenterPositionFromElement(const int& elementwide, const int& elementtall, int* x, int* y);

		ToolBar* GetToolBar();

		//virtual void MoveToFront();
		~Element();

		HWND m_Hwnd;
	protected:
		PropertyPage* m_PropertyPage;
		WNDPROC m_DefaultProc;
		Element* m_Parent;

		std::vector<Element*> m_Children;

		bool bDeleteThisHack;

		char* m_szName;
		char* m_szClassName;

		bool m_bVisible;
		bool m_bEnabled;
	
		int m_iCommandId;

		void SetClassname(const char* classname);
		void EmptyProc(ELEMENT_PROC_ITEMS) {}

	protected:
		std::vector<ToolTip*> m_ToolTips;

		virtual void AddToolTip(ToolTip* tip);

		friend class ToolTip;
	protected:
		ToolBar* m_ToolBar;

		virtual void SetToolBar(ToolBar* tbar);

		friend class ToolBar;
	};

	Element* GetElementFromPoint(POINT pt);
	Element* GetElementFromHwnd(HWND hwnd);
	Element* GetElementFocus();
}

#endif //__ELEMENT_H