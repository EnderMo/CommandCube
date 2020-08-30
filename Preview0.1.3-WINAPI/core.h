#pragma once
#include "framework.h"
#include <conio.h>
#include <string>
int DeleteDirectory(const std::wstring& refcstrRootDirectory,
    bool              bDeleteSubdirectories = true)
{
    bool            bSubdirectory = false;       // Flag, indicating whether
                                                 // subdirectories have been found
    HANDLE          hFile;                       // Handle to directory
    std::wstring     strFilePath;                 // Filepath
    std::wstring     strPattern;                  // Pattern
    WIN32_FIND_DATA FileInformation;             // File information


    strPattern = refcstrRootDirectory + L"\\*.*";
    hFile = ::FindFirstFile(strPattern.c_str(), &FileInformation);
    if (hFile != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (FileInformation.cFileName[0] != '.')
            {
                strFilePath.erase();
                strFilePath = refcstrRootDirectory + L"\\" + FileInformation.cFileName;

                if (FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    if (bDeleteSubdirectories)
                    {
                        // Delete subdirectory
                        int iRC = DeleteDirectory(strFilePath, bDeleteSubdirectories);
                        if (iRC)
                            return iRC;
                    }
                    else
                        bSubdirectory = true;
                }
                else
                {
                    // Set file attributes
                    if (::SetFileAttributes(strFilePath.c_str(),
                        FILE_ATTRIBUTE_NORMAL) == FALSE)
                        return ::GetLastError();

                    // Delete file
                    if (::DeleteFile(strFilePath.c_str()) == FALSE)
                        return ::GetLastError();
                }
            }
        } while (::FindNextFile(hFile, &FileInformation) == TRUE);

        // Close handle
        ::FindClose(hFile);

        DWORD dwError = ::GetLastError();
        if (dwError != ERROR_NO_MORE_FILES)
            return dwError;
        else
        {
            if (!bSubdirectory)
            {
                // Set directory attributes
                if (::SetFileAttributes(refcstrRootDirectory.c_str(),
                    FILE_ATTRIBUTE_NORMAL) == FALSE)
                    return ::GetLastError();

                // Delete directory
                if (::RemoveDirectory(refcstrRootDirectory.c_str()) == FALSE)
                    return ::GetLastError();
            }
        }
    }

    return 0;
}


void Opentext(const char* FN,char* buffer)
{
    filebuf* pbuf;

    ifstream filestr;

    long size;

    //char* buf;

    filestr.open(FN, ios::in | ios::binary);

    pbuf = filestr.rdbuf();

    size = pbuf->pubseekoff(0, ios::end, ios::in);

    pbuf->pubseekpos(0, ios::in);

    buffer = new char[size];

    pbuf->sgetn(buffer, size);

    filestr.close();
}
#define OPENTEXT Opentext
#define opentext Opentext
#define OpenText Opentext