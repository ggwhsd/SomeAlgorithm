#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <cstring>
#include <string> 
using namespace std;

//这个思维方式就是，
//如果有1、2、3，那么第一步就是将1、2看做一个整体，从A搬到B，3从A搬到C，然后1、2再作为一个整体从B搬到C
//因为1、2从A搬到B，借助于C，这一步递归的含义就是再将1从A到C，2从A到B，1从B到C。
//move n from A to C, can use B to cache
void hanoi(int n, char A, char B, char C)
{
    if(n==1)
    {
        cout<<"Move sheet "<<n<<" from "<< A <<" to "<< C <<"\n";
    }
    else
    {
        hanoi(n-1,A,C,B);
        cout<<"Move sheet "<< n <<" from "<< A <<" to "<< C <<"\n";
        hanoi(n-1,B,A,C);
    }

}

void hanoiTest()
{
    int n ;
    cout<<"请输入多少个hanoi"<<endl;
    cin>>n;
    hanoi(n,'A','B','C');
}


//费氏数列，可以理解为一个生长过程，每个生物都要经历一个成长期才能进入生产期，
// 下一次总数等于当前总数加上上一次总数，因为上一次总数将是下一次的增长数
void Fibonacci()
{
    int n ;
    cout<<"请输入多少代"<<endl;
    cin>>n;
    int *fib = new int[n]{0};
    int i =0;
    fib[0] = 1;
    fib[1] = 1;
    for(i=2;i<n;i++)
    {
        fib[i] = fib[i-1]+fib[i-2];
    }

    for(i=0;i<n;i++)
    {
        cout<<i<<"天="<<fib[i]<<"只兔子"<<endl;
    }


}
//巴斯卡三角形，我对其的理解意义在于概率的快速计算，比如一个硬币，ab两面
//其组合1A 1B
//若两次扔出，可能的组合（不考虑顺序） 1AA 2Ab 1BB
//3次，1AAA 3AAB 3BBA 1BBB
//依次类推
//同时也是二项式计算，(a+b)的平方\3\4等等次方。
//n从0算起，r从0算起
long combi(int n , int r)
{
    int i ;
    long p = 1;
    for(i = 1; i<=r; i++)
    {
        p = p*(n-i+1)/i;
    }
    return p;
}

void combiTest()
{
    int n,r,t;
    const int N = 10;
    for(n=0;n<=N;n++)
    {
        for(r=0;r<=n;r++)
        {
            int i;
            if(r==0)
            {
                //每行行首
                for(i=0;i<=(N-n);i++)
                {
                    cout<<"    ";
                }
            }
            else{
                cout<<"    ";
            }
            printf("%3d",combi(n,r));
        }
        cout<<"\n";
    }
}



//走迷宫(递归方式)
//走过一个格子就标志位1，找到一条满足的路径，则结束。
//数组传入，需要标明列宽
int VisitRoad(int (*maze)[7],int i, int j,int endI,int endJ,int &success)
{
    maze[i][j] = 1;
    cout<<"visit: "<<i<<"-"<<j<<endl;
    if(i == endI && j == endJ)
    {
        success = 1;
    }
    

    if( success!=1 && maze[i][j+1]==0)
        VisitRoad(maze,i,j+1,endI,endJ,success);
    if( success!=1 && maze[i+1][j]==0)
        VisitRoad(maze,i+1,j,endI,endJ,success);
    if( success!=1 && maze[i][j-1]==0)
        VisitRoad(maze,i,j-1,endI,endJ,success);
    if( success!=1 && maze[i-1][j]==0)
        VisitRoad(maze,i-1,j,endI,endJ,success);
    
    //如果四个格子递归都没有成功，则返回当前，重置当前状态为0，准备退回上一步
    if(success != 1)
        maze[i][j] = 0;

    return success;
}

//数组传入，使用指针，无需定义列宽，但是这种方法的前提是数组得是连续的，如果二维数组并非连续则不能这样使用
void DisplayRoad(int *maze,int w,int h)
{
    int i ,j;
    cout<<"显示迷宫：\n"<<endl;
    for(i =0; i<w; i++)
    {
        for(j=0;j<h;j++)
        {
            if(*(maze+h*i+j)==2)
            {
                //墙壁
                cout<<"*";
            }
            else if(*(maze+h*i+j)==1)
            {
                //标记路径
                cout<<"◇";
            }
            else
            {
                //路
                cout<<" ";
            }
        }
        cout<<"\n";
    }
}

