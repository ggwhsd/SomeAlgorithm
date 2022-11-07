#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <cstring>
#include <string> 
#include <cmath>
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

/// @brief 筛选法求质数。
/// 最简单的暴力回圈算法：从2开始检查所有小于N的数是否能够被N整除，能整除，则N不是质数。
/// 第一次改进算法：因为A*B=N，所以检查的数字范围只需要x*x<=N即可，无需全部遍历，可以减少一半遍历范围。
/// 筛选法算法：因为2的倍数都能被2整除，3的倍数都能被3整除，5的倍数都能被5整除，...，所以这些都要筛除，这样就只剩下几个数字去计算了。
void Eratosthenes()
{
    int i,j;
    const int N = 1000;
    int prime[N+1];

    //初始化，假设都是指数
    for(i = 2; i<= N; i++)
    {
        prime[i]=1;
    }
    clock_t start,end;//用于计时
    start = clock()    ;
    for(i = 2; i*i<=N; i++)
    {
        //开始筛选，第一次筛选数i为2，第二次这里满足条件的是3，第三次满足条件的是5，。。。，通过一遍一遍的筛选，最后剩下的就是质数。
        if(prime[i]==1){

            for(j=i+1; j<=N; j++)
            {
                //所有能被i整除的数，都要筛去
                if(j % i ==0)
                {
                    prime[j]=0; //该数不为质数
                }
            }
        }
    }
    end = clock();
    cout<<"筛选法耗时【"<<(long double)(end-start)/CLOCKS_PER_SEC <<"】秒"<<endl;

   

    //显示所有N以内的质数
    int endlPerCount = 0;
    for(i =2; i<N;i++)
    {
        if(prime[i] == 1)
        {
            cout<<i<<"\t";
            endlPerCount++;
            if(endlPerCount%10==0)
            {
                cout<<"\n";
            }
        }
        
    }


}
/// @brief 这种方式貌似比筛选法快点
void primenumber()
{
    const int N = 100000;
    int prime[N+1];
clock_t start,end;//用于计时
    start = clock()    ;
    bool isPrime= false;
    for(int i=2;i<=N;i++)
    {
        isPrime=true;
        for(int j = 2;j*j<=i; j++)
        {
            if( 0 == i %j)
            {
                prime[i]=0;
                isPrime = false;
                break;
            }
        }
        if(isPrime)
            prime[i]=1;
    }

      end = clock();
    cout<<"常规耗时【"<<(long double)(end-start)/CLOCKS_PER_SEC <<"】秒"<<endl;
     
     return;
    //显示所有N以内的质数
    int endlPerCount = 0;
    for(int i =2; i<N;i++)
    {
        if(prime[i] == 1)
        {
            cout<<i<<"\t";
            endlPerCount++;
            if(endlPerCount%10==0)
            {
                cout<<"\n";
            }
        }
        
    }
}


/// @brief 假设 1000 1230 3212 2312 +  1000 1230 3212 2312 = ?
/// 数组中每个位置存储的值上限我们设定为9999，更易于十进制可读性。
/// 如下属于类似大端模式，即低地址放高位数据。
/// 1000 1230 3212 2312
/// a[0] a[1] a[2] a[3]
///+1000 1230 3212 2312
///+b[0] b[1] b[2] b[3]
///=2000 2460 6424 4624
///=c[0] c[1] c[2] c[3]

class BigNumber
{
    public:
        int N ; //长度
    public:
        void Add(int *a, int *b, int *c)
        {
            int i , carry = 0;
            for(i = N -1 ; i >=0; i--)
            {
                //从低位数据开始计算，因为低位数据放在数组的最后面。
                c[i] = a[i] + b[i] + carry;
                if(c[i]<10000)
                    carry=0; //不进位
                else
                {
                    //进位
                    c[i]=c[i]-10000;
                    carry = 1;
                }
            }
        }

        void sub(int *a, int *b, int *c)
        {
            int i , borrow = 0;
            for(i = N-1; i>=0; i--)
            {
                c[i] = a[i] - b[i] - borrow;
                if(c[i]>=0)
                {
                    borrow=0;
                }
                else
                {
                    c[i] = c[i]+10000;
                    borrow=1; //借位
                }
            }
        }

        void mul(int *a, int b, int *c)
        {
            int i,tmp,carry=0;
            for(i = N - 1; i>=0; i--)
            {
                tmp = a[i]* b + carry;
                c[i] = tmp%10000;
                carry = tmp/10000;
            }
        }

