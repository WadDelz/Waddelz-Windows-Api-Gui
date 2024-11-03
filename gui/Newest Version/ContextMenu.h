#ifndef __CONTEXTMENU_H
#define __CONTEXTMENU_H

#include "Element.h"

#pragma once

namespace gui
{
	class ContextMenu
	{
	public:
		//set the bBaseMenu if the menu will be used as a base menu
		ContextMenu();
		virtual void DeleteMenu();

		virtual void AddItem(const char* text, int flags = MF_STRING, int id = NULL);
		virtual void AddSeperator();
		virtual void AddVerticleSeperator(const char* text, int id = NULL, int flags = MF_STRING);

		virtual void DisplayMenu(POINT pt, Element* parent, int flags = TPM_RIGHTBUTTON, RECT* prcRect = nullptr);

		virtual HMENU GetMenu();

		virtual void SetMenuText(const char* text, int type = MF_BYCOMMAND, int id = 0);
		virtual void CheckMenuItem(bool bChecked, int type = MF_BYCOMMAND, int id = 0, const char* backuptext = "");
		virtual void EnableMenuItem(bool bEnabled, bool bGreyedOut, int type = MF_BYCOMMAND, int id = 0, const char* backuptext = "");

		virtual HBITMAP GetItemIcon(BOOL bFromPosition, unsigned int id);
		virtual void SetMenuIcon(HICON icon, BOOL bFromPosition, unsigned int id);
		virtual void RemoveMenuIcon(BOOL bFromPosition, unsigned int id, bool bDeleteIcon = true);

		virtual void GetItemText(char* text, int size, BOOL bDoesUsePosition, int itemID);
		virtual int GetItemTextLength(BOOL bDoesUsePosition, int itemID);

		virtual unsigned int GetSubMenuState(int uID, int type = MF_BYPOSITION);

		virtual bool IsMenuEnabled(int uid, int type = MF_BYPOSITION);
		virtual bool IsMenuChecked(int uid, int type = MF_BYPOSITION);

		virtual void OnDeconstructor();

		~ContextMenu();
	protected:
		HMENU m_Menu;
	};
}

#endif