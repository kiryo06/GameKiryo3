#pragma once

class Input;
class SceneController;

/// <summary>
///  各シーンの基底クラス
/// </summary>
class Scene
{
protected:
	// 各状態が切り替えるために
	SceneController& controller_;

public:
	Scene(SceneController& cont);

	/// <summary>
	/// 内部変数の更新
	/// </summary>
	/// <param name="input">入力状態</param>
	virtual void Update(Input& input) = 0;

	/// <summary>
	///  描画
	/// </summary>
	virtual void Draw() = 0;
};