        void div(int *a, int b, int *c)
        {
            int i, tmp, remain = 0;
            for(i = 0; i<N; i++)
            {
                tmp = a[i] + remain;
                c[i] = tmp/b;
                remain = (tmp%b)*10000;
            }
        }

};

/// @brief 最大公约数和最小公倍数
void GCD()
{
    int a,b;
    cin.get();
    cout<<"请输入两个数字，空格分开"<<endl;
    cin>>a>>b;
    long int s = a * b;
    int c= 0;
    while(b!=0){
        c = a%b;
        a = b;
        b = c;
    }
    cout<<"GCD:"<<a<<endl;
    cout<<"LCM:"<<s/a<<endl;
}

void Armstrong()
{
    int a100,a10,a1;
    int number;
    cout<<"开始搜寻 armstrong 数:"
    <<endl;
    for(number = 100;number<1000;number++)
    {
        a100 = number/100;
        a10 = (number%100)/10;
        a1 = (number%10);
        if(pow(a100,3) + pow(a10,3)+pow(a1,3) == number)
        {

            cout<<number<<":"<<pow(a100,3)<<","<<pow(a10,3)<<","<<pow(a1,3)<<",";
        }
    }
    cout<<"结束搜寻 armstrong 数\n";
}

/// @brief 访客问题：将举行一个餐会，让访客事先填写到达时间与离开时间，为了掌握座位的数目，必须先估计不同时间的最大访客数
class Visitor
{
    //这个问题，其实可以换句话说，就是在某个时间点，来了多少人，走了多少，剩下多少人。
    //将来的人时间按从小到大排序，走的时间按照从小到大排序，这样在某个时间点上，来多少走多少一目了然。
    private:
        static const int MAX =5;

        void SWAP(int &x,int &y)
        {
            int t;
            t = x;
            x = y;
            y = t;
        }

        //分区排序
        int partition(int number[], int left, int right)
        {
            int i,j,s;
            s = number[right];
            i = left;
            for(j = left; j<right;j++)
            {
                if(number[j]<=s)
                {
                    i++;
                    SWAP(number[i],number[j]);
                }

            }
            SWAP(number[i+1], number[right]);
            return i+1;
        }

        void quicksort(int number[], int left, int right)
        {
            int q;
            if(left<right)
            {
                q = partition(number, left, right);
                quicksort(number, left, q-1);
                quicksort(number, q+1, right);
            }
        }
        //在某个时间点，当前有多少人
        int maxguest(int x[], int y[], int count, int time)
        {
            int i, num =0;

            for(i=0; i< count; i++)
            {
                if(time>x[i])
                    num++;
                if(time>y[i])
                    num--;
            }
            return num;
        }

        public :
            void MainTest()
            {
                srand(time(NULL));
                int x[MAX] = {0};
                int y[MAX] = {0};
                int time = 0;
                int count = 0;
                
                for(int i =0;i<MAX;i++)
                {
                    x[i] = (rand()/(double)RAND_MAX)*20;
                    y[i] = x[i] + 3;
                    cout<<x[i]<<" "<<y[i]<<endl;
                }
                quicksort(x,0,MAX-1);
                quicksort(y,0,MAX-1);
                for(int t =0; t<=24; t++)
                {
                    cout<<"时间:"<<t<<" "<<maxguest(x,y,MAX,t)<<endl;
                }
                cout<<"\n";
            }
            static void Test()
            {
                Visitor p;
                p.MainTest();
            }


};


void XiPai()
{
    const int N = 52;
    int pokers[N];
    int i,  j, tmp, remain;
    char pokerNames[13][3]={{" K"},{" Q"},{" J"},{"10"},{" 9"},{" 8"},{" 7"},{" 6"},{" 5"},{" 4"},{" 3"},{" 2"},{" 1"}};
    //每张扑克放在顺序的位置上
    for(i=0; i<N; i++)
    {
        pokers[i]=i;
    }
    srand(time(NULL));

    //以走访每个排位，然后随机将其与其他排位进行交换的方式，进行洗牌
    for(i = 0; i < N; i++)
    {
        j = rand()%52;
        tmp = pokers[i];
        pokers[i] = pokers[j];
        pokers[j]= tmp;
    }
    //给牌分配花色
    for(i = 0; i<N; i++)
    {
        switch ((pokers[i])%4)
        {
        case 0:
            cout<<"♤";
            break;
        case 1:
            cout<<"♡";
            break;
        case 2:
            cout<<"♢";
            break;
        case 3:
            cout<<"♧";
            break;
                
        
        default:
            break;
        }

        remain = pokers[i]%13;
        cout<<""<<pokerNames[remain];
    }




}


