#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<unistd.h>
#include<string.h>
#define CREDIT_LIMIT 22 ///bir ögrencinin alabileceði maks kredi
/*


		Semih Yazici 19011087 
		Bu kod DevC++ 5 ile yazilmistir.
		Win10 isletim sistemi.									*/

struct Lecture{
	
	char id[10];
	char name[30];
	int acad_id;
	int credit;
	int lect_pop;
	
	

};
struct Student{
	
	int id;
	char name[30];
	char surname[20];
	int total_credit;
	
	
	
};
struct Academician{
	
	int id;
	char name[30];
	char surname[20];
	char title[20];
	
	
	
};

typedef struct Student student;
typedef struct Academician academician;
typedef struct Lecture lecture;

void currentAcademcians(FILE *,academician *);
void deleteLine(FILE *,student *);
void showLectStu(FILE *,FILE *,FILE *,student *,lecture *);
void createClassroom(FILE *,FILE *,FILE *, FILE *,student *,lecture *,academician *);
void screenReturn(FILE *,FILE *,FILE *,FILE *,student *,academician *,lecture * );
void studentLect(FILE *,FILE *,FILE *,FILE *,student *,academician *,lecture *);
void updateAcademician(FILE *,FILE *,FILE *,FILE *,student *,academician *,lecture *);
void updateStudent(FILE *,FILE *,FILE *,FILE *,student *,academician *,lecture *);
void screen(FILE *,FILE *,FILE *,FILE *,student *,academician *,lecture *);



