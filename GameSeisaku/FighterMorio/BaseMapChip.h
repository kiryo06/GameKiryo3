#pragma once
class BaseMapChip
{
public:
	BaseMapChip();
	virtual ~BaseMapChip();
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
protected:
};

