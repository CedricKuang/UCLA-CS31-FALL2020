
#include <iostream>
#include <string>
#include <cassert>
using namespace std;
int appendToAll(string a[], int n, string value);
int lookup(string a[], int n, string value);
int positionOfMax(string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int divide(string a[], int n, string divider);

int main()
{
    string h[7] = { "martha", "mark", "joe", "susan", "", "kamala", "lindsey" };
    assert(lookup(h, 7, "kamala") == 5);
    assert(lookup(h, 7, "joe") == 2);
    assert(lookup(h, 2, "joe") == -1);
    assert(positionOfMax(h, 7) == 3);
    assert(positionOfMax(h, 0) == -1);

    string g[4] = { "martha", "mark", "lindsey", "sara" };
    assert(differ(h, 4, g, 4) == 2);
    assert(differ(h, 0, g, 4) == 0);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "martha?" && g[3] == "sara?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "lindsey?" && g[3] == "mark?");

    string e[4] = { "joe", "susan", "", "kamala" };
    assert(subsequence(h, 7, e, 4) == 2);
    assert(subsequence(h, 7, e, 0) == 0);
    assert(subsequence(h, 0, e, 4) == -1);

    string d[5] = { "mark", "mark", "mark", "susan", "susan" };
    assert(countRuns(d, 5) == 2);
    assert(countRuns(d, 0) == 0);

    string f[3] = { "lindsey", "joe", "mike" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "mike" && f[2] == "lindsey");

    assert(divide(h, 7, "lindsey") == 3);
    assert(divide(h, 0, "lindsey") == 0);

    cout << "All tests succeeded" << endl;

    
    return 0;
}

int appendToAll(string a[], int n, string value)   /*append value parameter to all strings in an array*/
{
    if (n < 0)      /*return -1 for negative value of n, same for other functions*/
        return -1;

    for (int i = 0; i < n; i++)   /*a loop that vists each element in the array*/
        a[i] += value;
    return n;
}

int lookup(string a[], int n, string value)    /*look up parameter in am array*/
{
    if (n < 0)
        return -1;

    for (int i = 0; i < n; i++)   /*a loop that vists each element in the array*/
    {
        if (a[i] == value)
            return i;
    }
    return -1;
}

int positionOfMax(string a[], int n)   /*find the position of maximun string in an array*/
{
    if (n < 0)
        return -1;

    string max = a[0];  /*initialize the string max to the first element of the array first*/
    for (int i = 0; i < n; i++)
    {
        if (a[i] >= max)
            max = a[i];      /*keep tracking the maximun string and assign it to maax*/
    }
    return lookup(a, n, max);   /*call the function lookup() to find the position of max*/
}

int rotateLeft(string a[], int n, int pos)
{
    if (n < 0 || pos < 0 || pos > n - 1)
        return -1;

    string temp = a[pos];       /*assign temp to the string at pos*/
    for (int i = pos; i < n - 1; i++)
        a[i] = a[i + 1];      /*keep assigning the string to the string behind it until the second last of the string*/
    a[n - 1] = temp;   /*the last string is assgined to the string at pos*/
    return pos;       
}

int countRuns(const string a[], int n)
{
    if (n < 0)
        return -1;

    int count = 0;
    int i = 0;
    int q;
    while (i < n ) /*a while loop that visits every element in the array*/
    {
        q = i;
        while (a[q] == a[q + 1])    /*keep testing whether the string is equal to the string behind it until it's not*/
            q++;
        count++;    /*add one to count*/
        i = q + 1;
    }
    return count;
}

int flip(string a[], int n)
{
    if (n < 0)
        return -1;

    for (int i = 0; i < n / 2; i++)   /*a for loop visting first half of the array*/
    {
        string temp = a[i];       /*assign the string to temp*/
        a[i] = a[n - i - 1];      /*assign the string's counterpart in the second half of the array to the string*/
        a[n - i - 1] = temp;      /*assign that counterpart to temp*/
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;

    int n3 = (n1 <= n2 ? n1 : n2);    /*assign n3 to n1 or n2, whichever is smaller*/

    for (int i = 0; i < n3; i++)     /*comparing each corresponding element in two array*/
    {
        if (a1[i] != a2[i])
            return i;               /*retur the number of position if there is difference*/
    }

    return n3;      /*return the smaller number if ther is no difference*/
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0 || n2 > n1)
        return -1;

    if (n2 == 0)    /*if a2 is an empty array, return 0*/
        return 0;

    for (int i = 0; i < n1; i++)      /*visit every element in a1*/
    {
        if (a1[i] == a2[0])          /*if find one element is equal to the first element in a2, repeatedly comparing following elements in both array*/
        {
            int n = 1, m = i+1;
            while (a1[m] == a2[n] && n < n2 && m < n1)
                m++, n++;
            if (n == n2)    /*if following elements are all the same, return the position i*/
                return i;
        }
    }

    return -1;     /*return -1 if a2 is not a sub string*/
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;

    for (int i = 0; i < n1; i++)      /*visit every element in a1*/
    {
        for (int m = 0; m < n2; m++)      /*visit every element in a2*/
        {
            if (a1[i] == a2[m])           /*if they are equal, return the position i*/
                return i;
        }
    }
    return -1;      /*if not, return -1*/
}

int divide(string a[], int n, string divider)
{
    for (int i = 0; i < n - 1; i++)          /*the "bubble sorting", rearranging the elements in the array from small to large*/
    {
        for (int m = 0; m < n - i - 1; m++)
        {
            if (a[m] > a[m + 1])           /*repeatedly swapping the elements if the string is larger than the string on its right side*/
            {
                string temp = a[m];
                a[m] = a[m + 1];
                a[m + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++)       /*finding the element that is no smaller than divider*/
    {
        if (divider <= a[i])
            return i;          /*return its position*/
    }
    return n;      /*if there is no such element, return n*/
}