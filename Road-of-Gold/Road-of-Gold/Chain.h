#pragma once

struct Vehicle;

enum struct Code
{
	None,
	Move,	//引数のIDの都市に移動
	Jump,	//引数の番地にジャンプ
	Wait,	//一日休止
	Buy,
	Sell,
	ERR,	//異常な値
};

struct Ring
{
	size_t	adress;
	Code	code;
	int		value;

	Ring(size_t	_adress, Code _code, int _value)
		: adress(_adress)
		, code(_code)
		, value(_value)
	{}
	String	valueText() const;
	String	codeText() const;
	void	set(Code _code, int _value);
};

struct Chain
{
	Array<Ring>	rings;
	size_t	readerPos;
	bool	isError;

	Chain() : readerPos(0), isError(false) {}
	size_t	size() const { return rings.size(); }
	bool	update(Vehicle* _v);
	void	clear();
	Chain&	operator =(const Chain& _chain);
};