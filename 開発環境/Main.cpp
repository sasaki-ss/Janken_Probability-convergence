#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

/*******************************************************************************
�R�[�h�̍쐬�� : ��������[
Project�J�n��  : 12/4
�o�[�W�������� : 
12/5 ver 1.0.0 : �����[�X�o�[�W����
12/5 ver 1.0.1 : �X�V���e
�E[add]���������\�������悤�ɂȂ�܂���
�E[add]�������\�������悤�ɂȂ�܂���
�E[update]���s��Results�N���X�ɕێ�����悤�ɂ��܂���
�E[fix]Debug�p�ɕ\�����Ă������̂��폜���܂���
12/5 ver 1.0.2 : �X�V���e
�E[fix]�����I�ɏI������o�O���C��

*******************************************************************************/

//���s�̎��
enum class eResultType {
	Draw,
	Lose,
	Win
};

//��̎��
enum class eHandType {
	Gu,
	Choki,
	Pa
};

class Results {
private:
	string resultText;	//���s���i�[����ϐ�
	string com_1Text;	//�R���s���[�^�P�̎�̕\���p�ϐ�
	string com_2Text;	//�R���s���[�^�Q�̎�̕\���p�ϐ�
	eHandType com_1;	//�R���s���[�^�P�̎�
	eHandType com_2;	//�R���s���[�^�Q�̎�
	eResultType result;	//�R���s���[�^�P��̏��s
public:
	//�R���X�g���N�^
	Results(eHandType _com_1, eHandType _com_2);
	//�R���\�[���ɕ\������悤�̏���
	void View() { cout << "Computer01 hand : " << com_1Text <<
		" Computer02 hand : " << com_2Text << " result : " << resultText << endl; }
	//��̎�ނɑΉ�����e�L�X�g��Ԃ�����
	string SetHandText(eHandType _hand);
	//���s���擾����
	eResultType GetResult() { return result; }
};

int main() {
	const int NUM_OF_TIMES = 10000;		//�������s����

	vector<Results*> results;			//����񂯂�̗v�f���������Ă�z��ϐ�

	eHandType com_1;	//�R���s���[�^�P�̎�
	eHandType com_2;	//�R���s���[�^�Q�̎�

	int winCount = 0;		//������
	float winRate = 0.0f;	//����

	//�����ɃV�[�h�l��^����
	srand((unsigned)time(NULL));

	//1���񂶂�񂯂���s��
	for (int i = 0; i < NUM_OF_TIMES; i++) {
		//�R���s���[�^�P�̎�����蓖�Ă�
		com_1 = static_cast<eHandType>(rand() % 3);
		//�R���s���[�^�Q�̎�����蓖�Ă�
		com_2 = static_cast<eHandType>(rand() % 3);

		//����񂯂�̗v�f���i�[����
		results.push_back(new Results(com_1, com_2));

		//���ʂȂǂ�\��
		results[i]->View();
	}

	//�����������߂�
	for (int i = 0; i < NUM_OF_TIMES; i++) {
		if (results[i]->GetResult() == eResultType::Win) {
			winCount++;
		}
	}

	//���������߂�
	winRate = (static_cast<float>(winCount) / NUM_OF_TIMES) * 100;

	cout << "������" << winCount << "��" << endl;
	cout << "����" << winRate << "%" << endl;


	//�����g��Ȃ��̂�delete����
	for (int i = 0; i < NUM_OF_TIMES; i++) {
		delete results[i];
	}

	//results�̗v�f�����N���A����
	results.clear();

	cout << "�I������ꍇ�̓L�[����͂��Ă�������....";

	//���͑҂�
	getchar();

	return 0;
}

Results::Results(eHandType _com_1, eHandType _com_2) {
	//�R���s���[�^�̎�̏����i�[����
	com_1 = _com_1;
	com_2 = _com_2;

	//�������K�p������
	com_1Text = SetHandText(com_1);
	com_2Text = SetHandText(com_2);

	//���ʂ��v�Z����
	result = static_cast<eResultType>(
		(static_cast<int>(com_1) - static_cast<int>(com_2) + 3) % 3);

	//���ʂ�\���p�̃e�L�X�g�Ɋ��蓖�Ă�
	switch (result) {
	case eResultType::Draw:
		resultText = "Draw";
		break;
	case eResultType::Lose:
		resultText = "Lose";
		break;
	case eResultType::Win:
		resultText = "Win";
		break;
	default:
		resultText = "Error";
		break;
	}
}

//��̎�ނɑΉ�����e�L�X�g��Ԃ�����
string Results::SetHandText(eHandType _hand) {
	//�Ή����镶�����Ԃ�
	switch (_hand) {
	case eHandType::Gu:
		return "�O�[�@";
	case eHandType::Choki:
		return "�`���L";
	case eHandType::Pa:
		return "�p�[�@";
	}

	return "Error";
}