int rollTwoDice()
{
    return (rand()%6+1)+(rand()%6+1);
}
/// @brief 两个骰子的游戏， 测算一下玩家的胜率
void crapsGame()
{
    int winCount = 0;
    int loseCount = 0;
    const int testCount = 1000;

    const int WIN = 0;
    const int LOSE = 1;
    const int CONTINUE = 2;
    int countRoll = 0; //投色子的次数
    int gameStatus = CONTINUE;
    int die1, die2, sumOfDice;
    int firstPoint = 0;
    char c;
    
    srand(time(NULL));

    cout<<"Craps赌博游戏，>>>>>>   <<<<<< "<<endl;
    int test_index = 0;
    while(test_index<testCount)
    {
        while(1)
        {
            //getchar();
            countRoll++;
            //投色子
            sumOfDice = rollTwoDice();
            cout<<"投出的点数和:"<<sumOfDice<<endl;
            if(countRoll==1){
                switch (sumOfDice)
                {
                case 7:
                case 11:
                    gameStatus = WIN;
                    break;
                case 2:case 3:case 12:
                    gameStatus = LOSE;
                    break;
                default:
                    gameStatus = CONTINUE;
                    firstPoint = sumOfDice;
                    break;
                }
            }
            else
            {
                if(sumOfDice == firstPoint)
                {
                    gameStatus = WIN;
                }
                else if(sumOfDice == 7)
                {
                    gameStatus = LOSE;
                }
            }

            if(gameStatus == CONTINUE)
            {
                cout<<"当前还未结束，继续投骰子..."<<endl;
            }
            else
            {
                if(gameStatus == WIN)
                {
                    cout<<"玩家获胜"<<endl;
                    winCount++;
                    break;
                }
                else
                {
                    cout<<"玩家失败"<<endl;
                    loseCount++;
                    break;
                }
                /*
                cout<<"再玩一次？"<<endl;
                cin>>c;
                if(c=='n')
                {
                    cout<<"游戏结束"<<endl;
                    break;
                }
                */
                countRoll = 0;
                
            }

            
        }
        test_index++;
    }
    cout<<"测试次数"<<test_index<<",胜率 "<<(double)winCount/loseCount<<endl;

}

/*
 说着名犹太历史学家 Josephus有过以下的故事： 在罗马人占领乔塔帕特后， 39 个犹
太人与Josephus及他的朋友躲到一个洞中， 39个犹太人决定宁愿死也不要被敌人到， 于是决定了
一个自杀方式， 41个人排成一个圆圈， 由第1个人 开始报数， 每报数到第3人该人就必须自杀，
然后再由下一个重新报数， 直到所有人都自杀身亡为止。
然而Josephus 和他的朋友并不想遵从， Josephus要他的朋友先假装遵从，他将朋友与自己安排
在第16个与第31个位置，于是逃过了这场死亡游戏
*/
void JosephusSurvive()
{
    
    const int nPerson = 41;  //人数
    const int nNumberDie = 3;         //数到3则死
    int person[nPerson] = {0}; //存入死亡顺序，默认0为未死亡。
    int count =1 ;
    int i =0, pos = -1;
    int alive = 3; //救下两个人

    while(count<=nPerson)
    {
        //开始数数字，一共要玩nPerson轮，每一轮确定一个人去死
        do{
            //环形数组
            pos = (pos+1)%nPerson;

            //我还没死，所以我数数字
            if(person[pos]==0)
                i++;
            //我数到了3，则
            if(i==nNumberDie)
            {
                //报到3的人得死，重置数数字
                i = 0;
                break;
            }
        }
        while(1);
        person[pos]=count;
        count++;
    }

    for(i = 0; i< nPerson; i++)
    {
        cout<<person[i]<<",";
    }
    
    cout<<"如果有如下"<<alive<<"数量的人不想真的去自杀，则需要安排在如下位置"<<endl;
    for(i = 0; i < nPerson; i++)
    {
        if(person[i] > (nPerson-alive))
            cout<<"O";
        else
            cout<<"X";
        if((i+1)%5 == 0)
            cout<<" ";
    }
    cout<<endl;
   

}

// 排列组合，比如1234四个数字，有多少种排列？

