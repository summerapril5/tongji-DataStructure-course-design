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
//չʾ�˵�
void menuDisplay()
{
    cout << "            �����㷨�Ƚ�            " << endl;
    cout << "====================================" << endl;
    cout << "  *         1---ð������         *  " << endl;
    cout << "  *         2---ѡ������         *  " << endl;
    cout << "  *         3---ֱ�Ӳ�������     *  " << endl;
    cout << "  *         4---ϣ������         *  " << endl;
    cout << "  *         5---��������         *  " << endl;
    cout << "  *         6---������           *  " << endl;
    cout << "  *         7---�鲢����         *  " << endl;
    cout << "  *         8---��������         *  " << endl;
    cout << "  *         9---�˳�����         *  " << endl;
    cout << "====================================" << endl;
}

//ϣ������
void shellSort(int arr[], int size, int& comparisons, int& swaps) {
  
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int key = arr[i];
            int j = i;//��¼ֵ

            
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

//ʹi��������ָ�������Ϊ������������
void heapify(int arr[], int size, int i, int& comparisons, int& swaps) {
    int largest = i;
    int left = 2 * i + 1;//����
    int right = 2 * i + 2;//�Һ���

   
    if (left < size && arr[left] > arr[largest]) {
        comparisons++;
        largest = left;
    }
    if (right < size && arr[right] > arr[largest]) {
        comparisons++;
        largest = right;
    }

    //����Ѿ����������֣��˳�
    if (largest != i) {
        swap(arr[i], arr[largest]);//�����������i���λ��
        swaps++;
        heapify(arr, size, largest, comparisons, swaps);
    }
}

//������
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

    //ʹ���Ԫ�س�Ϊ��������
    for (int i = size - 1; i >= 0; i--) {
       
        swap(arr[0], arr[i]);
        swaps++;
        heapify(arr, i, 0, comparisons, swaps);//��arr[0]���
    }
}


void merge(int arr[], int left, int mid, int right, int& comparisons, int& swaps)
{

    int n1 = mid - left + 1;//�󲿷ִ�С
    int n2 = right - mid;//�Ҳ��ִ�С

    //����������
    int* L = new int[n1];
    int* R = new int[n2];

    
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;//��ʼ��

    
    while (i < n1 && j < n2) {
        //ѡ���С�����ֲ������ƶ��������е���ȷλ��
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

    //����Ҳ��Ѽ����ϣ���push���
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        swaps++;
    }
    //�������Ѽ����ϣ���push�Ҳ�
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        swaps++;
    }
}

//�鲢����
void mergeSort(int arr[], int left, int right, int& comparisons, int& swaps) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, comparisons, swaps);
        mergeSort(arr, mid + 1, right, comparisons, swaps);
        merge(arr, left, mid, right, comparisons, swaps);
    }
}



//����������ֵ
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
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];//Push��С��
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = output[i];//���Ƶ�����
        swaps++;
    }
}
//��������
void radixSort(int arr[], int size, int& comparisons, int& swaps) {
    int max = getMax(arr, size);//������ֵ

    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSort(arr, size, exp, comparisons, swaps);
    }
}

//���������
void generateRandomNumbers(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = rand();
    }
}

//��������
void quickSort(int arr[], int left, int right, int& comparisons, int& swaps)
{
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];//���м�������׼

    //��С����
    while (i <= j) {

        while (arr[i] < pivot) {
            comparisons++;
            i++;
        }

        while (arr[j] > pivot) {
            comparisons++;
            j--;
        }

        //�ƶ�����С�ڵ�����
        if (i <= j) {
            swap(arr[i], arr[j]);//������С���󣬴�����
            swaps++;
            i++;
            j--;
        }
    }

    if (left < j)
        quickSort(arr, left, j, comparisons, swaps);//���󲿷�
    if (i < right)
        quickSort(arr, i, right, comparisons, swaps);//���Ҳ���

}

//��������
void insertionSort(int arr[], int size, int& comparisons, int& swaps) {

    for (int i = 1; i < size; ++i) {

        int key = arr[i];
        int j = i - 1;

        //���ʣ�µ��������֣�ֱ�������ҵ�һ����keyС������
        while (j >= 0 && arr[j] > key) {
            comparisons++;
            arr[j + 1] = arr[j];//�Ƶ�����һ��
            swaps++;
            j--;
        }

        arr[j + 1] = key;                                                     
    }

}

