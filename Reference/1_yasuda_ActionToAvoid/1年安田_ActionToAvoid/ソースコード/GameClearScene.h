#pragma once
#include "Scene.h"
#include "Game.h"
/// <summary>
/// �Q�[���I�[�o�[�V�[���N���X
/// </summary>
class GameClearScene :
	public Scene
{
private:
	//�J�[�\���I��
	enum Select
	{
		Title,	//�h���̃��g���C
	};

	enum Dir
	{
		kNutralRight, //�ʏ��� 0
		kNutralLeft, //�ʏ��� 1
		kWalkRight,	 //�E������� 2
		kWalkLeft,	 //��������� 3
	};

	//�O���t�B�b�N�n���h��
	int m_handle;
	int m_playerHandle;
	int m_bgHandle;
	int m_goalHandle;

	//�t���[��
	int m_frame;
	int m_animFrame;
	int m_clearFrame;
	int m_goalFrame;

		//�L�����̕\�����W
	float m_playerPosX;
	float m_playerPosY;
	
	int m_goalPosX;
	int m_goalPosY;

	//����
	float m_moveX;
	float m_moveY;

	Dir m_dir;
	bool m_isTurn;
	bool m_isAction;
	bool m_isClear;

	int nowButton = Title;
	int m_pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);


	//�O���t�B�b�N�n���h��
	int m_titleHandle01;
	//BGM�n���h��
	int m_bgmHandle;
	//SE�n���h��
	int m_seHandle001; //���艹
	int m_seHandle002; //�I����

	//�X�V�����o�֐�
	void (GameClearScene::* updateFunc_)(Input& input);
	//�`�惁���o�֐��|�C���^
	using DrawFunc_t = void(GameClearScene::*)();
	DrawFunc_t drawFunc_;

	//�X�V�֐�
	void FadeInUpdate(Input&); //�t�F�[�h�C�����
	void NormalUpdate(Input&); //�ʏ���
	void FadeOutUpdate(Input&); //�t�F�[�h�A�E�g���

	//�`��֐�
	void FadeDraw();//�t�F�[�h���`��
	void NormalDraw();//��t�F�[�h�`��

public:
	GameClearScene(SceneManager& manager);
	~GameClearScene();
	void Update(Input& input);
	void Draw();
};

