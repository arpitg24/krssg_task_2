#include<iostream>
#include<vector>

using namespace std;

class lift{
    public:
        int floor;
        char state;
};

int move(char state,int floor){
    if(state == 'U'){
        floor++;
    }
    
    if(state == 'D'){
        floor--;
    }

    return floor; 
}

class person{
    public:
        int start,stop;
        char dir;
        int onboard;
};

vector<person>p;

int main(){
    int n;
    cout<<"enter the no. of passengers: ";
    cin>>n;
    int max = -999;
    int min = 999;
    for(int i=0;i<n;i++){
        person temp;
        cin>>temp.start;
        if(temp.start>max){
            max = temp.start;
        }
        if(temp.start<min){
            min = temp.start;
        }
        cin>>temp.dir;
        cin>>temp.stop;
        if(temp.stop>max){
            max = temp.stop;
        }
        if(temp.stop<min){
            min = temp.stop;
        }
        temp.onboard = 0;
        p.push_back(temp);
    }

    lift l1,l2;
    char state_1,state_2;
    l1.floor = 0;
    
    l1.state = 'R';
    l2.state = 'R';

    if(max>0){
        l1.state = 'U';
    }
    if(min<0){
        l2.state = 'D';
    }

    cout<<max<<" "<<min<<endl;

    state_1 = l1.state;
    state_2 = l2.state;

    while(l1.state != 'R'){
        int temp_1 = move(l1.state,l1.floor);
        l1.floor = temp_1;
        for(int i =0;i<n;i++){
            person temp1 = p[i];
            if((temp1.start == l1.floor && temp1.dir == l1.state )&& temp1.onboard == 0){
                cout<<"lift1 picks passenger "<<i<<" from "<<l1.floor<<endl;
                temp1.onboard = 1;
                p[i] = temp1;
            }
            if(temp1.stop == l1.floor && temp1.onboard == 1){
                cout<<"lift1 drops passenger "<<i<<" to "<<l1.floor<<endl;
                temp1.dir = 'R';
                /*temp1.start = -999;
                temp1.stop = -999;*/
                temp1.onboard = 0;
                p[i] = temp1;
            }
        }
        if(temp_1 == max)
            l1.state = 'R';
            //l1.floor = max;
    }

    while(l2.state != 'R'){
        int temp_2 = move(l2.state,l2.floor);
        l2.floor = temp_2;
        for(int i =0;i<n;i++){
            person temp2 = p[i];
            if((temp2.start == l2.floor && temp2.dir == l2.state )&& temp2.onboard == 0){
                cout<<"lift2 picks passenger "<<i<<" from "<<l2.floor<<endl;
                temp2.onboard = 2;
                p[i] = temp2;
            }
            if(temp2.stop == l2.floor && temp2.onboard == 2){
                cout<<"lift2 drops passenger "<<i<<" to "<<l2.floor<<endl;
                temp2.dir = 'R';
                /*temp2.start = -999;
                temp2.stop = -999;*/
                temp2.onboard = 0;
                p[i] = temp2;
            }
        }
        if(temp_2 == min)
            l2.state = 'R';
            //l2.floor = min;
    }

    if(state_1 == 'U'){
        l1.state = 'D';
    }else if(state_1 == 'D'){
        l1.state = 'U';
    }

    if(state_2 == 'U'){
        l2.state = 'D';
    }else if (state_2 == 'D'){
        l2.state = 'U';
    }

    while(l1.state != 'R'){
        int temp_1 = move(l1.state,l1.floor);
        l1.floor = temp_1;
        for(int i =0;i<n;i++){
            person temp1 = p[i];
            if((temp1.start == l1.floor && temp1.dir == l1.state) && temp1.onboard==0){
                cout<<"lift1 picks passenger "<<i<<" from "<<l1.floor<<endl;
                temp1.onboard = 1;
                p[i] = temp1;
            }
            if(temp1.stop == l1.floor && temp1.onboard == 1){
                cout<<"lift1 drops passenger "<<i<<" to "<<l1.floor<<endl;
                temp1.dir = 'R';
                /*temp1.start = -999;
                temp1.stop = -999;*/
                temp1.onboard = 0;
                p[i] = temp1;
            }
        }
        if(temp_1 == min)
            l1.state = 'R';
    }

    while(l2.state != 'R'){
        int temp_2 = move(l2.state,l2.floor);
        l2.floor = temp_2;
        for(int i =0;i<n;i++){
            person temp2 = p[i];
            if((temp2.start == l2.floor && temp2.dir == l2.state) && temp2.onboard==0 ){
                cout<<"lift2 picks passenger "<<i<<" from "<<l2.floor<<endl;
                temp2.onboard = 2;
                p[i] = temp2;
            }
            if(temp2.stop == l2.floor && temp2.onboard == 2){
                cout<<"lift2 drops passenger "<<i<<" to "<<l2.floor<<endl;
                temp2.dir = 'R';
                /*temp2.start = -999;
                temp2.stop = -999;*/
                temp2.onboard = 0;
                p[i] = temp2;
            }
        }
        if(temp_2 == max)
            l2.state = 'R';
    }

}