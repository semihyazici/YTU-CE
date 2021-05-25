#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100
int MAXSIZE = MAX;       
char stack[MAX];     
int top = -1;            

int isempty() {

   if(top == -1)
      return 1;
   else
      return 0;
}
   
int isfull() {

   if(top == MAXSIZE)
      return 1;
   else
      return 0;
}

int peek() {
   return stack[top];
}

int pop() {
   int data;
	
   if(!isempty()) {
      data = stack[top];
      top--;   
      return data;
   } else {
      printf("Could not retrieve data, Stack is empty.\n");
      return -1;
   }
}

void push(int data) {

   if(!isfull()) {
      top = top + 1;   
      stack[top] = data;
   } else {
      printf("Could not insert data, Stack is full.\n");
      
   }
}


char *controller(char *code,int length){
	int i,j,tmp;
	
	for(i=0;i<length;i++){
		tmp = atoi(&code[i]);
		if(tmp == 0){
			//atoi fonksiyonu char sayilari inte çevirir
			//0 olduðu zaman bir sayi deðil harf gelmiþtir 
			push(code[i]);
		}
		else if(top+1 < tmp){
			printf("Bu islem yapilamaz %d  harf stackte bulunmamaktadir. \n",tmp);
			return;
		}
		else{
			printf("%d sayisi geldi.\n",tmp);
			char a;
			for(j=0;j<tmp;j++){
				a = pop();
				printf("%d. adimda %c silindi\n",j+1,a);
			}
		}
	}
	char codes[top+1];
    
	for(i=top;i>-1;i--){
		codes[i] = pop();
	}
	return (char *)codes;
	
}

int main() {
   char code1[MAX] = "cabc2ssss3uvxyz4sab2kabak4odun1" ;
   char code2[MAX] = "ama3cam1ses2usta2kopuk3yok3damla4ufuk3" ;
   /*
   printf("Please Enter The Code1:");
   scanf("%s",&code1);
   printf("Please Enter The Code2:");
   scanf("%s",&code2)
   */
   char *conCode1 = controller(code1,strlen(code1)+1);
   strcpy(code1,conCode1);
   char *conCode2 = controller(code2,strlen(code2)+1);
   strcpy(code2,conCode2);
   printf("Ilk Kod = %s\n",code1);
   printf("Ikinci Kod = %s\n",code2);
   

   if(strcmp(code1,code2) == 0){
   		printf("Casuslar konusabilir");
   }
   else{
   	    printf("Casuslar Konusamaz");
   }

   	    
   

   
   return 0;
}
