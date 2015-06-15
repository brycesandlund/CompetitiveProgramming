#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>

#define EP 1e-10

using namespace std;

typedef long long ll;

double calc_cat_perc(double sec, ll j, ll R) {
    return sec * j / (2*M_PI*R);
}

double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

double calc_mouse_time(double cat_perc, ll t, double r, ll R) {
    double theta = cat_perc * 2 * M_PI;
    double x = R * cos(theta);
    double y = R * sin(theta);

    //cerr << "theta: " << theta << " x: " << x << " y: " << y << endl;

    double d = dist(-r, 0, x, y);
    return d / t;
}

double func_val(double sec, ll j, ll R, double r, ll t) {
    double cat_perc = calc_cat_perc(sec, j, R);
    double mouse_time = calc_mouse_time(cat_perc, t, r, R);

    return sec - mouse_time;
}

int main() {
    ll T;
    cin >> T;

    for (ll cs = 1; cs <= T; ++cs) {
        ll R, t, j;
        cin >> R >> t >> j;

        double r = (double)t*R / j;
        double sec_straight = (R-r) / t;

        //cerr << "r: " << r << " R: " << R << endl;

        bool success;
        if (r > R+EP) {
            success = true;
        }
        else {
            double cat_perc = calc_cat_perc(sec_straight, j, R);
            
            //cerr << cat_perc << endl;
            double y = -sqrt(R*R - r*r);
            double theta = atan2(y, -r) + 2 * M_PI;
            double perc_upper = theta / (2*M_PI);
            //cerr << perc_upper << endl;
            
            if (cat_perc < .5 - EP) {
                success = true;
            }
            else if (cat_perc >= perc_upper - EP) {
                success = false;
            }
            else {
                double mouse = calc_mouse_time(perc_upper-EP, t, r, R);
                double val = func_val(mouse, j, R, r, t);
                if (val > EP)
                    success = true;
                else
                    success = false;
            }
            /*else {
                double lo = calc_mouse_time(.5, t, r, R);
                double hi = calc_mouse_time(perc_upper, t, r, R);

            //    cerr << lo << " " << hi << endl;

                success = false;
                while (hi - lo > EP) {
                    double m1 = 2.0/3 * lo + 1.0/3 * hi;
                    double m2 = 1.0/3 * lo + 2.0/3 * hi;

                    double val_m1 = func_val(m1, j, R, r, t);
                    double val_m2 = func_val(m2, j, R, r, t);
                    
                //    cerr << "val_m1: " << val_m1 << " val_m2: " << val_m2 << endl;
                    
                    if (val_m1 > EP || val_m2 > EP) {
                        success = true;
                        break;
                    }

                    if (val_m1 < val_m2) {
                        lo = m1;
                    }
                    else {
                        hi = m2;
                    }
                }
            }*/
        }

        if (success)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}