//ð������
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

//ѡ������
void selectionSort(int arr[], int size, int& comparisons, int& swaps) {
    for (int i = 0; i < size - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < size; ++j) {
            comparisons++;
            if (arr[j] < arr[minIndex])
                minIndex = j;//����minindex
        }
        std::swap(arr[i], arr[minIndex]);//������λ�ô洢���Ҳ��������ֵ���Сֵ
        swaps++;
    }
}

void bubbleCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    bubbleSort(arr, size, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "ð������Ƚϴ���: " << comparisons << std::endl;
    std::cout << "ð�����򽻻�����: " << swaps << std::endl;
    std::cout << "ð����������ʱ��: " << duration.count() << " ����" << std::endl;
}
void selectionCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    selectionSort(arr, size, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "ѡ������Ƚϴ���: " << comparisons << std::endl;
    std::cout << "ѡ�����򽻻�����: " << swaps << std::endl;
    std::cout << "ѡ����������ʱ��: " << duration.count() << " ����" << std::endl;
}

void insertionCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    insertionSort(arr, size, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "��������Ƚϴ���: " << comparisons << std::endl;
    std::cout << "�������򽻻�����: " << swaps << std::endl;
    std::cout << "������������ʱ��: " << duration.count() << " ����" << std::endl;
}

void shellCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    shellSort(arr, size, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "ϣ������Ƚϴ���: " << comparisons << std::endl;
    std::cout << "ϣ�����򽻻�����: " << swaps << std::endl;
    std::cout << "ϣ����������ʱ��: " << duration.count() << " ����" << std::endl;
}

void quickCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(arr, 0, size - 1, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "��������Ƚϴ���: " << comparisons << std::endl;
    std::cout << "�������򽻻�����: " << swaps << std::endl;
    std::cout << "������������ʱ��: " << duration.count() << " ����" << std::endl;
}

void heapCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    heapSort(arr, size, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "������Ƚϴ���: " << comparisons << std::endl;
    std::cout << "�����򽻻�����: " << swaps << std::endl;
    std::cout << "����������ʱ��: " << duration.count() << " ����" << std::endl;
}

void mergeCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(arr, 0, size - 1, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "�鲢����Ƚϴ���: " << comparisons << std::endl;
    std::cout << "�鲢���򽻻�����: " << swaps << std::endl;
    std::cout << "�鲢��������ʱ��: " << duration.count() << " ����" << std::endl;
}

void radixCalculate(int arr[], int size, int& comparisons, int& swaps)
{
    auto start = std::chrono::high_resolution_clock::now();
    radixSort(arr, size, comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "��������Ƚϴ���: " << comparisons << std::endl;
    std::cout << "�������򽻻�����: " << swaps << std::endl;
    std::cout << "������������ʱ��: " << duration.count() << " ����" << std::endl;
}
int main()
{
    while (true) {

        const int size = 10000;
        int arr[size];

        srand(static_cast<unsigned>(time(0)));
        generateRandomNumbers(arr, size);

        int comparisons = 0, swaps = 0;


        //����
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
                    cout << "������ɣ����س�����..." << endl;
                    pause();
                    break;
                case '2':
                    selectionCalculate(arr, size, comparisons, swaps);
                    cout << "������ɣ����س�����..." << endl;
                    pause();
                    break;
                case '3':
                    insertionCalculate(arr, size, comparisons, swaps);
                    cout << "������ɣ����س�����..." << endl;
                    pause();
                    break;
                case '4':
                    shellCalculate(arr, size, comparisons, swaps);
                    cout << "������ɣ����س�����..." << endl;
                    pause();
                    break;
                case '5':
                    quickCalculate(arr, size, comparisons, swaps);
                    cout << "������ɣ����س�����..." << endl;
                    pause();
                    break;
                case '6':
                    heapCalculate(arr, size, comparisons, swaps);
                    cout << "������ɣ����س�����..." << endl;
                    pause();
                    break;
                case '7':
                    mergeCalculate(arr, size, comparisons, swaps);
                    cout << "������ɣ����س�����..." << endl;
                    pause();
                    break;
                case '8':
                    radixCalculate(arr, size, comparisons, swaps);
                    cout << "������ɣ����س�����..." <<endl;
                    pause();
                    break;
                case '9':
                    cout << "���������" << endl;
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
