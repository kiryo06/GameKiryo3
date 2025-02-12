#pragma once
#include "Scene.h"
#include <string>
#include <vector>
#include <map>

/// <summary>
/// ポーズ中シーンクラス
/// </summary>
class PauseScene : public Scene
{
private:
	using UpdateFunc_t = void (PauseScene::*)(Input& input);
	using DrawFunc_t = void (PauseScene::*)();

	UpdateFunc_t update_;
	DrawFunc_t draw_;

	int frame_;
	int currentMenuIndex_;

	// 出現状態
	void AppearUpdate(Input& input);
	// ノーマル状態
	void NomalUpdate(Input& input);
	// 消滅中状態
	void DisappearUpdate(Input& input);

	// 通常描画
	void NomalDraw();
	// 途中描画
	void ShiftingDraw();

	/// <summary>
	/// ゲームに戻る
	/// </summary>
	void BackGame(Input&);
	/// <summary>
	/// キーコンフィグを立ち上げる
	/// </summary>
	void GoKeyConfig(Input&);
	/// <summary>
	/// その他設定
	/// </summary>
	void EtcConfig(Input&);
	/// <summary>
	/// タイトルに戻る
	/// </summary>
	void BackTitle(Input&);
	using MenuFunc_t = void (PauseScene::*)(Input&);
	// メニューを並べるためのvector
	std::vector<std::string> menuTexts_;
	// メニューと対応する関数をセットにしたテーブル
	std::map<std::string, MenuFunc_t> functionTable_;
	void DrawMenu();

public:
	PauseScene(SceneController& cont);
	/// <summary>
	/// 派生クラスで実装を実装
	/// </summary>
	virtual void Update(Input& input) override;

	virtual void Draw() override;
};

