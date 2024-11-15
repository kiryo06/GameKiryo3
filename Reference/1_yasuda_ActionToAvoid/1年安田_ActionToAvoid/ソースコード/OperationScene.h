#pragma once
#include "Scene.h"
#include "Game.h"

/// <summary>
/// ��������V�[���N���X
/// </summary>
class OperationScene : public Scene
{
private:

	enum Dir
	{
		kNutral, //�ʏ��� 0
		kWalk,	 //������� 1
		kJump,	 //�W�����v��� 2
		kFall,   //�������� 3
		kHit,	//����������� 4
	};

	//��������̃n���h��
	int m_explationHandle;
	int m_frame;
	int m_animFrame;
	int m_buttonAnimFrame;



	int m_buttonHandle;

	int m_playerHandle01;
	int m_playerHandle02;

	//�v���C���[�̕\�����W
	float m_playerPosX;
	float m_playerPosY;

	//�v���C���[�̈ړ���
	float m_moveX;
	float m_moveY;

	bool m_isJump;
	bool m_isLeft;
	bool m_isRight;
	bool m_isAnimJump;

	Dir m_dir;
	bool m_isAnimTurn;

	int m_animCount;
	int m_jumpCount;

	//BGM�n���h��
	int m_bgmHandle;
	//SE�n���h��
	int m_seHandle001; //�W�����v��
	int m_seHandle002; //�L�����Z����


	//�X�V�����o�֐�
	void (OperationScene::* m_updateFunc)(Input& input);
	//�`�惁���o�֐��|�C���^
	using DrawFunc_t = void(OperationScene::*)();
	DrawFunc_t m_drawFunc;

	//�X�V�֐�
	void FadeInUpdate(Input&); //�t�F�[�h�C�����
	void NormalUpdate(Input&); //�ʏ���
	void FadeOutUpdate(Input&); //�t�F�[�h�A�E�g���

	//�`��֐�
	void FadeDraw();//�t�F�[�h���`��
	void NormalDraw();//��t�F�[�h�`��

public:
	OperationScene(SceneManager& manager);
	virtual ~OperationScene();

	void Init();
	void Update(Input& input);
	void Draw();


};

