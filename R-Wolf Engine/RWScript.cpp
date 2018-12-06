#include "RWLevel.h"

void RWLevel::ScriptInit(const char* filename) {
	CoInitialize(NULL);
	XMFLOAT2 text_coord;
	try {
		CComPtr<IXMLDOMDocument> spXMLDOM;
		hres = spXMLDOM.CoCreateInstance(__uuidof(DOMDocument));
		if (FAILED(hres)) throw "Unable to create XML parser object";
		if (spXMLDOM.p == NULL) throw "Unable to create XML parser object";

		VARIANT_BOOL bSuccess = false;
		hres = spXMLDOM->load(CComVariant(filename), &bSuccess);
		if (FAILED(hres)) throw "Unable to load XML script into the parser";
		if (!bSuccess) throw "Unable to load XML script into the parser";

		CComBSTR bstrSS(L"rwxmldata/graphics");
		CComPtr<IXMLDOMNode> spXMLNode;
		hres = spXMLDOM->selectSingleNode(bstrSS, &spXMLNode);
		if (FAILED(hres)) throw "Unable to locate root 'rwxmldata' XML node";
		if (spXMLNode.p == NULL) throw "Unable to locate root 'rwxmldata' XML node";

		spXMLNode = NULL; // for releasing previous nodes
		bstrSS = L"rwxmldata/graphics/print/x";
		hres = spXMLDOM->selectSingleNode(bstrSS, &spXMLNode);
		if (FAILED(hres)) throw "Unable to locate 'graphics/print/x' XML node";
		if (spXMLNode.p == NULL) throw "Unable to locate 'graphics/print/x' XML node";

		CComVariant varPX(VT_EMPTY);
		hres = spXMLNode->get_nodeTypedValue(&varPX);
		if (FAILED(hres)) throw "Unable to retrieve 'X' coord";

		if (varPX.vt == VT_BSTR) {
			USES_CONVERSION;
			text_coord.x = varPX.fltVal;
		}

		spXMLNode = NULL; // for releasing previous nodes
		bstrSS = L"rwxmldata/graphics/print/y";
		hres = spXMLDOM->selectSingleNode(bstrSS, &spXMLNode);
		if (FAILED(hres)) throw "Unable to locate 'graphics/print/y' XML node";
		if (spXMLNode.p == NULL) throw "Unable to locate 'graphics/print/y' XML node";

		CComVariant varPY(VT_EMPTY);
		hres = spXMLNode->get_nodeTypedValue(&varPY);
		if (FAILED(hres)) throw "Unable to retrieve 'Y' coord";

		if (varPY.vt == VT_BSTR) {
			USES_CONVERSION;
			text_coord.y = varPY.fltVal;
		}

		spXMLNode = NULL; // for releasing previous nodes
		bstrSS = L"rwxmldata/graphics/print";
		hres = spXMLDOM->selectSingleNode(bstrSS, &spXMLNode);
		if (FAILED(hres)) throw "Unable to locate 'graphics/print' XML node";
		if (spXMLNode.p == NULL) throw "Unable to locate 'graphics/print' XML node";

		CComVariant varPrint(VT_EMPTY);
		hres = spXMLNode->get_nodeTypedValue(&varPrint);
		if (FAILED(hres)) throw "Unable to retrieve 'print' text";

		if (varPrint.vt == VT_BSTR) {
			USES_CONVERSION;
			LPCWSTR lpstrMsg = varPrint.bstrVal;
			core->PrintTextManual(lpstrMsg, text_coord, 25, core->RW_Roboto, core->DeepSkyBlue);
		}
		else {
			throw "Unable to retrieve 'print' argument";
		}
	}
	catch (char* lpstrErr) {
		//std::cout << lpstrErr << std::endl;
	}
	catch (...) {
		//std::cout << " " << std::endl;
	}
	CoUninitialize();
}