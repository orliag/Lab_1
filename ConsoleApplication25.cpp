#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <cstdlib>

using namespace std;

class point {
private:
    float pos_x;
    float pos_y;

    void set() {
        cout << "Print x:";
        cin >> pos_x;
        cout << endl;
        cout << "Print y:";
        cin >> pos_y;
        cout << endl;
    }
public:
    point() {
        set();
    }
    
    point(const point& adress) {
        pos_x = adress.pos_x;
        pos_y = adress.pos_y;
    }
    
    void stat() {
        cout << "X = " << setw(5) << pos_x << " Y = " << setw(5) << pos_y << "\n";
    }

    float get_x() {
        return pos_x;
    }

    float get_y() {
        return pos_y;
    }

    
};

class line {
protected:
    vector <point> dots;

    void add_dot() {
        point* new_dot = new point;
        dots.push_back(*new_dot);
        delete new_dot;
    }

    float proj_x(int a, int b) {
        return dots[b].get_x() - dots[a].get_x();
    }
    float proj_y(int a, int b) {
        return dots[b].get_y() - dots[a].get_y();
    }
    float modul_vec(int a, int b) {
        return sqrt(pow(proj_x(a, b), 2) + pow(proj_y(a, b), 2));
    }

public:
    line() {
        add_dot();
        add_dot();
        add_dot();
    }

    line(int n) {
        for (int i = 0; i < n; i++) {
            add_dot();
        }
    }

    line(const line& adress) {
        this->dots = adress.dots;
    }
    
    void stat() {
        cout << "Your dots are:" << "\n";
        for (unsigned int i = 0; i < dots.size(); i++) {
            dots[i].stat();
        }
    }

    float line_len() {
        float len = 0;
        for (unsigned int i = 0; i < dots.size() - 1; i++) {
            len += modul_vec(i, i + 1);
        }
        return len;
    }

};

class closed : public line{
public:
    closed() : line() {
    }

    closed(int n) : line(n) {
    }

    closed(const line& adress) : line(adress) {
    }

    float line_len() {
        float len = 0;
        for (unsigned int i = 0; i < dots.size() - 1; i++) {
            len += modul_vec(i, i + 1);
        }
        len += modul_vec(dots.size() - 1, 0);
        return len;
    }
};

class polygon {
protected:
    vector <point> dots;

    void add_dot() {
        point* new_point = new point;
        dots.push_back(*new_point);
        delete new_point;
    }


    void convexity() {
        bool flag = true;
        unsigned int i, j, k;
        float res, buf = 0;
        for (i = 0; i < dots.size(); i++) {
            j = (i + 1) % dots.size();
            k = (i + 2) % dots.size();
            res = (proj_x(j, k) * proj_y(i, j) - proj_y(j, k) * (proj_x(i, j)));
            if (res * buf < 0) {
                flag = false;
            }
            buf = res;
        }
        
        if (flag == false) {
            cout << "Error: convexity" << '\n';
        }
        else {
            cout << "convexity is good" << '\n';
        }
    }

    float proj_x(int a, int b) {
        return dots[b].get_x() - dots[a].get_x();
    }
    float proj_y(int a, int b) {
        return dots[b].get_y() - dots[a].get_y();
    }
    float modul_vec(int a, int b) {
        return sqrt(pow(proj_x(a, b), 2) + pow(proj_y(a, b), 2));
    }
public:
    polygon() {
        add_dot();
        add_dot();
        add_dot();
        add_dot();
        add_dot();
        cout << "cecking" << endl;
        convexity();
    }
    polygon(int n) {
        if(n >= 3){
            for (int i = 0; i < n; i++) {
                add_dot();
            }
            cout << "cecking" << endl;
            convexity();
        }
        else {
            cout << "Too low" << "\n";
        }
    }
    polygon(const polygon& adress) {
        this->dots = adress.dots;
    }

    void stat() {
        cout << "Your dots are:" << "\n";
        for (unsigned int i = 0; i < dots.size(); i++) {
            dots[i].stat();
        }
    }

    float perimatr() {
        float len = 0;
        for (unsigned int i = 0; i < dots.size() - 1; i++) {
            len += modul_vec(i, i + 1);
        }
        len += modul_vec(dots.size() - 1, 0);
        return len;
    }

    virtual float square() {
        float a = 0, b = 0;
        for (unsigned int i = 0; i < dots.size(); i++) {
            a += dots[i].get_x() * dots[(i + 1) % dots.size()].get_y();
            b += dots[(i + 1) % dots.size()].get_x() * dots[i].get_y();
        }
        return abs(a - b) / 2;
    }

};

