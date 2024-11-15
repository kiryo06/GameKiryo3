#pragma once
#include "Scene.h"
#include "Vec2.h"
#include <vector>
#include <memory>

class Player;
class EnemyBase;
class ItemBase;
class Map;
class Goal;

/// <summary>
/// �Q�[���v���C�V�[���N���X
/// </summary>
class GamePlayingScene : public Scene
{
private:
	int m_handle;
	int m_playerHandle;
	int m_enemyRunHandle;
	int m_enemyJumpHandle;
	int m_enemyJumpRunHandle;
	int m_map01Handle;
	int m_map02Handle;
	int m_itemHandleHp;
	int m_itemHandleBigHp;
	int m_goalHandle;
	int m_hpHandle;
	int m_tutorial001Handle;
	int m_tutorial002Handle;
	int m_tutorial003Handle;

	//BGM�n���h��
	int m_bgmHandle;

	//SE�n���h��
	int m_seHandle001; //�_���[�W��
	int m_seHandle002; //�_���[�W��(���ɗ��������̉�)
	int m_seHandle003; //�A�C�e����
	int m_seHandle004; //�S�[����
	int m_seHandle005; //�R�ɗ��������̉�

	int m_frame = 0;//�t�F�[�h����^�C�~���O�̃t���[��
	int m_damageFrame = 0;//�_���[�W���󂯂��ۂ̖��G���Ԃ̊Ԋu�t���[��

	bool m_isPlayerHit = false;
	bool m_isItemHit = false;
	bool m_isGoalHit = false;
	

	bool m_isGameOverFade = false;
	bool m_isGoalFade = false;

	//�v���C���[��HP
	int m_hp = 3;

	//�w�i��X���W
	int m_areaX;
	

	//�A�C�e����Y���W
	float m_animationHeight;

	//�A�C�e���̓����蔻����Ȃ����t���O
	bool m_isExist;
	//�v���C���[�̓����蔻����Ȃ����t���O
	bool m_isDamage;

	Vec2 m_shakeVec = {};//��ʗh��̈ړ��x�N�g��
	int m_shakeFrame = 0;//��ʗh��̎���
	float m_amp = 10.0f;//��ʗh��̐U�ꕝ
	int RT_;//��ʂ̏󋵂��L�^

	//�v���C���[�̃������m��
	std::shared_ptr<Player> pPlayer;
	//�G�̃������m��
	std::vector<EnemyBase*> pEnemy;
	//�}�b�v�̃������m��
	std::shared_ptr<Map> pMap;
	//�S�[���̃������m��
	std::shared_ptr<Goal> pGoal;
	//�A�C�e���̃������m��
	std::vector<ItemBase*> pItem;

	//�X�V�����o�֐�
	void (GamePlayingScene::* updateFunc_)(Input& input);
	//�`�惁���o�֐��|�C���^
	using DrawFunc_t = void(GamePlayingScene::*)();
	DrawFunc_t drawFunc_;

	//�X�V�֐�
	void FadeInUpdate(Input&); //�t�F�[�h�C�����
	void NormalUpdate(Input&); //�ʏ���
	void FadeOutUpdateGameOver(Input&); //�t�F�[�h�A�E�g���
	void FadeOutUpdateGameClear(Input&); //�t�F�[�h�A�E�g���

	//�`��֐�
	void FadeDraw();//�t�F�[�h���`��
	void NormalDraw();//��t�F�[�h�`��

	void CreateEnemyRun(float x, float y); //����G�𐶐�����֐�
	void CreateEnemyJump(float x, float y); //�W�����v����G�𐶐�����֐�
	void CreateEnemyJumpRun(float x , float y);//�����ăW�����v����G�𐶐�����֐�

	void CreateItemHp(float x, float y); //HP���P�񕜂��Ă����A�C�e���̐���
	void CreateItemBigHp(float x, float y);//HP���R�񕜂��Ă����A�C�e���̐���

	void BackScroll(const int areaX, const int handle, const int width, const int height);//�X�N���[������`��

public:
	GamePlayingScene(SceneManager& manager);//�R���X�g���N�^
	~GamePlayingScene();//�f�X�g���N�^

	void Init();//������
	void Update(Input& input);//�A�b�v�f�[�g����
	void Draw();//�`�揈��

	int GetScrollX();//X�̃X�N���[��
	int GetScrollY();//Y�̃X�N���[��
};

