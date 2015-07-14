#include <stdio.h>
#define debug
int abs(int x);                      //自写绝对值函数
int player;                          //当前落子人
int field[9]={0,0,0,0,0,0,0,0,0};    //棋盘
char sym(int n);                     //输出棋子
void DrawField();                    //绘制棋盘
bool isWin();                        //是否胜利
void AI();                           //人工智能

int main()
{
#ifdef debug
    printf("%X %X\n",&player,main);
#endif
	do
	{
		printf("请选择走棋次序。\n输入1先走，或者-1后走。");
		scanf("%d",&player);
	}
	while(player!=1&&player!=-1);	
	int pl;                      //落子位置
	DrawField();
	int i;
	for(i=1;i<=9;i++)
	{
		if(isWin())break;
		if(player==1)
		{
			printf("请输入落子位置：");
			scanf("%d",&pl);
			if(pl>9||pl<1||field[pl]!=0)
			{
				printf("输入错误，无此格子或格内已有子\n请重新输入:");
				i--;
				DrawField();
				continue;
			}
			else
			{
				field[pl]=player;
				
				player=-player;
				if(isWin())break;
			}
		}
		else AI();
	}
	if(i>=9)printf("平局\n");
	else printf("赢家是%d\n",sym(-player));
	getchar();getchar();                       //延迟窗口关闭 
	return 0;
}


int abs(int x)
{
	if(x<0)x=-x;
	return x;
}



char sym(int n)
{
	if(field[n]==1)return 'O';
	else if (field[n]==-1)return 'X';
	else return ' ';
}





void DrawField()
{
	printf("\n\nBattle of Waterloo\n");
	printf("┏━┯━┯━┓\n");
	printf("┃%2c│%2c│%2c┃\n",sym(7),sym(8),sym(9));
	printf("┠─┼─┼─┨\n");
	printf("┃%2c│%2c│%2c┃\n",sym(4),sym(5),sym(6));
	printf("┠─┼─┼─┨\n");
	printf("┃%2c│%2c│%2c┃\n",sym(1),sym(2),sym(3));
	printf("┗━┷━┷━┛\n");
}



bool isWin()
{
	if(abs(field[1]+field[2]+field[3])==3||abs(field[4]+field[5]+field[6])==3||abs(field[7]+field[8]+field[9])==3
||abs(field[1]+field[4]+field[7])==3||abs(field[2]+field[5]+field[8])==3||abs(field[3]+field[6]+field[9])==3
||abs(field[1]+field[5]+field[9])==3||abs(field[3]+field[5]+field[7])==3)

return true;
else return false;
}
void AI()
{
	for(int j=1;j<=9;j++)
	{
		if(field[j]==0)
		{
			field[j]=player;
			if(isWin())goto finish;
			field[j]=0;
		}
	}
	for(int j=1;j<=9;j++)
	{
		if(field[j]==0)
		{
			field[j]=-player;
			if(isWin()){field[j]=player;goto finish;}
			field[j]=0;
		}
	}
	if(field[5]==0){field[5]=player;goto finish;}
	// the next can be inprove
	if((field[1]!=0||field[9]!=0)&&field[3]==0){field[3]=player;goto finish;}
	if(field[3]!=0&&field[9]==0){field[9]=player;goto finish;}
	if(field[7]!=0&&field[1]==0){field[1]=player;goto finish;}
	if(field[2]!=0&&field[4]==0){field[4]=player;goto finish;}
	if(field[4]!=0&&field[2]==0){field[2]=player;goto finish;}
	if(field[8]!=0&&field[4]==0){field[4]=player;goto finish;}
	if(field[6]!=0&&field[8]==0){field[8]=player;goto finish;}
	for(int q=1;q<=9;q++)
	{
		if(field[q]==0)
		  {
		    field[q]=player;break;
		  }
	}
	finish:player=-player;DrawField();
}
