#pragma once

// core instruments:
#ifdef _RW_USE_GLOBAL_DEFINITIONS
#define clscr			clearScreen
#define cmd				createConsole
#define line			drawLine
#define rect			drawRectangle
#define ellipse			drawCircle
#define tri				drawTriangle
#define arc				drawArc
#define textdef			printText
#define textman			printTextManual
#define textnum			printNum
#define bar				progressBar
#define entity			drawEntity
#define info			showInfo
#define menu			showMenu
#define hware			showHardware
#define rw_iface		drawInterface
#define SW				ScreenWidth
#define SH				ScreenHeight
#endif

// actions enumeration:
enum Actions {
	RW_SYSTEM_CONSOLE = 0,
	RW_ACTION_SHOOT = 1,
	RW_ACTION_SWITCH_WEAPONS = 2,
	RW_ACTION_JUMP = 3,
	RW_ACTION_EQUIP_SHIELD = 4,
	RW_ACTION_DEQUIP_SHIELD = 5,
	RW_ACTION_THROW_GRENADE = 6,
	RW_ACTION_TAKE_ITEM = 7,
	RW_ACTION_DROP_ITEM = 8,
	RW_ACTION_INVENTORY = 9,
	RW_ACTION_USE = 10,
	RW_ACTION_RUN = 11,
	RW_ACTION_STEALTH = 12
};

// entity types structs:
struct Item {
	LPCWSTR name;
	double health;
	double damage;
};

// entity types enumeration:
enum ItemTypes {
	ENTITY_RECT = 0,
	ENTITY_BULLET = 1,
	ENTITY_AID = 2
};