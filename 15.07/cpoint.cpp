#include <iostream>
#include "cpoint.h"
#include <math.h>
using namespace std;


point::point(int x1, int y1){
			x=x1;
			y=y1;
		}

void point::print(){

			cout<<"x = "<<x<<" y = "<<y<<endl;

		}

int point::get_x(){

			return x;
		}

int point::get_y(){
			return y;
		}

double point::get_dist(point* p){

			return sqrt(pow(p->get_y()-this->get_y(),2)+pow(p->get_x()-this->get_x(),2));

		}
//1- the same, 0- different
int point::compare(point *p){

			if((this->get_x()==p->get_x())&&(this->get_y()==p->get_y()))
				return 1;

			return 0;
		}
