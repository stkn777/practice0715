#include <cstdio>
#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string.h>

using namespace std;
class point{

	private:
	int x,y;

	public:
		point(int x1, int y1){
			x=x1;
			y=y1;
		}

		void print(){

			cout<<"x = "<<x<<" y = "<<y<<endl;

		}

		int get_x(){

			return x;
		}

		int get_y(){
			return y;
		}

		double get_dist(point* p){

			return sqrt(pow(p->get_y()-this->get_y(),2)+pow(p->get_x()-this->get_x(),2));

		}
//1- the same, 0- different
		int compare(point *p){

			if((this->get_x()==p->get_x())&&(this->get_y()==p->get_y()))
				return 1;

			return 0;
		}

};

int check(vector<point*> point_vec,point*t){

	for(int i=0;i<point_vec.size();i++)
		if(point_vec[i]->compare(t))
			return 0;

	return 1;
}

vector<point*> read_vector( char* filename){
	vector<point*> point_vec;
	char c[256];
	char *c1;
	ifstream file(filename);
	int x,y;
	point *t;
	
	while (!file.eof()){
		file>>x>>y;
		t=new point(x,y);
		if(check(point_vec,t))
			point_vec.push_back(t);
	}
	
	return point_vec;
};


vector<point*> get_cluster(vector<point*> point_vec, double rad){
	
	double matr[point_vec.size()][point_vec.size()];
	vector<point*> cluster;
	int centr_num;
	int vol=0;
	int vol_t;
	for(int i=0;i<point_vec.size();i++)
		for(int j=0; j<point_vec.size();j++)
			matr[i][j]=point_vec[i]->get_dist(point_vec[j]);
			

	for(int i=0;i<point_vec.size();i++){
		vol_t=0;
		for(int j=0; j<point_vec.size();j++)
			if(matr[i][j]<=rad)				
				vol_t+=1;
		

		if(vol_t>vol){
			vol=vol_t;
			centr_num=i;
		}
	}	
		
	for(int i=0;i<point_vec.size();i++){
		if(matr[centr_num][i]<=rad)
			cluster.push_back(point_vec[i]);

	}
	
	return cluster;
}


point* get_mass_center(vector<point*> cluster){
	double x_c=0;
	double y_c=0;

	for(int i=0; i<cluster.size();i++){
		x_c+=cluster[i]->get_x();
		y_c+=cluster[i]->get_y();
	}

	return new point((int)(x_c/cluster.size()),(int)(y_c/cluster.size()));


}
//границы изображения
vector<point*> get_bounds(vector<point*> cluster){
	int mx,my,max,may;
	vector<point*> answ;


	mx=cluster[0]->get_x();
	my=cluster[0]->get_y();
	may=cluster[0]->get_y();
	max=cluster[0]->get_x();
	for(int i=0;i<cluster.size();i++){
		if(mx>cluster[i]->get_x())
			mx=cluster[i]->get_x();

		if(my>cluster[i]->get_y())
			my=cluster[i]->get_y();

		if(max<cluster[i]->get_x())
			max=cluster[i]->get_x();

		if(may<cluster[i]->get_y())
			may=cluster[i]->get_y();		

	}
	answ.push_back(new point(mx,my));
	answ.push_back(new point(max,may));
	return answ;


}

void draw_points(vector<point*> full_size, vector<point*> main_points, vector<point*> bounds, char* filename){

	ofstream file(filename);
	int x; int y;
	x=full_size[1]->get_x();
	y=full_size[1]->get_y();
	int ymin,ymax,xmax,xmin;

	ymin=bounds[0]->get_y();
	xmin=bounds[0]->get_x();

	ymax=bounds[1]->get_y();
	xmax=bounds[1]->get_x();

	int matr[x][y];
	//cout<<ymin<<" "<<xmin<<" "<<ymax<<" "<<xmax<<endl;
	file<<"P3"<<endl<<y<<" "<<x<<endl<<255<<endl;

	for(int i=0;i<x;i++)
		for (int j=0;j<y;j++){
			matr[i][j]=0;

			if((i+1>=xmin)&&(i+1<=xmax)&&((j+1==ymin)||(j+1==ymax)))
							matr[i][j]=1;
			
			if ((j+1>=ymin)&&(j+1<=ymax)&&((i+1==xmin)||(i+1==xmax)))
				matr[i][j]=1;
		}
	

	for(int i=0;i<main_points.size();i++)
		matr[main_points[i]->get_x()-1][main_points[i]->get_y()-1]=2;


	point* t;

	t=get_mass_center(main_points);

	matr[t->get_x()-1][t->get_y()-1]=3;

	
	for(int i=0;i<x;i++)
		for (int j=0;j<y;j++){
			switch(matr[x-1-i][j]){

				case 0: 
					file<<"255 255 255"<<endl;
					break;
				case 1: 
					file<<"100 100 100"<<endl;
					break;
				case 2: 
					file<<"0 0 0"<<endl;
					break;
				case 3:
					file<<"200 0 0"<<endl;
					break;
				default:break;

			}


		}
		
	
	file.close();



}

int main(int argc, char *argv[]){

	double rad;

	vector<point*> point_vec;
	vector<point*> cluster;
	vector<point*> bounds;
	point_vec= read_vector(argv[1]);


	/*for(int i=0;i<point_vec.size();i++)
		point_vec[i]->print();*/

	rad=atoi(argv[2]);

	
	cluster=get_cluster(point_vec,rad);
	cout<<"список точек:"<<endl;
	for(int i=0;i<cluster.size();i++)
		cluster[i]->print();


	cout<<endl<<"Центр масс: ";
	get_mass_center(cluster)->print();

	bounds= get_bounds(cluster);

	cout<<endl<<"Границы прямоугольной области:"<<endl;
	for(int i=0;i<bounds.size();i++)
		bounds[i]->print();

	cout<<"Длина границ: "<<bounds[1]->get_x()-bounds[0]->get_x()<<"x"<<bounds[1]->get_y()-bounds[0]->get_y()<<endl;

	draw_points(get_bounds(point_vec),cluster,bounds,argv[3]);

	return 0;



}
