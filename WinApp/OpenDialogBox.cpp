#include <windows.h>
#include <shobjidl.h> 

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	//Call CoInitializeEx to initialize the COM library
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	
	if (SUCCEEDED(hr))
	{
		IFileOpenDialog *pFileOpen;

		// Call CoCreateInstance to create the Common Item Dialog object and get a pointer to the object's IFileOpenDialog interface.
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

		if (SUCCEEDED(hr))
		{
			//Call the object's Show method, which shows the dialog box to the user. This method blocks until the user dismisses the dialog box.
			hr = pFileOpen->Show(NULL);

			// Get the file name from the dialog box.
			if (SUCCEEDED(hr))
			{
				IShellItem *pItem;
				//Call the object's GetResult method. This method returns a pointer to a second COM object, called a Shell item object. 
				//The Shell item, which implements the IShellItem interface, represents the file that the user selected.
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					PWSTR pszFilePath;
					//Call the Shell item's GetDisplayName method. This method gets the file path, in the form of a string.
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					// Display the file name to the user.
					if (SUCCEEDED(hr))
					{
						//Show a message box that displays the file path.
						MessageBox(NULL, pszFilePath, L"File Path", MB_OK);
						CoTaskMemFree(pszFilePath);
					}
					pItem->Release();
				}
			}
			pFileOpen->Release();
		}
		//Call CoUninitialize to uninitialize the COM library.
		CoUninitialize();
	}
	return 0;
}
