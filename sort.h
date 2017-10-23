#include "Global.h"

//��������-ֱ�Ӳ�������
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

//��������-ϣ������
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

//��������ð������
template<class T>
void bubbleSort(vector<T> &arr)
{
	int n = arr.size();
	for (int i=0;i<n-1;++i)//����
	{
		bool flag = false;
		for (int j=0;j<n-i-1;++j)//ÿһ������
		{
			if (arr[j]>arr[j+1])//����
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

//�������򡪿�������

//partition���ֲ������ڴ�������arr[low...high]����ȡһ��Ԫ��pivot��Ϊ��׼����<=pivot��Ԫ�ط���������ߣ�>pivot��Ԫ�ط��������ұߣ���pivot
//������������λ��arr[k]�ϣ��õ������ӱ�arr[low...k-1]��arr[k+1...high]�������һ�˿������򡣶���ֱ�ݹ�ض��������ӱ��ظ��������̣�ֱ��ÿ��������
//ֻ��һ��Ԫ�ػ�Ϊ�ա�

//partition�����ķ���ֵ����kֵ������ʵ�������ֲ���

//partition_1:ѡȡ�������еĵ�һ��Ԫ����Ϊ��׼����һ���ֲ�pivot���棬�������λ�þͱ��ڳ�����Ϊ����ʹ�ã����������λ�ý���ĴӴ������е���β���м�ɨ�裻
template<class T>
int partition_1(vector<T> &arr,int low,int high)
{
	if (low>high) return -1;

	swap(arr[low],arr[low+rand()%(high-low+1)]);//��ѡһ��Ԫ������Ԫ�ؽ��������ѡȡ�������������ֵĸ��ʣ��Ż�������

	T pivot = arr[low];//��һ��Ԫ����Ϊ��׼
	while (low<high)
	{
		while (low<high&&arr[high]>=pivot) --high;//β->�м� ɨ��,��ʱ��λΪlow
		arr[low] = arr[high];//��λ��Ϊhigh

		while (low<high&&arr[low]<=pivot) ++low;//��->�м� ɨ��,��ʱ��λΪhigh
		arr[high] = arr[low];//��λ��Ϊlow
	}
	arr[low] = pivot;//��û�׼
	return low;
}

//partition_2:ѡȡ�������е����һ��Ԫ����Ϊ��׼�����Ȼ�׼С��Ԫ��ȫ�������ķŵ���ߣ�����ָ��������һ��Ϊsmall��ʼΪlow-1��ʼ��ָ�����С�����Ȼ�׼С��
//���е����һ������һ��Ϊ����ָ��i�����α����������У����Ȼ�׼С�����û���small���档
//����ŵ㣺һ�λ��ֺ���Ŧλ��k��ߵ�Ԫ�����˳�򲻱�
template<class T>
int partition_2(vector<T> &arr,int low,int high)
{
	int small = low-1,i=low;
	if (low>high) return -1;

	swap(arr[high],arr[low+rand()%(high-low+1)]);//��ѡһ��Ԫ����βԪ�ؽ��������ѡȡ�������������ֵĸ��ʣ��Ż�������

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

//�ݹ�ʵ��
template<class T>
void quickSort(vector<T> &arr,int low,int high)
{
	if (low<high)//�ݹ��������
	{
		int pivot_k = partition_2(arr,low,high);//���ֲ�������arr[low...high]�Ի�׼Ԫ�ػ��ֳ������ӱ�����Ϊһ�˿���
		quickSort(arr,low,pivot_k-1);
		quickSort(arr,pivot_k+1,high);
	}
}

//�ǵݹ�ʵ��
//��ʵ�����ֶ�����ջ���洢ÿ�ηֿ���ŵ���ֹ�㣬ջ�ǿ�ʱѭ����ȡ������ջ
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
		if (pivot_k-1>p.low)//���ٺ�����Ԫ��
		{
			stack_lh.push(point(p.low,pivot_k-1));
		}
		if (p.high>pivot_k+1)//���ٺ�����Ԫ��
		{
			stack_lh.push(point(pivot_k+1,p.high));
		}
	}
}

//ѡ�����򡪼�ѡ������
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

//�鲢���򡪶�·�鲢����

//���������Ķ�·�鲢
//�����ڵ���������arr[low...mid] �� arr[mid+1...high]�����н��й鲢

//�鲢1����Ҫ����o(n)����ռ�
template<class T>
void merge_1(vector<T> &arr,int low,int mid,int high)
{
	//����һ���������鸴�Ʊ���arr[low...mid]����
	vector<T> leftArr(arr.begin()+low,arr.begin()+mid+1);
	//��leftArr��arr[mid+1...high]���й鲢��arr[low...high]
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
//�鲢2��ԭ�ع鲢����Ҫ���ٶ���ռ䣬����ʱ�临�ӶȾ͸���
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

//�ݹ�ʵ��(�Զ�����)
template<class T>
void mergeSort(vector<T> &arr,int low,int high)
{
	if (high-low<1) return; //�ݹ���������� ��������Ȼ����
	int mid = (low+high)/2;
	mergeSort(arr,low,mid);
	mergeSort(arr,mid+1,high);
	merge_2(arr,low,mid,high);//�鲢
}

//�ǵݹ�ʵ��(�Ե�����)
template<class T>
void mergeSort2(vector<T> &arr,int low,int high)
{
	int n = high-low+1;
	int step = 2;
	while (step<=2*n)//ע��˴���2*n������β����<step�Ķ���
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