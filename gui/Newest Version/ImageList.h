#ifndef __IMAGELIST_H
#define __IMAGELIST_H

#include "Element.h"
#include <CommCtrl.h>

#pragma once

namespace gui
{
	class ImageList
	{
	public:
		ImageList(int wide, int tall, unsigned int flags = ILC_COLOR32, int initialCount = 5, int growCount = 5);

		virtual std::vector<HICON> GetIcons();

		//ONLY USE IF YOU DESTROY IT
		virtual void CreateImageList(int wide, int tall, unsigned int flags = ILC_COLOR32, int initialCount = 5, int growCount = 5);

		virtual void DeleteImageList();

		virtual void AddIcon(HICON icon);
		virtual void RemoveIcon(HICON icon);
		virtual void RemoveIconByIndex(int index);

		virtual int FindIndexByIcon(HICON icon);

		virtual HIMAGELIST GetImageList();
	protected:
		HIMAGELIST m_ImageList;
		std::vector<HICON> m_vIcons;
	};
}

#endif