#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

void CreateRow(int** a, const int rowNo, const int n, const int Low, const int High, int colNo) {
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < n - 1)
        CreateRow(a, rowNo, n, Low, High, colNo + 1);
}

void CreateRows(int** a, const int k, const int n, const int Low, const int High, int rowNo) {
    CreateRow(a, rowNo, n, Low, High, 0);
    if (rowNo < k - 1)
        CreateRows(a, k, n, Low, High, rowNo + 1);
}
void PrintRow(int** a, const int rowNo, const int n, int colNo) {
    cout << setw(5) << a[rowNo][colNo];
    if (colNo < n - 1)
        PrintRow(a, rowNo, n, colNo + 1);
    else
        cout << endl;
}

void PrintRows(int** a, const int k, const int n, int rowNo) {
    PrintRow(a, rowNo, n, 0);
    if (rowNo < k - 1)
        PrintRows(a, k, n, rowNo + 1);
}

int FindMaxInRow(int** a, const int rowNo, const int n, int colNo, int maxVal) {
    if (a[rowNo][colNo] > maxVal)
        maxVal = a[rowNo][colNo];
    
    if (colNo < n - 1)
        return FindMaxInRow(a, rowNo, n, colNo + 1, maxVal);
    else
        return maxVal;
}

int SumMaxInEvenRows(int** a, const int k, const int n, int rowNo) {
    if (rowNo >= k) 
        return 0;

    int maxInCurrentRow = FindMaxInRow(a, rowNo, n, 1, a[rowNo][0]);
    
    cout << "Рядок " << setw(2) << rowNo << ": max = " << maxInCurrentRow << endl;

    return maxInCurrentRow + SumMaxInEvenRows(a, k, n, rowNo + 2);
}

int main() {
    setlocale(LC_ALL, "Ukrainian");
    srand((unsigned)time(NULL));

    int k, n;
    cout << "Введіть кількість рядків (k): "; cin >> k;
    cout << "Введіть кількість стовпців (n): "; cin >> n;

    int** a = new int*[k];
    for (int i = 0; i < k; i++)
        a[i] = new int[n];

    int Low = 1;   
    int High = 50; 

    CreateRows(a, k, n, Low, High, 0);
    
    cout << "\nСформована матриця:" << endl;
    PrintRows(a, k, n, 0);

    cout << "Пошук максимумів у парних рядках:" << endl;
    cout << "---------------------------------" << endl;
    int totalSum = SumMaxInEvenRows(a, k, n, 0);
    cout << "---------------------------------" << endl;
    
    cout << "Загальна сума максимальних елементів: " << totalSum << endl;

    for (int i = 0; i < k; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}
