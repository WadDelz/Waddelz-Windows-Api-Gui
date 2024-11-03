#ifndef __SUBDIALOG_H
#define __SUBDIALOG_H

#include "Element.h"
#include "gui_resource.h"

#pragma once

namespace gui
{
	class SubDialog : public Element
	{
		DECLARE_ELEMENT_DIALOG(SubDialog, Element)
		DECLARE_ELEMENT_DIALOG_DIFFERENT(SubDialog, Element)

		SubDialog();

		virtual void MakeDialog(Element* parent, int nResourceFile = _GUI_DIALOG);
		virtual void MakeDialogBox(Element* parent, int nResourceFile = _GUI_DIALOG);

		virtual void SetDeleteOnClose(bool bDelete);

		virtual void OnClose(ELEMENT_PROC_ITEMS);
		virtual void OnCloseDifferent(ELEMENT_PROC_ITEMS);

		DECLARE_ELEMENT_DLGPROC()
		DECLARE_ELEMENT_DLGPROC_DIFFERENT()
	private:
		bool m_bDeleteOnClose;
	};
}

#endif