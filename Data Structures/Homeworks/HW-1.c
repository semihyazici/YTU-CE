#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
    char dir[20];
    struct node *sibling; 
    struct node *child;  
    struct node *parent;
};
struct node *head = NULL;
struct node *iter;

void mkdir(char *name){
	//directory olusturmak icin.
	if(head == NULL){
		head = (struct node *)malloc(sizeof(struct node));
		iter = head;
		strcpy(iter->dir,name);
		iter->child = NULL;
	}
	else if(iter->child == NULL){
		iter->child = (struct node*)malloc(sizeof(struct node));
		strcpy(iter->child->dir,name);
		iter->child->parent = iter;
		iter->child->child = NULL;
		iter->child->sibling = NULL;
	}
	else {
		if(isAvailable(name) == 1){
			struct node *tmp;
			tmp = iter->child;
			while(tmp->sibling != NULL){
				tmp = tmp->sibling;
			}
			tmp->sibling = (struct node*)malloc(sizeof(struct node));
			tmp->sibling->parent = iter;
			tmp->sibling->sibling = NULL;
			tmp->sibling->child = NULL;
			strcpy(tmp->sibling->dir,name);
		}
		else{
			printf("%s ismi zaten kullanilmis.\n",name);
		}
	}
}
void chdir(char *name){
	//directory icine girmek icin.
	if(strcmp(name,"..") != 0){
		if(findSibDir(name) == -1){
			printf("Belirtilen Ada Sahip Directory Bulunmamaktadýr.");
		}
		else{
			iter->child = NULL;
		}
	}
	else{
		if(iter == head){
			printf("Ust directory bulunamamaktadir.\n");
		}
		else{
			iter = iter->parent;
			printf("Suanda %s directorysindesiniz.\n",iter);
		}
	}
	
	
}

void rmdir(char *name){
	//directory silmek icin.
	if(delDir(name) == 1){
		printf("%s basariyla silindi.\n",name);
	}
	else if(delDir(name) == -2){
		printf("%s isimli directory yok.\n",name);
	}
	else {
		printf("%s isimli directorynin altýnda baska directoryler bulunuyor bu yüzden silinemez.\n",name);
	}
	
}
int isAvailable(char *name){
	//name'in daha önce kullanýlýp kullanýlmadigini soyler.
	struct node *tmp = iter->child;
	
	while(tmp != NULL){
		
		if(strcmp(tmp->dir,name) == 0){
			return -1;
		}
		tmp = tmp->sibling;
	}
	return 1;
	
	
}
int delDir(char *name){
	//istenilen directorynin silinmesi icin.
	struct node *tmp = iter->child;
	
	if(tmp->child == NULL && strcmp(tmp->dir,name) == 0){
		iter->child = tmp->sibling;
		return 1;	
	}
	else{
		if(tmp != NULL){
			while(tmp->sibling != NULL && strcmp(tmp->sibling->dir,name) != 0){
				tmp = tmp->sibling;
			}
			if(tmp->sibling != NULL && isChild(tmp->child) == 0){
				tmp->sibling = tmp->sibling->sibling;
				return 1;
			}
			else if(tmp->sibling != NULL){
				return -1;
			}
			else{
				return -2;
			}
		}	
	}
}
void dir(){
	//bulunan directorydenin altinda bulunan directoryleri gostermek icin.
	struct node *tmp = iter->child;
	printf("%s directorynin altinda bulunan directoryler\n",iter->dir);
	while(tmp->sibling != NULL){
		printf("%s\n",tmp->dir);
		tmp = tmp->sibling;
	}
	if(tmp != NULL){
		printf("%s\n",tmp->dir);
	}
}
int isChild(struct node *temp){
	//silme islemi yaparken altinda cocugun olup olmadýgýný kontrol etmek icin.
	struct node *tmp = temp;
	int i=0;
	while(tmp->sibling != NULL){
		tmp = tmp->sibling;
		i++;
	}
	return i;
}
void count(){
	struct node *tmp = iter->child;
	int i=0;
	while(tmp != NULL){
		tmp = tmp->sibling;
		i++;
	}
	if(i>0){
		printf("%s adli directorynin altinda %d tane directory vardir\n",iter->dir,i);
	}
	else{
		printf("%s adli directorynin altinda hic directory yoktur.\n",iter->dir);
	}
}
int findSibDir(char *name){
	//siblingler icerisinde aranan isme sahip var mý kontrolu
	struct node *tmp = iter->child;
	while(tmp->sibling != NULL && strcmp(tmp->dir,name) != 0){
		tmp = tmp->sibling;
	}
	if(strcmp(tmp->dir,name) == 0){
		iter = tmp;
		return 1;
	}
	else{
		return -1;
	}
}
void interface(){
	//konsoldan giris yapmak icin.
	char operation[20];
	char directory[20];
	printf("Cikis yapmak icin 'cik' yaziniz.\n");
	scanf("%s",operation);
	while(strcmp(operation,"cik") !=0 ){
		if(strcmp(operation,"mkdir") == 0){
			scanf("%s",directory);
			mkdir(directory);
			printf("%s directorysi olusturuldu.\n",directory);
		}
		else if(strcmp(operation,"chdir") == 0){
			scanf("%s",directory);
			chdir(directory);
			if(strcmp(directory,"..") == 0){
				printf("Directoryden cikiliyor.\n");
			}			
		}
		else if(strcmp(operation,"rmdir") == 0){
			scanf("%s",directory);
			rmdir(directory);
		}
		else if(strcmp(operation,"dir") == 0){
			dir();
		}
		else if(strcmp(operation,"count") == 0){
			count();
		}
		else{
			printf("Yanlis komut girildi.");
		}
			scanf("%s",operation);	
	}
}
int main(){
	printf("Root yerlesterildikten sonra chdir ile icine girilmiyor direkt yeni node olusturulmali.\nOrn:\nmkdir a\nmkdir b\nchdir b\n");
	interface();
	return 0;	
}