int findLineNum(FILE *fptr){
	char c;		//dosyanýn satýr sayýsýný söylüyor
	int tmp=0;
	rewind(fptr); 
	while(!feof(fptr)){
		c = fgetc(fptr);
		if(c=='\n') tmp++;
		
	}
	
	return tmp;
	
	
}
void update(FILE *fptr,student *s){

			////güncelleme islemi icin
	int i;
	int len = findLineNum(fptr);
	fseek(fptr,SEEK_SET,0);
	for(i=0;i<len;i++){
		
		fprintf(fptr,"%d %s %s %d\n",s[i].id,s[i].name,s[i].surname,s[i].total_credit);
		
	}
	
}
int findLect(FILE *flec,lecture *l,char *ID){
	int limit = findLineNum(flec);
	int i=0;
	while(i < limit && (strcmp(l[i].id,ID)) != 0 ){
		i++;
	}
	if(i>=limit){

		return -1;
	}
	else{
		return i;
	}
	
	
}
void addToLog(FILE *flog,int stuID,char *lecID,char *status){
						//log dosyasýna ekleme yapýyor status ekledi(1) sildi(-1) anlamýna geliyor. 
	while(!feof(flog)){
		fgetc(flog);
	}						//bu calisiyor fseek bir sebepten calismiyordu
	
	fprintf(flog,"%d %s %s %s %s\n",stuID,lecID,status,__TIME__,__DATE__);
	
	
	
	
}
int findAcaID(FILE *fstd,academician *s,int val){
	//akademisyenin var olup olmadýðýna bakýyor varsa konumunu yoksa -1 döndürüyor
	int limit = findLineNum(fstd);
	int i=0;
	while(i < limit && s[i].id != val){
		i++;
	}
	if(i>=limit){
		return -1;
	}
	else{
		return i;
	}
	
	
}
int findLecID(FILE *fstd,lecture *s,char *lecName){
	//dersin var olup olmadýðýna bakýyor varsa konumunu yoksa -1 döndürüyor
	int limit = findLineNum(fstd);
	int i=0;
	while(i < limit && strcmp(s[i].id,lecName) != 0){
		i++;
	}
	if(i>=limit){
		return -1;
	}
	else{
		return i;
	}
	
	
}
int findID(FILE *fstd,student *s,int val){
	//öðrencinin var olup olmadýðýna bakýyor varsa konumunu yoksa -1 döndürüyor
	int limit = findLineNum(fstd);
	int i=0;
	while(i < limit && s[i].id != val){
		i++;
	}
	if(i>=limit){
		return -1;
	}
	else{
		return i;
	}
	
	
}
void addStu(FILE *fstd,FILE *flec,FILE *flog,FILE *faca,student *s,academician *a,lecture *l){
	//öðrenci ekleme iþlemi dosyaya
	system("cls");
	///dosyaya ögreci eklmek icin
	int len = findLineNum(fstd);
	printf("Ogrencinin ID'sini Girin: ");
	scanf("%d",&s[len].id);
	printf("Ogrencinin Ismini Girin: ");
	scanf("%s",s[len].name);
	printf("Ogrencinin Soyismini Girin: ");
	scanf("%s",s[len].surname);
	
	if(findID(fstd,s,s[len].id) == -1){
		//fseek(fstd,SEEK_END,0);
		fprintf(fstd,"%d %s %s %d\n",s[len].id,s[len].name,s[len].surname,0);
		int i;
		
		printf("Ogrenci Basariyla Eklendi.\n");
		
	}
	else {
		printf("Islem Gerceklestirilemedi,Ogrenci ID'si Zaten Bulunuyor.\n");
	}
	//sleep(5);
	
	screenReturn(fstd,faca,flec,flog,s,a,l);
	
	
}
void screenReturn(FILE *fstd,FILE *faca,FILE *flec,FILE *flog,student *s,academician *a,lecture *l ){
		//her seferinde ana ekrana dönüþü saðlýyor
		sleep(1);
		system("cls");
		printf("Ana Ekrana Donuluyor.\n");
		sleep(1);
		system("cls");
		screen(fstd,faca,flec,flog,s,a,l);
}
void addAca(FILE *fstd,FILE *flec,FILE *flog,FILE *faca,student *s,academician *a,lecture *l){
	//akademisyen ekleme yapýyor dosyaya
	int len = findLineNum(faca);
	
	///dosyaya akademisyen eklemek icin 
	printf("Akademisyen ID'sini Girin: ");
	scanf("%d",&a[len].id);
	printf("Akademisyen Adini Girin: ");
	scanf("%s",a[len].name);
	printf("Akademisyen Soyismini Girin: ");
	scanf("%s",a[len].surname);
	printf("Akademisyen Unvanini Girin: ");
	scanf("%s",a[len].title);
	//fseek(fstd,0,SEEK_END);
	
	if(findAcaID(faca,a,a[len].id) == -1){
		fprintf(faca,"%d %s %s %s\n",a[len].id,a[len].name,a[len].surname,a[len].title);
		printf("Akademisyen Basariyla Eklendi.\n");
	}
	else{
		printf("ID' Coktan Alinmis.\n");
		
	}
	

	
	
	
}
void addLec(FILE *fstd,FILE *faca,FILE *flec,FILE *flog,student *s,academician *a,lecture *l ){
	//dosyaya ders ekliyor
	system("cls");
	/////dosyaya ders eklemek icin öggrenciye ders eklemek icin degil!!
	int len = findLineNum(flec);
	printf("Dersin ID'sini Girin:");
	scanf("%s",l[len].id);
	printf("Dersin Ismini Girin:");
	scanf("%s",l[len].name);
	printf("Dersin Kredisini Girin:");
	scanf("%d",&l[len].credit);
	printf("Dersin En Fazla Kisi Sayisini Girin:");
	scanf("%d",&l[len].lect_pop);
	printf("Dersi Veren Akademisyenin ID'sini Girin:");
	scanf("%d",&l[len].acad_id);
	//fseek(fstd,0,SEEK_END);
	
	
	
	if(findLect(flec,l,l[len].id) == -1){
		fprintf(flec,"%s %s %d %d %d\n",l[len].id,l[len].name,l[len].credit,l[len].lect_pop,l[len].acad_id);
		printf("Ders Basariyla Eklendi.\n");
	}
	else printf("Dersin ID'si Mevcut Ders Eklenemedi.\n");
	
	
	
	
}
void readStudent(FILE *fstd,student *s){
	//structýn içini öðrenci dosyasýndan gelen bilgilerler dolduruyor
	int i = 0;
	rewind(fstd);
	while(!feof(fstd)){
		
		fscanf(fstd,"%d %s %s %d",&s[i].id,s[i].name,s[i].surname,&s[i].total_credit);
		
		i++;
	}
	
	
	
}
void readAcademican(FILE *faca,academician *a){
	//structýn içini öðretmenler dosyasýndan gelen bilgilerler dolduruyor
	fseek(faca,SEEK_SET,0);
	int i = 0;
	while(!feof(faca)){
		
		fscanf(faca,"%d %s %s %s",&a[i].id,a[i].name,a[i].surname,a[i].title);
		
		i++;
	}
	
	
}
void readLecture(FILE *flec,lecture *l){
	//structýn içini dersler dosyasýndan gelen bilgilerler dolduruyor
	fseek(flec,SEEK_SET,0);
	int i = 0;
	while(!feof(flec)){
		
		fscanf(flec,"%s %s %d %d %d",l[i].id,l[i].name,&l[i].credit,&l[i].lect_pop,&l[i].acad_id);
	
		i++;
	}
	
	
}
void nameSeperator(char *str){
	
	//iki isimlileri(_ ile baðlanan isimleri) ayiriyor 
	//dersler için de aynýsýný yapýyor 
	int i;
	for(i=0;str[i]!='\0';i++){
		if(str[i] == '_') {
			str[i] = ' ';
		}
	}
	
}
void nameReShaper(char *str){
	//dosyanýn üzerine yazarken formatýn bozulmamasý için tekrardan eski haline döndürüyor
	//nameSeperator fonksiyonunun tersini yapýyor
	int i;
	for(i=0;str[i]!='\0';i++){
		if(str[i] == ' ') {
			str[i] = '_';
		}
	}
	
}
void currentStudents(FILE *fstd,student *s){
	//anlýk olarak bulunan öðrencileri gösteriyor
	int i;
	rewind(fstd);
	int len = findLineNum(fstd);
	printf("ID     ISIM         SOYISIM    TOPLAM KREDI\n\n");
	for(i=0;i<len;i++){
		//printFormat() düzgün formatta yazmak icin bu lazým sonra hallet bunu
		
		
		nameSeperator(s[i].name);
		printf("%-6d %-16s %-16s %-5d\n",s[i].id,s[i].name,s[i].surname,s[i].total_credit);
		nameReShaper(s[i].name);	
	}
	
}
void delAca(FILE *faca,academician *a){
	//akademisyen silmek için kullanýlan fonksiyon
	int choice;
	int line;
	system("cls");
	printf("Akademisyen Listesini Goruntulemek Ister Misiniz?\nEvet->1\nHayir->0\n");
	scanf("%d",&choice);
	
	switch (choice){
		
		case 0:
			break;
		case 1:
			currentAcademcians(faca,a);
			break;
		
		
	}
	
	printf("Hangi Akademisyeninin Kaydini Silmek Istersiniz?(ID)\n");
	
	scanf("%d",&choice);
	
	line = findAcaID(faca,a,choice);
	
	if(line != -1){
		FILE *fcpy = fopen("input_copy.txt","w");
		if(fcpy == NULL ){
			printf("FCOPY Hatasi");
		}
	
	
	int tmp = 0;
	/////// calisiyor
	
	char c;
	
	
	fseek(faca,SEEK_SET,0);
	while((c=getc(faca))!=EOF){
		
		
		
		if(c == '\n'){
			
			if(tmp != line-1){
				fprintf(fcpy,"\n");
			}
			
			
			tmp++;
		}
		else if(tmp != line){
			fprintf(fcpy,"%c",c);
		}

		
	}
		fclose(fcpy);
		fclose(faca);
		char name1[30] = "input_copy.txt";	
		char name2[30] = "ögretmenler.txt";
		remove(name2);
		rename(name1,name2);
	
		faca = fopen("ögrenciler.txt","r+");			
	
		printf("Akademisyen Silindi.\n");
	}
	
	else{
		printf("Akademisyen ID'si Yanlis.\n");
	}
	
	
	
	
	
	
}
void delLec(FILE *fstd,FILE *flec,FILE *flog,FILE *faca,student *s,academician *a,lecture *l){
	//bir öðrenciden bir dersi silmek için
	char *lecName = (char *)malloc(20*sizeof(char));
	int choice;
	system("cls");
	printf("Hangi Ogrencinin Dersini Silmek Istersiniz.(Ogrenci Listesini Goruntulemek Icin 1 Goruntulememek icin 0)\n");
	scanf("%d",&choice);
	switch (choice){
		case 0:
			break;
		case 1:
			system("cls"); ////sistem ekran silme komutu
			readStudent(fstd,s);
			currentStudents(fstd,s);
			break;
		default:
			printf("Uygun Olmayan Sayi Cikiliyor");
			break;
		
	}
	int stuID;
	printf("Sorgulamak Istediginiz Ogrencinin ID'sini Girin.\n");
	scanf("%d",&stuID);
	if(findID(fstd,s,stuID)== -1) {
		printf("Ogrenci ID'si Yanlis.\n");
		
		
	}
	
	
	printf("Ogrencinin Aldigi Dersleri Goruntulemek Ister Misiniz?\nEvet->1\nHayir->0\n");
	scanf("%d",&choice);
	
	
	int tmp = 1,i;
	int limit = findLineNum(flec);
	
	
	switch (choice){
		case 0:
			break;
		case 1:
			printf("Ogrencinin Aldigi Dersler...\n");
			for(i=0;i<limit;i++){
				strcpy(lecName,l[i].id);
		
				if(showStudentLect(flog,stuID,lecName) == 1){
				printf("%d->%s %s\n",tmp,lecName,l[i].name);
				tmp++;
			}
		
		}
		if(tmp == 1){
			system("cls");
			printf("Ogrenci Ders Almamis\n");
			
		}
		break;
		default:
			printf("Uygun Olayan Sayi Girildi.\n");
			break;
	}
	
	
	
	
	
	int id,locStu,locLec;
	
	printf("Silmek Istediginiz Dersin Kodunu Giriniz.\n");
	scanf("%s",lecName);
	int lecTaken = showStudentLect(flog,stuID,lecName);
	
	locStu = findID(fstd,s,stuID);
	locLec = findLect(flec,l,lecName);
	
	if(locLec != -1 && lecTaken == 1){
		s[locStu].total_credit -= l[locLec].credit;
		update(fstd,s); //dosyayý tekrardan yazdýk
	
	//currentStudents(fstd,s);///suanda dogruluk kontrolü yapmýyor dogru bilgiler girildiði varsayiliyor
	
		addToLog(flog,stuID,lecName,"-1"); ///'1' ekledi '-1' sildi anlamýnda	
		printf("Ders Basariyla Silindi.\n");
		
		
	}
	else if(lecTaken != 1){
		printf("Ogrenci Dersi Almamis.\n");
	}
	else{
	
		printf("Ders Kodu Yanlis Girildi.\n");
		
		
	}
	
	
	
	
}
void currentLectures(FILE *flec,lecture *l){
	//anlýk olarak bulunan dersleri gösteriyor
	int i;
	rewind(flec);
	int len = findLineNum(flec);
	printf("ID            ISIM                             KREDI  POPULASYON   AKADEMISYEN ID'SI        \n\n");
	for(i=0;i<len;i++) {
		nameSeperator(l[i].name);
		//printf("%s        %d         %d         %d            %s\n",l[i].id,l[i].credit,l[i].lect_pop,l[i].acad_id,l[i].name);
		
		printf("%-12s %-35s %-7d %-13d  %-4d\n",l[i].id,l[i].name,l[i].credit,l[i].lect_pop,l[i].acad_id);
		nameReShaper(l[i].name);	
	}
	
	
}
void addLecToStu(FILE *fstd,FILE *faca,FILE *flec,FILE *flog,student *s,academician *a,lecture *l){
	//öðrenciye ders ekleme iþlemi
	system("cls");
	int choice;
	printf("Hangi Ogrenciye Dersi Eklemek Istersiniz.(Ogrenci Listesini Goruntulemek Icin 1 Goruntulememek icin 0)\n");
	scanf("%d",&choice);
	switch (choice){
		case 0:
			break;
		case 1:
			system("cls"); ////sistem ekran silme komutu
			readStudent(fstd,s);
			currentStudents(fstd,s);
			break;
		default:
			printf("Uygun Olmayan Sayi Cikiliyor");
			break;
		
	}
	printf("\nDersleri Goruntulemek Icin 1 Goruntulememek icin 0.\n");
	scanf("%d",&choice);
	switch(choice){
		case 0:
			break;
		case 1:
			readLecture(flec,l); ///dosyanýn degismesi ihtimaline karsi her daim yeniden okuyor.
			currentLectures(flec,l);
			break;
			
	}
	int id,locStu,locLec;
	char *lecName = (char *)malloc(20*sizeof(char));
	printf("Dersi Eklemek Ýstediginiz Ogrencinin ID'si Ve Dersin Kodunu Sirasiyla Giriniz.\n");
	scanf("%d%s",&id,lecName);
	
	
	
	locStu = findID(fstd,s,id);
	locLec = findLect(flec,l,lecName);
	int currentPopulation = lectPopulation(flog,fstd,s,lecName);
	int lecTaken = showStudentLect(flog,id,lecName);
	
	if(s[locStu].total_credit+l[locLec].credit <= CREDIT_LIMIT && currentPopulation < l[locLec].lect_pop && lecTaken != 1){
		
		
		s[locStu].total_credit += l[locLec].credit;
		update(fstd,s); //dosyayý tekrardan yazdýk
	
		//currentStudents(fstd,s);///suanda dogruluk kontrolü yapmýyor dogru bilgiler girildiði varsayiliyor
	
		addToLog(flog,id,lecName,"1"); ///'E' ekledi 'S' sildi anlamýnda
		printf("Ders Basariyla Eklendi.\n");
		
	}
	else if(lecTaken == 1){
		printf("Ogrenci Dersi Zaten Almis.\n");
	}
	else if(s[locStu].total_credit+l[locLec].credit > CREDIT_LIMIT){
		printf("Ogrencinin Bu Dersi Almasi Mumkun Degil Kredi Yetersiz.\n");
	} 
	else if(currentPopulation >= l[locLec].lect_pop){
		printf("Ders Kapasitesine Erisildi Ders Eklenemez.\n");
	}
	
	else {
		printf("Ders Kredi ve Kapasite Yüzünden Eklenemez.\n");
	}
	
	
	//ders kredi sinirlarina uyuyor
	
	free(lecName);
	
}
void currentAcademcians(FILE *faca,academician *a){
	//anlýk olarak bulunan akademisyenleri gösteriyor
	int limit = findLineNum(faca);
	
	int i;
	printf("ID     ISIM             SOYISIM           UNVAN\n\n");
	for(i=0;i<limit;i++){
		nameSeperator(a[i].name);
		printf("%-6d %-16s %-16s %-10s    \n",a[i].id,a[i].name,a[i].surname,a[i].title); ////formatlanmasý gerek
		nameReShaper(a[i].name);	
	}
	
	
}
void lectGivenByAca(FILE *flec,lecture *l,int acaID){
	//bir akademisyenin verdiði dersleri gösteren fonksiyon kullanýyor
	int limit = findLineNum(flec);
	int i;
	int tmp = 1;
	for(i=0;i<limit;i++){
		
		if(l[i].acad_id == acaID){
			printf("%d->%s %s \n",tmp,l[i].id,l[i].name);
			tmp++;
		}
		
	}
	
	
	
	
}
void propAca(FILE *faca,FILE *flec,lecture *l,academician *a){
	//bir akademisyenin verdiði dersleri gösteren fonksiyon
	system("cls");
	int choice;
	
	printf("Akademisyen Listesini Goruntulemek Ister misiniz?\nEvet->1\nHayir->0\n");
	scanf("%d",&choice);
	
	switch(choice){
		
		case 0:
			break;
		case 1:
			readAcademican(faca,a);
			currentAcademcians(faca,a);
			break;
		
	}
	
	printf("Hangi Akademisyenin Dersilerini Sorgulamak Istiyorsunuz?(ID)\n");
	scanf("%d",&choice);
	
	
	int loc = findAcaID(faca,a,choice);
	if(loc != -1){
		printf("%d ID'sine Sahip %s %s %s'nin Verdigi Dersler.\n",a[loc].id,a[loc].title,a[loc].name,a[loc].surname);
		
		lectGivenByAca(flec,l,choice);

		
	}
	
	
	
	
}
void studentOperation(FILE *fstd,FILE *flec,FILE *flog,FILE *faca,student *s,academician *a,lecture *l){
	//genel öðrenci iþlemlerini bulunduran fonksiyon
	//bu fonksiyondan iþlemlere geçiþ yapýlýyor
	int loc;
	
	
	readStudent(fstd,s);
	int choice;
	
	sleep(1);
	system("cls");
	
	printf("-------------------------------------------\n");
	printf("|Islemler:		                  |\n");
	printf("|1->Ogrenci Eklemek		          |\n");
	printf("|2->Ogrenciye Ders Eklemek                |\n");
	printf("|3->Ogrencinin Ders Kaydini Silmek        |\n");
	printf("|4->Ogrencinin Aldigi Dersleri Goruntule  |\n");
	printf("|5->Ogrencinin Bilgilerini Guncellemek    |\n");
	printf("|6->Ogrenci Listesi                       |\n");
	printf("|7->Ogrenci Silmek                        |\n");
	printf("|8->Cikis                                 |\n");
	printf("-------------------------------------------\n");
	
	
	scanf("%d",&choice);
											
		switch (choice){
		
		case 1:
			addStu(fstd,flec,flog,faca,s,a,l);
			screenReturn(fstd,faca,flec,flog,s,a,l);
			break;
		case 2:
			addLecToStu(fstd,faca,flec,flog,s,a,l);
			screenReturn(fstd,faca,flec,flog,s,a,l);
			break;
		case 3:
			delLec(fstd,flec,flog,faca,s,a,l);
			screenReturn(fstd,faca,flec,flog,s,a,l);
			break;
		case 4:
			
			studentLect(fstd,faca,flec,flog,s,a,l);
			screenReturn(fstd,faca,flec,flog,s,a,l);
			break;
		case 5:
			updateStudent(fstd,faca,flec,flog,s,a,l);
			break;
		case 6:
			system("cls");
			currentStudents(fstd,s);
			sleep(3);
			screenReturn(fstd,faca,flec,flog,s,a,l);
			break;
		case 7:
			deleteLine(fstd,s);
			screenReturn(fstd,faca,flec,flog,s,a,l);
			break;
		case 8:
			printf("Cikiliyor\n");
			screenReturn(fstd,faca,flec,flog,s,a,l);
			break;
		default:
			printf("Uygun Bir Sayi Girilmedi Cikiliyor...");
			screenReturn(fstd,faca,flec,flog,s,a,l);
		break;		
		
		
		}
	

}
void academicianOperation(FILE *flog,FILE *faca,FILE *flec,FILE *fstd,academician *a,lecture *l,student *s){
	//genel akademisyen iþlemlerini bulunduran fonksiyon
	//bu fonksiyondan iþlemlere geçiþ yapýlýyor
	int loc;
	readAcademican(faca,a);
	int choice;
	system("cls");
	
	printf("-------------------------------------------\n");
	printf("|Islemler:		                     |\n");
	printf("|1->Akademisyen Eklemek		             |\n");
	printf("|2->Akademisyen Silmek                       |\n");
	printf("|3->Verilen Dersleri Goruntule               |\n");
	printf("|4->Verilen Dersin Sinif Listesi             |\n");
	printf("|5->Akamademisyen Bilgilerini Guncellemek    |\n");
	printf("|6->Akademisyen Listesi                      |\n");
	printf("|7->Cikis                                    |\n");
	printf("-------------------------------------------\n");
	
	
	
	
	
	scanf("%d",&choice);
	
	switch (choice){
		
		case 1:
			system("cls");
			addAca(fstd,flec,flog,faca,s,a,l); 
			screenReturn(fstd,faca,flec,flog,s,a,l);
			break;
		case 2:
			delAca(faca,a);
			screenReturn(fstd,faca,flec,flog,s,a,l);
			break;
		case 3:
			propAca(faca,flec,l,a); 
			screenReturn(fstd,faca,flec,flog,s,a,l);

			break;
		case 4:
			createClassroom(flog,faca,fstd,flec,s,l,a);
			screenReturn(fstd,faca,flec,flog,s,a,l);
			break;
		case 5:
			updateAcademician(fstd,faca,flec,flog,s,a,l);
			screenReturn(fstd,faca,flec,flog,s,a,l);
			break;
		case 6:
			currentAcademcians(faca,a);
			screenReturn(fstd,faca,flec,flog,s,a,l);
			break;
		case 7:
			printf("Cikiliyor.\n");
			screenReturn(fstd,faca,flec,flog,s,a,l);
			
			
			break;
		default:
			
			printf("Uygun Bir Sayi Girilmedi Cikiliyor...");
			screenReturn(fstd,faca,flec,flog,s,a,l);
		break;		
		
	}

}
void updateLec(FILE *flec,lecture *s){
	//bulunan bir dersi güncellemek için kullanýlan fonksiyon
	system("cls");
	int choice;
	printf("Ders Listesini Goruntulemek Icin 1 Goruntulememek icin 0.\n");
	scanf("%d",&choice);
	switch (choice){
		case 0:
			break;
		case 1:
			readLecture(flec,s);
			currentLectures(flec,s);
			break;
		default:
			printf("Uygun Sayi Girilmedi Cikiliyor\n");
			break;
	}
	printf("Hangi Ders Bilgilerini Guncellemek Isterseniz O Dersin ID'sini Girin .\n");
	
	char *lectName = (char *)malloc(20*sizeof(char));
	scanf("%s",lectName);
	
	
	int len = findLineNum(flec);
	int loc = findLecID(flec,s,lectName);
	if(loc != -1){
		//printf("%d Ogrencinin Bilgileri %d %s %s ",s[line].id,s[line].name,s[line].surname);
		printf("Yeni bilgilerini giriniz(ID,DERSISMI,KREDI,SINIFSAYISI,AKADEMISYEN ID'si sirasi ile)\n");
		scanf("%s%s%d%d%d",s[loc].id,s[loc].name,&s[loc].credit,&s[loc].lect_pop,&s[loc].acad_id);
	
			////güncelleme islemi icin
		int i;
	
		rewind(flec);
		for(i=0;i<len;i++){
		
			if(i != len-1){
				fprintf(flec,"%s %s %d %d %d\n",s[i].id,s[i].name,s[i].credit,s[i].lect_pop,s[i].acad_id);
			}
			else fprintf(flec,"%s %s %d %d %d",s[i].id,s[i].name,s[i].credit,s[i].lect_pop,s[i].acad_id);
			
		
		}
	}
	
	
	
	
	
	
}
void delLecture(FILE *flec,lecture *l){
	//ders silmek için kullanýlan fonksiyon
	int choice;
	int line;
	system("cls");
	printf("Ders Listesini Goruntulemek Ister Misiniz?\nEvet->1\nHayir->0\n");
	scanf("%d",&choice);
	
	switch (choice){
		
		case 0:
			break;
		case 1:
			currentLectures(flec,l);
			break;
		
		
	}
	
	printf("Hangi Dersi Silmek Istersiniz?(ID)");
	char *lectName = (char *)malloc(10*sizeof(char));
	scanf("%s",lectName);
	
	line = findLecID(flec,l,lectName);
	
	if(line != -1){
		FILE *fcpy = fopen("input_copy.txt","w");

	
	
	int tmp = 0;
	/////// calisiyor
	
	char c;
	
	
	fseek(flec,SEEK_SET,0);
	while((c=getc(flec))!=EOF){
		
		//c = getc(fptr);
		
		if(c == '\n'){
			
			if(tmp != line-1){
				fprintf(fcpy,"\n");
			}
			
			
			tmp++;
		}
		else if(tmp != line){
			fprintf(fcpy,"%c",c);
		}

		
	}
		fclose(fcpy);
		fclose(flec);
		char name1[30] = "input_copy.txt";		////isim olayýna bakmak gerek
		char name2[30] = "dersler.txt";
		remove(name2);
		rename(name1,name2);
	
		flec = fopen("dersler.txt","r+");			////deger yazdýrmadan önce structý yeniden þekillendirmek gerek
	
		printf("Ders Silindi.\n");
	}
	
	else{
		printf("Ders ID'si Yanlis.\n");
	}
	
	
	
	
}
void lectureOperation(FILE *flec,FILE *flog,FILE *faca,FILE *fstd,lecture *l,student *s,academician *a){
	//genel ders iþlemlerini bulunduran fonksiyon
	//bu fonksiyondan iþlemlere geçiþ yapýlýyor
	int loc;
	readLecture(flec,l);
	int choice;
	printf("Ne yapmak istersiniz...\n");
	sleep(1);
	system("cls");
	printf("-----------------------------------\n");
	printf("|Islemler:		          |\n");
	printf("|1->Ders Eklemek		  |\n");
	printf("|2->Ders Silmek	                  |\n");
	printf("|3->Ders Bilgilerini Guncellemek  |\n");
	printf("|4->Sinif Listesi Olustur         |\n");
	printf("|5->Cikis		          |\n");
	printf("-----------------------------------\n");	
	
	scanf("%d",&choice);
	
	switch (choice){
		
		case 1:
			addLec(fstd,faca,flec,flog,s,a,l);
			screenReturn(fstd,faca,flec,flog,s,a,l);
			break;
		case 2:
			delLecture(flec,l); //
			screenReturn(fstd,faca,flec,flog,s,a,l);
			break;
		case 3:
			updateLec(flec,l); 
			screenReturn(fstd,faca,flec,flog,s,a,l);
			break;
		case 4:
			showLectStu(flog,fstd,flec,s,l);
			//screenReturn(fstd,faca,flec,flog,s,a,l);
			break;
		case 5:
			printf("Cikiliyor\n");
			screenReturn(fstd,faca,flec,flog,s,a,l);
			break;
			
		default:
			printf("Uygun Bir Sayi Girilmedi Cikiliyor...");
			screenReturn(fstd,faca,flec,flog,s,a,l);
			break;		
		
	}

}
void deleteLine(FILE *fstd,student *s){
	//öðrenci silmek iin kullanýlan fonksiyon
	int choice;
	int line;
	system("cls");
	printf("Ogrenci Listesini Goruntulemek Ister Misiniz?\nEvet->1\nHayir->0\n");
	scanf("%d",&choice);
	
	switch (choice){
		
		case 0:
			break;
		case 1:
			currentStudents(fstd,s);
			break;
		
		
	}
	
	printf("Hangi Ogrenciyi Silmek Istersiniz?(ID)");
	scanf("%d",&choice);
	
	line = findID(fstd,s,choice);
	
	if(line != -1){
		FILE *fcpy = fopen("input_copy.txt","w");

	
	
	int tmp = 0;
	/////// calisiyor
	
	char c;
	
	
	fseek(fstd,SEEK_SET,0);
	while((c=getc(fstd))!=EOF){
		
		//c = getc(fptr);
		
		if(c == '\n'){
			
			if(tmp != line-1){
				fprintf(fcpy,"\n");
			}
			
			
			tmp++;
		}
		else if(tmp != line){
			fprintf(fcpy,"%c",c);
		}

		
	}
		fclose(fcpy);
		fclose(fstd);
		char name1[30] = "input_copy.txt";		////isim olayýna bakmak gerek
		char name2[30] = "ögrenciler.txt";
		remove(name2);
		rename(name1,name2);
	
		fstd = fopen("ögrenciler.txt","r+");			////deger yazdýrmadan önce structý yeniden þekillendirmek gerek
	
		printf("Ogrenci Silindi.\n");
	}
	
	else{
		printf("Ogrenci ID'si Yanlis.\n");
	}
	
	
	
	
}
int lectPopulation(FILE *flog,FILE *fstu,student *s,char *lectName){
	///bir dersi alan ögrenci sayisini donduruyor bu sekilde populasyondan fazla ogrenci ekleyemez
	int i;
	int limit = findLineNum(fstu);
	int tmp = 1;
	for(i=0;i<limit;i++){
		
		if(showStudentLect(flog,s[i].id,lectName) == 1){ ///bu fonksiyon sayesinde dersin bulunup bulunmadýðýný anlýyor
			
			
			tmp++;
		}
		
		
	}
	return tmp;
	
}
void showLectStu(FILE *flog,FILE *fstu,FILE *flec,student *s,lecture *l){
	system("cls");
	//id'si girilen akademisyenin verdiði bir dersin sinif listesini oluþturan fonksiyon içinde kullanýlan fonksiyon
	int i;
	int limit = findLineNum(fstu);
	int tmp = 1;
	currentLectures(flec,l);
	char *lectName = (char *)malloc(30*sizeof(char));
	printf("\nHangi Dersin Sinif Listesini Olusturmak Istersiniz.\n");
	scanf("%s",lectName);
	for(i=0;i<limit;i++){
		
		if(showStudentLect(flog,s[i].id,lectName) == 1){ ///eðer bir öðrenci dersi aliyorsa 1 döndürüyor ve bastiriyor
			
			printf("%d->%d %s %s\n",tmp,s[i].id,s[i].name,s[i].surname);
			
			tmp++;
		}
		
		
	}
	
	free(lectName);
}
void showStuList(FILE *flog,FILE *fptr,FILE *fstu,student *s,char *lectName){
	//id'si girilen akademisyenin verdiði bir dersin sinif listesini oluþturan fonksiyon içinde kullanýlan fonksiyon
	int i;
	int limit = findLineNum(fstu);
	int tmp = 1;
	for(i=0;i<limit;i++){
		
		if(showStudentLect(flog,s[i].id,lectName) == 1){ ///eðer bir öðrenci dersi aliyorsa 1 döndürüyor ve bastiriyor
			
			printf("%d->%d %s %s\n",tmp,s[i].id,s[i].name,s[i].surname);
			fprintf(fptr,"%d->%d %s %s\n",tmp,s[i].id,s[i].name,s[i].surname);
			tmp++;
		}
		
		
	}
	
	
}
void createClassroom(FILE *flog,FILE *faca,FILE *fstd, FILE *flec,student *s,lecture *l,academician *a){
	//id'si girilen akademisyenin verdiði bir dersin sinif listesini oluþturan fonksiyon
	int choice;
	system("cls");
	
	
	
	printf("Akademisyen Listesini Goruntulemek Ister Misiniz?\nEvet->1\nHayir->0\n");
	scanf("%d",&choice);
		
	switch(choice){
		
		case 0:
			break;
		case 1:
			readAcademican(faca,a);
			currentAcademcians(faca,a);
			break;
		default:
			printf("Uygun Sayi Girilmedi Cikiliyor.\n");
			break;
		
	}
	printf("Hangi Akademisyenin Derslerini Goruntulemek Istersiniz?(ID)\n");
	scanf("%d",&choice);
	
	
	int loc = findAcaID(faca,a,choice);
	if(loc != -1){
		int limit = findLineNum(flog);
		printf("%d ID'sine Sahip %s %s %s'nin Verdigi Dersler.\n",a[loc].id,a[loc].title,a[loc].name,a[loc].surname);
		
		lectGivenByAca(flec,l,choice);
		printf("Hangi Dersin Sinif Listesini Olusturmak Istersiniz?(DERS ID)");
		char *lectName = (char *)malloc(10*sizeof(char));
		char *FileName = (char *)malloc(40*sizeof(char));
		scanf("%s",lectName);
		strcpy(FileName,lectName);
		strcat(FileName,"_SINIFLÝSTESÝ.txt");
		
		FILE *fptr = fopen(FileName,"w");
		int locLec = findLecID(flec,l,lectName);
		if(locLec != -1){
			system("cls");
			
			printf("%d ID'sine Sahip %s %s %s'nin Verdigi %s Kodlu %s Dersini Alan Ogrenci Listesi\n",a[loc].id,a[loc].title,a[loc].name,a[loc].surname,l[locLec].id,l[locLec].name);
			
			showStuList(flog,fptr,fstd,s,lectName);
			free(lectName);
			free(FileName);
		}
		else printf("Ders Bulunamadi");
		
		fclose(fptr);		
	}
	else printf("ID bulunamadi");
	
	
	//

	
}
void screen(FILE *fstd,FILE *faca,FILE *flec,FILE *flog,student *s,academician *a,lecture *l){
	//ana ekran bütün iþlemlere burdan gidiliyor
	
	fclose(fstd);
	fclose(faca);
	fclose(flec);
	fclose(flog);
						
	faca = fopen("ogretmenler.txt","r+");
	flec = fopen("dersler.txt","r+");
	fstd = fopen("ogrenciler.txt","r+");
	flog = fopen("log.txt","r+");
	///dosya üzerinde yapýlan iþlemler dosya kapanmadýðý takdirde program üzerinden okunamýyor bu yüzden
	///dosyayi açip kapayarak her seferinde yapýlan iþlemleri text dosyasina yazmiþ oluyor 
	///bu sayede iþlemlerin gerçekleþiðini görmek için kodun kapanmasýna gerek kalmamiþ oluyor
	
	
 
	//normalde realloc ile dosya boyutunu deðiþtirmek gerekli ancak realloc kullanmak efektif olmadýðý için
	//realloc kullanmadým.

	
	readAcademican(faca,a);
	readLecture(flec,l);
	readStudent(fstd,s);

	int choice;

	printf("-----------------------------------\n");
	printf("|Islemler:		          |\n");
	printf("|1->Ogrenci		          |\n");
	printf("|2->Akademisyen	                  |\n");
	printf("|3->Ders		          |\n");
	printf("|4->Cikis		          |\n");
	printf("-----------------------------------\n");
	
	scanf("%d",&choice);	   
	


	
		switch (choice){
		
			case 1:
				system("cls");
				studentOperation(fstd,flec,flog,faca,s,a,l);
				break;
			case 2:
				system("cls");
				academicianOperation(flog,faca,flec,fstd,a,l,s);
				break;
			case 3:
				system("cls");
				lectureOperation(flec,flog,faca,fstd,l,s,a);
				break;
			case 4:
				system("cls");
				printf("Cikiliyor\n");
				sleep(1);
				break;
			default:
				system("cls");
				printf("Uygun Olmayan Sayi Girildi Cikiliyor.");
				sleep(1);
				break;
		
		}

}
void updateAcademician(FILE *fstd,FILE *faca,FILE *flec,FILE *flog,student *s,academician *a,lecture *l){
	//bir akademisyenin bilgilerini güncellemek için kullanýlan fonksiyon 
	int choice;
	system("cls");
	printf("Akademisyen Listesini Goruntulemek Icin 1 Goruntulememek icin 0.\n");
	scanf("%d",&choice);
	switch (choice){
		case 0:
			break;
		case 1:
			readAcademican(faca,a);
			currentAcademcians(faca,a);
			break;
		default:
			printf("Uygun Sayi Girilmedi Cikiliyor\n");
			sleep(1);
			system("cls");
			break;
	}
	printf("Hangi Akademisyenin Bilgilerini Guncellemek Isterseniz O Akademisyenin ID'sini Girin .\n");
	scanf("%d",&choice);
	
	
	int len = findLineNum(faca);
	int loc = findAcaID(faca,a,choice);

	if(loc != -1){
		//printf("%d Ogrencinin Bilgileri %d %s %s ",s[line].id,s[line].name,s[line].surname);

		printf("Yeni bilgilerini giriniz(ID,ISIM,SOYISIM UNVAN sirasi ile)\n");
		scanf("%d %s %s %s",&a[loc].id,a[loc].name,a[loc].surname,a[loc].title);
	
			////güncelleme islemi icin
		int i;
	
		
		//readAcademican(faca,a);
		fseek(faca,SEEK_SET,0);
		
		for(i=0;i<len;i++){
			
			if(i != len-1){
				fprintf(faca,"%d %s %s %s\n",a[i].id,a[i].name,a[i].surname,a[i].title);
			}
			else fprintf(faca,"%d %s %s %s",a[i].id,a[i].name,a[i].surname,a[i].title);
			
		
		}
		printf("Akademisyen Guncelleme Basarili.\n");
	}
	else{
		printf("Akademisyen Bulunamadi.");
	}
	//screenReturn(fstd,faca,flec,flog,s,a,l);
	
}
void updateStudent(FILE *fstd,FILE *faca,FILE *flec,FILE *flog,student *s,academician *a,lecture *l){
	//bir öðrencinin bilgilerini güncellemek için kullanýlan fonksiyon
	int choice;
	system("cls");
	printf("Ogrenci Listesini Goruntulemek Icin 1 Goruntulememek icin 0.\n");
	scanf("%d",&choice);
	switch (choice){
		case 0:
			break;
		case 1:
			readStudent(fstd,s);
			currentStudents(fstd,s);
			break;
		default:
			printf("Uygun Sayi Girilmedi Cikiliyor\n");
			sleep(1);
			system("cls");
			break;
	}
	printf("Hangi Ogrencinin Bilgilerini Guncellemek Isterseniz O Ogrencinin ID'sini Girin .\n");
	scanf("%d",&choice);
	
	
	int len = findLineNum(fstd);
	int loc = findID(fstd,s,choice);
	if(loc != -1){
		//printf("%d Ogrencinin Bilgileri %d %s %s ",s[line].id,s[line].name,s[line].surname);
		printf("Yeni bilgilerini giriniz(ID,ISIM,SOYISIM sirasi ile)\n");
		scanf("%d%s%s",&s[loc].id,s[loc].name,s[loc].surname);
	
			////güncelleme islemi icin
		int i;
	
		rewind(fstd);
		for(i=0;i<len;i++){
		
			if(i != len-1){
				fprintf(fstd,"%d %s %s %d\n",s[i].id,s[i].name,s[i].surname,s[i].total_credit);
			}
			else fprintf(fstd,"%d %s %s %d",s[i].id,s[i].name,s[i].surname,s[i].total_credit);
		
		}
		printf("Ogrenci Guncellendi.\n");
	}
	else{
		printf("Ogrenci Bulunamadý.");
	}
	screenReturn(fstd,faca,flec,flog,s,a,l);
	
}
void studentLect(FILE *fstd,FILE *faca,FILE *flec,FILE *flog,student *s,academician *a,lecture *l){
	//öðrencinin aldiði dersleri bastiran fonksiyon
	int choice;
	int stuID;
	char *lectName = (char * )malloc(20*sizeof(char));
	system("cls");
	printf("Ogrenci Listesini Goruntulemek Ister misiniz?\nEvet->1\nHayir->0\n");
	scanf("%d",&choice);
	
	switch (choice){
		case 0:
			break;
		case 1:
			readStudent(fstd,s);
			currentStudents(fstd,s);
			break;
		
	}
	printf("Sorgulamak Istediginiz Ogrencinin ID'sini Girin.\n");
	scanf("%d",&stuID);
	
	
	int tmp = 1,i;
	int limit = findLineNum(flec);
	printf("Ogrencinin Aldigi Dersler...\n");
	for(i=0;i<limit;i++){
		strcpy(lectName,l[i].id);
		
		if(showStudentLect(flog,stuID,lectName) == 1){
			nameSeperator(l[i].name);
			printf("%d->%s %s\n",tmp,lectName,l[i].name);
			tmp++;
		}
		
		
		
		
	}
	
	
	free(lectName);
	
}
int showStudentLect(FILE *flog,int stuID,char *lectName){
	///bir ögrencinin aldýgý dersleri göstermek için studentLect altinda kullanýlan fonksiyon
	
	int i;
	int limit = findLineNum(flog);	
	int tempStuID;
	
	int tempStatus;
	int status=0;
	int tmp = 0;
	int year,day;
	

	char hour[8];
    char month[6];
    char tempLectName[20];
    
   	fseek(flog,SEEK_SET,0);
    for(i=0;i<limit;i++){
   		fscanf(flog,"%d %s %d %s %s %d %d",&tempStuID,tempLectName,&tempStatus,hour,month,&day,&year);
		   	
   		if(tempStuID == stuID && strcmp(tempLectName,lectName) == 0){
   					///dogru kisim bulunmuþ ise
   			
   			status += tempStatus;
   			
   			
		}
   }

	
	return status;
}
int main(){
	
	FILE *faca = fopen("ogretmenler.txt","r+");
	FILE *flec = fopen("dersler.txt","r+");
	FILE *fstd = fopen("ogrenciler.txt","r+");
	FILE *flog = fopen("log.txt","r+");
	

	
	student *s = (student *)malloc(100*sizeof(student));
	academician *a = (academician *)malloc(100*sizeof(academician));
	lecture *l = (lecture *)malloc(100*sizeof(lecture));
	if(s == NULL){
		free(a);
		free(l);
		exit(0);
	}
	if(a == NULL){
		free(s);
		free(l);
		exit(0);
	}
	if(l == NULL){
		free(a);
		free(s);
		exit(0);
	}
	

	if(fstd == NULL || faca == NULL || flec == NULL||flog == NULL){
		
		printf("NULL ERROR");
		exit(0);
		fclose(flog);
		fclose(fstd);
		fclose(faca);
		fclose(flec);
	}
	
	
    screen(fstd,faca,flec,flog,s,a,l);
	
	
	
	free(s);
	free(a);
	free(l);
	
	fclose(fstd);
	fclose(faca);
	fclose(flec);
	fclose(flog);
	
	
	
	return 0;
}





