//用荷兰国旗方法快排
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;
void quickSort(vector<int>& arr, int left, int right);
void sort_arr(vector<int>& arr) {
	int left = 0;
	int right = arr.size() - 1;
	quickSort(arr,left,right);
}
//arr=[2,5,6,4,3,1]
void quickSort(vector<int>& arr, int left, int right) {
	int less = left - 1;
	int more = right + 1;
	int mid = (left + right) / 2;
	int cur = left;
	int flag = arr[right];
	while (cur < more) {
		if (arr[cur] < flag) {
			swap(arr[++less], arr[cur++]);
		}
		else if (arr[cur] > flag) {
			swap(arr[cur], arr[--more]);
		}
		else
			cur++;
	}
	if(left<less)
		quickSort(arr, left, less);
	if(more<right)
		quickSort(arr, more, right);
}

/********************test test**************************/
vector<int> genRandomArray(int maxSize, int maxValue) {
	int size = rand() % maxSize;
	vector<int> arr(size);
	for (int i = 0; i < size; ++i)
		arr[i] = rand() % maxValue;
	return arr;
}
//vector<int> copyArray(vector<int>& arr1,vector<int>& arr2) {
//	for (int i = 0; i < arr2.size(); ++i)
//		arr1[i++] = arr2[i++];
//}
bool isEqual(vector<int>& arr1,vector<int>& arr2) {
	if ((arr1.size() == 0 && arr2.size() != 0) || (arr1.size() != 0 && arr2.size() == 0))
		return false;
	if (arr1.size() == 0 && arr1.size() == 0)
		return true;
	if (arr1.size() != arr2.size())
		return false;
	for (int i = 0; i < arr1.size(); ++i)//两者都不为空且长度相等
		if (arr1[i] != arr2[i])
			return false;
	return true;
}
void printArray(vector<int>& arr) {
	for (int i = 0; i < arr.size(); ++i)
		cout << arr[i]<<' ';
	cout << endl;
}
int main() {
	srand((int)time(0));//产生随机数种子
	int testTime = 500000;
	int maxSize = 100;
	int maxValue = 100;
	bool succeed = true;
	for (int i = 0; i < testTime; ++i) {
		vector<int> arr1 = genRandomArray(maxSize, maxValue);
		vector<int> arr2(arr1);
		if(arr1.size()!=0)
			sort_arr(arr1);
		sort(arr2.begin(), arr2.end());
		if (!isEqual(arr1, arr2)) {
			succeed = false;
			break;
		}
	}
	cout << (succeed ? "Nice!~" : "Fucking fuced!");
	vector<int> arr = genRandomArray(maxSize, maxValue);
	printArray(arr);
	sort_arr(arr);
	printArray(arr);
}
/********************test test**************************/

//int main()
//{
//	vector<int> arr{ 3,2,4,3,2,5,2,6 };
//	sort_arr(arr);
//	for (int i = 0; i < arr.size(); ++i)
//		cout << arr[i] << ' ';
//	cout << endl;
//	//vector<int> arr1{ 3,2,4,3,2,5,2,6 };
//	//sort(arr1.begin(), arr1.end());
//	//for (int i = 0; i < arr1.size(); ++i)
//	//	cout << arr1[i] << ' ';
//	return 0;
//}
//