class PaiLieZuHe
{
    public:
       const int N = 4;
    void perm(int* num, int i) 
    {
        int j, k, tmp;
        if(i < N) {
        for(j = i; j <= N; j++) {
        tmp = num[j];
        // 旋转该区段最右边数字至最左边
        for(k = j; k > i; k--)
        num[k] = num[k-1];
        num[i] = tmp;
        perm(num, i+1);
        // 还原
        for(k = i; k < j; k++)
        num[k] = num[k+1];
        num[j] = tmp;
        }
        }
        else { // 显示此次排列
        for(j = 1; j <= N; j++)
        printf("%d ", num[j]);
        cout<<endl;
        }
    }
    void MainTest()
    {
        int num[N+1],i;
        for(i=1;i<=N;i++)
        {
        num[i] = i;
        }
        perm(num,1);
    }
    static void Test()
    {
        PaiLieZuHe p ;
        p.MainTest();
    }
};


// 学生成绩得分排名
//提供了两个方法，一个最容易想到的方法，复杂度为n的平方，另一个高效方法，为2N
class ScoreAndSort
{
    private:
        static const int MAX = 100;  //最多100个人
        static const int MIN = 0;   //最少0人

    public:
        void MainTest()
        {
            int score[MAX+1]={0}; //保存所有分数
            int juni[MAX+2]={0};  //索引用作排名，内容是对应的分数
            int count =0,i;
            //输入分数，score保存
            do{
                printf("输入分数，-1结束:");
                scanf("%d",&score[count++]);
            }
            while(score[count-1]!=-1);
            count--;

            for(i=0;i<count;i++)
            {
                juni[score[i]]++;  //根据不同分数，索引juni对应位置的数值进行+1操作，代表该分数出现过一次。
            }

            //此时juni中保存了所有分数出现的次数。
            //将最右边设置为1，表示第一名。这样可以避免第一名同时有两个成绩的情况。
            juni[MAX+1]=1;
            //从右往左，依次将当前数值加上右边数值后的值填入当前数值。 因为没有出现的分数对应位置是0，所以结果可以代表当前分数对应的排名。
            for(i=MAX; i>= MIN; i--)
            {
                //第i的位置表示的是i-1人的排名
                juni[i] = juni[i] + juni[i+1];
            }
            
            //显示
            for(i=0;i<count;i++)
            {
                printf("%d\t%d\n", score[i], juni[score[i]+1]);
            }

        }

        static void Test()
        {
            ScoreAndSort sas ;
            sas.MainTest();
        }

};


class Sort
{
    public:
        static const int N = 10;
        int num[N] = {0};
        void RandNum()
        {
            cout<<"排序前"<<endl;
            for(int i = 0; i<10;i++)
            {
                num[i]= rand()%100;
                cout<<num[i]<<" ";
            }
            cout<<"\n";
        }
        Sort()
        {
            srand(time(NULL));
            RandNum();
        }

        /// @brief 从小到大排序，每次从右边的非排序数列中找到一个最小的放入到左边有序列中
        void selectSort()
        {
            int minValueIndex = 0;
            for(int i = 0; i<10-1; i++)
            {
                //只要对10-1个值进行选择插叙
                minValueIndex = i;
                for(int j = i+1; j< 10; j++)
                {
                    if(num[j]<num[minValueIndex])
                    {
                        minValueIndex = j;
                    }
                }
                if(i!=minValueIndex)
                {
                    //如果找到最小的并非当前i位置的值，则交换
                    swap(num[i],num[minValueIndex]);
                }
                cout<<"第"<<i+1<<"次排序";
                for(int k=0; k<10;k++)
                {
                    cout<<num[k]<<" ";
                }
                cout<<endl;
            }
        }
        /// @brief 将后面无序的最前的数取出，插入到前面有序列中的恰当位置
        void insertSort()
        {
            RandNum();
            int tempValue = 0;
            int j = 0;
            //第一个数不需要，直接从第二个数开始
            for(int i = 1; i<10; i++)
            {
                
                tempValue = num[i]; //待插入值
                
                for( j= i-1; j>= 0; j--)
                {
                    if(num[j]>tempValue)
                    {
                        num[j+1] = num[j];//大的值往后移动一位
                    }
                    else
                    {
                        break; //找到位置
                    }
                    
                }
                num[j+1] = tempValue;



                cout<<"第"<<i<<"次排序";
                for(int k=0; k<10;k++)
                {
                    cout<<num[k]<<" ";
                }
                cout<<endl;
            }
        }

