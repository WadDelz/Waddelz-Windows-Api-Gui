#ifndef __PROPERTYPAGE_H
#define __PROPERTYPAGE_H

#include "Element.h"

#pragma once

//todo: add source engine style property page thinggy-me-bobs

namespace gui
{
	class PropertyPage
	{
	public:
		PropertyPage();
		PropertyPage(Element* parent);

		virtual Element* GetParent();
		virtual void SetParent(Element* parent);

		virtual void OnSelect();
		virtual void OnDeselect();

		virtual void AddElement(Element* element);
		virtual void RemoveElement(Element* element, const bool& bDelete = true);

		std::vector<Element*> GetElements();
	
		virtual void ShowAllItems(const bool& bShow);
		virtual void DeleteAllItems();
	protected:
		Element* m_Parent;

		std::vector<Element*> m_vItems;
	};

	class PropertyPageManager
	{
	public:
		PropertyPageManager();

		virtual void AddPage(PropertyPage* page);
		virtual void RemovePage(PropertyPage* page, const bool& bDelete = false);
		virtual void RemovePage(const unsigned int& index);

		virtual PropertyPage* GetPageFromIndex(const unsigned int& index);

		virtual void SelectPage(const unsigned int& index);

		virtual Element* GetParent();
		virtual void SetParent(Element* parent);
		
		virtual std::vector<PropertyPage*> GetPages();

		virtual void DeleteEverything(bool bDeleteThis = false);
	protected:
		Element* m_Parent;

		std::vector<PropertyPage*> m_vPPages;
	};
}

#endif