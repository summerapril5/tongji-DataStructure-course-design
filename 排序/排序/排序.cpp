#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <conio.h>
using namespace std;


void pause()
{
    while (_getch() != '\r')
        ;
    cout << endl;
}
//展示菜单
void menuDisplay()
{
    cout << "            排序算法比较            " << endl;
    cout << "====================================" << endl;
    cout << "  *         1---冒泡排序         *  " << endl;
    cout << "  *         2---选择排序         *  " << endl;
    cout << "  *         3---直接插入排序     *  " << endl;
    cout << "  *         4---希尔排序         *  " << endl;
    cout << "  *         5---快速排序         *  " << endl;
    cout << "  *         6---堆排序           *  " << endl;
    cout << "  *         7---归并排序         *  " << endl;
    cout << "  *         8---基数排序         *  " << endl;
    cout << "  *         9---退出程序         *  " << endl;
    cout << "====================================" << endl;
}

//希尔排序
void shellSort(int arr[], int size, int& comparisons, int& swaps) {
  
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int key = arr[i];
            int j = i;//记录值

            
            while (j >= gap && arr[j - gap] > key) {
                comparisons++;
                arr[j] = arr[j - gap];
                swaps++;
                j -= gap;
            }

            arr[j] = key;
        }
    }
}

//使i的索引所指向的数成为其子项的最大数
void heapify(int arr[], int size, int i, int& comparisons, int& swaps) {
    int largest = i;
    int left = 2 * i + 1;//左孩子
    int right = 2 * i + 2;//右孩子

   
    if (left < size && arr[left] > arr[largest]) {
        comparisons++;
        largest = left;
    }
    if (right < size && arr[right] > arr[largest]) {
        comparisons++;
        largest = right;
    }

    //如果已经有最大的数字，退出
    if (largest != i) {
        swap(arr[i], arr[largest]);//交换最大数到i这个位置
        swaps++;
        heapify(arr, size, largest, comparisons, swaps);
    }
}

//堆排序
void heapSort(int arr[], int size, int& comparisons, int& swaps) {
    //0 1 2 3 4 5 6 7 8 9(index)
    //4 is the parent of 9
    //3 is the parent of 7 8
    //2 is the parent of 5 6
    //1 is the parent of 3 4
    //0 is the parent of 1 2
    //Form the bottom to the top
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(arr, size, i, comparisons, swaps);
    }

    //使最后元素成为最大的数字
    for (int i = size - 1; i >= 0; i--) {
       
        swap(arr[0], arr[i]);
        swaps++;
        heapify(arr, i, 0, comparisons, swaps);//让arr[0]最大
    }
}


void merge(int arr[], int left, int mid, int right, int& comparisons, int& swaps)
{

    int n1 = mid - left + 1;//左部分大小
    int n2 = right - mid;//右部分大小

    //储存两部分
    int* L = new int[n1];
    int* R = new int[n2];

    
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;//初始化

    
    while (i < n1 && j < n2) {
        //选择较小的数字并将其移动到阵列中的正确位置
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        swaps++;
        comparisons++;
        k++;
    }

    //如果右侧已检查完毕，则push左侧
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        swaps++;
    }
    //如果左侧已检查完毕，则push右侧
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        swaps++;
    }
}

//归并排序
void mergeSort(int arr[], int left, int right, int& comparisons, int& swaps) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, comparisons, swaps);
        mergeSort(arr, mid + 1, right, comparisons, swaps);
        merge(arr, left, mid, right, comparisons, swaps);
    }
}



//获得数组最大值
int getMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}


void countSort(int arr[], int size, int exp, int& comparisons, int& swaps)
{
    int* output = new int[size];
    int count[10] = { 0 };

    for (int i = 0; i < size; i++) {
        count[(arr[i] / exp) % 10]++; //(arr[i] / exp) % 10 is the key 
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];//Push最小的
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = output[i];//复制到数组
        swaps++;
    }
}
//基数排序
void radixSort(int arr[], int size, int& comparisons, int& swaps) {
    int max = getMax(arr, size);//获得最大值

    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSort(arr, size, exp, comparisons, swaps);
    }
}

//产生随机数
void generateRandomNumbers(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = rand();
    }
}

//快速排序
void quickSort(int arr[], int left, int right, int& comparisons, int& swaps)
{
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];//把中间数做基准

    //左小于右
    while (i <= j) {

        while (arr[i] < pivot) {
            comparisons++;
            i++;
        }

        while (arr[j] > pivot) {
            comparisons++;
            j--;
        }

        //移动后左小于等于右
        if (i <= j) {
            swap(arr[i], arr[j]);//交换，小在左，大在右
            swaps++;
            i++;
            j--;
        }
    }

    if (left < j)
        quickSort(arr, left, j, comparisons, swaps);//进左部分
    if (i < right)
        quickSort(arr, i, right, comparisons, swaps);//进右部分

}

