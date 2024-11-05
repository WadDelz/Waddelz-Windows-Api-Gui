#include "PropertyPage.h"

using namespace gui;

PropertyPage::PropertyPage()
{
	m_Parent = nullptr;
	m_vItems = {};
}

PropertyPage::PropertyPage(Element* parent)
{
	m_Parent = parent;
	m_vItems = {};
}

Element* PropertyPage::GetParent()
{
	return m_Parent;
}

void PropertyPage::SetParent(Element* parent)
{
	m_Parent = parent;
}

void PropertyPage::OnSelect() { ShowAllItems(true); }
void PropertyPage::OnDeselect() { ShowAllItems(false); }

void PropertyPage::AddElement(Element* element)
{
	auto it = std::find(m_vItems.begin(), m_vItems.end(), element);
	if (it == m_vItems.end())
		m_vItems.push_back(element);

	element->SetPropertyPage(this);
}

void PropertyPage::RemoveElement(Element* element, const bool& bDelete)
{
	auto it = std::find(m_vItems.begin(), m_vItems.end(), element);
	if (it != m_vItems.end())
	{
		m_vItems.erase(it);

		if (bDelete)
			delete element;
	}
}

std::vector<Element*> PropertyPage::GetElements()
{
	return m_vItems;
}

void PropertyPage::ShowAllItems(const bool& bShow)
{
	for (unsigned int i = 0; i < m_vItems.size(); i++)
	{
		Element* curr = m_vItems[i];
		if (!curr)
			return;

		curr->SetVisible(bShow);
	}
}

void PropertyPage::DeleteAllItems()
{
	for (unsigned int i = 0; i < m_vItems.size(); i++)
	{
		Element* curr = m_vItems[i];
		if (!curr)
			return;

		delete curr;
	}
	m_vItems.clear();
}

PropertyPageManager::PropertyPageManager()
{
	m_Parent = nullptr;
	m_vPPages = {};
}

void PropertyPageManager::AddPage(PropertyPage* page)
{
	auto it = std::find(m_vPPages.begin(), m_vPPages.end(), page);
	if (it == m_vPPages.end())
		m_vPPages.push_back(page);
}

void PropertyPageManager::RemovePage(PropertyPage* page, const bool& bDelete)
{
	auto it = std::find(m_vPPages.begin(), m_vPPages.end(), page);
	if (it != m_vPPages.end())
	{
		m_vPPages.erase(it);

		if (bDelete)
			delete page;
	}
}

void PropertyPageManager::RemovePage(const unsigned int& index)
{
	if (index < m_vPPages.size())
	{
		PropertyPage* ppage = m_vPPages[index];
		if (ppage)
			delete ppage;

		m_vPPages.erase(m_vPPages.begin() + index);
	}
}

PropertyPage* PropertyPageManager::GetPageFromIndex(const unsigned int& index)
{
	if (index >= m_vPPages.size())
		return nullptr;

	return m_vPPages[index];
}

void PropertyPageManager::SelectPage(const unsigned int& index)
{
	if (index >= m_vPPages.size())
		return;

	for (unsigned int i = 0; i < m_vPPages.size(); i++)
	{
		PropertyPage* page = m_vPPages[i];
		if (!page)
			continue;

		if (i == index)
			page->OnSelect();
		else
			page->OnDeselect();
	}
}

Element* PropertyPageManager::GetParent()
{
	return m_Parent;
}

void PropertyPageManager::SetParent(Element* parent)
{
	m_Parent = parent;
	for (unsigned int i = 0; i < m_vPPages.size(); i++)
	{
		PropertyPage* page = m_vPPages[i];
		if (!page)
			continue;

		page->SetParent(parent);
	}
}

std::vector<PropertyPage*> PropertyPageManager::GetPages()
{
	return m_vPPages;
}

void PropertyPageManager::DeleteEverything(bool bDeleteThis)
{
	for (unsigned int i = 0; i < m_vPPages.size(); i++)
	{
		PropertyPage* page = m_vPPages[i];
		if (!page)
			continue;

		page->DeleteAllItems();
		delete page;
	}
	m_vPPages.clear();

	if (bDeleteThis)
		delete this;
}
