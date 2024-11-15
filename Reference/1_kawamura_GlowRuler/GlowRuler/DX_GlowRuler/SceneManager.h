#pragma once

class TitleScene;
class GameScene;
class EndingScene;
class File;
class Uti;
class StageMakerScene;

class Sound;

class Handle;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void SceneMove();
	void Update();
	void Draw();

	bool End() const { return m_isEnd; }
private:
	// ハンドルデータ
	Handle* m_handleData;
	// セーブデータ
	File* m_dataFile;

	// タイトル
	TitleScene* m_pTitle;
	int m_gameMode;
	// ゲーム部分
	GameScene* m_pGame;
	int m_stageNum;
	bool m_isTransScene;
	// エンディング
	EndingScene* m_pEnding;

	// メーカー
	StageMakerScene* m_pMaker;

	// 全体共通の設定部分
	Uti* m_pSet;
	int m_lightPow;
	int m_BGMPow;
	int m_SEPow;

	// 結果タイム
	int m_time;
	// ゲーム終了フラグ
	bool m_isEnd;

	bool m_isMaker;

	int m_handleNum;
	int m_handleTimer;
};