        //从左向右，从小到大排序冒泡，最大的数第一轮就会排到最后面，最小的数最后一轮才会排前面
        void bubleSort()
        {
            RandNum();
            int i,j,k;
            bool flag = true; //如果为false，就是没有发生元素变动，说明已经全部排序完成，无序再继续回圈遍历比较。
            for(i=0;i<(10-1) && flag; i++)
            {
                flag = false;
                for(j=0; j< 10-i-1; j++)
                {
                    if(num[j]>num[j+1])
                    {
                        swap(num[j+1],num[j]);
                        flag = true;
                    }
                }
                cout<<"第"<<i+1<<"次排序";
                for(int k=0; k<10;k++)
                {
                    cout<<num[k]<<" ";
                }
                cout<<endl;
            }
        }
        /// @brief 普通间隔的希尔排序：改良的插入排序,充分利用每次排序的信息作为前提来指导下次排序。
        void shellInsertSort()
        {
            RandNum();
            int i,j,k,gap,t;
            int count = 0;
            for(gap = N/2;gap>0;gap=gap/2)
            {
                for(k=0;k<gap;k++)
                {
                    count++;
                    //下面就是普通插入排序的算法了，只不过取数据的时候要gap距离
                    //选出所有gap距离的数据,除去第一个元素
                    for(i = k+gap;i<N;i+=gap)
                    {
                        //将选出的数据插入到之前的有序列中,这里选择交换的方式插入，
                        for(j = i-gap;j>=k;j-=gap)
                        {
                            if(num[j]>num[j+gap])
                            {
                                swap(num[j+gap],  num[j]); //大的数据往后移动
                            }
                            else
                            {
                                break;
                            }
                        }
                          
                    }
                    cout<<"第"<<count<<"次排序";
                    for(int k=0; k<10;k++)
                    {
                        cout<<num[k]<<" ";
                    }
                    cout<<endl;
                }
               
            }

        }
        /// @brief 思想：每次遍历，既要选出最大值，也要选出最小值，分别放在最右边和最左边，这样可以减少排序次数。这个思想可以用于其他排序。
        void shakerSort()
        {
            //不高兴写了，就是加left和right两个变量指示最大和最小的位置，在此位置之间的才是需要排序的数字。
        }

        int sortCount = 0;
        void createHeap()
        {
            sortCount = 0;
            cout<<"创建一个大顶堆"<<endl;

            int i,s,p;
            int len = sizeof(num)/sizeof(num[0]);
            //获取倒数第一个非叶子节点，因为叶子节点没有子节点无需比较，
            //该非叶子节点之前的节点肯定都是非叶子节点。
            for(i= len/2-1; i>=0; i--)
            {
               //调整堆
               adjustHeap(i,len);
            }



        }
        /// @brief 改良的选择排序法：堆排序，堆排序每次从一条路径选择，而不是所有元素，所以称之为改进的选择排序。
        /// 从小到大的升序排序，是需要先创建大顶堆，然后将堆顶元素与尾节点互换，再依次构造大顶堆，互换这种方式。
        /*
        堆排序的基本思想是：1.将待排序序列构造成一个大顶堆，此时，整个序列的最大值就是堆顶的根节点。
                          2.将其与末尾元素进行交换，此时末尾就为最大值。
                          3.然后将剩余n-1个元素重新构造成一个堆，
                          4.这样会得到n个元素的次小值。如此反复执行，便能得到一个有序序列
        */
        void heapSort()
        {
            cout<<"heapSort"<<endl;
            RandNum();
            

            createHeap();
            int i=0;
            for(i = 0; i < N; i++)
                printf("%d ", num[i]);
            
            for(int j=N-1;j>0;j--)
            {
                //交换大堆顶和尾部数据
                swap(num[0],num[j]);
                //对剩余数据进行重新调整。
                adjustHeap(0,j);
            }

            cout<<"执行次数:"<<sortCount<<endl;

            
            
        }
        
        //调整大顶堆,将位置i的元素调整为最大的值，会沿着一条路径一直往下调整
        void adjustHeap(int i, int length)
        {
            //缓存调整的数值
            int temp = num[i];
            //我觉得：k=k*2+1，每次如果出现值调整，必须沿着路径一直往下调整，如果没有调整，实际上无需沿着路径往下调整。
            bool isAdjust = false;
            for(int k = i*2+1; k<length; k=k*2+1)
            {
                //获取i的左子节点i*2+1。
                if(k+1<length && num[k]<num[k+1])
                {
                    k++; //如果右子节点存在，则比较左右子节点。
                    //如果右节点大于左节点，则k定位为右节点。
                    //此时 k 是左右节点中的较大值
                }
                //将较大的子节点与父节点比较
                if(num[k] > temp)
                {
                    isAdjust = true;
                    num[i] = num[k];
                    i = k;  //k位置的数据赋值给i位置，那么k位置的数据就是多余的了，将k保存起来，以便最后将原始i位置的数据填入到k位置。这样就不用每次都进行交换元素了。
                }
                sortCount++;
                if(isAdjust==false)
                {
                    break;
                }

            }


            num[i] = temp;

            cout<<"第x次排序";
            for(int k=0; k<10;k++)
            {
                cout<<num[k]<<" ";
            }
            cout<<endl;

        }

