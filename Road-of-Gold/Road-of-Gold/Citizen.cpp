#include"Citizen.h"
#include"Wallet.h"
#include"CitizenData.h"

Citizen::Citizen(int _citizenType)
	: citizenType(_citizenType)
	, walletID(getNewWalletID())
	, jobProgress(0)
	, personality(Random(0.1, 0.9))
	, jobEfficiency(Random(0.25, 1.0))
	, averageIncome(0)
{
	incomeLog.resize(5);
	wallet().price = 1000;
	wallet().owner = Owner::Citizen;
}
CitizenData&	Citizen::data() const { return citizenData.at(citizenType); }
Wallet&	Citizen::wallet() const { return wallets[walletID]; }