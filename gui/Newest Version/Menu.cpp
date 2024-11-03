#include "Menu.h"
#include "Icon.h"

using namespace gui;

Menu::Menu(bool bCreateMenu)
{
	m_Parent = nullptr;
	m_MenuParent = nullptr;
	m_Child = nullptr;
	m_Next = nullptr;

	if (bCreateMenu)
		m_Menu = CreateMenu();
	else
		m_Menu = nullptr;
}

void Menu::SetMenu(HMENU menu)
{
	m_Menu = menu;
}

void Menu::SetParent(Element* parent)
{
	m_Parent = parent;
}

void Menu::DeleteMenu()
{
	if (m_Menu)
		DestroyMenu(m_Menu);

	if (m_Next)
		m_Next->DeleteMenu();

	if (m_Child)
		m_Child->DeleteMenu();

	delete this;
}

void Menu::AddItem(const char* text, int flags, int id)
{
	AppendMenu(m_Menu, flags, id, text);
}

void Menu::AddSeperator()
{
	AppendMenu(m_Menu, MF_SEPARATOR, NULL, nullptr);
}

void Menu::AddVerticleSeperator(const char* text, int id, int flags)
{
	AppendMenu(m_Menu, MF_MENUBARBREAK | flags, id, text);
}

void Menu::AddMenu(Menu* menu, const char* text, int flags)
{
	if (!menu)
		return;

	if (!menu->m_Menu)
		return;

	AppendMenu(m_Menu, flags, (UINT_PTR)menu->m_Menu, text);

	Menu* tmp = m_Child;
	m_Child = menu;
	menu->m_Next = tmp;
}

Menu* Menu::CreateNewMenu()
{
	Menu* ret = new Menu(true);
	ret->m_MenuParent = this;
	return ret;
}

Menu* Menu::GetChild()
{
	return m_Child;
}

Menu* Menu::GetMenuParent()
{
	return m_MenuParent;
}

Menu* Menu::GetNext()
{
	return m_Next;
}

Menu* Menu::FindMenuByHMenu(HMENU menu)
{
	if (m_Menu = menu)
		return this;

	Menu* curr = m_Child;
	while (curr)
	{
		Menu* find = curr->FindMenuByHMenu(menu);
		if (find)
			return find;
			
		curr = curr->m_Next;
	}

	return nullptr;
}

Element* Menu::GetParent()
{
	return m_Parent;
}

HMENU Menu::GetMenu()
{
	return m_Menu;	
}

void Menu::SetMenuText(const char* text, int type, int id)
{
	ModifyMenu(m_Menu, id, type | MF_STRING, id, text);
}

void Menu::CheckMenuItem(bool bChecked, int type, int id, const char* backuptext)
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

void Menu::EnableMenuItem(bool bEnabled, bool bGreyedOut, int type, int id, const char* backuptext)
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

void Menu::SetMenuIcon(HICON icon, BOOL bFromPosition, unsigned int id)
{
	MENUITEMINFO mii = {};
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_BITMAP;

	mii.hbmpItem = CreateBitmapFromIcon(icon);
	SetMenuItemInfo(m_Menu, id, bFromPosition, &mii);
}

HBITMAP Menu::GetItemIcon(BOOL bFromPosition, unsigned int id)
{
	MENUITEMINFO mii = {};
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_BITMAP;

	if (GetMenuItemInfo(m_Menu, id, bFromPosition, &mii))
		return mii.hbmpItem;

	return nullptr;
}

void Menu::RemoveMenuIcon(BOOL bFromPosition, unsigned int id, bool bDeleteIcon)
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

unsigned int Menu::GetSubMenuState(int uID, int type)
{
	return GetMenuState(m_Menu, uID, type);
}

bool Menu::IsMenuEnabled(int uid, int type)
{
	UINT state = GetMenuState(m_Menu, uid, type);
	return !(state & MF_DISABLED) && !(state & MF_GRAYED);
}

bool Menu::IsMenuChecked(int uid, int type)
{
	UINT state = GetMenuState(m_Menu, uid, type);
	return (state & MF_CHECKED);
}

void Menu::GetItemText(char* text, int size, BOOL bDoesUsePosition, int itemID)
{
	MENUITEMINFO mii = {};
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_STRING;
	mii.dwTypeData = text;
	mii.cch = size;

	GetMenuItemInfo(m_Menu, itemID, bDoesUsePosition, &mii);
}

int Menu::GetItemTextLength(BOOL bDoesUsePosition, int itemID)
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