        /// @brief 快速排序属于较为推荐的排序，不过其最差情况是O(n*n)
        /// 在数列中找出适当的轴心，然后将数列一分为二，分别对左边与右边数列进行排序，而影响快速排序法效率的正是轴心的选
        void quickSort_v1()
        {
            sortCount = 0;
            RandNum();
            //int tempNum[N]={67,20,14,25,53,19,3,17,22,56};
            //memcpy(num,tempNum,N*4);


            printf("排序前： ");
            int i=0;
            for(i = 0; i < N; i++)
                printf("%d ", num[i]);

            quickSort_v1(0,N-1);

            printf("排序后： ");
            
            for(i = 0; i < N; i++)
                printf("%d ", num[i]);
            cout<<"执行次数:"<<sortCount<<endl;
        }

        void quickSort_v1(int left, int right)
        {
            int len = sizeof(num)/sizeof(num[0]);
            int i_left,j_right,s_flagNumber;
            if(left<right)
            {
                s_flagNumber = num[left];
                i_left = left;
                j_right = right+1;
                while(true){
                    //向右找到不小于s_flagNumber数的位置
                    while(i_left+1<len)
                    {
                        sortCount++;
                        i_left++;
                        if(num[i_left]<s_flagNumber)
                        {
                        }
                        else
                            break;
                    }
                    while(j_right-1 >=0)
                    {
                        sortCount++;
                        j_right--;
                        if(num[j_right]>s_flagNumber)
                        {
                        }
                        else
                            break;
                    }
                    if(i_left >= j_right)
                        break;
                    swap(num[i_left],num[j_right]);
                }
                num[left] = num[j_right];
                num[j_right] = s_flagNumber;
                quickSort_v1(left,j_right-1);
                quickSort_v1(j_right+1,right);
            }
            else
            {

            }
        }
        /// @brief s_flagNumber每次去最左边的数，如果遇到原有数据就是按照从左到右或者从右到左排序的，则算法复杂度就是O(n*n)了，
        /// 因此改进这种方法，将s_flagNumber=中间位置 (left+right)/2，这样每次都从中间开始。
        void quickSort_v2()
        {
            //RandNum();
            int tempNum[N]={67,20,14,25,53,19,3,17,22,56};
            memcpy(num,tempNum,N*4);

            sortCount=0;
            printf("排序前： ");
            int i=0;
            for(i = 0; i < N; i++)
                printf("%d ", num[i]);

            quickSort_v2(num,0,N-1);

            printf("排序后： ");
            
            for(i = 0; i < N; i++)
                printf("%d ", num[i]);
            cout<<"执行次数:"<<sortCount<<endl;         
        }

        void quickSort_v2(int nums[],int left, int right)
        {
            int len = right+1;
            int i_left,j_right,s_flagNumber;
            if(left<right)
            {
                s_flagNumber = nums[(left+right)/2]; 
                i_left = left-1;
                j_right = right+1;
                while(true){
                    //向右找到不小于s_flagNumber数的位置
                    while(i_left+1<len)
                    {
                        sortCount++;
                        i_left++;
                        if(nums[i_left]<s_flagNumber)
                        {
                        }
                        else
                            break;
                    }
                    while(j_right-1 >=0)
                    {
                        sortCount++;
                        j_right--;
                        if(nums[j_right]>s_flagNumber)
                        {
                        }
                        else
                            break;
                    }
                    if(i_left >= j_right)
                        break;
                    swap(nums[i_left],nums[j_right]);
                }
               
                quickSort_v2(nums,left,i_left-1);
                quickSort_v2(nums,j_right+1,right);
            }
            else
            {

            }
        }

        
        /// @brief 合并排序，主要用于对两个有序的序列进行合并，当然也可以对一个无序的序列进行不停的递归拆分至一个元素，然后反过来再进行合并。
        void mergeSort()
        {

            sortCount=0;
            printf("排序前： ");
            int i=0;
            for(i = 0; i < N; i++)
                printf("%d ", num[i]);

            int number1[N] = {67,20,14,25,53,19,3,17,22,56};
            int number2[N] = {67,20,14,31,36,38,58,78,83,92};
            int number3[N+N] = {0};
            int n;
            
            quickSort_v2(number1,0,N-1);
            quickSort_v2(number2,0,N-1);

            cout<<"先分别排序2笔："<<endl;
            for(i = 0; i < N; i++)
                printf("%d ", number1[i]);
            cout<<"\n";
            for(i = 0; i < N; i++)
                printf("%d ", number2[i]);
            cout<<"\n";

            mergeSort(number1,N,number2,N,number3);
            
            printf("合并排序后： ");
             for(i = 0; i < N*2; i++)
                printf("%d ", number3[i]);
            cout<<"\n";
        }

       
        /// @brief 将number1数组和number2数组合并排序到number3，M代表number1的长度，N代表number2的长度。
        /// @param number1 
        /// @param M 
        /// @param number2 
        /// @param N 
        /// @param number3 
        void mergeSort(int number1[], int M, int number2[], int N, int number3[])
        {
            int i=0; 
            int j=0;
            int k=0;
            while(i<M&& j<N){
                if(number1[i]<=number2[j])
                {
                    //将大的数放到number3，大的数组当前索引往后走一位。
                    number3[k++] = number1[i++];
                }
                else
                {
                    number3[k++] = number2[j++];
                }

            }
            while(i<M)
            {
                number3[k++] = number1[i++];

            }
            while(j<N)
            {
                number3[k++]=number2[j++];
            }
        }



