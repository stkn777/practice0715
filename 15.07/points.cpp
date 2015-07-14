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

void draw_points(vector<point*> full_size, vector<point*> main_points,  char* filename){

	ofstream file(filename);
	int x; int y;
	x=full_size[1]->get_x();
	y=full_size[1]->get_y();
	vector<point*> bounds;
	bounds = get_bounds(main_points);
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

class color{
public:
	int r,g,b;


	color(int r, int g, int b){
		this->r=r;
		this->g=g;
		this->b = b;

	}

	void print(){

		cout<<this->r<<" "<<this->g<<" "<<this->b<<endl;

	}

	int compare(color *c){

		if((this->r!=c->r)||(this->g!=c->g)||(this->b!=c->b))
			return 0;

		return 1;
	}

};



vector<point*> get_color_points(char* fl, int* color){
	vector<point*> p;
	
	ifstream file(fl);
	point *t;
	int x,y,temp;
	int *c=new int[3];
	string s;
	
	getline(file,s);
	file>>y>>x>>temp;
	
	
	for(int i=x;i>0;i--)
		for(int j=1;j<=y;j++){
			file>>c[0]>>c[1]>>c[2];
			
			if((c[0]==color[0])&&(c[1]==color[1])&&(c[2]==color[2])){
				t=new point(i,j);
				p.push_back(t);
			}


		}

	return p;
}

void write_file(vector<point*> p, char* fn){
	ofstream file(fn);
	
	for(int i=0;i<p.size();i++)
		file<<p[i]->get_x()<<" "<<p[i]->get_y()<<endl;

	file.close();

}


void draw_rect(char * fn, vector<point*> p){
	ifstream file(fn);
	color *c;

	char of[]="repainted.pnm";
	int x,y,temp,r,g,b;
	string s;
		
	color *white=new color(255,255,255);

	vector<point*> bounds;
	bounds = get_bounds(p);
	int ymin,ymax,xmax,xmin;

	ymin=bounds[0]->get_y()-1;
	xmin=bounds[0]->get_x()-1;

	if(ymin>=1) ymin-1;
	if(xmin>=1) xmin-1;

	ymax=bounds[1]->get_y()+1;
	xmax=bounds[1]->get_x()+1;

	if(ymax<=x-2) ymax+1;
	if(xmax<=x-2) xmax+1;

	getline(file,s);
	file>>y>>x>>temp;

	color *matr[x][y];

	for(int i=x-1;i>=0;i--)
		for(int j=0;j<y;j++){
			file>>r>>g>>b;

			matr[i][j]=new color(r,g,b);
			if((i+1>=xmin)&&(i+1<=xmax)&&((j+1==ymin)||(j+1==ymax)))
				if(matr[i][j]->compare(white))
					matr[i][j]=new color(100,100,100);
			
			if ((j+1>=ymin)&&(j+1<=ymax)&&((i+1==xmin)||(i+1==xmax)))
				if(matr[i][j]->compare(white))
					matr[i][j]=new color(100,100,100);


		}

	file.close();

	ofstream f(of);


	f<<"P3"<<endl<<y<<" "<<x<<endl<<255<<endl;

	for(int i=x-1;i>=0;i--)
		for(int j=0;j<y;j++){
			f<<matr[i][j]->r<<" "<<matr[i][j]->g<<" "<<matr[i][j]->b<<endl;

		}

		f.close();


}

int main(int argc, char *argv[]){

	double rad;

	vector<point*> point_vec;
	vector<point*> yellow;


	char fn[]="man.pnm";
	char fon[]="datayellow";
	int *color=new int[3];
	color[0]=255;
	color[1]=255;
	color[2]=0;

	point_vec=get_color_points(fn,color);

	write_file(point_vec,fon);

	yellow=get_cluster(point_vec,5);

	cout<<"Желтый объект: "<<endl;

	for(int i=0;i<point_vec.size();i++)
		point_vec[i]->print();


	draw_rect(fn,yellow);

	return 0;



}
