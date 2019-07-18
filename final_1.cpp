#include<bits/stdc++.h>
using namespace std;
int max_load=300;
int city[100][100];
int weight[100][100];
int rover_travel[30];
int N=0;
vector<pair<int,int>> shop;

struct rover_type{
      int x,y;
      int travel;
};

struct product_type{
      int p_no;
      string p_name;

};

struct user_type{
      string name;
      int  x,y;
};

vector<user_type> user;

rover_type rover[30];

int get_rover(int shop_no){
      if(shop_no==1){
            for(int i=0;i<10;i++){
                  if(rover_travel[i]==0)
                  return i;
            }
      }
      else if(shop_no==2){
            for(int i=10;i<20;i++){
                  if(rover_travel[i]==0)
                  return i;
            }
      }
      else{
            for(int i=20;i<30;i++){
                  if(rover_travel[i]==0)
                  return i;
            }
      }
      return -1;
}

void newPage(){
      // cout<<"\n";
      for(int i=0;i<500;i++)
      cout<<"\n";
}

void daily_basis(){
      int count=rand()%6 + 4,sum1=0;
            for(int i=0;i<30;i++){
                  if(rover_travel[i] && count--)
                  sum1+=rover_travel[i];
            }
      cout<<"\n Average daily basis income statement: Rs."<<sum1*0.50<<"\n";
}

void monthly_basis(){
      int sum1=0;
      for(int i=0;i<30;i++){
            if(rover_travel[i])
            sum1+=rover_travel[i];
      }
      cout<<"\nAverage Monthly basis income statement: Rs."<<sum1*0.50<<"\n";
}

void business_basis(){
      cout<<"\nbusiness daily/monthly statement\n";
}


//charan's part

void findpath(int sx,int sy,int dx,int dy,int &No_of_Delvery,int currdelvery,string currpath,string &final_path,int w)
{
	if(sx>dx or sy>dy)
		return;
	if(w<0)
		return;
	//Reaching the Destination.
	if(sx==dx and sy==dy)
	{
		if(currdelvery>No_of_Delvery)
		{
			No_of_Delvery=currdelvery;
			final_path=currpath;
		}
		return;
	}
	int x=0;
	if(city[sx][sy]==1)
		x=1;
	//Weight will be added when Weight is less than MaximumWeight.
	if(x==1)
	{
		w = w - weight[sx][sy];
	}
	findpath(sx,sy+1,dx,dy,No_of_Delvery,x+currdelvery,currpath+'R',final_path,w);
	findpath(sx+1,sy,dx,dy,No_of_Delvery,x+currdelvery,currpath+'D',final_path,w);
}

string path(int source_x,int source_y,int destination_x,int destination_y)
{
	string PathString="";
	int No_of_Delvery=0;
	int w = max_load - weight[destination_x][destination_y];
	findpath(source_x,source_y,destination_x,destination_y,No_of_Delvery,0,"",PathString,w);
	//Final Path is stored in PathString.
	return PathString;
}


// shivam






void deliver_all_order(string direction,int source)
{
//	cout<<"hello";
	// the main funda over here is try to deliver all the product with the help of different rover(if needed)
	if(direction=="")
	return;
	int no=get_rover(source);
	int source_x = shop[source].first,source_y = shop[source].second;
	int curr_weight = 0,i = 0,distance = 0,curr_distance = 0,curr_position_x=0,curr_position_y=0;
	while(curr_weight<max_load && i<direction.length())
	{
		while(curr_weight<max_load and i<direction.length())
		{
			
			char move = direction[i];
	
			//update the current direction
			if(move=='L')source_x-=1;
			if(move=='R')source_x+=1;
			if(move=='U')source_y-=1;
			if(move=='D')source_y+=1;
		
			//check if need to deliver over here
			if(city[source_x][source_y]==1 and (curr_weight+weight[source_x][source_y])<max_load)
			{
				if((rover[no].travel+curr_distance)<100000)
				{
					curr_weight += weight[source_x][source_y];
					distance += curr_distance; 
					curr_position_x = source_x;
					curr_position_y = source_y;
					city[source_x][source_y]=0;
					cout<<"\nProduct delivered to: "<<source_x<<" "<<source_y<<"\n";
				}
				else
				{
					continue;
				} 
			}
			curr_distance++;
			i++;
			direction = direction.substr(i);
		}
		

		//update the rover

            
		rover[no].travel+=distance;
		rover[no].x = curr_position_x;
		rover[no].y = curr_position_y;
		
		//update rover travelled diatnce for a perticular product
		// weight[source.first][source.second].rover+=distance;
             rover[no].travel+=distance;
		//this rover is useless now
		//look for another rover

		distance = 0;
		
	}
}






