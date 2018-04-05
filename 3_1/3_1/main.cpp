#include<iostream>
#include<stdio.h>
#include<sstream>
using namespace std;
void get_data(int* &arr, int &len);

int main()
{
	int *arr = NULL, len = 0;
	get_data(arr, len);
	int maxHeapLen = 0, minHeapLen = 0;
	int *maxHeap = new int[len / 2 + 1];
	int *minHeap = new int[len / 2 + 1];
	
	maxHeap[0] = arr[0];
	maxHeapLen++;
	printf("%d ", maxHeap[0]);

	for (int i = 1; i < len; i++)
	{
		if (maxHeapLen > minHeapLen)
		{
			if (arr[i] >= maxHeap[0])
			{
				//add arr[i] to min
				int index = minHeapLen;
				while (index > 0)
				{
					if (minHeap[(index - 1) / 2] > arr[i])
					{
						minHeap[index] = minHeap[(index - 1) / 2];
						index = (index - 1) / 2;
					}
					else
					{
						break;
					}
				}
				minHeap[index] = arr[i];
				minHeapLen++;
			}
			else
			{
				//add max[0] to min
				int index = minHeapLen;
				while (index > 0)
				{
					if (minHeap[(index - 1) / 2] > maxHeap[0])
					{
						minHeap[index] = minHeap[(index - 1) / 2];
						index = (index - 1) / 2;
					}
					else
					{
						break;
					}
				}
				minHeap[index] = maxHeap[0];
				minHeapLen++;
				//add arr[i] to max
				index = 0;
				while (1)
				{
					int max_child = ((2 * index + 2 < maxHeapLen) && (maxHeap[2 * index + 1] < maxHeap[2 * index + 2])) ?
						2 * index + 2 : 2 * index + 1;
					if (max_child < maxHeapLen && arr[i] < maxHeap[max_child])	
					{
						maxHeap[index] = maxHeap[max_child];
						index = max_child;
					}
					else											
					{
						break;
					}
				}
				maxHeap[index] = arr[i];
			}
		}
		else
		{
			if(arr[i]>minHeap[0])
			{
				//add min[0] to max
				int index = maxHeapLen;
				while (index > 0)
				{
					if (maxHeap[(index - 1) / 2] < minHeap[0])
					{
						maxHeap[index] = maxHeap[(index - 1) / 2];
						index = (index - 1) / 2;
					}
					else
					{
						break;
					}
				}
				maxHeap[index] = minHeap[0];
				maxHeapLen++;
				//add arr[i] to min
				index = 0;
				while (1)
				{
					int min_child = ((2 * index + 2 < minHeapLen) && (minHeap[2 * index + 1] > minHeap[2 * index + 2])) ?
						2 * index + 2 : 2 * index + 1;
					if (min_child < minHeapLen && arr[i] > minHeap[min_child])
					{
						minHeap[index] = minHeap[min_child];
						index = min_child;
					}
					else
					{
						break;
					}
				}
				minHeap[index] = arr[i];
			}
			else
			{
				//add arr[i] to max
				int index = maxHeapLen;
				while (index > 0)
				{
					if (maxHeap[(index - 1) / 2] < arr[i])
					{
						maxHeap[index] = maxHeap[(index - 1) / 2];
						index = (index - 1) / 2;
					}
					else
					{
						break;
					}
				}
				maxHeap[index] = arr[i];
				maxHeapLen++;
			}
		}

		printf("%d ", maxHeap[0]);
	}

	cout << endl;
	delete[]arr;
	delete[]maxHeap;
	delete[]minHeap;
	return 0;
}




void get_data(int* &arr, int &len)
{
	string buf = "";
	getline(cin, buf);
	len = 0;
	for (int i = 0; i < int(buf.length()); i++)
	{
		if (buf[i] == ' ')
		{
			len++;
		}
	}

	stringstream stream;
	stream.clear();
	stream << buf;
	arr = new int[len];
	for (int i = 0; i < len; i++)
	{
		stream >> arr[i];
	}
}