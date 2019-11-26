#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<dos.h>

struct info {
	int icode;
	char name[100];
	float price;
	int quan;
	}item[100];
int ni=0,cust=0,tB=0,toBuy[100][10];
char stat[6]="FALSE";

void main();
void inventory();

void chDetails(){
int x,chCode,nCode,y,isFound;
char ch,nName[100],nc[4];

if(ni!=0){
nItem:
isFound=0;
clrscr();
inventory();
printf("Enter Code of Item you want to change: "); scanf("%d",&chCode);
for(x=1;x<=ni;x++)
 if(chCode==item[x].icode){
  isFound=1;
  curItem:
  clrscr();
  printf("UPDATE ITEM %d :\n%s\tPHP %.2f\t%d pcs.\n",item[x].icode,item[x].name,item[x].price,item[x].quan);
  printf("[A] Code\n[B] Name\n[C] Price\n[D] Add Quantity\n[E] Cancel");
  ch=getch();ch=toupper(ch);
   switch(ch){
    case 'A':
     codeItem:
     clrscr();
     printf("Enter New Code: "); scanf("%d",&nCode);
     if(nCode>9999&&nCode<1000){
      printf("Code Length either too long or too short!!!");
      getch();
      goto codeItem;
     }
     for(y=1;y<=ni;y++) {
      if(nCode==item[y].icode){
       printf("\nCode already in use!!!");
       getch();
       goto codeItem;
      }
     }
     item[x].icode=nCode;
     printf("\nItem Code successfully updated!!!\n\n");
    break;
    case 'B':
     nameItem:
     clrscr();
     printf("Enter New Name: "); gets(nName);
     strcpy (item[x].name,nName);
     printf("\nItem Name successfully updated!!!\n\n");
    break;
    case 'C':
     float nPrice;
     priceItem:
     clrscr();
     printf("Enter New Price: "); scanf("%f",&nPrice);
     item[x].price=nPrice;
     printf("\nItem Price successfully updated!!!\n\n");
    break;
    case 'D':
     int nQuan;
     quanItem:
     clrscr();
     printf("Enter Quantity of Item to Add: "); scanf("%d",&nQuan);
     item[x].quan+=nQuan;
     printf("\nItem Quantity successfully added!!!\n\n");
    break;
    case 'E':
     main();
    break;
    default:
     goto curItem;
    break;
    }//end of switch
  getch();
  clrscr();
  option:
   printf("[A] Change Another Detail of Current Item\n");
   printf("[B] Change Details of Another Item\n");
   printf("[C] Main Menu");  ch=getch();ch=toupper(ch);
    if(ch=='A') goto curItem;
    else if(ch=='B') goto nItem;
    else if(ch=='C') main();
    else {
     clrscr();
     goto option;
    }

 }//end of if-statement

 if(isFound!=1){
  printf("\nITEM NOT FOUND!!!");
  getch();
  goto nItem;
 }
} //end of if
else {
 clrscr();
 printf("NO RECORDS YET!!!");
 getch();
 main();
}
}

void add() {
char ch;
int  x;
float pr;

accept:
ni++;
printf("Item Code ");
 for(x=0;x<3;x++){
  delay(300); printf(".");
 }
clrscr();
item[ni].icode=rand()%9000+1000;
printf("Item Code\t: %d\n",item[ni].icode);
fflush(stdin);
printf("Item Name\t: "); gets(item[ni].name);
printf("Price\t\t: "); scanf("%f", &pr);
item[ni].price=pr;
printf("Quantity\t: "); scanf("%d", &item[ni].quan);

printf("\nItem successfully added!!!");
getch();

option:
 clrscr();
 printf("\n[A] Add More\n[B] Menu"); ch=getch();ch=toupper(ch);
 if(ch=='A'){
  clrscr();
  goto accept;
 }
 else if(ch=='B'){
  main();
 }
 else
  goto option;
}

void cheap(){
int tQuan,tCode,i,x,y;
char tName[100];
float tPrice;

for(x=1;x<=ni;x++)
 for(y=1;y<=ni;y++)
  if(item[x].price<item[y].price){
   tCode=item[y].icode;
   item[y].icode=item[x].icode;
   item[x].icode=tCode;

   strcpy(tName,item[y].name);
   strcpy(item[y].name,item[x].name);
   strcpy(item[x].name,tName);

   tPrice=item[y].price;
   item[y].price=item[x].price;
   item[x].price=tPrice;

   tQuan=item[y].quan;
   item[y].quan=item[x].quan;
   item[x].quan=tQuan;
 }
}

void inventory(){
int i,y,x,cod;
char ch;

disp:
y=5;
clrscr();
cheap();
  printf("\t\t\t*** AVAILABLE ITEMS ***\n");
printf("--------------------------------------------------------------------------------");
printf("CODE |\t\t\t    NAME    \t\t\t|    PRICE   | QNTY LEFT");
printf("--------------------------------------------------------------------------------");
if(ni!=0)
 for (i = 1; i <= ni; i++){
  printf("%4d | %s ",item[i].icode, item[i].name);
  gotoxy(57,y); printf("| %.2f ",item[i].price);
  gotoxy(70,y); printf("| %d \n", item[i].quan);
  y++;
 }

if (ni==0)
 printf("\t\t\tNO RECORDS!!!\n");
 printf("--------------------------------------------------------------------------------\n");
}

