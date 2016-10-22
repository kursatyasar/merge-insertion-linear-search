#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <string>
#include <math.h>
#include <limits>
#include <ctime>

using namespace std;

struct places {
	int number, x, y;

};
void yazdir(places*, int);
void linear_search(places *, places *, int, int, int, int);
void insertion_sort(places *, int, int, int);
int euclidean(int x, int y, int given_x, int given_y);
void merge_sort(places *, int , int, int, int);
void merge(places *, int, int, int, int, int);	//merge birleþtime fonksiyonu


int main(int argc, char **argv) {
	
	clock_t Time;

	char *dosyaadi;
	FILE *place;
	

	if (argc != 6){			//girdide hata olmasýný engellemek için
		cout << endl << "please check your input you have to enter 5 input" << endl;
		return 0;

	}

	if (atoi(argv[1]) > 1000000 || atoi(argv[1]) <= 0 || atoi(argv[2])>atoi(argv[1]) || atoi(argv[2]) <=0) {
		cout << endl << "please check your inputs there are some wrong inputs" << endl;
		return 0;
	}

	


	int Array_Length = atoi(argv[1]);	//ilk ve ikinci deðerlerini K ve N olarak atýyoruz
	int closest_length = atoi(argv[2]);

	int x_place = atoi(argv[4]);		//x ve y verileri terminalden alýnýyor
	int y_place = atoi(argv[5]);

	string secim = argv[3];
	

	places *array=new places[Array_Length];
	places *closest = new places[closest_length];
	ifstream readfile;
	readfile.open("warehouselocations.txt");

	for (int i = 0; i < Array_Length; i++) {

		readfile >> array[i].number;
		readfile >> array[i].x;
		readfile >> array[i].y;

	
	}

	if (secim == "MS") {		//merge short mu istiyor diye bakýyoruz.
		Time = clock();
		merge_sort(array, 0, Array_Length, x_place, y_place);
		Time = clock() - Time;					//fonksiyonda önce bulduðumuz zamaný sonrakinden çýkarýp aradaki zamaný buluyoruz
		cout <<endl<< "Sorting in MS "<<Array_Length<<" numbers takes "<< ((float)Time) / CLOCKS_PER_SEC <<endl << "You can find sorted list in output.txt" << endl;
		yazdir(array, closest_length);



	}


	else if (secim == "IS") {
		Time = clock();
		insertion_sort(array, Array_Length, x_place, y_place);
		Time = clock() - Time;
		cout << endl << "Sorting in IS " << Array_Length << " numbers takes " << ((float)Time) / CLOCKS_PER_SEC << endl<<"You can find sorted list in output.txt"<<endl;
		yazdir(array, closest_length);


	}
	
	else if (secim == "LS") {

		for (int i = 0; i < closest_length; i++) {

			closest[i] = array[i];
		}
		Time = clock();
		linear_search(array, closest, Array_Length, closest_length, x_place, y_place);
		Time = clock() - Time;
		cout << endl << "Sorting in LS " << Array_Length << " numbers takes " << ((float)Time) / CLOCKS_PER_SEC << endl << "You can find sorted list in output.txt" << endl;
		yazdir(closest, closest_length);
	}
	else {
		cout << "wrong short type";
		return 0;
	}
		
	
	readfile.close();
	

	

	
	

	system("pause");
}

void merge_sort(places *array, int p, int r, int given_x, int given_y) {
	if (p < r) {
		int mid = p+((r-p) / 2);
		merge_sort(array, p, mid,given_x,given_y);			//iki parçaya ayýrýp kendini tekrar çaðýrýyor.
		merge_sort(array, mid + 1, r, given_x, given_y);
		merge(array, p, mid, r, given_x, given_y);
	}


}


void merge(places* array, int p, int middle, int r, int given_x, int given_y) { //sýlayýp tekrar birleþtimeyi yapan fonksiyon

	int n1 = (middle - p) + 1;
	int n2 = (r - middle);

	places *left = new places[n1];
	places *right = new places[n2];

	for (int i = 0; i < n1; i++)
	{
		left[i].number = array[p + i].number;		// bu kýsýmlarý left[i]=array[p+i] þeklinde yazabilirdim.
		left[i].x = array[p + i].x;
		left[i].y = array[p + i].y;
	}
	for (int j = 0; j < n2; j++)
	{
		right[j].number = array[middle + j + 1].number;
		right[j].x = array[middle + j + 1].x;
		right[j].y = array[middle + j + 1].y;
	}


	int i = 0, j = 0, k = p;

	while (i < n1 && j < n2)
	{
		int a = euclidean(left[i].x, left[i].y, given_x, given_y);
		int b = euclidean(right[i].x, right[i].y, given_x, given_y);
		if (a <= b)
		{
			array[k].number = left[i].number;
			array[k].x = left[i].x;
			array[k].y = left[i].y;
			i++;
		}
		else
		{
			array[k].number = right[j].number;
			array[k].x = right[j].x;
			array[k].y = right[j].y;
			j++;
		}
		k++;
	}

	while (i < n1) {
		array[k].number = left[i].number;
		array[k].x = left[i].x;
		array[k].y = left[i].y;
		i++;
		k++;
	}

	while (j < n2) {
		array[k].number = right[j].number;
		array[k].x = right[j].x;
		array[k].y = right[j].y;
		j++;
		k++;
	}

	delete left;
	delete right;
}



int euclidean(int x, int y, int given_x, int given_y) {			//bize verilen x ve y verilerine göre dosyadaki x,y verileri arasýdnaki uzaklýðý bulur.
																// karekökünü almadým gerek yoktu.
	return (pow(given_x - x, 2) + pow(given_y - y, 2));



}

void insertion_sort(places *array, int length, int given_x, int given_y) {
	int j;
	places temp;

	for (int i = 0; i < length; i++) {
		j = i;
		while (j > 0 && euclidean(array[j].x, array[j].y, given_x, given_y) < euclidean(array[j - 1].x, array[j - 1].y, given_x, given_y)) {
			temp = array[j];
			array[j] = array[j - 1];
			array[j - 1] = temp;
			j--;
		}
	}
}


void linear_search(places * array, places * closest, int a_count, int c_count, int given_x, int given_y) {
	places temp;
	for (int i = 0; i < a_count; i++) {
		for (int j = 0; j < c_count; j++) {
			if (euclidean(array[i].x, array[i].y, given_x, given_y) < euclidean(closest[j].x, closest[j].y, given_x, given_y)) {

				closest[j] = array[i];
				break;
			}
			

		}

	}

}


void yazdir(places *array, int array_length) {
	ofstream writefile;					//output dosyasýný açýp sonuçlarý ayzdýrýyor.
	writefile.open("output.txt");
	for (int i = 0; i < array_length; i++) {
		writefile << array[i].number<<"\t";
		writefile << array[i].x << "\t";
		writefile << array[i].y << "\n";
		
	}
	writefile.close();
}