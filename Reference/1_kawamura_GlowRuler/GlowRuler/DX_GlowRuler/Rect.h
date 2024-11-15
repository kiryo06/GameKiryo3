#pragma once
#include "Vec2.h"
class Rect
{
public:
	float m_left;	// 左のX座標 (左上)
	float m_top;	// 上のY座標 (左上)
	float m_right;	// 右のY座標 (右下)
	float m_bottom;	// 下のY座標 (右下)
	Rect();
	virtual ~Rect();

	void zero() { m_left = 0.0f; m_top = 0.0f; m_right = 0.0f; m_bottom = 0.0f; }

	// 描画
	void Draw(unsigned int color, bool isFill) const;


	/// 左上座標と幅, 高さを保存
	void SetLT(float left, float top, float width, float height);


	/// 中心座標と幅, 高さを保存
	void SetCenter(float x, float y, float width, float height);


	// 必要な情報を取得する
	float GetWidth() const;		// 矩形の幅
	float GetHeight() const;	// 矩形の高さ
	Vec2 GetCenter() const;		// 矩形の中心座標


	/// 矩形同士の当たり判定
	bool IsCollsion(const Rect& target);

	int IsPointInRect(const Vec2& point);

private:
	
};

