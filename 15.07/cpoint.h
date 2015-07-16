#ifndef CPOINT_H
#define CPOINT_H


class point{

	private:
	int x,y;

	public:
		point(int , int );

		void print();

		int get_x();

		int get_y();

		double get_dist(point* );
//1- the same, 0- different
		int compare(point* );

};



#endif
