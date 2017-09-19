#pragma once

struct Wallet;
struct CitizenData;

struct Citizen
{
	int		citizenType;
	int		walletID;
	int		targetRevenue;	//�ڕW����グ
	double	jobProgress;
	Array<int>	incomeLog;
	double	personality;
	double	jobEfficiency;
	int		averageIncome;

	Citizen(int _citizenType);
	CitizenData&	data() const;
	Wallet&	wallet() const;
};