void buy(){
int x,y,code,i,isFound,qty;
float gtot,tot[100],ap;;
char ch;

ecode:
clrscr();
isFound=0;
inventory();

if(ni!=0){
 inventory();
 printf("Enter Item Code: "); scanf("%d",&code);

 for(x=1;x<=ni;x++){
  if(code==item[x].icode){
   isFound=1;
    if(item[x].quan==0){
     printf("No stock!!!");
     getch();
     goto ecode;
    }
   printf("\n%s: Php %.2f\n",item[x].name,item[x].price);
   printf("\nQuantity : "); scanf("%d",&qty);
    if(qty>item[x].quan){
     printf("Not enough stocks");
     getch();
     goto ecode;
    }
    else {
     printf("Cost\t : %.2f",qty*item[x].price);
     getch();
     toBuy[tB][1]=qty;
     toBuy[tB][0]=x;
     item[x].quan-=toBuy[tB][1];
    }
  }
 }

 if(isFound!=1){
  printf("Item not found!!!\n\nPress Any Key to Try Again");
  getch();
  clrscr();
  goto ecode;
 }

 if(isFound==1){
  buyM:
  clrscr();
  inventory();
  printf("Buy More? Y/N : "); ch=getch();ch=toupper(ch);
   switch(ch){
    case 'Y':
     clrscr();
     tB++;
     goto ecode;
    break;
    case 'N':
     clrscr();
     for(x=0;x<=tB;x++){
      tot[x]=item[toBuy[x][0]].price*toBuy[x][1];
      gtot+=(item[toBuy[x][0]].price*toBuy[x][1]);
     }
     disp:
      printf("\nCODE |\t\t\t  NAME  \t\t|   PRICE   | QNTY |\tTOTAL\n");
      printf("------------------------------------------------------------------- ------------");
      for (i = 0; i <=tB; i++){
       printf("%d | %s",item[toBuy[i][0]].icode, item[toBuy[i][0]].name);
       gotoxy(49,i+4); printf("| %.2f",item[toBuy[i][0]].price);
       gotoxy(61,i+4); printf("| %d",toBuy[i][1]);
       gotoxy(68,i+4); printf("| %.2f\n",tot[i]);
      }
      printf("------------------------------------------------------------------- ------------");
      printf("\t\t\tGRAND TOTAL: Php %.2f",gtot);
      //payment
      printf("\n\nAmount Paid: "); scanf("%f",&ap);
      if(ap<gtot){
       clrscr();
       goto disp;
      }

      printf("Change: %.2f",ap-gtot);
      tB=0; //set buy item to 0 for new customer
    break;
    default:
     clrscr();
     goto buyM;
    break;
  }//end of switch
  cust++;
 }
}

getch();
}

void import(){
 int x;

  for(x=ni+1;x<ni+6;x++)
   item[x].icode=rand()%9000+1000;

  strcpy(item[ni+1].name,"Dell Latitude E5530 i5 -3rd Gen 4Gb 320Gb HDD"); item[ni+1].price=10500; item[ni+1].quan=200;
  strcpy(item[ni+2].name,"Toshiba Satellite B552 core i5 3320 2.6 GHz"); item[ni+2].price=8490; item[ni+2].quan=200;
  strcpy(item[ni+3].name,"Lenovo IDEAPAD 330 -15IKB i3 8th Gen 4Gb 1Tb HDD"); item[ni+3].price=24999; item[ni+3].quan=200;
  strcpy(item[ni+4].name,"NightHawk Arise QuadCore Gaming PC"); item[ni+4].price=11850; item[ni+4].quan=200;
  strcpy(item[ni+5].name,"Xtreme Core i5 7400 Kaby Lake Processor"); item[ni+5].price=20249; item[ni+5].quan=200;
  ni+=5;
}

void main(){
char ch;
struct info item[100];

start:
 clrscr();
 gotoxy(25,2); printf("     E - COMPUTER SUPPLY");
gotoxy(25,3); printf("+63950-665-5070 - Loon Branch");
gotoxy(25,4); printf("       Estd: 2019 B.S.\n");
printf("\t--------------------------------------------------------------");

 printf("\n\n\n\t\t\t[A] Buy Item\n");
 printf("\t\t\t[B] Add Item\n");
 printf("\t\t\t[C] Change Info\n");
 printf("\t\t\t[D] Inventory\n");
 printf("\t\t\t[E] Import Default Items [%s]\n",stat);
 printf("\t\t\t[F] Exit\n"); ch=getch();ch=toupper(ch);
  switch(ch){
   case 'A':
   clrscr();
    buy();
    goto start;
   break;
   case 'B':
    clrscr();
    add();
    goto start;
   break;
   case 'C':
    clrscr();
    chDetails();
    goto start;
   break;
   case 'D':
	clrscr();
	 inventory();
	 getch();
	 goto start;
   break;
   case 'E':
    if(strcmp(stat,"FALSE")==0){
     import();
     strcpy(stat,"TRUE");
    }
   goto start;
   break;
   case 'F':
    exit(0);
   break;
   default:
    goto start;
   break;
 }
}