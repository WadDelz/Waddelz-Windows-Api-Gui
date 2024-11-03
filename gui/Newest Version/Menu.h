#ifndef __MENU_H
#define __MENU_H

#include "Element.h"

#pragma once

namespace gui
{
	class Menu
	{
	public:
		//set the bBaseMenu if the menu will be used as a base menu
		Menu(bool bCreateMenu = true);

		virtual void DeleteMenu();
		virtual void SetParent(Element* parent);
		virtual void SetMenu(HMENU menu);

		virtual void AddItem(const char* text, int flags = MF_STRING, int id = NULL);
		virtual void AddSeperator();
		virtual void AddVerticleSeperator(const char* text, int id = NULL, int flags = MF_STRING);

		virtual void AddMenu(Menu* menu, const char* text, int flags = MF_POPUP);

		virtual Menu* CreateNewMenu();
		virtual Menu* GetChild();
		virtual Menu* GetMenuParent();
		virtual Menu* GetNext();
		virtual Menu* FindMenuByHMenu(HMENU menu);

		virtual Element* GetParent();
		virtual HMENU GetMenu();

		virtual void SetMenuText(const char* text, int type = MF_BYCOMMAND, int id = 0);
		virtual void CheckMenuItem(bool bChecked, int type = MF_BYCOMMAND, int id = 0, const char* backuptext = "");
		virtual void EnableMenuItem(bool bEnabled, bool bGreyedOut, int type = MF_BYCOMMAND, int id = 0, const char* backuptext = "");

		virtual HBITMAP GetItemIcon(BOOL bFromPosition, unsigned int id);
		virtual void SetMenuIcon(HICON icon, BOOL bFromPosition, unsigned int id);
		virtual void RemoveMenuIcon(BOOL bFromPosition, unsigned int id, bool bDeleteIcon = true);

		virtual unsigned int GetSubMenuState(int uID, int type = MF_BYPOSITION);

		virtual bool IsMenuEnabled(int uid, int type = MF_BYPOSITION);
		virtual bool IsMenuChecked(int uid, int type = MF_BYPOSITION);

		virtual void GetItemText(char* text, int size, BOOL bDoesUsePosition, int itemID);
		virtual int GetItemTextLength(BOOL bDoesUsePosition, int itemID);
	protected:
		Element* m_Parent;
		HMENU m_Menu;

		Menu* m_Child;
		Menu* m_Next;
		Menu* m_MenuParent;
	};
}

#endif