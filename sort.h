#include "Global.h"

//插入排序-直接插入排序
template<class T>
void insertSort(vector<T> &arr)
{
	int n = arr.size();
	if (n<2) return;
	int j = 0;
	for (int i=1;i<n;++i)
	{
		j = i-1;
		T t = arr[i];
		if (t<arr[j])
		{
			for (j=i-1;j>=0;--j)
			{
				if (arr[j]>t)
				{
					arr[j+1] = arr[j];
				}
				else
				{
					break;
				}
			}
			arr[j+1] = t;
		}
	}
}

//插入排序-希尔排序
template<class T>
void shellSort(vector<T> &arr)
{
	int n = arr.size();
	if (n<2) return;
	for (int step=n/2;step>=1;step/=2)
	{
		int j;
		for (int i=step;i<n;++i)
		{
			j=i-step;
			T t = arr[i];
			if (t<arr[j])
			{
				for (;j>=0;j-=step)
				{
					if (t<arr[j])
					{
						arr[j+step] = arr[j];
					}
					else break;
				}
				arr[j+step] = t;
			}
		}
	}
}

//交换排序—冒泡排序
template<class T>
void bubbleSort(vector<T> &arr)
{
	int n = arr.size();
	for (int i=0;i<n-1;++i)//趟数
	{
		bool flag = false;
		for (int j=0;j<n-i-1;++j)//每一趟排序
		{
			if (arr[j]>arr[j+1])//逆序
			{
				swap(arr[j],arr[j+1]);
				flag = true;
			}
		}
		if (!flag)
		{
			return;
		}
	}
}

//交换排序—快速排序

//partition划分操作：在待排序列arr[low...high]中任取一个元素pivot作为基准，把<=pivot的元素放在它的左边，>pivot的元素放在它的右边，则pivot
//放在它的最终位置arr[k]上，得到两个子表arr[low...k-1]和arr[k+1...high]，这就是一趟快速排序。而后分别递归地对这两个子表重复上述过程，直至每个部分内
//只有一个元素或为空。

//partition函数的返回值就是k值，它的实现有两种策略

//partition_1:选取待排序列的第一个元素作为基准并用一个局部pivot保存，这样这个位置就被腾出来作为交换使用，利用这个空位置交替的从待排序列的首尾向中间扫描；
template<class T>
int partition_1(vector<T> &arr,int low,int high)
{
	if (low>high) return -1;

	swap(arr[low],arr[low+rand()%(high-low+1)]);//任选一个元素与首元素交换，随机选取，降低最坏情况出现的概率（优化方法）

	T pivot = arr[low];//第一个元素作为基准
	while (low<high)
	{
		while (low<high&&arr[high]>=pivot) --high;//尾->中间 扫描,此时空位为low
		arr[low] = arr[high];//空位变为high

		while (low<high&&arr[low]<=pivot) ++low;//首->中间 扫描,此时空位为high
		arr[high] = arr[low];//空位变为low
	}
	arr[low] = pivot;//填好基准
	return low;
}

//partition_2:选取待排序列的最后一个元素作为基准，将比基准小的元素全部连续的放到左边，两个指针索引，一个为small初始为low-1，始终指向左边小数（比基准小）
//序列的最后一个；另一个为遍历指针i，依次遍历待排序列，将比基准小的数置换到small后面。
//最大优点：一次划分后，枢纽位置k左边的元素相对顺序不变
template<class T>
int partition_2(vector<T> &arr,int low,int high)
{
	int small = low-1,i=low;
	if (low>high) return -1;

	swap(arr[high],arr[low+rand()%(high-low+1)]);//任选一个元素与尾元素交换，随机选取，降低最坏情况出现的概率（优化方法）

	T pivot = arr[high];
	for (;i<high;++i)
	{
		if (arr[i]<pivot)
		{
			swap(arr[++small],arr[i]);
		}
	}
	swap(arr[++small],arr[high]);
	return small;
}

//递归实现
template<class T>
void quickSort(vector<T> &arr,int low,int high)
{
	if (low<high)//递归结束条件
	{
		int pivot_k = partition_2(arr,low,high);//划分操作，将arr[low...high]以基准元素划分成两个子表，被称为一趟快排
		quickSort(arr,low,pivot_k-1);
		quickSort(arr,pivot_k+1,high);
	}
}

