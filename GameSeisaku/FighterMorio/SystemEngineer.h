#pragma once
class SystemEngineer
{
public:
	SystemEngineer();
	~SystemEngineer();
	/// <summary>
	/// ����������
	/// </summary>
	void Init();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
	/// <summary>
	/// �`��ݒ菈��
	/// </summary>
	void DrawSetUp();
	/// <summary>
	/// �X�R�A��ݒ�
	/// </summary>
	/// <param name="score">�ݒ肷��X�R�A</param>
	/// <returns>�ݒ肳�ꂽ�X�R�A</returns>
	void SetScore(bool score){ IsScore = score; }
	/// <summary>
	/// �X�R�A���擾
	/// </summary>
	/// <returns>���݂̃X�R�A</returns>
	int GetScore() const { return m_Score; }
	/// <summary>
	/// �^�C�}�[���擾
	/// </summary>
	/// <returns>���݂̃^�C�}�[�l</returns>
	int GetTimer() const { return m_Timer; }
	void SetBGM(bool bgm) { m_Bgm = bgm; }
	void SetStop(bool isStop) { m_IsStop = isStop; }
private:
	bool IsScore;					// �X�R�A�t���O
	int m_Score;					// �X�R�A
	int m_Timer;					// �^�C�}�[	
	int m_FrameCounter;				// �J�E���^
	int m_fontHandle;				// �t�H���g�̏��
	int dsad;
	bool m_Bgm;
	bool m_IsStop;
};

