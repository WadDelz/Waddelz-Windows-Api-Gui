#include "ContextMenu.h"
#include "Icon.h"

using namespace gui;

ContextMenu::ContextMenu()
{
	m_Menu = CreatePopupMenu();
}

void ContextMenu::DeleteMenu()
{
	if (m_Menu)
		DestroyMenu(m_Menu);
}

void ContextMenu::AddItem(const char* text, int flags, int id)
{
	AppendMenu(m_Menu, flags, id, text);
}

void ContextMenu::AddSeperator()
{
	AppendMenu(m_Menu, MF_SEPARATOR, NULL, nullptr);
}

void ContextMenu::AddVerticleSeperator(const char* text, int id, int flags)
{
	AppendMenu(m_Menu, MF_MENUBARBREAK | flags, id, text);
}

void ContextMenu::DisplayMenu(POINT pt, Element* parent, int flags, RECT* prcRect)
{
	TrackPopupMenu(m_Menu, flags, pt.x, pt.y, NULL, parent->GetHandle(), prcRect);
}

HMENU ContextMenu::GetMenu()
{
	return m_Menu;
}

void ContextMenu::SetMenuText(const char* text, int type, int id)
{
	ModifyMenu(m_Menu, id, type | MF_STRING, id, text);
}

void ContextMenu::CheckMenuItem(bool bChecked, int type, int id, const char* backuptext)
{
	int text = GetItemTextLength(type & MF_BYPOSITION, id);
	if (text == -1)
	{
		int enabled = (bChecked) ? MF_CHECKED : MF_UNCHECKED;
		ModifyMenu(m_Menu, id, type | enabled, id, backuptext);
		return;
	}

	char* buf = new char[text + 1];
	GetItemText(buf, text + 1, type & MF_BYPOSITION, id);

	int enabled = (bChecked) ? MF_CHECKED : MF_UNCHECKED;
	ModifyMenu(m_Menu, id, type | enabled, id, buf);

	delete[] buf;
}

void ContextMenu::EnableMenuItem(bool bEnabled, bool bGreyedOut, int type, int id, const char* backuptext)
{
	int text = GetItemTextLength(type & MF_BYPOSITION, id);
	if (text == -1)
	{
		int enabled = (bEnabled) ? MF_ENABLED : MF_DISABLED;
		if (bGreyedOut)
			enabled |= MF_GRAYED;

		ModifyMenu(m_Menu, id, type | enabled, id, backuptext);
		return;
	}

	char* buf = new char[text + 1];
	GetItemText(buf, text + 1, type & MF_BYPOSITION, id);

	int enabled = (bEnabled) ? MF_ENABLED : MF_DISABLED;
	if (bGreyedOut)
		enabled |= MF_GRAYED;

	ModifyMenu(m_Menu, id, type | enabled, id, buf);

	delete[] buf;
}

void ContextMenu::SetMenuIcon(HICON icon, BOOL bFromPosition, unsigned int id)
{
	MENUITEMINFO mii = {};
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_BITMAP;

	mii.hbmpItem = CreateBitmapFromIcon(icon);
	SetMenuItemInfo(m_Menu, id, bFromPosition, &mii);
}

HBITMAP ContextMenu::GetItemIcon(BOOL bFromPosition, unsigned int id)
{
	MENUITEMINFO mii = {};
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_BITMAP;

	if (GetMenuItemInfo(m_Menu, id, bFromPosition, &mii))
		return mii.hbmpItem;

	return nullptr;
}

void ContextMenu::RemoveMenuIcon(BOOL bFromPosition, unsigned int id, bool bDeleteIcon)
{
	if (bDeleteIcon)
	{
		HBITMAP bitmap = GetItemIcon(bFromPosition, id);
		if (bitmap)
			DeleteObject(bitmap);
	}

	MENUITEMINFO mii = {};
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_BITMAP;
	mii.hbmpItem = nullptr;

	SetMenuItemInfo(m_Menu, id, bFromPosition, &mii);
}

void ContextMenu::GetItemText(char* text, int size, BOOL bDoesUsePosition, int itemID)
{
	MENUITEMINFO mii = {};
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_STRING;
	mii.dwTypeData = text;
	mii.cch = size;

	GetMenuItemInfo(m_Menu, itemID, bDoesUsePosition, &mii);
}

int ContextMenu::GetItemTextLength(BOOL bDoesUsePosition, int itemID)
{
	MENUITEMINFO mii = {};
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_STRING;
	mii.dwTypeData = NULL;
	mii.cch = 0;

	if (GetMenuItemInfo(m_Menu, itemID, bDoesUsePosition, &mii))
		return mii.cch;

	return -1;
}

unsigned int ContextMenu::GetSubMenuState(int uID, int type)
{
	return GetMenuState(m_Menu, uID, type);
}

bool ContextMenu::IsMenuEnabled(int uid, int type)
{
	UINT state = GetMenuState(m_Menu, uid, type);
	return !(state & MF_DISABLED) && !(state & MF_GRAYED);
}

bool ContextMenu::IsMenuChecked(int uid, int type)
{
	UINT state = GetMenuState(m_Menu, uid, type);
	return (state & MF_CHECKED);
}


void ContextMenu::OnDeconstructor()
{
	DeleteMenu();
}

ContextMenu::~ContextMenu()
{
	OnDeconstructor();
}