        /// @brief 计算数组中的数字的最大位数
        /// @param data 
        /// @param n 
        /// @return 
        int maxbit(int data[],int n)
        {
            int d=1;
            for(int i=0;i<n;i++)
            {
                int c=1;
                int p=data[i];
                while(p/10)
                {
                    p=p/10;
                    c++;
                }
                if(c>d)
                    d=c;
            }
            return d;
        }   
        /// @brief 基数排序:将数字按照位数，依次对个位数进行排序，此时得到一个个位数上从小到大的序列，然后在此基础上再按照十位数进行排序，依次类推，直到所有位数都排序完之后，就完成了排序
        void radixSort()
        {
            //因为tmp数据没有采用链表或者二维数组，而是采用了一维数组，因此逻辑上稍微难懂一点，不过很巧妙，与成绩排名问题很像。
            int data[N] = {67,20,14,25,53,19,3,17,22,56};
            int tmp[N]={0};
            int count[N] = {0};  //桶
            cout<<"\n排序前"<<endl;
            for(int i = 0; i < 10; i++)
            {
                cout<<" "<<data[i];
            }

            int digit = maxbit(data,10);
            int r=1;
            int k=0;
            for(int i=0;i<digit;i++)
            {
                //有几位，就要基数排几轮
                for(int j=0;j<N;j++)//装桶之前要先清桶
                    count[i]=0;


                for(int j=0;j<N;j++) //记录每个桶的记录数，从前往后取数
                {
                     k=(data[j]/r)%10;  //获取对应位数,r=1，获取个位，r=10，则十位数
                     count[k]++;  //对应位数的桶进行记录
                }
                
                for(int j = 1; j < N; j++)
                {
                    count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
                }


                for(int j = N - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中，从后往前
                {
                    k = (data[j] / r) % 10;
                    tmp[count[k] - 1] = data[j];
                    count[k]--;
                }

                for(int j = 0; j < N; j++) //将临时数组的内容复制到data中
                    data[j] = tmp[j];
                r = r * 10;
            }
            cout<<"\n排序后"<<endl;
            for(int i = 0; i < 10; i++)
            {
                cout<<" "<<data[i];
            }
          

        }

        static void Test()
        {
            Sort s ; 
            //冒泡排序优于选择和插入排序，因为冒泡可能提前发现数据已经有序而提前完成排序。
            s.selectSort();
            s.insertSort();
            s.bubleSort();
            s.shellInsertSort();
            s.heapSort();
            s.quickSort_v1();
            s.quickSort_v2();
            s.mergeSort();
            s.radixSort();
        }

}
;


class Search
{
    public:
    int findCount = 0;
    void BaseSearch()
    {
        int data[10] = {67,20,14,25,53,19,3,17,22,56};
        int key = 3;
        int i=0;
        while(i<10)
        {
            if(data[i]==key)
            {
                break;
            }
            i++;
        }

        cout<<"search的位置："<<i<<endl;
    }

