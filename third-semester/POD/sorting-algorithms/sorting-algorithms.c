/**
 * @file sorting_algorithms.c
 * @author Breno Soares Alves
 * @version 0.3
 * @date 03-30-2023
 *
 * @copyright Copyright (c) 2023
 *
 *
 * @brief Arquivo template para trabalho de Pesquisa e Ordenação.
 *
 *      Cada estudante deve implementar as funções conforme as assinaturas
 * abaixo e realizar as impressões dos vetores após a ordenação. Após, o(a)
 * estudante deve implementar o trecho de código para impressão dos vetores
 * ordenados dentro da função `main` conforme o exemplo do Bubble Sort abaixo.
 *
 * Atenção: Antes de entregar, conferir se dos dados acima da documentação estão
 * preenchidos corretamente.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Sort Methods Initializations
void bubbleSort(int *A, int size);
void selectionSort(int *A, int size);
void insertionSort(int *A, int size);
void mergeSort(int *A, int size);
void quickSort(int *A, int size);
void heapSort(int *A, int size);
void countingSort(int *A, int size);
void radixSort(int *A, int size);

// Auxiliary Functions Initializations
void sort(int *original_vec, int vec_len, char* sort_name, void (*sort_function)(int*, int));
void copy(int *A, int *v, int size);

void quick(int *A, int startIndex, int endIndex);
int partitionate(int *A, int start, int end);

void merge(int *A, int startIndex, int endIndex);
void intercalate(int *A, int start, int mid, int end);

void createHeap(int *A, int k, int size);

int searchGreater(int *A, int size);
int verifyIntegrity(int *A, int size);

void countingToRadix(int *A, int size, int pos);

int main()
{
    int i;
    int vector[] = {1, 13, 7, 3, 28, 100, 69};
    int vector_len = (int)sizeof(vector) / sizeof(int);

    printf("\nOriginal vector: ");
    for (i = 0; i < vector_len; i++)
        printf("%d ", vector[i]);

    printf("\nVector size: %d\n", vector_len);

    // bubble sort
    sort(vector, vector_len, "Bubble", bubbleSort);

    // selection sort
    sort(vector, vector_len, "Selection", selectionSort);

    // insertion sort
    sort(vector, vector_len, "Insertion", insertionSort);

    // merge sort
    sort(vector, vector_len, "Merge", mergeSort);

    // quick sort
    sort(vector, vector_len, "Quick", quickSort);

    // heap sort
    sort(vector, vector_len, "Heap", heapSort);

    // counting sort
    sort(vector, vector_len, "Counting", countingSort);

    // radix sort
    sort(vector, vector_len, "Radix",  radixSort);

    return 0;
}

void sort(int *original_vec, int vec_len, char* sort_name, void (*sort_function)(int*, int))
{
    int sorted_vec[vec_len];
    copy(original_vec, sorted_vec, vec_len);
    if(strcmp("Counting", sort_name) == 0 || strcmp("Radix", sort_name) == 0)
    {
        if(verifyIntegrity(sorted_vec, vec_len) == 0)
        {
            printf("\nYou can't make counting sort with negative numbers!!\n");
            return;
        }
    }
    sort_function(sorted_vec, vec_len);
    printf("\n%s sort:\t", sort_name);
    for (int i = 0; i < vec_len; i++)
        printf("%d ", sorted_vec[i]);
    printf("\n");
}

void bubbleSort(int *A, int size)
{
    for (int i = size - 1; i > 0; i--)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (A[j] > A[j + 1])
            {
                int c = A[j];
                A[j] = A[j + 1];
                A[j + 1] = c;
            }
        }
    }
}

void selectionSort(int *A, int size)
{
    int lower;
    for (int i = 0; i < size - 1; i++)
    {
        lower = i;
        for (int j = i + 1; j < size; j++)
        {
            if (A[lower] > A[j])
                lower = j;
        }
        int c = A[i];
        A[i] = A[lower];
        A[lower] = c;
    }
}

void insertionSort(int *A, int size)
{
    int i, j;
    for (i = 1; i < size; i++)
    {
        int p = A[i];
        j = i-1;
        while (j >= 0 && p < A[j])
        {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = p;
    }
}

void mergeSort(int *A, int size)
{
    merge(A, 0, size-1);
}

void quickSort(int *A, int size)
{
    quick(A, 0, size-1);
}

void heapSort(int *A, int size)
{
    for(int k = (size/2)-1; k >= 0; k--)
        createHeap(A, k, size);
    
    for(int k = size-1; k >= 1; k--)
    {
        int temp = A[0];
        A[0] = A[k];
        A[k] = temp;
        createHeap(A, 0, k);
    }
}

void countingSort(int *A, int size)
{
    int k = searchGreater(A, size);
    
    int count[k+1];
    int aux[size];

    for(int i = 0; i <= k; i++)
        count[i] = 0;

    for(int i = 0; i < size; i++)
    count[A[i]]++;

    for(int i = 1; i <= k; i++)
        count[i] += count[i-1];

    for(int i = size-1; i >= 0; i--)
    {
        count[A[i]] = count[A[i]] - 1;
        aux[count[A[i]]] = A[i];
    }

    for(int i = 0; i < size; i++)
        A[i] = aux[i];
}

void radixSort(int *A, int size)
{
    int pos;
    int max = searchGreater(A, size);
    for(pos = 1; max/pos > 0; pos*=10)
        countingToRadix(A, size, pos);
}

void merge(int *A, int startIndex, int endIndex)
{
    if(startIndex < endIndex) 
    {
        int midIndex = (startIndex + endIndex)/2;
        merge(A, startIndex, midIndex);
        merge(A, midIndex + 1, endIndex);
        intercalate(A, startIndex, midIndex, endIndex);
    }
}

void intercalate(int *A, int start, int mid, int end)
{
    int *aux = malloc(sizeof(int)*(end-start));
    int i = start;
    int j = mid + 1;
    int k = 0;
    while(i <= mid && j <= end)
    {
        if(A[i] <= A[j])
        {
            aux[k] = A[i];
            i++;
        }
        else 
        {
            aux[k] = A[j];
            j++;
        }
        k++;
    }
    while(i <= mid)
    {
        aux[k] = A[i];
        k++;
        i++;
    }
    while(j <= end)
    {
        aux[k] = A[j];
        k++;
        j++;
    }

    for(k = start; k <= end; k++)
    {
        A[k] = aux[k-start];
    }

    free(aux);
}

void quick(int *A, int start, int end)
{
    if(start < end)
    {
        int posPivot = partitionate(A, start, end);
        quick(A, start, posPivot-1);
        quick(A, posPivot+1, end);
    }
}

int partitionate(int *A, int start, int end)
{
    int posPivot = start;
    int i = start;
    int j = end;
    while(i<j)
    {
        while(A[i] <= A[posPivot] && i < end)
            i++;
        while(A[j] > A[posPivot])
            j--;
        if(i<j)
        {
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    int temp = A[posPivot];
    A[posPivot] = A[j];
    A[j] = temp;
    return j;
}

void createHeap(int *A, int k, int size)
{
    int greater = k;
    int left = 2*k + 1;
    int right = 2*k + 2;
    if(left < size && A[left] > A[k])
        greater = left;
    if(right < size && A[right] > A[greater])
        greater = right;

    if(greater != k)
    {
        int temp = A[k];
        A[k] = A[greater];
        A[greater] = temp;
        createHeap(A, greater, size);
    }
}

int searchGreater(int *A, int size)
{
    int greater = 0;
    for(int i = 0; i < size; i++)
    {
        if(A[i] > greater)
            greater = A[i];
    }
    return greater;
}

int verifyIntegrity(int *A, int size)
{
    for(int i = 0; i < size-1; i++)
    {
        if(A[i] < 0)
            return 0;
    }
    return 1;
}

void countingToRadix(int *A, int size, int pos)
{
    int aux[size];
    int count[10];

    for(int i = 0; i < 10; i++)
    {
        count[i] = 0;
    }

    for(int i = 0; i < size; i++)
    {
        int digit = (A[i]/pos) % 10;
        count[digit]++;
    }

    for(int i = 1; i < 10; i++)
    {
        count[i] = count[i] + count[i-1];
    }

    for(int i = size-1; i >= 0; i--)
    {
        int digit = (A[i] / pos) % 10;
        count[digit]--;
        aux[count[digit]] = A[i];
    }

    for(int i = 0; i < size; i++)
    {
        A[i] = aux[i];
    }
}

void copy(int *A, int *V, int size)
{
    int i;
    for (i = 0; i < size; i++)
        V[i] = A[i];
}