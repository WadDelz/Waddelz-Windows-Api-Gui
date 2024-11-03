#include "FileDialogs.h"

using namespace gui;

FileDialog::FileDialog(Element* parent, int id, FileDialogType type)
{
    m_Parent = parent;
    m_uId = id;
    m_Type = type;
}

void FileDialog::SetId(int id)
{
    m_uId = id;
}

int FileDialog::GetId()
{
    return m_uId;
}

bool FileDialog::Show(const char* title, int flags, const char* filter, int* filterIndex, const char* defFilePath)
{
    switch (m_Type)
    {
    case FileDialogType::FILE_OPEN_DIALOG:
        return OpenFileDialog(title, filter, filterIndex, defFilePath, flags);
    case FileDialogType::FOLDER_OPEN_DIALOG:
        return FolderOpenDialog(title, flags);
    case FileDialogType::FILE_SAVE_DIALOG:
        return SaveFileDialog(title, filter, filterIndex, defFilePath, flags);
    case FileDialogType::FOLDER_OPEN_NORMAL_DIALOG:
        return FolderOpenNormalDialog(title);
    case FileDialogType::FILE_OPEN_SHELL:
        return FileOpenShellDialog(title);
    default:
        return false;
    }
}

void FileDialog::SetType(FileDialogType type)
{
    m_Type = type;
}

FileDialogType FileDialog::GetType()
{
    return m_Type;
}

void FileDialog::SetParent(Element* parent)
{
    m_Parent = parent;
}

Element* FileDialog::GetParent()
{
    return m_Parent;
}

bool FileDialog::OpenFileDialog(const char* title, const char* filter, int* filterIndex, const char* defFilePath, int flags)
{
    char filePath[MAX_PATH] = { 0 };
    if (defFilePath)
        strcpy_s(filePath, defFilePath);

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = m_Parent ? m_Parent->GetHandle() : nullptr;
    ofn.lpstrFile = filePath;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = title;
    ofn.lpstrFilter = filter;
    ofn.Flags = flags;

    if (filterIndex)
        ofn.nFilterIndex = *filterIndex;

    if (GetOpenFileName(&ofn) == TRUE)
    {
        if (filterIndex)
            *filterIndex = ofn.nFilterIndex;

        NotifyParent(filePath);
        return true;
    }
    return false;
}

bool FileDialog::FileOpenShellDialog(const char* title)
{
    BROWSEINFO bi;
    ZeroMemory(&bi, sizeof(bi));
    bi.hwndOwner = m_Parent ? m_Parent->GetHandle() : nullptr;
    bi.lpszTitle = title;
    bi.ulFlags = BIF_BROWSEINCLUDEFILES | BIF_NEWDIALOGSTYLE;

    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
    if (pidl != nullptr)
    {
        char filePath[MAX_PATH];
        if (SHGetPathFromIDList(pidl, filePath))
        {
            NotifyParent(filePath);
            CoTaskMemFree(pidl);
            return true;
        }
        CoTaskMemFree(pidl);
    }
    return false;
}


bool FileDialog::FolderOpenDialog(const char* title, int flags)
{
    BROWSEINFO bi;
    ZeroMemory(&bi, sizeof(bi));
    bi.hwndOwner = m_Parent ? m_Parent->GetHandle() : nullptr;
    bi.lpszTitle = title;
    bi.ulFlags = flags;

    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
    if (pidl != nullptr)
    {
        char folderPath[MAX_PATH];
        if (SHGetPathFromIDList(pidl, folderPath))
        {
            NotifyParent(folderPath);
            CoTaskMemFree(pidl);
            return true;
        }
        CoTaskMemFree(pidl);
    }
    return false;
}

bool FileDialog::FolderOpenNormalDialog(const char* title)
{
    IFileDialog* pfd = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
    if (SUCCEEDED(hr))
    {
        DWORD options;
        hr = pfd->GetOptions(&options);
        if (SUCCEEDED(hr))
            pfd->SetOptions(options | FOS_PICKFOLDERS);

        if (title)
            pfd->SetTitle((LPWSTR)title);

        hr = pfd->Show(m_Parent ? m_Parent->GetHandle() : nullptr);
        if (SUCCEEDED(hr))
        {
            IShellItem* psi;
            hr = pfd->GetResult(&psi);
            if (SUCCEEDED(hr))
            {
                PWSTR path;
                hr = psi->GetDisplayName(SIGDN_FILESYSPATH, &path);
                if (SUCCEEDED(hr))
                {
                    char folderPath[MAX_PATH];
                    wcstombs(folderPath, path, MAX_PATH);
                    NotifyParent(folderPath);
                    CoTaskMemFree(path);
                }
                psi->Release();
            }
        }
        pfd->Release();
    }
    return SUCCEEDED(hr);
}


bool FileDialog::SaveFileDialog(const char* title, const char* filter, int* filterIndex, const char* defFilePath, int flags)
{
    char filePath[MAX_PATH] = { 0 };
    if (defFilePath)
        strcpy_s(filePath, defFilePath);

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = m_Parent ? m_Parent->GetHandle() : nullptr;
    ofn.lpstrFile = filePath;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = title;
    ofn.lpstrFilter = filter;
    ofn.Flags = flags;

    if (filterIndex)
        ofn.nFilterIndex = *filterIndex;

    if (GetSaveFileName(&ofn) == TRUE)
    {
        if (filterIndex)
            *filterIndex = ofn.nFilterIndex;

        NotifyParent(filePath);
        return true;
    }
    return false;
}

void FileDialog::NotifyParent(const char* selectedPath)
{
    if (m_Parent)
    {
        m_Parent->OnFileSelected(m_uId, selectedPath, m_Type);
    }
}
