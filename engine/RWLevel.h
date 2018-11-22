#pragma once
#include "RWGraphics.h"
#include "RWSpriteSystem.h"
#include "RWSound.h"
#include <iostream>
#include <sstream>
#include <string>
#include <atlbase.h>
#include <msxml.h>

class RWLevel {
protected:
	IXMLDOMAttribute*		attr;
	IXMLDOMElement*			elem;
	IXMLDOMNamedNodeMap*	map;
	IXMLDOMNode*			XMLNode;
	CComBSTR				path;
	CComVariant				name, varval;
	CComVariant				valuex, valuey;
	HRESULT					hres;
	FLOAT					dtime, ttime;
	WCHAR*					con_in;

	static RWGraphics*				core;
	static RWSpriteSystem*			picture;
	static RWSpriteSystem*			tex;
	static RWSpriteAlternative*		sprite;
	static RWSound*					sound;
public:
	XMFLOAT2				mapsize;
	XMFLOAT2				startpos;
	XMFLOAT2				objectpos;
	UINT					encounter;
	DOUBLE					speed;
	INT						anim;

	float SW, SH;
	bool console;
	int consoleSwitcher;

	std::wstring AdapterName, buildnum, buildname;
	std::wstring CurrentLevelName;

	void ScriptInit(const char* filename);

	static void Initialize(RWGraphics* graphics) {
		core = graphics;
	}

	virtual double TranslateData(XMFLOAT2 vec) = 0;
	virtual void Action(UINT code) = 0;
	virtual void TranslateRect(UINT width, UINT height) = 0;
	virtual void GetConsoleInput(WCHAR* input) = 0;

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(double timeTotal, double timeDelta) = 0;
	virtual void Render() = 0;
};