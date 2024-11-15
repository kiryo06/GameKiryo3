#pragma once
class Input;
class SceneManager;
/// <summary>
/// シーン基底クラス
/// 色んなシーンのもとになるクラス
/// </summary>
class Scene
{
protected:
	SceneManager& manager_;
public:
	/// <summary>
	/// 生成時にSceneManagerの参照を受け取っておく
	/// </summary>
	/// <param name="manager">SceneManagerの参照</param>
	Scene(SceneManager& manager);

	/// <summary>
	/// シーンの更新
	/// </summary>
	/// <param name="input">入力オブジェクト</param>
	virtual void Update(Input& input) = 0;

	/// <summary>
	/// シーンの描画
	/// </summary>
	virtual void Draw() = 0;
};

