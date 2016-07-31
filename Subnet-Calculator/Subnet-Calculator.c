#include <stdio.h>
#include <math.h>
int main(void)
{
	char again='n';
	do{
		unsigned int cidr=0,hosts=0;
		unsigned char nets=0;
		int ipclass,AA,check=5;
		unsigned int ip_first[4]={0,0,0,0};
		unsigned char ip[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
		
		do{
			printf("Enter an Alpha Bravo or Charlie class IP and a valid CIDR(8-30)\n >> ");
			check=scanf("%d.%d.%d.%d/%d",&ip_first[0],&ip_first[1],&ip_first[2],&ip_first[3],&cidr);
			fflush(stdin);
			system("cls");
			for(AA=0;AA<=3;AA++){     
				  if(ip_first[AA]>255){
					   check=0;
				  }else{
					   ip[0][AA]=ip_first[AA];
				  }
			}
			if((check!=5)||(ip_first[0]>223)||(cidr<8||cidr>30)){
				  printf("Oops! Please check your input and try again\a\n");
				  check=0;
			}
		}while(check!=5);
	
		int x=(cidr/8);
		int y=8-(cidr%8);
		unsigned int z=(pow(2,y)-1);
		nets=(256/(z+1));
		ip[1][x]=~z;
		for(x;x>0;x--){
			 ip[1][(x-1)]=255;
		}
		int i;
		for(i=0;i<=3;i++)
		{
			 ip[2][i]=(ip[0][i]&ip[1][i]);
			 ip[3][i]=~(ip[1][i]^ip[2][i]);
			 
		}
		
		hosts=~((((((ip[1][0]*256)+ip[1][1])*256)+ip[1][2])*256)+ip[1][3]);
		ipclass=64+(ip[0][0]/64);
		if(ipclass==64){
			 ipclass++;
		}
		
		printf("You entered ---------->> %d.%d.%d.%d\n", ip[0][0],ip[0][1],ip[0][2],ip[0][3]);
		printf("Subnet Mask ---------->> %d.%d.%d.%d\n", ip[1][0],ip[1][1],ip[1][2],ip[1][3]);
		printf("Network ID ----------->> %d.%d.%d.%d\n", ip[2][0],ip[2][1],ip[2][2],ip[2][3]);
		printf("First assignable IP -->> %d.%d.%d.%d\n", ip[2][0],ip[2][1],ip[2][2],(ip[2][3]+1));
		printf("Last assignable IP --->> %d.%d.%d.%d\n", ip[3][0],ip[3][1],ip[3][2],(ip[3][3]-1));
		printf("Network broadcast ---->> %d.%d.%d.%d\n", ip[3][0],ip[3][1],ip[3][2],ip[3][3]);
		printf("Class ---->> %c\nNetworks ->> %d\nHosts ---->> %d\n",ipclass,nets,(hosts-1));
		printf("Would you like to enter another IP y/n >> ");
		scanf("%c",&again);
		system("cls");
		
	}while(again=='y');
	
	printf("Goodbye!!!\a\a\n");
	system("pause");
	return 0;
}
