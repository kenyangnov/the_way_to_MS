#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

struct parenthese {
	int lp;
	int rp;
};
string ToSr(const string &s) {
	string str = s;
	int len = s.length();
	//��SL��SR�ֽ�
	parenthese* cur = new parenthese[len];
	if (str[0] == '(') {
		cur[0].lp = 1;
		cur[0].rp = 0;
	}
	else {
		cur[0].lp = 0;
		cur[0].rp = 1;
	}
	for (int i = 1; i < len; i++) {
		if (str[i] == '(') {
			cur[i].lp = cur[i - 1].lp + 1;
			cur[i].rp = cur[i - 1].rp;
		}
		else {
			cur[i].rp = cur[i - 1].rp + 1;
			cur[i].lp = cur[i - 1].lp;
		}
	}
	int sum_lp = cur[len - 1].lp;
	int sum_rp = cur[len - 1].rp;
	int edge = 0;
	bool flag = false; //��־�Ƿ���Ҫ��ת
	for (int i = 0; i < len; i++) {
		edge = i;
		if (cur[i].lp<cur[i].rp && (sum_lp - cur[i].lp)>(sum_rp - cur[i].rp)) {
			flag = true;	//��Ҫ��ת
			break;
		}
	}
	for (int i = 0; i < len; i++) {
		cout <<i<<"---"<< cur[i].lp << "---" << cur[i].rp << endl;
	}
	cout << edge << endl;
	delete[] cur;
	if (!flag) { //����SL�����跭ת��ֱ�ӷ���str
		return str;
	}
	// �������SL����SL�Ȼ����ٷ�ת
	int i = 0, j = edge + 1;
	for (i; i < j; i++) {
		if (str[i] == '(') {
			str[i] = ')';
		}
		else {
			str[i] = '(';
		}
	}
	while (i < j) {
		swap(str[i++], str[j--]);
	}
	// ���ش�������ַ���
	return str;
}

int GetMinP(const string &s) {
	int cnt = 0;
	// ջ��˼��
	for (unsigned int i = 0; i < s.length(); i++) {
		if (s[i] == '(') {
			cnt++;
		}
		else {
			cnt--;
		}
	}
	return cnt;
}

int f(int ** &dp, int i, int j, int *limit) {
	if (i == 0||j == 0) {
		return 1;
	}
	int sum = 0;
	for (int k = 0; k <= limit[i-1]; k++) {
		sum += f(dp, i - 1, k, limit);
	}
	dp[i][j] = sum;
	return dp[i][j];
}

int GetT(const string &s) {
	//���
	int cnt = 1; //��һ�������ż�������һ��һ���������ţ�
	int *limit = new int[s.length()];
	int limit_num = 0;
	for (unsigned int i = 1; i < s.length(); i++) {	//������ǰ���Բ���������
		if (s[i] == '(') {
			limit[limit_num] = cnt;
			cnt++;
			limit_num++;
		}
		else { //s[i] ==')'
			cnt--;
		}
	}
	limit[limit_num] = cnt; //���һ��λ�ÿ��Բ���������
	/*
	for (int i = 0; i < limit_num + 1; i++) {
		cout << i << "--" << limit[i] << endl;
	}
	*/
	//��̬�滮
	//f[i][j]��ʾ��ǰi��λ��һ��������j���������ж����ַ���
	//f[i][j] = f[i-1][0] + f[i-1][1] + ... + f[i-1][limit[i-1]]
	
	int **dp;
	dp = new int*[limit_num + 1];
	for (int i = 0; i < limit_num + 1; i++) {
		dp[i] = new int[cnt + 1];
	}
	int result = f(dp, limit_num, cnt, limit);
	for (int i = 0; i < limit_num + 1; i++) {
		for (int j = 0; j < cnt + 1; j++) {
			cout << dp[i][j] << "--";
		}
		cout << "*" << endl;
	}
	for (int i = 0; i < limit_num; i++) {
		delete[] dp[i];
	}
	delete[] dp;
	delete[] limit;
	return result;
}
int main()
{
	string s;
	cin >> s;
	string str = ToSr(s);	//���ַ���ת��ΪSR��
	cout << str << endl;
	int min = GetMinP(str); //�����������ŵ���Сֵ
	cout << min << endl;
	int t = GetT(str); //����������ŵĲ�ͬ�����
	cout << t << endl;
	system("pause");
}