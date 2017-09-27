#pragma once
#include"Vehicle.h"
#include"Chain.h"

struct Route;
struct Fleet;
struct Urban;

enum struct UIState
{
	None,				//�����\�����Ȃ�
	UrbanInfo,			//�P���Urban�̏���\��
	AllUrbansInfo,		//���ׂĂ�Urban�̔�r����\��
	FleetInfo,			//��̑D�c�ɑ΂���ҏW
	FleetsInfo,			//�����̑D�c�ɑ΂���ҏW
	ExportRelationsInfo,//�S�s�s�Ԃ̖f�Պ֌W
};

struct RouteMaker
{
	struct WayPoint
	{
		Urban* urban;
		Optional<int> buyItemType;

		WayPoint(Urban* _urban)
			: urban(_urban)
			, buyItemType(none)
		{}
	};

	Fleet*	targetFleet;
	Array<WayPoint>	wayPoints;


	RouteMaker()
		: targetFleet(nullptr)
	{}
	void	set(Fleet* _targetFleet);
	void	update();
};
extern RouteMaker routeMaker;

struct Selecter
{
	Urban*	selectedUrban;
	Array<Fleet*> selectedFleets;
	Optional<Vec2>	selectedPos;

	Selecter()
		: selectedUrban(nullptr)
		, selectedPos(none)
	{}
	void	update();
	void	draw() const;
	RectF	selectedRegion() const;
};
extern Selecter	selecter;

struct DisplayUrban
{
	enum struct UrbanInfoState
	{
		Worker,
		Shelves,
	} urbanInfoState;
	Stopwatch	openElapsedTime;	//�J���Ă���̌o�ߎ���
	Stopwatch	closeElapsedTime;	//���Ă���̌o�ߎ���

	DisplayUrban()
		: openElapsedTime(MillisecondsF(10000.0), true)
		, closeElapsedTime(MillisecondsF(10000.0), true)
	{}
	void	update();
};
extern DisplayUrban	displayUrban;

struct DisplayFleets
{
	Stopwatch	openElapsedTime;	//�J���Ă���̌o�ߎ���
	Stopwatch	closeElapsedTime;	//���Ă���̌o�ߎ���

	DisplayFleets()
		: openElapsedTime(MillisecondsF(10000.0), true)
		, closeElapsedTime(MillisecondsF(10000.0), true)
	{}
	void	update();
};
extern DisplayFleets	displayFleets;
extern Array<Font*>	globalFonts;

/*
struct Display
{

	Stopwatch	elapsedTime;	//�ʂ�UI�J�����ۂ̌o�ߎ���
	bool	useRouteMenu;
	bool	useUrbanMenu;
	int		urbanDrawState;
	bool	drawExportLineEnabled;
	bool	drawExportImportPowerEnabled;
	Route*	selectedRoute;
	Chain	newChain;
	TextBox	fleetNameTextBox;
	bool	keyControlBlocked;
	int		destinationUrbanID;
	int		transportItemType;
	UIState	uiState;
	Array<Font*>	globalFonts;

	Display();
	void	updateSelectItem();
	void	updateAllUrbansInfo();
	void	updateFleetInfo();
	void	updateFleetsInfo();
	void	updateExportRelationsInfo();
};

extern Display		display;
*/

void	drawUI();
void	updateTimeSpeed();