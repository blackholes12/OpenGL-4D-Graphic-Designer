#include <Windows.h>
#include <ObjIdl.h>
#include <gdiplus.h>
#include <uxtheme.h>
#include <shobjidl_core.h>

#pragma comment (lib,"Gdiplus.lib")
#pragma comment(lib,"Uxtheme")

#define MAX_LOADSTRING 100
#define IDB_BUTTON1 101

using namespace Gdiplus;
using namespace std;


void putImage(HDC, HWND);
void Opendialog();

HWND hwnd;
PWSTR pszFilePath;
BOOL flag = 0;
HRESULT hr;
char filepath[255];
void Opendialog()
{
    hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
        COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        IFileOpenDialog* pFileOpen;

        // Create the FileOpenDialog object.
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
            IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

        if (SUCCEEDED(hr))
        {
            // Show the Open dialog box.
            hr = pFileOpen->Show(NULL);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hr))
            {
                IShellItem* pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                    // Display the file name to the user.
                    if (SUCCEEDED(hr))
                    {
                   //MessageBox(NULL, pszFilePath, L"File Path", MB_OK);
                        CoTaskMemFree(pszFilePath);
                        WideCharToMultiByte(CP_ACP, 0, pszFilePath, -1, filepath, sizeof(filepath), NULL, NULL);
                    }
                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
    }
}