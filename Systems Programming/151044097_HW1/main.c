
#include <stdio.h>

int read(FILE* dosya,const char* Ara);/*Dosya okuma fonksiyonu.Bulunan sayısını return eder.*/

int main(int argc, char** argv) {
	if(argc<3){					/*Usage kontrolü*/
        printf("Eksik Girdi \n");
		return 0;
    }
	else if(argc>3){			/*Usage kontrolü*/
		printf("Fazla Girdi \n");
		return 0;
	}
    FILE* dosya;						/*Dosya pointerı*/
    
    const char* dosyaAdi=argv[2];		/*Dosya adı*/
    dosya=fopen(dosyaAdi,"r");			/*Dosya açma*/
	if(dosya==NULL){					/*Dosya açma kontrolü*/
		printf("Dosya bulunamadı\n");
		return 0;
	}
    const char* Ara=argv[1]; /*Aranacak kelime */
    
	printf("%d adet %s bulundu %s dosyasında.\n",read(dosya,Ara),Ara,dosyaAdi);/*Fonksiyonun return değerini print alma*/
	
	return 0;
}
  

int read(FILE* dosya,const char* Ara){/*Dosya okuma fonksiyonu.Bulunan sayısını return eder.*/
	int stringLen=0,satir=1,sutun=0,i=0,Bulunan=0,counter=0;
    char ch;
	for(i=0; Ara[i] !='\0' ;++i){/*Aranacak stringin uzunluğunu bulma*/
            stringLen+=1;
    }
   	while((ch=fgetc(dosya))!=EOF){/*Dosyayı karakter karakter oku ve kontrol et*/
        ++sutun;			/*kelimenin ilk karakteri alınır ve sutun 1 arttırılır*/
        if(ch=='\n')		/*Satır sonuna gelince satır 1 arttırılır ve sutun sıfırlanır*/
        {   
            sutun=0;
            ++satir;
        }
        else if(ch==' '){/*ilk karakter boşluk olamaz.Ama karakterler arasında yok sayılır*/
            continue;
        }
        else if(ch==Ara[0])
        {
            for(i=0;i<stringLen;++i)/*aranacak kelimenin boyunda dosyadan karakter okunur*/
            {
                counter+=1;/*Dosyadan okunan karakter sayısı.Her yeni String kontrolünde sıfırlanır*/
               	while(ch==' ' || ch=='\n'){/*ilk karakter boşluk olamaz.Ama karakterler arasında yok sayılır*/
					ch=fgetc(dosya);
                   	counter+=1;/*Counter ,FOR döngüsüne girdikten sonra dosyadan kaç tane karakter okunduğunu tutar*/
                }                
                if(ch!=Ara[i] && ch!=' ' && ch!='\n'){/*Eğer farklı bir karakter bulunursa ,FOR döngüsünden çıkılır*/
                    if((ch=fgetc(dosya))!=EOF){/*Eğer sıradaki karakter aranan kelimedeki karaktere eşit değilse "COUNTER" kadar dosyada geri gidilir*/
                     	fseek(dosya,-(counter),SEEK_CUR);/*Aslında COUNTER-1 kadar gidilir ama IF statement'ında dosya sonu kontrolü yapılırken karakter okunur*/
                    }
                    else{
						fclose(dosya);/*Dosya sonuna geldiysek dosya kapatılır*/
						return Bulunan;
					}                        
                	counter=0;
                    break;
                }              
                if(i<stringLen-1){/*Yeterince karakter okumadıysak ve hata yoksa tekrar okunur ve döngü devam eder*/
                    ch=fgetc(dosya);                   
                }
                else if(i==stringLen-1){/*Yeterince okuma yapıldıysa ve döngü bozulmadıysa kelimeyi bulduk*/
                    fseek(dosya,-(counter-1),SEEK_CUR);/*Dosya COUNTER-1 kadar başa sarılır*/
                    Bulunan+=1;/*Bulunan aranan kelime sayısı*/
                    printf("[%d,%d] konumunda ilk karakter bulundu.\n",satir,sutun);
                    counter=0;/*Counter sıfırlanır*/
                }
			}
        }
	}
}



