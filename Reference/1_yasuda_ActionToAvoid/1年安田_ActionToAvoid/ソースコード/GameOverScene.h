#pragma once
#include "Scene.h"
#include "Game.h"
#include "Pad.h"



/// <summary>
/// �Q�[���I�[�o�[�V�[���N���X
/// </summary>
class GameOverScene :
    public Scene
{
private:
	//�J�[�\���I��
	enum Select
	{
		Retry,	//�h���̃��g���C
		Title, //�^�C�g����ʂ�
	};

	enum Dir
	{
		kNutralRight, //�ʏ��� 0
		kNutralLeft, //�ʏ��� 1
		kWalkRight,	 //�E������� 2
		kWalkLeft,	 //��������� 3
	};

	int m_handle;
	int m_playerHandle;

	int m_pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	

	//�L�����̕\�����W
	float m_playerPosX = Game::kScreenWidth * 0.5;
	float m_playerPosY = 420;

	//����
	float m_moveX = 0.0f;
	float m_moveY = 0.0f;

	int m_frame = 0;
	int m_animFrame = 0;

	//�I���{�^��
	int nowButton = Retry;
	
	//�Z���N�g���
	int m_retryHandle01;
	int m_titleHandle01;

	//�Z���N�g����Ă���n���h��
	int m_retryHandle02;
	int m_titleHandle02;


	//BGM�n���h��
	int m_bgmHandle;
	//SE�n���h��
	int m_seHandle001; //���艹
	int m_seHandle002; //�I����


	Dir m_dir = kNutralRight;
	bool m_isTurn = false;
	bool m_isActionR = false;
	bool m_isActionL = false;


	//�X�V�����o�֐�
	void (GameOverScene::* updateFunc_)(Input& input);
	//�`�惁���o�֐��|�C���^
	using DrawFunc_t = void(GameOverScene::*)();
	DrawFunc_t drawFunc_;

	//�X�V�֐�
	void FadeInUpdate(Input&); //�t�F�[�h�C�����
	void NormalUpdate(Input&); //�ʏ���
	void FadeOutUpdate(Input&); //�t�F�[�h�A�E�g���

	//�`��֐�
	void FadeDraw();//�t�F�[�h���`��
	void NormalDraw();//��t�F�[�h�`��

public:
	GameOverScene(SceneManager& manager);
	~GameOverScene();
	void Update(Input& input);
	void Draw();
};