//返现一条路径
void FindRoadTest()
{
    
    int maze[7][7]= {   {2, 2, 2, 2, 2, 2, 2},
                        {2, 0, 0, 0, 0, 0, 2},
                        {2, 0, 2, 0, 2, 0, 2},
                        {2, 0, 0, 2, 0, 2, 2},
                        {2, 2, 0, 2, 0, 2, 2},
                        {2, 0, 0, 0, 0, 0, 2},
                        {2, 2, 2, 2, 2, 2, 2}};
    int startI = 1, startJ = 1;
    int endI = 5, endJ = 5;
    int success = 0 ;
    DisplayRoad((int *)maze,7,7);
    
    if(VisitRoad(maze,startI,startJ,endI,endJ,success)==0)
    {
        cout<<"\n没有找到出口"<<endl;
    }
    else
    {
        cout<<"\n找到路径:\n";
        DisplayRoad((int *)maze,7,7);
    }
   
}


//走迷宫(递归方式)
//走过一个格子就标志位1，找到所有满足的路径。
//数组传入，需要标明列宽
int VisitRoad2(int (*maze)[9],int i, int j,int endI,int endJ,int &success)
{
    maze[i][j] = 1;
    cout<<"visit: "<<i<<"-"<<j<<endl;
    if(i == endI && j == endJ)
    {
        success = 1;
    }
    

    if( maze[i][j+1]==0)
        VisitRoad2(maze,i,j+1,endI,endJ,success);
    if(  maze[i+1][j]==0)
        VisitRoad2(maze,i+1,j,endI,endJ,success);
    if( maze[i][j-1]==0)
        VisitRoad2(maze,i,j-1,endI,endJ,success);
    if(  maze[i-1][j]==0)
        VisitRoad2(maze,i-1,j,endI,endJ,success);
    
   

    
}
//返现一条路径
void FindRoad2Test()
{
    
    int maze[9][9] = {{2, 2, 2, 2, 2, 2, 2, 2, 2},
                        {2, 0, 0, 0, 0, 0, 0, 0, 2},
                        {2, 0, 2, 2, 0, 2, 2, 0, 2},
                        {2, 0, 2, 0, 0, 2, 0, 0, 2},
                        {2, 0, 2, 0, 2, 0, 2, 0, 2},
                        {2, 0, 0, 0, 0, 0, 2, 0, 2},
                        {2, 2, 0, 2, 2, 0, 2, 2, 2},
                        {2, 0, 0, 0, 0, 0, 0, 0, 2},
                        {2, 2, 2, 2, 2, 2, 2, 2, 2}};

    int startI = 1, startJ = 1;
    int endI = 7, endJ = 7;
    int success = 0 ;
    DisplayRoad((int *)maze,9,9);
    
    VisitRoad2(maze,startI,startJ,endI,endJ,success);
    if(success!=1)
    {
        cout<<"\n没有找到出口"<<endl;
    }
    else
    {
        cout<<"\n找到路径:\n";
        DisplayRoad((int *)maze,9,9);
    }
   
}

class EightQueue
{
public:
    const static int N = 8;
        int column[N]; //同一列是否有其他皇后,从1位置开始
        int rup[2*N+1]; //右上角左下角是否有，右斜杠，一共十五条，从左上角的格子算作第一根。 数组的前两个不使用，从第三个位置开始使用，即2
        int lup[2*N+1]; //左上角右下角是否有，左斜杠，也是15条，从右上角的格子算作第一根按照从小打到排序。数组的前两个不使用，从第三个位置开始使用，即2，即lup[2]对应第一根线。
        int queen[N+1] = {0};  //8个皇后所在位置
        int num;

public:
    void ShowAnswer()
    {
        int x,y;
        cout<<"\n解答:"<<++num<<"\n";
        for(y=1;y<=N;y++)
        {
            for(x=1;x<=N;x++)
            {
                if(queen[y]==x)
                {
                    cout<<"★ ";
                }
                else
                    cout<<"☆ ";
            }
            cout<<"\n";
        }
    }

    void backtrack(int irow)
    {
        int j;
        if(irow>N)
        {
            ShowAnswer();
        }
        else{
            for(j=1;j<=N;j++)
            {
                //第一列没有皇后，第irow+j条右斜线没有皇后，第irow-j+N条左斜线没有皇后
                if(column[j] == 1 && rup[irow+j] == 1 && lup[irow-j+N]==1)
                {
                    //这一行，可以放皇后irow
                    queen[irow]=j;
                    //皇后放置后，对应的列，斜线都得占有
                    column[j]=rup[irow+j] = lup[irow-j+N]=0;
                    //继续在下一行放下一个皇后
                    backtrack(irow+1);
                    //取消皇后放置在该位置，继续下一次回溯准备
                    column[j]=rup[irow+j]=lup[irow-j+N]=1;
                }
            }
        }
    }
//八个皇后相安无事的摆放方法
     void EightQueueTest()
    {
        
        int i =0;
        num = 0;
        for(i = 1; i<=N; i++)
        {
            column[i] = 1;
        }
        for(i=1; i<=2*N; i++)
        {
            rup[i] = lup[i] = 1;
        }
        //初始化过程完成。

        backtrack(1);
    }