class traezoid : public polygon {
protected:

    void pararell() {
        bool flag = false;
        if ((((proj_x(1, 0)) * (proj_y(3, 2))) == ((proj_y(1, 0)) * (proj_x(3, 2)))) or (((proj_x(2, 1)) *(proj_y(0, 3))) == ((proj_y(2, 1)) * (proj_x(0, 3))))) {
            flag = true;
        }

        if (flag == false) {
            cout << "Error: convexity" << '\n';
        }
        else {
            cout << "pararell is good" << '\n';
            
        }
    }


public:
    traezoid() : polygon(4) {
        cout << "cecking pararell" << endl;
        pararell();
    }

    traezoid(const traezoid& adress) : polygon(adress) {
    }

    
};

class triangle : public polygon {
public:
    float square() override {
        cout << "Geron" << endl;
        float p = (modul_vec(0, 1) + modul_vec(1, 2) + modul_vec(2, 0)) / 2;
        return sqrt(p*(p-modul_vec(0, 1)) * (p - modul_vec(1, 2)) * (p - modul_vec(2, 0))) ;
    }

    triangle() : polygon(3) {
    }

    triangle(const triangle& adress) : polygon(adress) {
    }
};

class right_polygon : public polygon {
protected:

    void right() {
        bool flag = true;
        unsigned int i = dots.size() - 1, j = (i + 1) % dots.size(), k = (i + 2) % dots.size();
        float buf = modul_vec(i, j);
        float tangle, buf_tangle = acos(((proj_x(j, i)) * (proj_x(j, k)) + (proj_y(j, i)) * (proj_y(j, k))) / (modul_vec(j, i) + modul_vec(j, k)));
        for (i = 0; i < dots.size(); i++) {
            j = (i + 1) % dots.size();
            k = (i + 2) % dots.size();
            tangle = acos(((proj_x(j, i)) * (proj_x(j, k)) + (proj_y(j, i)) * (proj_y(j, k))) / (modul_vec(j, i) + modul_vec(j, k)));
            if ((modul_vec(i, j) != buf) or (tangle != buf_tangle)) {
                flag = false;
            }
        }
        if (flag == false) {
            cout << "Error: convexity" << '\n';
        }
        else {
            cout << "right is good" << '\n';
        }
    }
public:
    right_polygon() : polygon() {
        cout << "cecking right" << endl;
        right();
    }

    right_polygon(int n) : polygon(n) {
        cout << "cecking right" << endl;
        right();
    }

    right_polygon(const right_polygon& adress) : polygon(adress) {
    }
};

int main()
{

    triangle trio;
    trio.stat();
    cout << "triangle per is:" << trio.perimatr() << "\n";
    cout << "triangle square is:" << trio.square() << "\n";

    cout << "\n";
    cout << "\n";

    point dot;
    point dot2;
    dot.stat();
    dot2.stat();

    cout << "\n";
    cout << "\n";

    line linage;
    line linage2(4);
    linage.stat();
    linage2.stat();
    cout << "Line 1 length is:" << linage.line_len() << "\n";
    cout << "Line 2 length is:" << linage2.line_len() << "\n";

    cout << "\n";
    cout << "\n";

    closed cl_line;
    closed cl_line2(5);
    cl_line.stat();
    cl_line2.stat();
    cout << "closed Line 1 length is:" << cl_line.line_len() << "\n";
    cout << "closed Line 2 length is:" << cl_line2.line_len() << "\n";

    cout << "\n";
    cout << "\n";

    polygon linal;
    polygon linal2(5);
    linal.stat();
    linal2.stat();
    cout << "Polygon 1 per is:" << linal.perimatr() << "\n";
    cout << "Polygon 2 per is:" << linal2.perimatr() << "\n";
    cout << "Polygon 1 square is:" << linal.square() << "\n";
    cout << "Polygon 2 square is:" << linal2.square() << "\n";

    cout << "\n";
    cout << "\n";

    traezoid trap;
    trap.stat();
    cout << "Traezoid per is:" << trap.perimatr() << "\n";
    cout << "Traezoid square is:" << trap.square() << "\n";

    cout << "\n";
    cout << "\n";

    right_polygon cube(4);
    cube.stat();
    cout << "cube per is:" << cube.perimatr() << "\n";
    cout << "cube square is:" << cube.square() << "\n";


    point dots[5];
    for (int i = 0; i < 5; i++) {
        dots[i].stat();
    }



    return 0;
}