//插入排序
void insertionSort(int arr[], int size, int& comparisons, int& swaps) {

    for (int i = 1; i < size; ++i) {

        int key = arr[i];
        int j = i - 1;

        //检查剩下的所有数字，直到我们找到一个比key小的数字
        while (j >= 0 && arr[j] > key) {
            comparisons++;
            arr[j + 1] = arr[j];//移到右面一个
            swaps++;
            j--;
        }

        arr[j + 1] = key;                                                     
    }

}

//冒泡排序
void bubbleSort(int arr[], int size, int& comparisons, int& swaps) {

    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swaps++;
            }
        }
    }
}

//选择排序
void selectionSort(int arr[], int size, int& comparisons, int& swaps) {
    for (int i = 0; i < size - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < size; ++j) {
            comparisons++;
            if (arr[j] < arr[minIndex])
                minIndex = j;//更新minindex
        }
        std::swap(arr[i], arr[minIndex]);//总是让位置存储其右侧所有数字的最小值
        swaps++;
    }
}

void bubbleCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    bubbleSort(arr, size, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "冒泡排序比较次数: " << comparisons << std::endl;
    std::cout << "冒泡排序交换次数: " << swaps << std::endl;
    std::cout << "冒泡排序所需时间: " << duration.count() << " 毫秒" << std::endl;
}
void selectionCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    selectionSort(arr, size, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "选择排序比较次数: " << comparisons << std::endl;
    std::cout << "选择排序交换次数: " << swaps << std::endl;
    std::cout << "选择排序所需时间: " << duration.count() << " 毫秒" << std::endl;
}

void insertionCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    insertionSort(arr, size, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "插入排序比较次数: " << comparisons << std::endl;
    std::cout << "插入排序交换次数: " << swaps << std::endl;
    std::cout << "插入排序所需时间: " << duration.count() << " 毫秒" << std::endl;
}

void shellCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    shellSort(arr, size, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "希尔排序比较次数: " << comparisons << std::endl;
    std::cout << "希尔排序交换次数: " << swaps << std::endl;
    std::cout << "希尔排序所需时间: " << duration.count() << " 毫秒" << std::endl;
}

void quickCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(arr, 0, size - 1, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "快速排序比较次数: " << comparisons << std::endl;
    std::cout << "快速排序交换次数: " << swaps << std::endl;
    std::cout << "快速排序所需时间: " << duration.count() << " 毫秒" << std::endl;
}

void heapCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    heapSort(arr, size, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "堆排序比较次数: " << comparisons << std::endl;
    std::cout << "堆排序交换次数: " << swaps << std::endl;
    std::cout << "堆排序所需时间: " << duration.count() << " 毫秒" << std::endl;
}

void mergeCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(arr, 0, size - 1, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "归并排序比较次数: " << comparisons << std::endl;
    std::cout << "归并排序交换次数: " << swaps << std::endl;
    std::cout << "归并排序所需时间: " << duration.count() << " 毫秒" << std::endl;
}

void radixCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    radixSort(arr, size, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "基数排序比较次数: " << comparisons << std::endl;
    std::cout << "基数排序交换次数: " << swaps << std::endl;
    std::cout << "基数排序所需时间: " << duration.count() << " 毫秒" << std::endl;
}
int main()
{
    while (true) {

        const int size = 10000;
        int arr[size];

        srand(static_cast<unsigned>(time(0)));
        generateRandomNumbers(arr, size);

        int comparisons = 0, swaps = 0;


        //清屏
        system("cls");

        
        menuDisplay();

        char controller;
        while (true) {
            controller = _getch();

            if (controller >= '1' && controller <= '9') {
                cout << controller << endl;

                switch (controller)
                {
                case '1':
                    bubbleCalculate(arr, size, comparisons, swaps);
                    cout << "操作完成，按回车继续..." << endl;
                    pause();
                    break;
                case '2':
                    selectionCalculate(arr, size, comparisons, swaps);
                    cout << "操作完成，按回车继续..." << endl;
                    pause();
                    break;
                case '3':
                    insertionCalculate(arr, size, comparisons, swaps);
                    cout << "操作完成，按回车继续..." << endl;
                    pause();
                    break;
                case '4':
                    shellCalculate(arr, size, comparisons, swaps);
                    cout << "操作完成，按回车继续..." << endl;
                    pause();
                    break;
                case '5':
                    quickCalculate(arr, size, comparisons, swaps);
                    cout << "操作完成，按回车继续..." << endl;
                    pause();
                    break;
                case '6':
                    heapCalculate(arr, size, comparisons, swaps);
                    cout << "操作完成，按回车继续..." << endl;
                    pause();
                    break;
                case '7':
                    mergeCalculate(arr, size, comparisons, swaps);
                    cout << "操作完成，按回车继续..." << endl;
                    pause();
                    break;
                case '8':
                    radixCalculate(arr, size, comparisons, swaps);
                    cout << "操作完成，按回车继续..." <<endl;
                    pause();
                    break;
                case '9':
                    cout << "程序结束！" << endl;
                    return 0;
                default:
                    continue;
                }
                break;
            }
        }

    }

    return 0;
}
