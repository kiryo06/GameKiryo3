#pragma once
#include "Scene.h"
#include "Game.h"



/// <summary>
/// �^�C�g���V�[���N���X
/// </summary>
class TitleScene : public Scene
{
public:
	TitleScene(SceneManager& manager);
	virtual ~TitleScene();

	void Init();
	void Update(Input& input);
	void Draw();

	void BackScroll(const int areaX, const int handle, const int width, const int height);

private:
	//�J�[�\���I��
	enum Select
	{
		Start,		//�X�^�[�g
		Explation,	//����
		End,	//�I��
	};

	enum Dir
	{
		kNutralRight, //�ʏ��� 0
		kNutralLeft, //�ʏ��� 1
		kWalkRight,	 //�E������� 2
		kWalkLeft,	 //��������� 3
	};

	//�I���{�^��
	int m_nowButton;

	//�O���t�B�b�N�n���h��
	int m_TitleLogHandle;
	int m_bgHandle;
	int m_playerHandle;

	//�Z���N�g���
	int m_startHandle01;
	int m_explationHandle01;
	int m_optionHandle01;
	int m_endHandle01;

	//�Z���N�g����Ă��鎞�̃n���h��
	int m_startHandle02;
	int m_explationHandle02;
	int m_optionHandle02;
	int m_endHandle02;

	//�{�^���̃n���h��
	int m_decisionHandle;
	int m_buttonHandle;

	//BGM�n���h��
	int m_bgmHandle;
	//SE�n���h��
	int m_seHandle001; //���艹
	int m_seHandle002; //�I����
	int m_seHandle003; //�L�����Z����

	//�t���[��
	int m_frame = 0;
	int m_animFrame = 0;
	int m_buttonAnimFrame = 0;

	//�\���ʒu
	float m_posX = Game::kScreenWidth * 0.25;
	float m_posY = 100.0f;

	float m_playerPosX = 0;
	float m_playerPosY = 690;

	bool m_isAction = false;

	bool m_isStartFade = false;
	bool m_isFade = false;
	bool m_isHalfFade = false;

	//����
	float m_moveX = 0.0f;
	float m_moveY = 0.0f;

	Dir m_dir = kWalkRight;

	//�w�i��X���W
	int m_areaX;

	//�X�V�����o�֐�
	void (TitleScene::* m_updateFunc)(Input& input);
	//�`�惁���o�֐��|�C���^
	using DrawFunc_t = void(TitleScene::*)();
	DrawFunc_t m_drawFunc;

	//�X�V�֐�
	void FadeInUpdate(Input&); //�t�F�[�h�C�����
	void NormalUpdate(Input&); //�ʏ���
	void FadeOutUpdate(Input&); //�t�F�[�h�A�E�g���
	void FadeOutUpdateStart(Input&);//�X�^�[�g���������ꍇ�̃t�F�[�h�A�E�g���
	void NoFadeOutUpdate(Input&);//�t�F�[�h�A�E�g�����Ȃ��ꍇ�̊֐�

	//�`��֐�
	void FadeDraw();//�t�F�[�h���`��
	void NormalDraw();//��t�F�[�h�`��

};

