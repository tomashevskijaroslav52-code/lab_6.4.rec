#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Рекурсивне створення масиву
void Create(double* a, const int size, const double Low, const double High, int i)
{
    a[i] = Low + (double)rand() / RAND_MAX * (High - Low);
    if (i < size - 1)
        Create(a, size, Low, High, i + 1);
}

// Рекурсивне виведення масиву
void Print(const double* a, const int size, int i)
{
    cout << setw(8) << fixed << setprecision(2) << a[i];
    if (i < size - 1)
        Print(a, size, i + 1);
    else
        cout << endl;
}

// 1.1. Рекурсивне обчислення кількості елементів, більших за C
int CountGreaterThanC(const double* a, const int size, const double C, int i)
{
    if (i < size)
    {
        if (a[i] > C)
            return 1 + CountGreaterThanC(a, size, C, i + 1);
        else
            return CountGreaterThanC(a, size, C, i + 1);
    }
    else
    {
        return 0;
    }
}

// Допоміжна рекурсивна функція для пошуку індексу максимального за модулем елемента
void FindMaxAbsIndexRec(const double* a, const int size, int i, double& maxAbs, int& maxIndex)
{
    if (i < size)
    {
        if (fabs(a[i]) > maxAbs)
        {
            maxAbs = fabs(a[i]);
            maxIndex = i;
        }
        FindMaxAbsIndexRec(a, size, i + 1, maxAbs, maxIndex);
    }
}

int FindMaxAbsIndex(const double* a, const int size)
{
    if (size <= 0) return -1;
    double maxAbs = fabs(a[0]);
    int maxIndex = 0;
    FindMaxAbsIndexRec(a, size, 1, maxAbs, maxIndex);
    return maxIndex;
}

// 1.2. Рекурсивне обчислення добутку елементів, розташованих після максимального за модулем
double ProductAfterMaxAbsRec(const double* a, const int size, int i)
{
    if (i < size)
    {
        return a[i] * ProductAfterMaxAbsRec(a, size, i + 1);
    }
    else
    {
        return 1.0;
    }
}

double ProductAfterMaxAbs(const double* a, const int size)
{
    int maxIndex = FindMaxAbsIndex(a, size);
    if (maxIndex == -1 || maxIndex >= size - 1)
    {
        return 0; // Якщо після максимального немає елементів
    }
    return ProductAfterMaxAbsRec(a, size, maxIndex + 1);
}

// Допоміжна рекурсивна функція для копіювання від'ємних елементів
int CopyNegative(const double* a, const int size, double* temp, int i, int destIdx)
{
    if (i < size)
    {
        if (a[i] < 0)
        {
            temp[destIdx++] = a[i];
        }
        return CopyNegative(a, size, temp, i + 1, destIdx);
    }
    return destIdx;
}

// Допоміжна рекурсивна функція для копіювання додатних і нулів
int CopyPositive(const double* a, const int size, double* temp, int i, int destIdx)
{
    if (i < size)
    {
        if (a[i] >= 0)
        {
            temp[destIdx++] = a[i];
        }
        return CopyPositive(a, size, temp, i + 1, destIdx);
    }
    return destIdx;
}

// Рекурсивне перенесення елементів назад у масив
void CopyBack(double* a, const double* temp, const int size, int i)
{
    if (i < size)
    {
        a[i] = temp[i];
        CopyBack(a, temp, size, i + 1);
    }
}

// 2. Рекурсивне перетворення масиву (спочатку від'ємні, потім невід'ємні)
void TransformArray(double* a, const int size)
{
    double* temp = new double[size];
    int nextIdx = CopyNegative(a, size, temp, 0, 0);
    CopyPositive(a, size, temp, 0, nextIdx);
    CopyBack(a, temp, size, 0);
    delete[] temp;
}

int main()
{
    srand((unsigned)time(NULL));

    int n;
    cout << "Enter n: ";
    cin >> n;

    double C;
    cout << "Enter C: ";
    cin >> C;

    double* a = new double[n];

    double Low = -10.0;
    double High = 10.0;

    Create(a, n, Low, High, 0);
    cout << "\nInitial array:" << endl;
    Print(a, n, 0);

    int countC = CountGreaterThanC(a, n, C, 0);
    cout << "1.1. Count of elements > " << C << " = " << countC << endl;

    int maxAbsIdx = FindMaxAbsIndex(a, n);
    cout << "Max absolute element = " << a[maxAbsIdx] << " at index " << maxAbsIdx << endl;

    double prod = ProductAfterMaxAbs(a, n);
    cout << "1.2. Product after max abs element = " << prod << endl;

    TransformArray(a, n);
    cout << "\nModified array (negative first, then positive/zero):" << endl;
    Print(a, n, 0);

    delete[] a;

    return 0;
}