    static void Test()
    {
        EightQueue* p = new EightQueue();
        p->EightQueueTest();
        delete p;
    }
};


/// @brief 8个硬币，用最少次数找出哪个是和其他硬币不一样，并且该硬币是轻了还会重了。
/// 实际上扩展到n个硬币的话，我觉得，可以是在此基础上，每次分8堆，然后将没堆看做一个硬币，找到假的那个，接着将这堆包含假币的小堆再分成8个小，依次递归。
class EightCoin
{
    private:
        int coins[8]={0};
        int i;
    public:
        void compare(int coins[], int i,int j,int k)
        {
           int heavy = i;
           int light = j;
           if(coins[i]<coins[j])
            {
                heavy = j;
                light = i;
            }

            if(coins[heavy]>coins[k])
            {
                
                cout<<"\n假币位置 "<<heavy+1<<" 较重";
            }
            else
            {
                cout<<"\n假币位置 "<<light+1<<" 较轻";
            }
        }
        void eightcoins(int coins[])
        {
            if(coins[0]+coins[1]+coins[2] == coins[3]+ coins[4]+coins[5])
            {
                compare(coins,6,7,0);
            }
            else if(coins[0]+coins[1]+coins[2] > coins[3]+ coins[4]+coins[5])
            {
                if(coins[0]+coins[3] == coins[1]+ coins[4])
                {
                    compare(coins,2,5,0);
                }
                else if(coins[0]+coins[3] > coins[1] + coins[4])
                {
                    //将1和3硬币换了顺序后，依然是左边大于右边，说明1和3不影响平衡，1、3都是真。
                    compare(coins,0,4,1);
                }
                if(coins[0]+coins[3] < coins[1]+coins[4])
                {
                    //将1和3硬币换了顺序后，左边<右边，说明1和3影响平衡，1、3有假。
                    compare(coins,1,3,0);
                }
            }
            else if(coins[0]+coins[1]+coins[2] < coins[3]+ coins[4]+coins[5])
            {
                if(coins[0]+coins[3] == coins[1]+ coins[4])
                {
                    compare(coins,2,5,0);
                }
                else if(coins[0]+coins[3] > coins[1] + coins[4])
                {
                    //将1和3硬币换了顺序后，左边<右边，说明1和3影响平衡，1、3有假。
                    compare(coins,1,3,0);
                }
                if(coins[0]+coins[3] < coins[1]+coins[4])
                {
                    //将1和3硬币换了顺序后，依然是左边大于右边，说明1和3不影响平衡，1、3都是真。
                    compare(coins,0,4,1);
                }
            }
        }

        void MainTest()
        {
            srand(time(NULL));
            for(i=0; i<8;i++)
            {
                coins[i]=10;
            }
            //假币
            coins[rand()%8]=8;
            eightcoins(coins);
            cout<<"\n列出所有币重量"<<endl;
            for(i=0; i<8;i++)
            {
                cout<<coins[i]<<" ";
            }
            cout<<endl;
        }

        static void Test()
        {
            EightCoin *p = new EightCoin();
            p->MainTest();
            delete p;
        }

};


enum GameOfLifeSTATUS
    {
        DEAD,
        ALIVE
    };
/*

*/
class GameOfLife
{
    
    public:
        static const int MAX_ROW = 10;
        static const int MAX_COL = 25;
        int map[MAX_ROW][MAX_COL], new_map[MAX_ROW][MAX_COL];
        void init()
        {
            int row,col;
            for(row=0; row<MAX_ROW; row++)
            {
                for(col=0; col<MAX_COL; col++)
                {
                    map[row][col] = GameOfLifeSTATUS::DEAD;
                }
            }
            cout<<"Game of life program\n"<<endl;
            cout<<"Enter x, y where x,y is living cell"<<endl;
            cout<<"0<=x<="<<MAX_ROW-1<<"0<=y<="<<MAX_COL-1<<"\n";
            cout<<"Terminate with x,y = -1,-1"<<endl;
            while(1)
            {
                cin>>row>>col;
                if(0<=row && row< MAX_ROW && 0<=col && col<MAX_COL)
                {
                    map[row][col] = GameOfLifeSTATUS::ALIVE;
                }
                else if(row==-1 || col == -1)
                {
                    break;
                }
                else
                {
                    cout<<"exceeds map range "<<row<<" "<<col<<endl;
                }
            }

        }
        void outputMap()
        {
            cout<<"current cell status:\n";
            for(int row=0; row<MAX_ROW; row++)
            {
                cout<<"\n";
                for(int col=0; col<MAX_COL; col++)
                {
                    if(map[row][col]==GameOfLifeSTATUS::ALIVE)
                        cout<<"●";
                    else
                        cout<<"○";
                }
            }
        }

