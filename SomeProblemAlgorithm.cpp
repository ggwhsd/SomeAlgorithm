#include <iostream>
#include <stdio.h>
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
//走过一个格子就标志位1
int VisitRoad(int **maze,int i, int j,int endI,int endJ)
{
    maze[i][j] = 1;
    if(i == endI && j == endJ)
    {
        
    }
    return 0;
}
void FindRoadTest()
{
    int maze[7][7]= {   {2, 2, 2, 2, 2, 2, 2},
                        {2, 0, 0, 0, 0, 0, 2},
                        {2, 0, 2, 0, 2, 0, 2},
                        {2, 0, 0, 2, 0, 2, 2},
                        {2, 2, 0, 2, 0, 2, 2},
                        {2, 0, 0, 0, 0, 0, 2},
                        {2, 2, 2, 2, 2, 2, 2}};
    int startI = 0, startJ = 1;
    int endI = 6, endJ = 5;
    int success = 0 ;

   
}



int main()
{
    std::cout<<"程序启动!\n"<<std::endl;   
    hanoiTest();
    Fibonacci();
    combiTest();
    cout<<"程序结束\n"<<endl;
    return 0;
}

//cmake -DCMAKE_BUILD_TYPE=Debug .


