

struct point_c { // Structure of points for priority queue
	int value; // height of a building
	int label; // label or sequance number of a building

	point_c(int lab, int val) // function for declaration for point
	{
		label = lab;
		value = val;
	}
	point_c()
	{
		value = 0;
		label = 0;

	}
	point_c& operator =(const point_c& rhs)  // operator overloading for equal sign
	{
		value = rhs.value;
		label = rhs.label;
		return *this;
	}
	friend bool operator <(const point_c & lhs, const point_c & rhs) { // operator overloading for smaller sign ,returns boolean type
		return (lhs.value < rhs.value);
	}
	friend bool operator >(const point_c & lhs, const point_c & rhs) {// operator overloading for greater sign , returns boolean type
		return (lhs.value > rhs.value);
	}
};




class MPQ { // Modefined Priority Queue 
	int* location;
	point_c* heap;
public:

	/*Constructor*/
	MPQ(int capacity_arr) {
		currentSize = 0; // variable store number of item in queue
		heap = new point_c[capacity_arr + 1]; // dynamically allocated array for heap
		location = new int[capacity_arr + 1]; // dynamically allocated array for location , finding location of given label O(1) complexity
		capacity = capacity_arr; // variable store capacity of heap
	}
	/*Default Constructor*/
	MPQ() {
		currentSize = 0;
		heap = new point_c[101];
		location = new int[101];
		capacity = 100;
	}

	/*Destructor*/
	~MPQ() {
		delete[] heap; // deallocate memory , exist for avoiding memory leak
	}

	int insert(const int & value, const int & label); // insert item(label) which has given value as point_c type 

	point_c Remove(int label); //search element with given label, remove this element from queue (heap)

    int GetMax() { // return maximun value of queue
		if (!IsEmpty()) {
			return(heap[1].value);
		}
	}
	bool isFull() { // if queue is full return true otherwise false
		return(currentSize == capacity);
	}
	bool IsEmpty() { // if queue is empty return true otherwise false
		return (currentSize == 0);
	}
	
private:
	int currentSize; // Number of elements in heap
	int capacity;
	void percolateDown(int hole); // restore heap structure with percolate down point

};

point_c MPQ::Remove(int label) {
	if (IsEmpty()) {
		point_c p(-1, -1);
		return p;
	}
	else {
		point_c deleted_Item = heap[location[label]];
		heap[location[label]] = heap[currentSize--];
		percolateDown(location[label]); // I have changed only one line
		return deleted_Item;
	}

}
int MPQ::insert(const int & value, const int & label)
{
	if (isFull()) {
		return -1;
	}
	else {
		point_c p(label, value);
		// Percolate up
		// Note that instead of swapping we move the hole up
		int hole = ++currentSize;

		for (; hole > 1 && p > heap[hole / 2]; hole /= 2) {
			location[heap[hole / 2].label] = hole;
			heap[hole] = heap[hole / 2];
		}
		location[label] = hole;
		heap[hole] = p;
		return 0;
	}
}

void MPQ::percolateDown(int hole)
{
	int child;
	point_c tmp = heap[hole];

	for (; hole * 2 <= currentSize; hole = child)
	{
		child = hole * 2;
		if (child != currentSize && heap[child + 1] > heap[child]) {
			child++;
		}
		if (heap[child] > tmp) {
			location[heap[child].label] = hole;
			heap[hole] = heap[child];
		}
		else {
			break;
		}
	}
	location[tmp.label] = hole;
	heap[hole] = tmp;
}
