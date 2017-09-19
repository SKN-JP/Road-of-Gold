#pragma once

#include"Casket.h"
#include"Export.h"
#include"Chain.h"

struct Wallet;
struct VehicleData;
struct Fleet;
struct Pos;
struct Urban;
struct Route;

struct Vehicle
{
	int		vehicleType;
	int		walletID;
	Casket	cargo;
	double	routeProgress;
	double	sleepTimer;
	Urban*	nowUrban;
	Route*	route;
	Export	exportLog;
	bool	stopFlag;	//trueならば事業を中断
	bool	planFixed;
	double	timer;	//運用期間
	double	period;	//一周するのに要する時間
	Chain	chain;

	Vehicle(int _vehicleType, Urban* _nowUrban);
	VehicleData&	data() const;
	Vec2	pos() const;
	double	angle() const;
	Wallet&	wallet() const;
	bool	mouseOver() const;
	int		id() const;
};

extern Array<Vehicle> vehicles;

void	updateVehicles();
void	drawVehicles();