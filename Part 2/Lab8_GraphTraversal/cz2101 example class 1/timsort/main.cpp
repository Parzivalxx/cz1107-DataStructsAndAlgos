#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

const int maxn = 1e4+1;
int n, a[maxn], mer[maxn/2], b[maxn];

void merge(int l, int r) {
  int mi = (l+r)/2;
  for(int ll = l, i = 1; ll <= mi; ll++, i++) {
    mer[i] = a[ll];
  }
  int k = l;
  int i = 1, j = mi+1;
  for(; i <= mi-l+1 && j <= r; k++) {
    if(mer[i] < a[j]) a[k] = mer[i++];    else a[k] = a[j++];
  }
  if(j > r)
    while(i <= mi-l+1) a[k++] = mer[i++];
}

void mergeSort(int l,int r) {
  if(l >= r) return;
  int mi = (l+r)/2;
  mergeSort(l, mi);
  mergeSort(mi+1, r);
  merge(l, r);
}

void insertionSort(int l = 1, int r = maxn) {
  for(int i = l; i <= r; i++) {
    for(int j = i-1; j >= l; j--) {
      if(b[j] > b[j+1]) swap(b[j], b[j+1]);
      else break;
    }
  }
}

void generateArray() {
  srand(time(0));
  for(int i = 1; i <= n; i++) a[i] = b[i] = rand();
}

bool testOrder() {
  for(int i = 1; i < n; i++) {
    if(a[i] > a[i+1] || b[i] > b[i+1]) {
      return false;
    }
  }
  return true;
}

void testTimeFor2(int size, int times) {
  n = size;
  int insertionTime = 0, mergeTime = 0;
  for(int i = 1; i <= times; i++) {
    generateArray();
    auto start = high_resolution_clock::now();
    insertionSort(1, n);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end-start);
    insertionTime += duration.count();


    start = high_resolution_clock::now();
    mergeSort(1, n);
    end = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(end-start);
    mergeTime += duration.count();


    if(!testOrder()) {
      cout << "sort error\n";
      return;
    }
  }
  cout << size << "\t\t" << insertionTime/times << "\t\t" << mergeTime/times << "\n";
}

int main() {
  ios::sync_with_stdio(0);
  cout << "arraySize\tinsertionTime\tmergeTime\n";
  for(int i = 1; i <= 100; i++) testTimeFor2(i, 1000);
  // for(int i = 1; i <= 10; i++) cout << clock() << endl;
  // for(int i = 1; i <= 20; i++) cout << a[i] << ' ' << b[i] << endl;
  return 0;
}