    void BaseSearch_Guard()
    {
        int data[10] = {67,20,14,25,53,19,3,17,22,56};
        int key = 3;
        if(data[0]==key)
        {
            cout<<"search的位置："<<0<<endl;
            return;
        }
        else
        {
            data[0] = key;
            int i =9;
            while(data[i]!=key)
            {
                i--;
            }
            if(i==0)
            {
                 cout<<"search不到"<<endl;
            }
            else
            {
                cout<<"search的位置："<<i<<endl;
            }
        }
    }
    /// @brief 对已经有序的数据进行二分查找,二分查找是每次采取中间位置，可以理解为50%的比例位置来做
    /// @param num 
    /// @param num_length 
    /// @param key 
    int BinarySearch(int num[],int num_length, int key)
    {
        findCount = 0;
        int low_index,high_index,mid_index;
        low_index = 0;
        high_index = num_length-1;
        while(low_index<=high_index)
        {
            //每次找到需要查询数据范围的中间位置
            mid_index = ( low_index + high_index )/2;
            if(num[mid_index] == key)
            {
                return mid_index;
            }
            else if(num[mid_index] > key)
            {
                high_index = mid_index-1;
            }
            else
            {
                low_index = mid_index + 1;
            }
            findCount++;
        }
        return -1;

    }
    /// @brief 插补搜寻法，与二分查找法类似，不过用的比例不是50%，而是根据简单的比例公式来计算. 但是这个适用于数量比较大的情况下，据说是大于500以上，才可能有效果。
    /// 
    /// @param num 
    /// @param num_length 
    /// @param key 
    int InterpolationSearch(int num[],int num_length, int key)
    {
        findCount = 0;
        int low_index,high_index,mid_index;
        low_index = 0;
        high_index = num_length-1;
        while(low_index<=high_index)
        {
            //每次找到需要查询数据范围的中间位置
            mid_index = (key - num[low_index])/(num[high_index] - num[low_index])*(high_index-low_index)+low_index;
            if(mid_index < low_index || mid_index > high_index)
            {
                return -1;
            }
            if(num[mid_index] == key)
            {
                return mid_index;
            }
            else if(num[mid_index] > key)
            {
                high_index = mid_index-1;
            }
            else
            {
                low_index = mid_index + 1;
            }
            findCount++;
        }
        return -1;      
    }

    static void Test()
    {
        Search s;
        s.BaseSearch_Guard();

        Sort sort ;
        sort.quickSort_v1();
        cout<<"InterpolationSearchIndex:"<<s.InterpolationSearch(sort.num,sort.N,sort.num[6]);
        cout<<" "<<s.findCount<<endl;

        cout<<"binarySearchIndex:"<<s.BinarySearch(sort.num,sort.N,sort.num[7]);
        cout<<" "<<s.findCount<<endl;
    }
};

/// @brief 稀疏矩阵，即对于一个实际资料量很少但是元素数量本身很多的矩阵。 比如 一个矩阵只有一个位置有数，则只要记录一下矩阵本身大小以及含有1个数，然后再记录下哪行哪列哪个数字。
void SparseMatrix()
{
    /*
        0 0 0 0 0 0
        0 3 0 0 0 0
        0 0 0 6 0 0
        0 0 9 0 0 0
        0 0 0 0 12 0
    */
    int num[5][3] = {{5, 6, 4},
                    {1, 1, 3},
                    {2, 3, 6},
                    {3, 2, 9},
                    {4, 4, 12}};
    int i,j,k = 1;
    cout<<"稀疏矩阵的节约存储方式:\n";
    for(i = 0;i<5;i++)
    {
        for(j = 0; j<3;j++)
        {
            printf("%4d",num[i][j]);
        }
    }
    cout<<endl;
    cout<<"还原原始矩阵:\n";
    //输出多少行：5
    for(i = 0; i<num[0][0]; i++)
    {
        //输出多少列：6
        for(j =0; j<num[0][1]; j++)
        {
            
            if(k<num[0][2])
            {
                //输出位置与对应记录的位置一样，则输出值
                if(i == num[k][0] && j == num[k][1])
                {
                    printf("%4d",num[k][2]);
                    k++;
                }
                else
                    printf("%4d", 0);
            }
            else
                    printf("%4d", 0);
        }
        cout<<""<<endl;
    }

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
    //MetoCarloPi();
    //Eratosthenes();
    //primenumber();
    //GCD();
    //Armstrong();
    //Visitor::Test();
    //XiPai();
    //crapsGame();
    //JosephusSurvive();
    //PaiLieZuHe::Test();
   // ScoreAndSort::Test();
   //Sort::Test();
   //Search::Test();
   SparseMatrix();
    cout<<"程序结束\n"<<endl;
    return 0;
}

//cmake -DCMAKE_BUILD_TYPE=Debug .


