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

struct DisplayUrban
{
	enum struct UrbanInfoState
	{
		Worker,
		Shelves,
	} urbanInfoState;
	Stopwatch	openElapsedTime;	//�J���Ă���̌o�ߎ���
	Stopwatch	closeElapsedTime;	//���Ă���̌o�ߎ���
	Urban*	selectedUrban;

	void	update();
	DisplayUrban()
		: openElapsedTime(MillisecondsF(10000.0), true)
		, closeElapsedTime(true)
	{}
};


struct Display
{

	Stopwatch	elapsedTime;	//�ʂ�UI�J�����ۂ̌o�ߎ���
	bool	useRouteMenu;
	bool	useUrbanMenu;
	int		urbanDrawState;
	Urban*	selectedUrban;
	int		selectedFleetID;
	int		selectedItemType;
	bool	drawExportLineEnabled;
	bool	drawExportImportPowerEnabled;
	Route*	selectedRoute;
	Chain	newChain;
	TextBox	fleetNameTextBox;
	bool	keyControlBlocked;
	RectF	selectedRegion;
	int		destinationUrbanID;
	int		transportItemType;
	UIState	uiState;
	Array<Fleet*> selectedFleets;
	Array<Font*>	fonts;

	Display();
	void	updateSelectItem();
	void	updateAllUrbansInfo();
	void	updateFleetInfo();
	void	updateFleetsInfo();
	void	updateExportRelationsInfo();
};

extern Display		display;
extern DisplayUrban	displayUrban;

void	drawUI();
void	updateTimeSpeed();