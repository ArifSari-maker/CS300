
#include <iostream>
#include <fstream>
#include <sstream>
#include<string>
#include "ModefinedPriorityQueue.h"
using namespace std;

/* Arif Kemal Sari 28999
   city skyline implementation code
   reading point from input.txt
   input.txt should be given order first line number of buildings other lines
   first element left side of building middle element height of building last element right side of building
   3
   10 20 20
   20 30 40
   30 30 50
   printing changing point (standart:out)
*/
struct point {
	int value; // coordinat of x
	char right_left; // right side or left side of a building , if left side point value is l , otherwise r.
	int label; // label or sequance number of a building
	int height; // height of given point

	point & operator =(const point& rhs)// operator overloading for equal sign 
	{
		value = rhs.value;
		right_left = rhs.right_left;
		label = rhs.label;
		height = rhs.height;
		return *this;
	}
	friend bool operator <(const point & lhs, const point & rhs) { // operator overloading for smaller sign ,returns boolean type
		return (lhs.value < rhs.value);
	}
	friend bool operator >(const point & lhs, const point & rhs) {// operator overloading for greater sign , returns boolean type
		return (lhs.value > rhs.value);
	}
};

void point_declaration(point & p,int value , int label, char right_left, int height){ // point declaration for given point
	
	p.value = value;
	p.right_left = right_left;
	p.label = label;
	p.height = height;
	
}

inline int leftChild(int i)
{
	return 2 * i + 1;
}


// for deleteMax
	  // a is the array, i is the position to percolate down from
	  // n is the logical size of the array
void percDown(point* & a, int i, int n)// percolate down  function for heapsort algorithm
{
	int child;
	point tmp;

	for (tmp = a[i]; leftChild(i) < n; i = child)
	{
		child = leftChild(i);
		if (child != n - 1 && a[child] < a[child + 1])
			child++;
		if (a[child] > tmp)
			a[i] = a[child];
		else
			break;
	}
	a[i] = tmp;
}
void swap(point & a, point & b) { // swap function for heapsort algorithm
	point temp = a;
	a = b;
	b = temp;
}
void heapsort(point* & a,int size) // heapsort algorithm for sorting given point array
{
	// buildHeap
	for (int i = size / 2; i >= 0; i--)
		percDown(a, i, size);

	// sort
	for (int j = size - 1; j > 0; j--)
	{
		swap(a[0], a[j]);  // swap max to the last pos.
		percDown(a, 0, j); // re-form the heap
	}
}

int main()
{ 

	fstream new_file;
	
	new_file.open("input.txt", ios::in);
	if (new_file.is_open()) { // checking file open or not
		string line;
		int num_buildings;
		int label = 1;
		getline(new_file, line);
		istringstream iss(line);
		iss >> num_buildings; // using string stream read every line
		int size_array = 2 * num_buildings;
		point* arr_buildings = new point[size_array];
	
		int location = 1;
		point p1;
		point p2;
		while (getline(new_file, line)) { // read file line by line 
			
			int x_left, height, x_right;
			istringstream iss(line);
			iss >> x_left>>height>>x_right;
			if (location < size_array) {
				point_declaration(p1, x_left, label, 'l', height);
				point_declaration(p2, x_right, label, 'r', height);
				arr_buildings[location - 1] = p1;
				arr_buildings[location] = p2;

			}
			label += 1; // label as sequence number
			location += 2; // location of array
		}
		new_file.close();
		
		heapsort(arr_buildings, size_array); // sorting array in ascending order
		MPQ q(size_array); // modefined priority queue for finding maximum heigth
		int max = 0;
		if (arr_buildings[0].value != 0) {
			cout << 0 << " " << 0 << endl;
		}
		
		for (int i = 0; i < size_array; i++) { // sweep left to rigth 
			if (arr_buildings[i].right_left == 'l') { // if point is left side of building insert to qeueue 
				q.insert(arr_buildings[i].height, arr_buildings[i].label);

			}
			
			else {
				q.Remove(arr_buildings[i].label);	// if point is right side of building remove form queue
			}
			while (i + 1 < size_array&& arr_buildings[i].value == arr_buildings[i + 1].value) { // checking overlapping points
				i += 1;
				if (arr_buildings[i].right_left == 'l') {
					q.insert(arr_buildings[i].height, arr_buildings[i].label);
				}
				else
				{
					q.Remove(arr_buildings[i].label);
				}
			}
			if (!q.IsEmpty()) { 
				if (max != q.GetMax()) { // if maximum change ,print changing point of skyline
					max = q.GetMax();
					cout << arr_buildings[i].value << " " << q.GetMax()<< endl;
				}
			}
			else {
				if (!(i + 1 < size_array&&arr_buildings[i].value == arr_buildings[i + 1].value)) {
					cout << arr_buildings[i].value << " " <<0<< endl;
					max = 0;
				}
				
			}
			
		}

		
	}
	else {
		cout << "No such file"<<endl;
	}



	return 0;
}