        //计算邻居8个位置，不包含自身
        int neighbors(int row,int col)
        {
            int count = 0,c,r;
            for(r = row-1; r<=row+1;r++)
            {
                for(c=col-1; c<=col+1;c++)
                {
                    if(r<0 || r>=MAX_ROW || c<0||c>=MAX_COL || (row==r && col==c))
                    {
                        continue;
                    }
                    else if(map[r][c] == GameOfLifeSTATUS::ALIVE)
                    {
                        count++;    
                    }
                    else
                    {

                    }
                }
            }
            return count;
        }
        void copyMap()
        {
            for(int row=0; row<MAX_ROW; row++)
            {
                
                for(int col=0; col<MAX_COL; col++)
                {
                    map[row][col]=new_map[row][col];
                }
            }
        }
        void MianTest()
        {
            int row,col;
            char ans;
            init();
            while(1)
            {
                outputMap();
                for(row=0; row< MAX_ROW; row++)
                {
                    for(col=0; col<MAX_COL; col++)
                    {
                        switch (neighbors(row,col))
                        {
                            case 0:
                            case 1:
                            case 4:
                            case 5:
                            case 6:
                            case 7:
                            case 8:
                                new_map[row][col] = GameOfLifeSTATUS::DEAD;
                                break;
                            case 2:
                                new_map[row][col] = map[row][col];
                                break;
                            case 3:
                                new_map[row][col] = GameOfLifeSTATUS::ALIVE;
                                break;
                            default:
                                break;
                        }
                    }
                }
                 
                cout<<"继续下一代？"<<endl;
                char input;
                cin>>input;
                if(toupper(input)=='Y')
                {
                    copyMap();
                    continue;
                }
                else
                    break;
            }
           
        }

        static void Test()
        {
            GameOfLife game;
            game.MianTest();
        }
        
};

class SkipStringFind
{
    public:
        //建立前进表,其中放了前n-1个字符对应的前进值
        //前进表依赖于如下分析： 如果字符串匹配，必然每个字符都能匹配，因此，反过来，如果查询当前位置的字符，与关键字符串中有一个字符匹配，那么根据其再在关键字符串中的位置，将查询位置前进对应位数，就可以减少部分不必要的查询。
        //                      比如 i am a superasuperb， 关键字符串superb
        //                      step1: i am a与superb比较，不符合，此时如果是穷举法，则是将 am a 与superb，然后am a s与superb，依次类推，这种方法效率低。
        //                      step2: 如果采用前进表法，则是检查最后一个字符a，在superb中不存在，所以直接跳到第6位置" super"与"superb"进行比较
        //                      step3：" super"与"superb"不同，此时查询当前位置为r，r是superb中的字符，位于关键字倒数第二位，因此我们将查询位置往后移动1位
        //                      step4: "supera"与"superb"不同，此时当前位置为a，a不是superb中的字符，移动superb的长度6位，正好落在b字符，获取该位置之前的n字节"superb"
        //                      step5: "superb"找到了。如果当前位置没有超出字符串长度，则会继续查找后续相同字符串的位置，可以实现查出所有字符串。
        void table(char* key)
        {
            int k,n;
            n = strlen(key);
            cout<<"table:\n";
            for(k = 0; k<=255; k++)
            {
                skip[k] = n;
            }
            for(k = 0; k<n-1; k++)
            {
                skip[key[k]] = n - k -1;
                cout<<key[k]<<"-"<<(n-k-1)<<endl;
            }
        }
        //查询
        int search(int p, char* input, char* key)
        {
            int i,m,n;\
            char tmp[80] = {'\0'};
            m = strlen(input);
            n = strlen(key);

            while(p<m){
                //在p位置上，截取前n长度的字符串
                substring(input, tmp, p-n+1, p);
                if(!strcmp(tmp, key))
                {
                    return p-n+1;
                }
                //如果不匹配，则根据最后一位是否在前进表中找到，如果找到，则p前进对应位置，在此位置之前的n位可能符合查询字符串
                cout<<"p="<<p<<" "<<input[p]<<" "<<skip[input[p]]<<endl;
                p+=skip[input[p]];
                
            }
            return -1;
        }
        //截取text中从s开始e结束的字符串，并赋值给tmp
        void substring(char* text, char* tmp, int s, int e)
        {
            int i,j;
            for( i=s,j=0; i<=e; i++,j++)
            {
                tmp[j] = text[i];
            }
            tmp[j]='\0';

        }
    
