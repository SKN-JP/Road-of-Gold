#pragma once

enum struct Owner
{
	Vehicle,
	Citizen,
	Urban,
	Group,
}; 

struct Wallet
{
	int		money;

	//Market関連
	int		price;	//Marketから振り込み時に価格を書き込み
	int		expenses;	//支出を記録
	int		income;		//収入を記録
	Owner	owner;

	Wallet();
	void	sendTo(Wallet* _wallet, int	_money);	//送金
	void	add(int _money);
	void	pull(int _money);
	int		id() const;
};

extern Array<Wallet>	wallets;

int		getNewWalletID();