void admin_mode(){
      int flag=1;
      while(flag){
            // newPage();
            cout<<"\n1: Daily basis income statement\n2: Monthly basis income statement\n3: Business daily/monthly statement\n4: Go back\n";
            int chioce;
            cout<<"Enter your choice: ";
            cin>>chioce;
            switch(chioce){
                  case 1: daily_basis();
                          break;
                  case 2: monthly_basis();
                          break;
                  case 3: business_basis();
                          break;
                  case 4: flag=0;
                          break;
                  default:cout<<"\nEnter correct chioce !!!";
                           break;                           
            }
      }
}

void grocery_getdata(){
     shop.push_back(make_pair(0,0));
     shop.push_back(make_pair(10,10));
}


void restaurant(int num){
      cout<<"\nproducte name: abcd        price: 200     weight:5\n";
      int n=200;
      weight[user[num].x][user[num].y]=5;
      city[user[num].x][user[num].y]=0;
      string s= path(shop[0].first,shop[0].second,user[num].x,user[num].y);
//      cout<<s<<"\n";
      deliver_all_order(s,0);
      cout<<"\nProduct delivered to: "<<user[num].x<<" "<<user[num].y<<"\n";
}


void grocery(int num){
      cout<<"\nproducte name: abcde        price: 280     weight:10\n";
      int n=280;
      weight[user[num].x][user[num].y]=10;
      city[user[num].x][user[num].y]=0;
      string s= path(shop[1].first,shop[1].second,user[num].x,user[num].y);
      deliver_all_order(s,1);
      cout<<"\nProduct delivered to: "<<user[num].x<<" "<<user[num].y<<"\n";
}

void user_mode(){
      user_type u;
      string s;
      int flag=1;
      int x_pos,y_pos;
      cout<<"\nEnter your name: ";
      // getline(cin,s);
      cin>>s;
      cout<<"\n Enter location x and y: ";
      cin>>x_pos>>y_pos;
      u.name=s,u.x=x_pos,u.y=y_pos;
      user.push_back(u);
      city[x_pos][y_pos]=1;
      N++;
      int choice;
      while(flag==1){
            cout<<"\n1: Restaurant\n2: Grocery\n3: Go back \n4: exit\n";
            cout<<"Enter your chioce: ";
            cin>>choice;
            switch(choice){
                  case 1: //cout<<"res";
                          restaurant(N-1);
                          break;
                  case 2: grocery(N-1);
                          break;
                  case 3: flag=0;
                          break; 
                  default:cout<<"\nEnter correct choice!!!";
                          break;                       
            }
      }
}

int main(){
      
      //#ifndef ONLINE_JUDGE
      //freopen("output","w",stdout);
      //#endif
         
      grocery_getdata();
      // restaurant_getdata();
      city[0][2]=1,city[1][0]=1,city[2][1]=1,city[2][2]=1,city[5][5]=1,city[55][55]=1,city[99][99]=1;
      
	  weight[0][2]=9,weight[1][0]=6,weight[2][1]=4,weight[2][2]=5,weight[5][5]=5,weight[55][55]=6,weight[99][99]=8;
      
	  rover_travel[1]=6,rover_travel[4]=3,rover_travel[12]=5,rover_travel[21]=2,rover_travel[26]=9,rover;


      int choice;   
      cout<<"  \t\tWelcome To smart city\n\t\t\t -Odessa";
      while(1){
            // newPage();
            cout<<"\n1: Admin Mode\n2: User Mode\n3: Exit\n";
            cout<<"Enter your choice: ";
            cin>>choice;
            switch(choice){
                  case 1: admin_mode();
                        break;
                  case 2: user_mode();
                        break;
                  case 3: //newPage();
                        cout<<"BYE BYE !!!!";
                        exit(0);
                  default:cout<<"\nEnter Valid Number !!!!";
                        break;                         
            }
      }
}
