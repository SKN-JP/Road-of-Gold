#pragma once

#include"Casket.h"

struct Wallet;

struct Buyer
{
	Casket	casket;
	int		walletID;
	int		target;		//�ڕW�w����
	int		progress;	//�i�s�x
	int		period;		//�^�p����
	int		price;		//�w�����E���i

	Buyer(int _walletID, int _itemType, int _period, int _target);
	Wallet&	wallet() const;
};