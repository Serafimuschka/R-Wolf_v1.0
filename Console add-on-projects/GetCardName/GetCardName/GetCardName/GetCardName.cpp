// GetCardName.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "stdafx.h"
#include <iostream>
#include <dxgi.h>
#pragma comment (lib, "dxgi.lib")
using namespace std;

int main()
{
	IDXGIFactory1 * pFactory;
	HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)(&pFactory));
	int AdapterNumber = 0;
	IDXGIAdapter1* Adapter;
	cout << "Adapters:" << endl;
	pFactory->EnumAdapters1(0, &Adapter);
		DXGI_ADAPTER_DESC1 Desc;
		Adapter->GetDesc1(&Desc);
		wprintf(L"%s\n", Desc.Description);
		Adapter->Release();
	pFactory->Release();
	system("pause");
	return 0;
}