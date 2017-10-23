#include "sort.h"

int main()
{
	int a1[] = {4,0,2,3,1};
	vector<int> arr1(a1,a1+sizeof(a1)/sizeof(int));
	insertSort(arr1);

	int a2[] = {49,38,65,97,76,13,27,49,55,4};
	vector<int> arr2(a2,a2+sizeof(a2)/sizeof(int));
	shellSort(arr2);

	int a3[] = {5,2,7,4,6,3,1};
	vector<int> arr3(a3,a3+sizeof(a3)/sizeof(int));
	bubbleSort(arr3);

	int a4[] = {6,3,8,2,5,9,4,5,1,7};
	vector<int> arr4(a4,a4+sizeof(a4)/sizeof(int));
	quickSort2(arr4,0,sizeof(a4)/sizeof(int)-1);

	int a5[] = {6,3,8,2,5,9,4,5,1,7};
	vector<int> arr5(a5,a5+sizeof(a5)/sizeof(int));
	selectSort(arr5);

	int a6[] = {49,38,65,97,76,13,27};
	vector<int> arr6(a6,a6+sizeof(a6)/sizeof(int));
	mergeSort2(arr6,0,sizeof(a6)/sizeof(int)-1);

	return 0;
}