#pragma once
#include"Chain.h"
#include"Export.h"
#include"VehicleData.h"
#include"Casket.h"

struct Vehicle;
struct Route;
struct Wallet;
struct Urban;

struct Fleet
{
	String	name;
	Array<Vehicle*>	ownVehicles;
	int		walletID;
	double	routeProgress;
	double	sleepTimer;
	Urban*	nowUrban;
	Route*	route;
	Export	exportLog;
	bool	stopFlag;	//true�Ȃ�Ύ��Ƃ𒆒f
	bool	planFixed;
	double	timer;	//�^�p����
	double	period;	//�������̂ɗv���鎞��
	Chain	chain;
	Casket	cargo;
	VehicleData	data;

	Fleet(int _ownVehicleType, Urban* _nowUrban);
	void	add(Vehicle* _v);
	Vec2	pos() const;
	double	angle() const;
	Wallet&	wallet() const;
	bool	mouseOver() const;
	int		id() const;
	bool	canMoveTo(const Urban& _u) const;
	void	setMoveTo(const Urban& _u);
};

extern Array<Fleet>	fleets;

void	updateFleets();
void	drawFleets();