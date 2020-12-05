#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

/*******************************************************************************
コードの作成者 : かいちょー
Project開始日  : 12/4
バージョン履歴 : 
12/5 ver 1.0.0 : リリースバージョン
12/5 ver 1.0.1 : 更新内容
・[add]勝利数が表示されるようになりました
・[add]勝率が表示されるようになりました
・[update]勝敗をResultsクラスに保持するようにしました
・[fix]Debug用に表示していたものを削除しました
12/5 ver 1.0.2 : 更新内容
・[fix]自動的に終了するバグを修正

*******************************************************************************/

//勝敗の種類
enum class eResultType {
	Draw,
	Lose,
	Win
};

//手の種類
enum class eHandType {
	Gu,
	Choki,
	Pa
};

class Results {
private:
	string resultText;	//勝敗を格納する変数
	string com_1Text;	//コンピュータ１の手の表示用変数
	string com_2Text;	//コンピュータ２の手の表示用変数
	eHandType com_1;	//コンピュータ１の手
	eHandType com_2;	//コンピュータ２の手
	eResultType result;	//コンピュータ１基準の勝敗
public:
	//コンストラクタ
	Results(eHandType _com_1, eHandType _com_2);
	//コンソールに表示するようの処理
	void View() { cout << "Computer01 hand : " << com_1Text <<
		" Computer02 hand : " << com_2Text << " result : " << resultText << endl; }
	//手の種類に対応するテキストを返す処理
	string SetHandText(eHandType _hand);
	//勝敗を取得する
	eResultType GetResult() { return result; }
};

int main() {
	const int NUM_OF_TIMES = 10000;		//処理を行う回数

	vector<Results*> results;			//じゃんけんの要素を所持してる配列変数

	eHandType com_1;	//コンピュータ１の手
	eHandType com_2;	//コンピュータ２の手

	int winCount = 0;		//勝利数
	float winRate = 0.0f;	//勝率

	//乱数にシード値を与える
	srand((unsigned)time(NULL));

	//1万回じゃんけんを行う
	for (int i = 0; i < NUM_OF_TIMES; i++) {
		//コンピュータ１の手を割り当てる
		com_1 = static_cast<eHandType>(rand() % 3);
		//コンピュータ２の手を割り当てる
		com_2 = static_cast<eHandType>(rand() % 3);

		//じゃんけんの要素を格納する
		results.push_back(new Results(com_1, com_2));

		//結果などを表示
		results[i]->View();
	}

	//勝利数を求める
	for (int i = 0; i < NUM_OF_TIMES; i++) {
		if (results[i]->GetResult() == eResultType::Win) {
			winCount++;
		}
	}

	//勝率を求める
	winRate = (static_cast<float>(winCount) / NUM_OF_TIMES) * 100;

	cout << "勝利数" << winCount << "回" << endl;
	cout << "勝率" << winRate << "%" << endl;


	//もう使わないのでdeleteする
	for (int i = 0; i < NUM_OF_TIMES; i++) {
		delete results[i];
	}

	//resultsの要素数もクリアする
	results.clear();

	cout << "終了する場合はキーを入力してください....";

	//入力待ち
	getchar();

	return 0;
}

Results::Results(eHandType _com_1, eHandType _com_2) {
	//コンピュータの手の情報を格納する
	com_1 = _com_1;
	com_2 = _com_2;

	//文字列を適用させる
	com_1Text = SetHandText(com_1);
	com_2Text = SetHandText(com_2);

	//結果を計算する
	result = static_cast<eResultType>(
		(static_cast<int>(com_1) - static_cast<int>(com_2) + 3) % 3);

	//結果を表示用のテキストに割り当てる
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

//手の種類に対応するテキストを返す処理
string Results::SetHandText(eHandType _hand) {
	//対応する文字列を返す
	switch (_hand) {
	case eHandType::Gu:
		return "グー　";
	case eHandType::Choki:
		return "チョキ";
	case eHandType::Pa:
		return "パー　";
	}

	return "Error";
}