//非递归实现
//其实就是手动利用栈来存储每次分块快排的起止点，栈非空时循环获取中轴入栈
struct point
{
	int low;
	int high;
	point(int l,int h):low(l),high(h){}
};
template<class T>
void quickSort2(vector<T> &arr,int low,int high)
{
	stack<point> stack_lh;
	stack_lh.push(point(low,high));
	while (!stack_lh.empty())
	{
		point p = stack_lh.top();
		stack_lh.pop();
		int pivot_k = partition_2(arr,p.low,p.high);
		if (pivot_k-1>p.low)//至少含两个元素
		{
			stack_lh.push(point(p.low,pivot_k-1));
		}
		if (p.high>pivot_k+1)//至少含两个元素
		{
			stack_lh.push(point(pivot_k+1,p.high));
		}
	}
}

//选择排序—简单选择排序
template<class T>
void selectSort(vector<T> &arr)
{
	int n = arr.size();
	for (int i=0;i<n-1;++i)
	{
		int min = i;
		for (int j=i+1;j<n;++j)
		{
			if (arr[min]>arr[j])
			{
				min = j;
			}
		}
		swap(arr[i],arr[min]);
	}
}

//归并排序—二路归并排序

//有序向量的二路归并
//对相邻的两个有序（arr[low...mid] 和 arr[mid+1...high]）序列进行归并

//归并1：需要开辟o(n)额外空间
template<class T>
void merge_1(vector<T> &arr,int low,int mid,int high)
{
	//开辟一个额外数组复制保存arr[low...mid]序列
	vector<T> leftArr(arr.begin()+low,arr.begin()+mid+1);
	//对leftArr和arr[mid+1...high]进行归并到arr[low...high]
	int leftSize = mid-low+1;
	int left_i = 0,right_i = mid+1;
	while (left_i<leftSize && right_i<=high)
	{
		if (leftArr[left_i]<=arr[right_i]) arr[low++] = leftArr[left_i++];
		else arr[low++] = arr[right_i++];
	}
	while (left_i<leftSize) arr[low++] = leftArr[left_i++];
	while(right_i<=high) arr[low++] = arr[right_i++];
}
//归并2：原地归并不需要开辟额外空间，但是时间复杂度就高啦
template<class T>
void reverse(vector<T> &arr,int start,int end)
{
	while (start<end)
	{
		swap(arr[start++],arr[end--]);
	}
}

template<class T>
void exchange(vector<T> &arr,int low,int mid,int high)
{
	if (low<=mid&&mid+1<=high)
	{
		reverse(arr,low,mid);
		reverse(arr,mid+1,high);
		reverse(arr,low,high);
	}
}

template<class T>
void merge_2(vector<T> &arr,int low,int mid,int high)
{
	int j = mid+1;
	while (low<j&&j<=high)
	{
		int step = 0;
		while (low<j&&arr[low]<=arr[j]) ++low;
		while (j<=high&&arr[j]<=arr[low])
		{
			++j;
			++step;
		}
		exchange(arr,low,mid,j-1);
		low += step-1;
		mid = j-1;
	}
}

//递归实现(自顶向下)
template<class T>
void mergeSort(vector<T> &arr,int low,int high)
{
	if (high-low<1) return; //递归结束条件， 单区间自然有序
	int mid = (low+high)/2;
	mergeSort(arr,low,mid);
	mergeSort(arr,mid+1,high);
	merge_2(arr,low,mid,high);//归并
}

//非递归实现(自底向上)
template<class T>
void mergeSort2(vector<T> &arr,int low,int high)
{
	int n = high-low+1;
	int step = 2;
	while (step<=2*n)//注意此处是2*n，可能尾端有<step的多余
	{
		int low_i = low;
		while (low_i<=high)
		{
			int high_i = low_i+step-1;
			if (high_i>high) high_i = high;
			int mid_i = (low_i+high_i)/2;

			merge_1(arr,low_i,mid_i,high_i);

			low_i += step;
		}

		step *=2;
	}
}