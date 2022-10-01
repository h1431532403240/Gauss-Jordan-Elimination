#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
void change(int m1, int n, int i, double** arr) { // 交換前導為0的列
	int j;
	double tmp;
	for (j = 0; j < n; j++) {
		tmp = arr[m1][j];
		arr[m1][j] = arr[i][j];
		arr[i][j] = tmp;
	}
}
void leading(int m, int n, int m1, int n1, double** arr) { // 設定前導壹、前導壹的上下列為0
	int i, j;
	double tmp;
	if (arr[m1][n1] != 1) {
		tmp = arr[m1][n1];
		for (i = 0; i < n; i++) {
			arr[m1][i] = arr[m1][i] / tmp;
		}
	}
	for (i = 0; i < m; i++) {
		if (i == m1) {
			continue;
		}
		tmp = -1 * arr[i][n1];
		for (j = 0; j < n; j++) {
			arr[i][j] = arr[i][j] + (tmp * arr[m1][j]);
		}
	}
}
void gauss_jordan(int m, int n, int m1, int n1, int reverse, double** arr) { // 判斷要交換或是運算
	int i, times_m = 0, judge = 0;
	for (i = m1; i < m; i++) {
		if (arr[i][n1] != 0) {
			judge = i;
			break;
		}
		else {
			times_m++;
		}
	}
	if (times_m == reverse) {
		n1++;
		return gauss_jordan(m, n, m1, n1, reverse, arr);
	}
	else {
		if (m1 != judge) {
			change(m1, n, judge,arr);
		}
	}
	leading(m, n, m1, n1, arr);
}
int main() {
	int m, n; // 列 行
	int m1, n1 = 0; // 運算時儲存的列 行
	int reverse; // 反向運算 列
	int i, j; // 迴圈用
	cout << "請輸入要幾列：";
	cin >> m;
	cout << "請輸入要幾行：";
	cin >> n;
	double** arr; // 設定動態二維陣列
	arr = new double* [m];
	for (i = 0; i < m; i++) {
		arr[i] = new double[n];
	}
	for (i = 0; i < m; i++) { // 輸入矩陣
		for (j = 0; j < n; j++) {
			cout << "請輸入第" << i + 1 << "列第" << j + 1 << "行的內容：";
			cin >> arr[i][j];
		}
	}
	for (i = 0; i < m; i++) { // 輸出矩陣
		for (j = 0; j < n; j++) {
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}
	reverse = m;
	for (m1 = 0; m1 < m; m1++, n1++) {
		gauss_jordan(m, n, m1, n1, reverse, arr);
		reverse--;
	}
	for (i = 0; i < m; i++) { // 輸出矩陣
		for (j = 0; j < n; j++) {
			if (arr[i][j] == -0)
				arr[i][j] = fabs(arr[i][j]);
			cout << fixed << setprecision(3) << arr[i][j] << "\t";
		}
		cout << endl;
	}
	for (int i = 0; i < m; i++) {
		delete[] arr[i];
	}
	delete[] arr;
	return 0;
}
