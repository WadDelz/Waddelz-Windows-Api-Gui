#ifndef __FILEDIALOG_H
#define __FILEDIALOG_H

#include "Element.h"  
#include <windows.h>
#include <commdlg.h>
#include <shlobj.h>
#include <string>

#pragma once

#define DEF_FLAGS_OPENFILE OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST
#define DEF_FLAGS_OPEN_FOLDER BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE
#define DEF_FLAGS_SAVEFILE OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT

namespace gui
{
    class FileDialog
    {
    public:
        FileDialog(Element* parent, int id, FileDialogType type);

        virtual void SetId(int id);
        virtual int GetId();

        virtual bool Show(const char* title, int flags, const char* filter = "All Files\0*.*\0",
            int* filterIndex = nullptr, const char* defFilePath = nullptr);

        virtual void SetType(FileDialogType type);
        virtual FileDialogType GetType();

        virtual void SetParent(Element* parent);
        virtual Element* GetParent();
    protected:
        Element* m_Parent;
        FileDialogType m_Type;
        int m_uId;

    protected:
        bool OpenFileDialog(const char* title, const char* filter, int* filterIndex, const char* defFilePath, int flags);
        bool FileOpenShellDialog(const char* title);
        bool FolderOpenDialog(const char* title, int flags);
        bool FolderOpenNormalDialog(const char* title);
        bool SaveFileDialog(const char* title, const char* filter, int* filterIndex, const char* defFilePath, int flags);

        void NotifyParent(const char* selectedPath);
    };
}

#endif