    private:
        int skip[256];

    public:
        void MainTest()
        {
            char str_input[80];
            char str_key[80];
            char tmp[80]={'\0'};
            int m,n,p;

            cin.get(); //清空

            cout<<"请输入字符串:";
            string input_tmp;
            getline(cin,input_tmp);
            strcpy(str_input,input_tmp.c_str());
            cout<<"请输入查询关键串:";
            getline(cin,input_tmp);
            strcpy(str_key,input_tmp.c_str());
            m = strlen(str_input);
            n = strlen(str_key);
            table(str_key);
            p = search(n-1,str_input,str_key);
            while(p !=-1)
            {
                substring(str_input,tmp,p,m);
                cout<<""<<tmp<<"\n";
                p = search(p+n+1,str_input,str_key);
            }
            cout<<"\n"<<endl;
        }

        static void Test()
        {
            SkipStringFind ssf;
            ssf.MainTest();
        }
};



class BagPorblem
{
    private :
    static const int LIMIT = 9; //重量限制
    static const int N = 5;     //物品种类
    static const int MIN = 1;   //最小重量
    struct body {
        char name[20];
        int size;
        int price;
    };
    typedef struct body fruit;
 fruit a[5]= {{"李子",4,4500},
                        {"苹果",2,5700},
                        {"橘子",2,2250},
                        {"草莓",2,1100},
                        {"甜瓜",2,6700},
                        };
    public:
    void Display(int *item, int *value, int newvalue)
    {
        cout<<"本次结果"<<newvalue<<endl;
        for(int i=0;i<=LIMIT;i++)
        {
            cout<<"重量"<<i<<"\t"<<value[i]<<"\t"<<a[item[i]].name<<"\n";
        }
    }
        void MainTest()
        {
            int item[LIMIT+1]= {0};   //对应重量下，放入的最后一个水果
            int value[LIMIT+1]={0}; //每个累积重量对应的当前最佳价格，默认都为0
            int newvalue,i,s,p;
           
            for(i = 0; i< N; i++)
            {
                for(s = a[i].size;s<=LIMIT;s++)
                {
                    //p 为减去当前重量之后的重量
                    p = s-a[i].size;
                    //p重量下的最大值，加上 当前水果的价格，如果大于s重量下的最大值，则s重量下的最大价格需要更新为当前价格。
                    newvalue = value[p]+a[i].price;
                    if(newvalue > value[s])
                    {
                        value[s]=newvalue;
                        item[s] = i;
                    }
                    
                }
                Display(item,value,newvalue);
                
            }
            cout<<"物品\t价格\t\n";
            //逆序，先按照最大重量情况下放入的最后一个水果来，然后剪掉该水果重量下，剩余重量放置的最后一个水果。
            for(i = LIMIT; i>=MIN; i= i-a[item[i]].size)
            {
                if(value[i]>0) //要加上这个判断，才能正确输出结果
                {
                    cout<<a[item[i]].name <<"\t"<<a[item[i]].price<<"\n";
                }
            }
        }

        static void Test()
        {
            BagPorblem bp;
            bp.MainTest();
        }
};

//蒙特卡洛方法去求解pi
//蒙特卡洛实际上就是一种求概率的思想
void MetoCarloPi()
{
    int i,sum;
    i = sum = 0;
    double x,y;
    srand(time(NULL));
    int N = 5000;
    //随机计算N次，看看点落在圆圈内和边上的次数
    for(int i =1;i<N;i++)
    {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if((x*x+y*y)<=1)
        {
            sum++; //点 落在圆圈内和边上的次数
        }
    }
    cout<<"PI="<<(double)4*sum/N<<endl;
}


int main()
{
    std::cout<<"程序启动!\n"<<std::endl;   
   // hanoiTest();
  //  Fibonacci();
   // combiTest();
  //  FindRoadTest();
  //  FindRoad2Test();
   // EightQueue::Test();
    //EightCoin::Test();
    //GameOfLife::Test();
   // SkipStringFind::Test();
    //BagPorblem::Test();
MetoCarloPi();
    cout<<"程序结束\n"<<endl;
    return 0;
}

//cmake -DCMAKE_BUILD_TYPE=Debug .


