#include "ImageList.h"

using namespace gui;

ImageList::ImageList(int wide, int tall, unsigned int flags, int initialCount, int growCount)
{
	m_vIcons = {};
	m_ImageList = ImageList_Create(wide, tall, flags, initialCount, growCount);
}

std::vector<HICON> ImageList::GetIcons()
{
	return m_vIcons;
}

void ImageList::CreateImageList(int wide, int tall, unsigned int flags, int initialCount, int growCount)
{
	m_ImageList = ImageList_Create(wide, tall, flags, initialCount, growCount);
}

void ImageList::DeleteImageList()
{
	ImageList_Destroy(m_ImageList);
	m_ImageList = nullptr;
	m_vIcons = {};
}

void ImageList::AddIcon(HICON icon)
{
	ImageList_AddIcon(m_ImageList, icon);
	m_vIcons.push_back(icon);
}

void ImageList::RemoveIcon(HICON icon)
{
	unsigned int index = 0;
	for (unsigned int i = 0; i < m_vIcons.size(); i++)
	{
		if (m_vIcons.at(i) == icon)
			index = i;
	}

	ImageList_Remove(m_ImageList, index);
	m_vIcons.erase(m_vIcons.begin() + index);
}

void ImageList::RemoveIconByIndex(int index)
{
	ImageList_Remove(m_ImageList, index);
	m_vIcons.erase(m_vIcons.begin() + index);
}

int ImageList::FindIndexByIcon(HICON icon)
{
	for (unsigned int i = 0; i < m_vIcons.size(); i++)
	{
		if (m_vIcons.at(i) == icon)
			return i;
	}
	return -1;
}

HIMAGELIST ImageList::GetImageList()
{
	return m_ImageList;
}
