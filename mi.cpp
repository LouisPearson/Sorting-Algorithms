#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <climits>

using namespace std;

int B[200000]; //global variable

void Fixheap (int A[ ], int root, int key, int bound) 
          // key is the key to be placed at the root, and
          // bound is index of the rightmost node of the last level 

        { 
           int vacant, Lgrchild; //Lgrchild is the child with the largest key of the vacant node 
           bool inserted = false;  // if we can not re-arrange a heap any further we
                                               // set inserted = true.

           vacant = root; // originally, the vacant node is the root 
           while ( (2*vacant <= bound) && (!inserted) )
           { 
                 Lgrchild = 2 * vacant; /* we make the right child be the node with largest key */
                 if ( (Lgrchild < bound) && A[Lgrchild +1] > A[Lgrchild])
                 {
                 	Lgrchild++;
                 } // if vacant node has
                                                                                                                     // right child and
                                                                                                                     // right child has the 
                                                                                                                     // largest key.
                             
                      if ( key <  A[Lgrchild])
                         { A[vacant] = A[Lgrchild];
                            vacant = Lgrchild;
                         }
                      else inserted=true;
            } 
      A[vacant] = key;
}
void Heapsort (int A[ ], int n)
          {
              int i, heapsize, max;
              
              // *******  Heap Construction *******//
              for (i=n/2; i >= 1; i--) 
				{

					Fixheap(A,i,A[i],n);
				}
                     

              // ******* Heap Sort **************//

               for (heapsize = n; heapsize >=2; heapsize --)
                    {  max = A[1]; // max is the largest key
                        Fixheap (A,1, A[heapsize], heapsize - 1);
                        A[heapsize]=max;
                    }

         }




void Insertion(int A[], int n) // in reality the elements to be sorted are indexed from
{							   // index 1 to index n

	int i, j, temp;
	A[0] = -32768; //smallest possible integer using 2 bytes integer representation
	for (i = 1; i <= n; i++) {
		j = i;
		while (A[j] < A[j - 1]) 
		{ // swap
			temp = A[j];
			A[j] = A[j - 1];
			A[j - 1] = temp;
			j--;
		}
	}
}
void Merge(int A[], int low, int mid, int high) // we assume that B is a global // variable
{
	int l = low, i = low, h = mid + 1, k; // i is the index corresponding to array B
	while ((l <= mid) && (h <= high)) { // exactly one of the pointers will reach its limit
		if (A[l] <= A[h]) 
		{
		B[i] = A[l]; // push A[l] to B
		l++; //increment l
		}
		else
		{
			B[i] = A[h];
			h++;
		}// we must A[h] to B
		i++;
	} //end while
	// now one of the pointer has reached its limit so we push the remaining
	// elements into B.
	if (l > mid) { // we pushed the remaining elements starting at A[h]
		for (k = h; k <= high; k++)
		{
			B[i] = A[k];
			i++;
		}
	} //end if
	else
	{
		for (k = l; k <= mid; k++) // we push remaining elements starting at A[l]
		{
			B[i] = A[k];
			i++;
		}
	}// end else
// Next we move B[low:high] to A[low:high]
	for (k = low; k <= high; k++) {

		A[k] = B[k];
	} // enf for
} // end algorithm
void Mergesort(int low, int high, int A[])
{
	if (low < high) { // if the sub-list has more than one element
		int mid = (low + high) / 2;
		Mergesort(low, mid, A); // we call Mergesort for the first half
		Mergesort(mid + 1, high, A); //we call Mergesort for the second half
		// at this point the two halves are sorted
		Merge(A, low, mid, high);
	}	
}// end algorithm
int main()

{

	int bounds[6] = { 100, 1000, 10000, 50000, 100000, 200000 };


	cout << "\tMergesort vs. Insertion Sort vs Heapsort time analysis" << endl;

	cout << "Size of Array\t Mergesort(time)\t InsertionSort(time)\t Heapsort(time)" << endl;

	for (int i = 0; i<6; i++) //run for each new size of the array

	{
		time_t timeR; //declare a timer to time how many seconds pass


		int *n = new int[bounds[i]];
		int *copy = new int[bounds[i]];
		int* copy2 = new int[bounds[i]];

		for (int j = 0; j<bounds[i]; j++)

		{

			n[j] = rand() % 10000;
			copy[j] = n[j]; //we need 2 arrays to sort two different times
			copy2[i] = n[j];


		}
	
	cout << bounds[i] << "\t\t\t";

	
	double time1 = (clock()/CLOCKS_PER_SEC);

	Mergesort(0, bounds[i] - 1, n);

	double time2 = (clock()/CLOCKS_PER_SEC);

	cout << time2-time1<< "\t\t\t";

	double time3 = (clock()/CLOCKS_PER_SEC);
	
	Insertion(copy, bounds[i]-1);

	double time4 = (clock()/CLOCKS_PER_SEC);

	cout << time4-time3 << "\t\t\t";

	double time5 = (clock()/CLOCKS_PER_SEC);

	Heapsort(copy2, bounds[i]-1);

	double time6 = (clock()/CLOCKS_PER_SEC);
	
	cout << time6-time5 << "\t\t";

	cout << endl;

	}

	//system("pause");

	return 0;
}