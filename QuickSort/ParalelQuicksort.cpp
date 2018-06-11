#include <iostream>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <algorithm>
#include <vector>
#include <thread>
using namespace std;
int threadsMax = 0; //макс число потоків
int threadsNow = 0;    //поточне число потоків
void quick(vector<int> &arr, int l, int r)
{
	if (l >= r) return;
	int as = arr[(l + r) >> 1];
	int i = l, j = r;
	do
	{
		while (arr[i] < as) i++;
		while (as < arr[j]) j--;
		if (i <= j)
		{
			swap(arr[i], arr[j]);
			i++; j--;
		}
	} while (i <= j);
	if (threadsNow < threadsMax) {
		thread t1(quick, std::ref(arr), l, j);
		thread t2(quick, std::ref(arr), i, r);
		t1.join();
		t2.join();
		threadsNow += 2;
	}
	else {
		quick(arr, l, j);
		quick(arr, i, r);
	}
}
void QuickSort(vector<int> &arr)
{
	quick(arr, 0, arr.size() - 1);
}
int main() {
	srand((int)time(NULL));
	vector<int> arr, a;
	unsigned int t_start, t_end;
	int n;
	cout << "Enter quantity of elements: ";
	cin >> n;
    for (int i = 0; i < n; i++) arr.push_back(rand() % 1000);
	cout << "Before sorting: \n";
	for (int i = 0; i < n; i++) cout << arr[i] << " "; cout << endl;
	for (int k = 0; k < 4; k++)
	{
		threadsMax = pow(2.0, k);
		threadsNow = 1;
		cout << "\nWorking with " << threadsMax << " thread(s)." << endl;
	
	a = arr;
	t_start = clock();
	QuickSort(a);
	t_end = clock();
	cout << "QuickSort time:\t" << t_end - t_start << endl;
	}
	cout << "\nSorted array:\n";
	for (int i = 0; i < n; i++) cout << a[i] << " ";cout << endl;
	
	system("pause");
	return 0;
}