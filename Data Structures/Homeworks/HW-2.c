#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#define MAX 15
#define SUGGESTARR 3
/*
	Semih Yazici
	19011087
	//////////////////
	Ornek:
	1->kok graf = elma
	2->subgraflar = sirkesi suyu puresi (cikis yapiniz) 
	3->kok graf = uzum
	4->subgraflar = kek hosaf suyu kurabiye cekirdegi (cikis yapiniz)
	5->Birinci grafta sorgulanacak kelimeler = sirkesi sirkesi sirkesi suyu suyu puresi (cikis yapiniz)
	6->Ikinci grafta sorgulanacak kelimeler = kek kek kek hosaf hosaf suyu suyu kurabiye kurabiye kurabiye kurabiye cekirdegi cekirdegi cekirdegi cekirdegi (cikis yapiniz)
	7->Hangi Kelimeye Oneri Almak Istersiniz = hangi kelime secilirse ona öneri yapilir mesela 'uzum' olsun
	kurabiye kelimesi 4 kere aranmistir.
	cekirdegi kelimesi 4 kere aranmistir.
	kek kelimesi 3 kere aranmistir.	
	Sonucu elde edilir.	
																	*/
struct node{
	char a[20];
	int komsuSayisi;
	int aranmaSayisi;
	struct node *komsu[MAX];
};
struct node *head;
void komsuInit(struct node *iter){
	//verilen node'un komsularina yer acar 
	int i;
	for(i = 0;i<MAX;i++){
		iter->komsu[i] = (struct node *)malloc(sizeof(struct node));
	}
}
void firstInit(struct node *iter){
	int i;
	iter->aranmaSayisi = 0;
	iter->komsuSayisi = 0;
	for(i=0;i<MAX;i++){
		iter->komsu[i]->komsuSayisi = 0;
		iter->komsu[i]->aranmaSayisi =0;
	}	
}
bool isExit(char *c){
	//cikis durumunu kontrol eder
	if(strcmp(c,"Q") == 0){
		return true;
	}
	return false;
}
void mergeGraph(struct node *iter1 ,struct node *iter2){
	//2 grafi ilk grafta birleþtirir 
	int i,j;
	for(i=0;i<iter1->komsuSayisi;i++){
		for(j=0;j<iter2->komsuSayisi;j++){
			if(strcmp(iter1->komsu[i]->a,iter2->komsu[j]->a) == 0){
				iter1->komsu[i]->komsu[iter1->komsu[i]->komsuSayisi] = iter2;
				iter1->komsu[i]->komsuSayisi++;
			}
		}
	}		
}

void graphInitializer(struct node *iter){
	//tek bir grafin birleþtirilmeden önceki halini hazirlar 
	toHead(iter);
	char c[20];
	printf("Kok Grafin Stringini Girin:");
	scanf("%s",iter->a);
	printf("Subgraflari Girin(Cikmak icin 'Q' Yaziniz.)"); 
	scanf("%s",c);
	while(!isExit(c)){
		strcpy(iter->komsu[iter->komsuSayisi]->a,c);
		komsuInit(iter->komsu[iter->komsuSayisi]);
		firstInit(iter->komsu[iter->komsuSayisi]);
		iter->komsu[iter->komsuSayisi]->komsu[0] = iter;
		iter->komsu[iter->komsuSayisi]->komsuSayisi++;
		iter->komsuSayisi++;
		scanf("%s",c);
	}
	
}
void toHead(struct node *iter){
	//verilen node'un en baþtaki konuma dönmesi
	*iter = *head;	
}

