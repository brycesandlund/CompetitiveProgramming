#include <iostream>

int main() {

    input s[n], t[m]		#the index is begin with 0
    sort(s)				#sort in descending order
    sort(t)				#sort in descending order
    available_last_seat = m - 1	#last available seat's index
    cur_seat = 0			#current seat index
    round_done = 0			#round have done
    for (int i = 0; i < n; ++i){
        if (s[i] > available_last_seat + 1) return false;
        while (cur_seat + s[i] > available_last_seat){
            s[i] = cur_seat + s[i] - (available_last_seat + 1);
            cur_seat = 0;
            ++cur_round;
            while (available_last_seat >= 0 && t[available_last_seat] == cur_round)
                --available_last_seat;
            if (available_last_seat == -1){
                if (s[i] != 0) return false;
                break;
            }
        }
        cur_seat = cur_seat + s[i];
    }
    return true;

}
