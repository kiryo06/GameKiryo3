#pragma once
class Uti
{
public:
	Uti();
	~Uti();

	void Init();
	void Update();

	int GetLight() const { return m_light; }
	int GetBGM() const { return m_BGM; }
	int GetSE() const { return m_SE; }

	void SetUti(int BGM, int SE, int light);

private:
	// int：設定画面でいじる数値　float：intに応じて、実際にBGM等の数値をいじる倍率
	
	// 光量
	int m_lightSet;
	int m_light;
	// BGM音量
	int m_BGMSet;
	int m_BGM;
	// SE音量
	int m_SESet;
	int m_SE;

};