void callFunc(struct node *iter){
	//bir çok fonksiyonun bir arada kullanýlmasý için kolaylýk amaçlý fonksiyon
	head = iter;
	komsuInit(iter);
	firstInit(iter);
	graphInitializer(iter);
}
void searchStr(struct node *iter,char *str){
	//aranýn kelimenin verilen node'un direkt baðlantili olduðu nodelerda bulunup bulunmamasýna bakar bulunuyorsa aranma sayisini arttýrýr
	//yoksa hata mesaji döndürür.
	int i = 0;
	if(strcmp(iter->a,str) == 0) iter->aranmaSayisi++;
	else{
		while(i<iter->komsuSayisi && strcmp(str,iter->komsu[i]->a) != 0 ) i++;
		if(strcmp(str,iter->komsu[i]->a) == 0)iter->komsu[i]->aranmaSayisi++;
		else printf("Aradiginiz Kelime Bulunmamaktadir.\n");
	}
}
struct node *findLoc(struct node *iter,char *str){
	//verilen graph içerisinde istenen kelimenin bulunmasý icin
	int i;
	struct node *tmp =NULL;
	if(strcmp(iter->a,str) == 0){
		return iter;
	}
	for(i=0;i<iter->komsuSayisi;i++){
			if(strcmp(iter->komsu[i]->a,str) == 0){
				return iter->komsu[i];
			}
			else{
				if(iter->komsuSayisi != 1 && strcmp(iter->komsu[i]->a, head->a) != 0){
					tmp = findLoc(iter->komsu[i],str);
				}	
			}
			if(tmp != NULL){
				return tmp;
			}
	}
	return NULL;
}
int arrMaxInx(int *arr,int len){
	//verilen dizinin bulunan en büyük elemanýnýn indeksini döndürüyor
	int max;
	int i,j=0;
	max = arr[0];
	for(i=1;i<len;i++){
		if(arr[i] > max){
			max = arr[i];
			j=i;
		}
	}
	return j;	
}
void suggestThree(struct node *iter,char *str){
	//secilen kelimeye 3 öneride bulunmak icin
	int i;
	struct node *loc = findLoc(iter,str);
	if(loc == NULL){
		printf("Aranan Kelime Bulunmamaktadir Cikiliyor...\n");
		return;
	}
	if(loc->komsuSayisi > SUGGESTARR){
		int *arr = (int *)malloc(loc->komsuSayisi * sizeof(int));
		int arrLoc[SUGGESTARR];
		for(i=0;i<loc->komsuSayisi;i++){
			arr[i] = loc->komsu[i]->aranmaSayisi;
		}
		for(i=0;i<SUGGESTARR;i++){
			//SUGGESTARR degeri ödevdeki önerilmesi istenen sayidir yani 3;
			arrLoc[i] = arrMaxInx(arr,loc->komsuSayisi); 
			arr[arrMaxInx(arr,loc->komsuSayisi)] = -1;
		}
		for(i=0;i<SUGGESTARR;i++){
			printf("%s kelimesi %d kere aranmistir.\n",loc->komsu[arrLoc[i]]->a,loc->komsu[arrLoc[i]]->aranmaSayisi);
		}	
		free(arr);
	}
	else{
		for(i=0;i<loc->komsuSayisi;i++) printf("%s kelimesi %d kere aranmistir.\n",loc->komsu[i]->a,loc->komsu[i]->aranmaSayisi);	
	}	
}
void interface(struct node *graph1,struct node *graph2){
	callFunc(graph1);
	callFunc(graph2);
	head = graph1;
	char c[20];
	printf("Birinci Graf Icin Sorgulamak Istediginiz Kelimeyi Girin(Cikmak icin 'Q' Yaziniz.)\n");
	scanf("%s",c);
	while(!isExit(c)){
		searchStr(graph1,c);
		scanf("%s",c);
	}
	printf("Ikinci Graf Icin Sorgulamak Istediginiz Kelimeyi Girin(Cikmak icin 'Q' Yaziniz.)\n");
	scanf("%s",c);
	while(!isExit(c)){
		searchStr(graph2,c);
		scanf("%s",c);
	}
	mergeGraph(graph1,graph2); //iki graf birlestirilip graph1 üzerine yazilir.
	printf("Hangi Kelimeye Oneri Almak Istersiniz.\n");
	scanf("%s",c);
	suggestThree(graph1,c);	
}
int main(){
	
	struct node *graph1 = (struct node *)malloc(sizeof(struct node));
	struct node *graph2 = (struct node *)malloc(sizeof(struct node));
	interface(graph1,graph2);
	
	free(graph1);
	free(graph2);
	return 0;
	
}
