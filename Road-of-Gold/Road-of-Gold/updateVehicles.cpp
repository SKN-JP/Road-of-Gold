#include"Planet.h"
#include"Vehicle.h"
#include"Urban.h"
#include"Route.h"
#include"VehicleData.h"
#include"ItemData.h"
#include"UI.h"
#include"Sound.h"
#include"Export.h"


void	updateVehicles()
{
	for (auto& v : vehicles)
	{
		double actionTime = planet.timeSpeed;

		for (;;)
		{
			if (v.route != nullptr)	//実行中のルートがあるならば
			{
				if (v.route->movingCost / v.data().speed <= v.routeProgress + actionTime)
				{
					actionTime -= v.route->movingCost / v.data().speed - v.routeProgress;
					v.timer += v.route->movingCost / v.data().speed - v.routeProgress;
					v.routeProgress = 0;
					v.nowUrban = v.route->toUrban;
					v.route->pullVehicle();
					v.route = nullptr;
					v.chain.readerPos++;
				}
				else
				{
					v.routeProgress += actionTime;
					v.timer += actionTime;
					actionTime = 0;
					break;
				}
			}
			else if (v.sleepTimer > 0)	//休憩中ならば
			{
				if (v.sleepTimer <= actionTime)
				{
					v.sleepTimer = 0.0;
					actionTime -= v.sleepTimer;
					v.timer += v.sleepTimer;
					v.chain.readerPos++;
				}
				else
				{
					v.sleepTimer -= actionTime;
					v.timer += actionTime;
					actionTime = 0;
					break;
				}
			}
			else if (v.stopFlag)	//事業停止
			{
				v.stopFlag = false;
				for (auto& e : exports)
				{
					if (e.from == v.exportLog.from &&
						e.to == v.exportLog.to &&
						e.itemType == v.exportLog.itemType)
					{
						e.numItemPerDay -= v.exportLog.numItemPerDay;
						break;
					}
				}
				exports.remove_if([](const Export& e) { return e.numItemPerDay == 0; });
				v.chain.clear();

				for (auto& u : urbans)
				{
					u.buyers.remove_if([&v](const Buyer& b) { return b.walletID == v.walletID; });
				}
				break;
			}
			else if(v.chain.update(&v)) break;	//errorの場合脱出
		}
	}
}