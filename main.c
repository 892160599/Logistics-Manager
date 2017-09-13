#include <stdio.h>
#include <ListTool.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <wincon.h>
#include <windef.h>
#include "shlobj.h"
#include <wingdi.h>

//TODO: ����

int selectRow = 1;

route * initData();
void printSomeSpace(int num);
void printSomeG(int num);

void printFronPage();
void printPowerBy();
void printRoutePage(route * routeHeadP);
void printSitePage(route *routeP, route * routeHeadP);
void printCarPage(site * siteP);
void quickQuery(route * routeHeadP);

void addRoute(route * routeHeadP);
car* addCar(car * carHeadP);
site* addSite(site * siteHeadP, char* routeIDIN, route * routeHeadP);

int changeSite(site * siteSpecific, int notFirst, site * siteHeadP);
int changeRoute(route * routeSpecial);
int changeCar(car * carSpecific);

void updateCarsFILE(car * carHeadP, char * fileName);
void updateRoutesFILE(route* routeHeadP);
void updateSitesFILE(site * siteHeadP);

char* noNfgets(char * Buffer, int MaxConut, FILE* Stream);
void changeOldRouteID(route * routeSpecific);
int changeSaveName(char* old, char* new);
void updateSitesCount(route * routeSpecific);
void initConsole();

void makeCsv(route * routeHeadP);
float totalTime(route *routeP);
float getMile(char *routeIDThis, route * routeHeadP);
float totalMile(route *routeP);
void updateAlld2S(site * siteP);

void LocSubMenu(int num, SMALL_RECT *rc);

void saveALL(route* routeHeadP);

int main() {

	route* routeHeadP;
	routeHeadP = initData();//��ʼ������������
	char *url = malloc(sizeof(char) * 20);//���ٿռ��ʹ��
    int space = 60;

	initConsole();

    //������������˵�һ����Ϣչʾ
	while (1) {
	    printFronPage();

		int input1 = 0;
		scanf("%d%*c", &input1);

		if (input1 == 1) {
			int isRoutePage = 1;
			while (isRoutePage) {
				printRoutePage(routeHeadP);//���·��ҳ����Ϣ
				int input2 = 0; scanf("%d%*c", &input2);
				int seq = 0;

				if (input2 == 1) {
					printSomeSpace(space);printf("����ϸ�鿴�ڼ���·�ߵ�վ����Ϣ��");
					seq = 0; scanf("%d%*c", &seq);
					route * routeSpecific = getRoutePointer(routeHeadP, seq - 1);
					if (routeSpecific != NULL){
					    printSitePage(getRoutePointer(routeHeadP, seq - 1), routeHeadP);//����ú����ڲ�
					} else {
                        printSomeSpace(space);printf("��������\n");
					}

				} else if (input2 == 2) {
					printSomeSpace(space);printf("���޸ĵڼ���·�ߣ�");
					seq = 0; scanf("%d%*c", &seq);
					changeRoute(getRoutePointer(routeHeadP, seq-1));
					updateRoutesFILE(routeHeadP);
					MessageBox(NULL, TEXT("�ɹ��޸�·��"), TEXT("�����ɹ�"), MB_OK);
					system("cls");
				} else if (input2 == 3) {
					printSomeSpace(space);printf("��ɾ���ڼ���·�ߣ�");
					seq = 0; scanf("%d%*c", &seq);
					//ɾ����Ӧ�Ĵ浵�ļ� TODO�����ɸѡδ�ظ�վ��ɾ��
					strcpy(url, "save/");
					strcat(url, getRoutePointer(routeHeadP, seq - 1)->routeID);
					strcat(url, ".txt");
					remove(url);
					//�ٸ���·�ߺϼ��浵
					routeHeadP = DelRoutePos(routeHeadP, seq-1);
					updateRoutesFILE(routeHeadP);
					MessageBox(NULL, TEXT("�ɹ�ɾ��·��"), TEXT("�����ɹ�"), MB_OK);
					system("cls");
				} else if (input2 == 4) {
					addRoute(routeHeadP);
					updateRoutesFILE(routeHeadP);
					MessageBox(NULL, TEXT("�ɹ�����·��\n������������·����ϸ��Ϣ�������վ����Ϣ"), TEXT("�����ɹ�"), MB_OK);
					system("cls");
				} else if (input2 == 5) {
                    //���ٲ�ѯ����
                    quickQuery(routeHeadP);
					system("cls");
				} else if (input2 == 6){
                    makeCsv(routeHeadP);//����ͳ�Ʊ���
					system("cls");
				} else if (input2 == 7){
				    isRoutePage = 0;
					system("cls");
				}
			}
		} else if (input1 == 2) {
			printPowerBy();
			continue;
		} else {
			system("cls");
			printSomeSpace(space);printf("�������ָ��\n");
		}
	}
	free(url);

	return 0;
}

//���ٲ�ѯʵ���߼�
void quickQuery(route * routeHeadP){
    route * routeP = routeHeadP;
    system("cls");
    printSomeSpace(60);system("date /T");
	printSomeSpace(60);printf("-------------------���ٲ�ѯ----------------------\n");
	printSomeSpace(60);printf("|\t1.��ѯָ��˾�����ػ�ж�����\t\t|\n");
	printSomeSpace(60);printf("|\t2.��ѯָ��������˾����ϵ��ʽ\t\t|\n");
	printSomeSpace(60);printf("|\t3.��ѯָ������������·��\t\t|\n");
	printSomeSpace(60);printf("|\t4.��ѯ��ͣĳվ�������·��\t\t|\n");
	printSomeSpace(60);printf("|\t5.��ѯ��ʱ���·��\t\t\t|\n");
	printSomeSpace(60);printf("|\t6.��ѯ��ʱ��̵�·��\t\t\t|\n");
	printSomeSpace(60);printf("|\t7.��ѯ���������·��\t\t\t|\n");
	printSomeSpace(60);printf("|\t8.��ѯ��������̵�·��\t\t\t|\n");
	printSomeSpace(60);printf("-------------------------------------------------\n");
	int seq = 0;printSomeSpace(60);scanf("%d%*c",&seq);
	char input[21];
	float tempFloat = 0;
	int isSuccessful = 0;
	printf("\n");
	printSomeSpace(60);
	switch (seq){
	case 1:
	    printf("������˾��������");
	    noNfgets(input, 20, stdin);
	    l4:while (routeP != NULL){
            site* siteP = routeP->firstSite;
            while (siteP != NULL){
                car* carP = siteP->carHeadP;
                while (carP != NULL){
                    if(strcmp(input, carP->driverName) == 0){
                        printSomeSpace(60);
                        if (carP->good != NULL){
                            printf("˾�� %s�ػ�������Ϊ%.3f��%s��ж��������Ϊ%.3f��%s\n", input, carP->good->upVolume, carP->good->uploadType, carP->good->downVolume, carP->good->downloadType);
                        } else {
                            printf("��˾���޻�����Ϣ\n");
                        }
                        isSuccessful = 1;
                        carP = NULL;
                        siteP = NULL;
                        routeP = NULL;
                        goto l4;//jump out from loops
                    }
                    carP = carP->next;
                }
                siteP = siteP->next;
            }
            routeP = routeP->next;
	    }
	    break;
    case 2:
        printf("�����복�����գ�");
        noNfgets(input, 20, stdin);
        l3:while (routeP != NULL){
            site* siteP = routeP->firstSite;
            while (siteP != NULL){
                car* carP = siteP->carHeadP;
                while (carP != NULL){
                    if (strcmp(carP->carID, input) == 0){
                        printSomeSpace(60);printf("����%s��˾��%s����ϵ��ʽΪ%s\n", input, carP->driverName, carP->driverTel);
                        isSuccessful = 1;
                        carP = NULL;
                        siteP = NULL;
                        routeP = NULL;
                        goto l3;//jump out from loops
                    }
                    carP = carP->next;
                }
                siteP = siteP->next;
            }
            routeP = routeP->next;
	    }
	    break;
    case 3:
        printf("�����복�����գ�");
        noNfgets(input, 20, stdin);
        l2:while (routeP != NULL){
            site* siteP = routeP->firstSite;
            while (siteP != NULL){
                car* carP = siteP->carHeadP;
                while (carP != NULL){
                    if (strcmp(carP->carID, input) == 0){
                        printSomeSpace(60);printf("����%s������·��Ϊ%s\n", input, carP->routeID);
                        isSuccessful = 1;
                        carP = NULL;
                        siteP = NULL;
                        routeP = NULL;
                        goto l2;//jump out from loops
                    }
                    carP = carP->next;
                }
                siteP = siteP->next;
            }
            routeP = routeP->next;
	    }
	    break;
    case 4:
        printf("������վ���ţ�");
        noNfgets(input, 20, stdin);
        l1:while (routeP != NULL){
            site * siteP = routeP->firstSite;
            while (siteP != NULL){
                if (strcmp(siteP->siteID, input) == 0){
                    printSomeSpace(60);printf("��ͣվ��%s������·��:%s\n", input, siteP->routeIDArray);
                    isSuccessful = 1;
                    siteP = NULL;
                    routeP = NULL;//jump out from loops
                    goto l1;
                }
                siteP = siteP->next;
            }
            routeP = routeP->next;
        }
	    break;
    case 5:
        tempFloat = -1;
        while (routeP != NULL){
            if (routeP->period > tempFloat){
                tempFloat = routeP->period;
                strcpy(input, routeP->routeID);
                isSuccessful = 1;
            }
            routeP = routeP->next;
        }
        printf("��ʱ���·����%s���ܺ�ʱΪ%.3f\n", input, tempFloat);
	    break;
    case 6:
        tempFloat = 99999;
        while (routeP != NULL){
            if (routeP->period < tempFloat){
                tempFloat = routeP->period;
                strcpy(input, routeP->routeID);
                isSuccessful = 1;
            }
            routeP = routeP->next;
        }
        printf("��ʱ��̵�·����%s���ܺ�ʱΪ%.3f\n", input, tempFloat);
	    break;
    case 7:
        tempFloat = -1;
        while (routeP != NULL){
            if (routeP->miles > tempFloat){
                tempFloat = routeP->miles;
                strcpy(input, routeP->routeID);
                isSuccessful = 1;
            }
            routeP = routeP->next;
        }
        printf("���·����%s���ܹ�����Ϊ%.3f\n", input, tempFloat);
//        system("pause");
	    break;
    case 8:
        tempFloat = 99999;
        while (routeP != NULL){
            if (routeP->miles < tempFloat){
                tempFloat = routeP->miles;
                strcpy(input, routeP->routeID);
                isSuccessful = 1;
            }
            routeP = routeP->next;
        }
        printf("��̵�·����%s���ܹ�����Ϊ%.3f\n", input, tempFloat);
	    break;
	default:
	    break;
	}
    if (!isSuccessful){
        printSomeSpace(60);printf("�Ҳ��������Ϣ\n");
    }
    printSomeSpace(60);system("pause");
}

//��ʼ������̨������һЩ���Ի�����
void initConsole(){
//    HWND hwnd=GetForegroundWindow();
    system("mode con:cols=175 lines=30");
    system("color 3B");
    SetConsoleTitle("������Ϣ����ϵͳ");
}

/*��ʼ�����ݣ���ȡ�浵*/
route * initData() {
	FILE *fRouteP = fopen("save/routes.txt", "r");
	route * routeHeadP = NULL;
	if (fRouteP == NULL) {
	    printf ("initData error.");
		return NULL;
	} else {
		//test
		routeHeadP = creatRouteList(fRouteP);
		fclose(fRouteP);
		char *url = malloc(sizeof(char) * 20);
		register int i = 0;
		register int j = 0;
		register int k = 0;
		for (i = 0; i < sizeRouteList(routeHeadP); i++) {
			route *routeP = getRoutePointer(routeHeadP,i);
			strcpy(url, "save/");
			strcat(url, routeP->routeID);
			strcat(url, ".txt");
			FILE *fSite = fopen(url, "r+");
			if (fSite == NULL) {
				routeP->firstSite = NULL;
				continue;
			}
			site * siteHeadP = creatSiteList(fSite);
			fclose(fSite);
			routeP->firstSite = siteHeadP;//��վ�������ͷ���ָ�봫�ݸ���Ӧ��·��

			//set infomation about those cars in this site
			for (j = 0; j < sizeSiteList(siteHeadP); j++) {
				site * siteP = getSitePointer(siteHeadP, j);
				strcpy(url, "save/");
				strcat(url, siteP->siteID);
				strcat(url, ".txt");
				FILE * fCar = fopen(url, "r+");
				if (fCar == NULL) {
					siteP->carHeadP = NULL;
					continue;//�����Ĵ浵��û�У�����˵������
				}
				car * carHeadP = creatCarList(fCar);
				siteP->carHeadP = carHeadP;

				for (k = 0; k < sizeCarList(carHeadP); k++) {
					car * carP = getCarPointer(carHeadP, k);
					strcpy(url, "save/");
					strcat(url, carP->carID);
					strcat(url, ".txt");
					FILE * fGood = fopen(url, "r+");
					if (fGood == NULL) {
						carP->good = NULL;
						continue;
					}
					carP->good = creatGood(fGood);
					fclose(fGood);
				}
				fclose(fCar);
			}
			fclose(fSite);
		}
	}
	return routeHeadP;
}

//�����ҳ
void printFronPage() {
	printSomeSpace(60);
    system("date /T");printSomeSpace(60);
	printf("----------------------------------------------------\n");printSomeSpace(60);
	printf("|��ӭ����������Ϣ����ϵͳ������Ӧ���ֽ��빦��\t|\n");printSomeSpace(60);
	printf("|\t1.����ϵͳ\t\t\t\t\t|\n");printSomeSpace(60);
	printf("|\t2.��������Ϣ\t\t\t\t\t|\n");printSomeSpace(60);
	printf("----------------------------------------------------\n");printSomeSpace(60);

}

//�鿴��������Ϣ�߼�
void printPowerBy() {
	MessageBox(NULL, TEXT("���пƼ���ѧ\nIOT1601 �����\nC���Գ������_�γ������Ʒ\n������Ϣ��ѯϵͳ"), TEXT("��������Ϣ"), MB_OK);
	system("cls");
}

//���·����Ϣ
void printRoutePage(route * routeHeadP) {
	route * routeP = routeHeadP;
	system("cls");
	system("date /T");

	printSomeG(75);printf("����·����Ϣ");printSomeG(76);printf("\n");//title

	char first[] = "���";
	char second[] = "����";
	char third[] = "վ����";
	char fourth[] = "������";
	char fifth[] = "��ʱ";
	char sixth[] = "��ʼվ��";
	char seventh[] = "��ֹվ��";
	char eighth[] = "������";
	char ninth[] = "�̶��绰";
	char tenth[] = "�ƶ��绰";
	char eleventh[] = "��������";
	printf("|  %-6s %-20s %-6s %-10s %-10s %-10s %-10s %-8s %-8s %-11s %-50s|\n", first, second, third, fourth, fifth, sixth, seventh, eighth, ninth, tenth, eleventh);
    printf("|");printSomeSpace(161);printf("|\n");
	register int i = 1;
	while (routeP != NULL) {
		printf("|%d:",i);
		printf("%-6s %-20s %-6d %-10.3f %-10.3f %-10s %-10s %-8s %-8s %-11s %-50s|\n", routeP->routeID, routeP->name, routeP->siteNums, routeP->miles, routeP->period, routeP->startSite, routeP->endSite, routeP->adminName, routeP->tel, routeP->mTel, routeP->email);
		routeP = routeP->next;
		i++;
	}
	int space = 60;
	printSomeG(163);
	printf("\n");
	printSomeSpace(space);
	printf("|\t1.�鿴·�߾�����Ϣ\t\t\t|\n");printSomeSpace(space);
	printf("|\t2.�����޸�\t\t\t\t|\n");printSomeSpace(space);
	printf("|\t3.����ɾ��\t\t\t\t|\n");printSomeSpace(space);
	printf("|\t4.��������\t\t\t\t|\n");printSomeSpace(space);
	printf("|\t5.���ٲ�ѯ\t\t\t\t|\n");printSomeSpace(space);
	printf("|\t6.����ͳ�Ʊ���\t\t\t\t|\n");printSomeSpace(space);
	printf("|\t7.�����ϼ��˵�\t\t\t\t|\n");printSomeSpace(space);
	printf("--------------������ѡ����-----------------\n");printSomeSpace(space);
}

//rewrite file from list
void updateRoutesFILE(route* routeHeadP) {
	route * routeP = routeHeadP;
	FILE *fRouteP = fopen("save/routes.txt", "w+");//��ͷ��д�ı�
	while (routeP != NULL) {
		fprintf(fRouteP,"%s;%s;%d;%f;%f;%s;%s;%s;%s;%s;%s\n",routeP->routeID, routeP->name, routeP->siteNums, routeP->miles, routeP->period, routeP->startSite, routeP->endSite, routeP->adminName, routeP->tel, routeP->mTel, routeP->email);
		routeP = routeP->next;
	}
	fclose(fRouteP);
}
void updateSitesFILE(site * siteHeadP) {
	site * siteP = siteHeadP;
	char * url = (char*)malloc(sizeof(char) * 20);
	strcpy(url, "save/");
	strcat(url, siteHeadP->routeID);
	strcat(url, ".txt");
	FILE *fSiteP = fopen(url, "w+");//��ͷ��д�ı�
	while (siteP != NULL) {
		fprintf(fSiteP, "%s;%d;%s;%s;%f;%f;%f;%f;%s\n",siteP->routeID,siteP->siteSID, siteP->siteID, siteP->siteName, siteP->d2Start, siteP->d2Last, siteP->time2Last, siteP->waitTime, siteP->routeIDArray);
		siteP = siteP->next;
	}
	fclose(fSiteP);
	free(url);
}
void updateCarsFILE(car * carHeadP, char * fileName) {
	car * carP = carHeadP;
	char * url = (char*)malloc(sizeof(char) * 20);
	strcpy(url, "save/");
	strcat(url, fileName);//for example s00100
	strcat(url, ".txt");
	FILE *fCarP = fopen(url, "w+");//��ͷ��д�ı�
	while (carP != NULL) {
		fprintf(fCarP, "%s;%s;%s;%s\n", carP->carID, carP->routeID, carP->driverName, carP->driverTel);
		carP = carP->next;
	}
	fclose(fCarP);

	//Update good file automatically, 'cause it's too small to open an another method to realize it.
	carP = carHeadP;//init again
	while (carP != NULL) {
		strcpy(url, "save/");
		strcat(url, carP->carID);
		strcat(url, ".txt");
		FILE * fGoodP = fopen(url, "w+");
		good * goodP = carP->good;
		fprintf(fGoodP, "%s;%f;%s;%f\n", goodP->uploadType, goodP->upVolume, goodP->downloadType, goodP->downVolume);
		carP = carP->next;
		fclose(fGoodP);
	}
	free(url);
}
//The new route would be the last node in this list.
void addRoute(route * routeHeadP) {
	route * newRouteP = AddRouteNode(routeHeadP, sizeRouteList(routeHeadP));
	if (newRouteP != NULL) {
		char inputTemp[51];
		printSomeSpace(60);
		printf("---------------��������·�ߵ���Ϣ----------------\n");
		printSomeSpace(60);printf("��������:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->routeID, inputTemp);
		printSomeSpace(60);printf("����������:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->name, inputTemp);

        newRouteP->firstSite = NULL;//��Ϊ���µ�·�ߣ��ʽ�ָ���վ������ָ���ÿ�

		newRouteP->siteNums = 0;//auto complete siteConut. default -> 0;

		newRouteP->miles = 0;
		newRouteP->period = 0;

		printSomeSpace(60);printf("��������ʼվ����:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->startSite, inputTemp);
		printSomeSpace(60);printf("��������ֹվ����:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->endSite, inputTemp);
		printSomeSpace(60);printf("�����븺��������:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->adminName, inputTemp);
		printSomeSpace(60);printf("�����븺���˰칫�ҵ绰:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->tel, inputTemp);
		printSomeSpace(60);printf("�����븺�����ƶ��绰:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->mTel, inputTemp);
		printSomeSpace(60);printf("�����븺���˵�������:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->email, inputTemp);
	} else {
		system("cls");
		printf("addRoute error\n");
	}
}
site* addSite(site * siteHeadP, char* routeIDIN, route * routeHeadP){
    printf("---------------��������վ�����Ϣ----------------\n");
	printSomeSpace(60);printf("��������վ����·���е����:");//��վ���λ��
	int seq = 0; scanf("%d%*c", &seq);

    int flag = 0;
    site * newSiteP = NULL;
    if (siteHeadP == NULL){
        newSiteP = (site*)malloc(sizeof(site));
        flag = 1;//the new head pointer( siteHeadP is a NULL pointer
    } else {
        newSiteP = AddSiteNode(siteHeadP, seq - 1);
    }

	if (newSiteP != NULL) {
	    newSiteP->carHeadP = NULL;
		char inputTemp[51];
		printSomeSpace(60);printf("������վ����:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newSiteP->siteID, inputTemp);

        //����Ƿ�վ���ظ�
        route * routeP = routeHeadP;
        while(routeP != NULL){
            site * siteP = routeP->firstSite;
            while(siteP != NULL){
                if(!strcmp(siteP->siteID, newSiteP->siteID)){//һ��
                    newSiteP->carHeadP = siteP->carHeadP;
                }
                siteP = siteP->next;
            }
            routeP = routeP->next;
        }

		printSomeSpace(60);printf("������վ������:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newSiteP->siteName, inputTemp);

		printSomeSpace(60);printf("����������һ��վ�㽻ͨ��ʱ:");
		float fPeriod = 0;
		scanf("%f%*c", &fPeriod);
		newSiteP->time2Last = fPeriod;

		printSomeSpace(60);printf("������ͣ����ʱ:");
		float waitTimeN = 0;
		scanf("%f%*c", &waitTimeN);
		newSiteP->waitTime = waitTimeN;

		printSomeSpace(60);printf("�����뾭����վ��̶�·�߱��:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newSiteP->routeIDArray, inputTemp);

        //�ܾ���
        if (seq == 1){
            newSiteP->d2Start = 0;
            newSiteP->d2Last = 0;
        } else {
            printSomeSpace(60);printf("����������һ��վ�����:");
            float d2L = 0;
            scanf("%f%*c", &d2L);
            newSiteP->d2Last = d2L;
            site * siteTempP = siteHeadP;
            while(siteTempP->next != newSiteP){
                siteTempP = siteTempP->next;
            }
            newSiteP->d2Start = siteTempP->d2Start + d2L;
        }
        //�Զ���������վ�������ʼվ�����
        updateAlld2S(newSiteP);


        //�Զ���ȫ���
        newSiteP->siteSID = seq;
		strcpy(newSiteP->routeID, routeIDIN);
        if (flag == 1){//the first one in new save file
            newSiteP->next = NULL;
            return newSiteP;
        } else {
            //�Զ����±����������SID
            site * siteTemp = getSitePointer(siteHeadP, seq);
            while (siteTemp != NULL) {
                siteTemp->siteSID = siteTemp->siteSID + 1;
                siteTemp = siteTemp->next;
            }
            return siteHeadP;
        }
	} else {
		system("cls");
		printSomeSpace(60);printf("addSite error\n");
		return NULL;
	}
}
//return the new car head pointer
car* addCar(car * carHeadP) {
    int flag = 0;
    car* newCarP = NULL;
    good* newGoodP = NULL;
    if (carHeadP == NULL){
        newCarP = (car *)malloc(sizeof(car));
        flag = 1;
    } else {//flag == 0
        newCarP = AddCarNode(carHeadP, sizeCarList(carHeadP));
    }
    newGoodP = (good *)malloc(sizeof(good));
    newCarP->good = newGoodP;

    char inputTemp[51];//auto free
    printf("---------------��������·�ߵ���Ϣ----------------\n");
    printSomeSpace(60);printf("�����복������:");
    noNfgets(inputTemp, 50, stdin);
    strcpy(newCarP->carID, inputTemp);
    printSomeSpace(60);printf("������ִ������·�߱��:");
    noNfgets(inputTemp, 50, stdin);
    strcpy(newCarP->routeID, inputTemp);
    printSomeSpace(60);printf("������˾������:");
    noNfgets(inputTemp, 50, stdin);
    strcpy(newCarP->driverName, inputTemp);
    printSomeSpace(60);printf("������˾���ƶ��绰:");
    noNfgets(inputTemp, 50, stdin);
    strcpy(newCarP->driverTel, inputTemp);

    printSomeSpace(60);printf("�������ػ���������:");
    noNfgets(inputTemp, 50, stdin);
    strcpy(newCarP->good->uploadType, inputTemp);
    printSomeSpace(60);printf("�������ػ���������:");
    float upV = 0; scanf("%f%*c", &upV);
    newCarP->good->upVolume = upV;
    printSomeSpace(60);printf("������ж����������:");
    noNfgets(inputTemp, 50, stdin);
    strcpy(newCarP->good->downloadType, inputTemp);
    printSomeSpace(60);printf("������ж����������:");
    float downV = 0; scanf("%f%*c", &downV);
    newCarP->good->downVolume = downV;
    if (flag == 0){
        return carHeadP;
    } else {//flag == 1
        newCarP->next = NULL;
        return newCarP;
    }
}

//����ȡ���з���fgets��������
char* noNfgets(char * Buffer, int MaxConut, FILE* Stream) {
	char* returnPointer = fgets(Buffer, MaxConut, Stream);//now there is data in Buffer with '\n'.
	register int i = 0;
	while (Buffer[i] != '\n') {
		i++;
	}
	//now i points '\n'
	Buffer[i] = '\0';
	return returnPointer;
}
//�޸���Ϣ�߼�
int changeRoute(route * routeSpecific) {
    printSomeSpace(60);
	printf("-------------------------------------------------\n");
	char temp[] = " ";
	printf("%60s1.���\n%60s2.����\n%60s3.�ܹ�����\n%60s4.��ʼվ����\n%60s5.��ֹվ����\n%60s6.����������\n%60s7.�����˰칫�ҵ绰\n%60s8.�������ƶ��绰\n%60s8.�����˵�������\n\n%60s��ѡ����Ҫ�޸ĵ�����:",temp,temp,temp,temp,temp,temp,temp,temp,temp,temp,temp);
	int choose = 0;
	scanf("%d%*c", &choose);
	char input[51];//no free
	switch (choose) {
	case 1:
		printSomeSpace(60);printf("�������µı��:");
		char * oldID = (char *)malloc(sizeof(char) * 30);
		strcpy(oldID, routeSpecific->routeID);
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->routeID, input);
		//�ı����Ŷ�Ӧ�Ĵ浵�ļ���
		changeSaveName(oldID, routeSpecific->routeID);
		changeOldRouteID(routeSpecific);
		free(oldID);
		break;
	case 2:
		printSomeSpace(60);printf("�������µ�����:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->name, input);
		break;
	case 3:
		printSomeSpace(60);printf("�������µ��ܹ�����:");
		float newMiles = 0;
		scanf("%f%*c", &newMiles);
		routeSpecific->miles = newMiles;
		break;
    routeSpecific->period = 0;
	case 4:
		printSomeSpace(60);printf("�������µ���ʼվ����:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->startSite, input);
		break;
	case 5:
		printSomeSpace(60);printf("�������µ���ֹվ����:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->endSite, input);
		break;
	case 6:
		printSomeSpace(60);printf("�������µĸ���������:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->adminName, input);
		break;
	case 7:
		printSomeSpace(60);printf("�������µĸ����˰칫�ҵ绰:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->tel, input);
		break;
	case 8:
		printSomeSpace(60);printf("�������µĸ������ƶ��绰:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->mTel, input);
		break;
	case 9:
		printSomeSpace(60);printf("�������µĸ����˵�������:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->email, input);
		break;
	default:
		printf("��������\n");
		return 0;
	}
	return 1;
}
int changeSite(site * siteSpecific, int notFirst, site * siteHeadP) {
    printSomeSpace(60);
	printf("----------------------------------------------\n");
	char space[] = " ";
	if (notFirst){
        printf("%60s1.վ����\n%60s2.վ������\n%60s3.������վ��Ĺ̶�·�߱��\n%60s4.ͣ����ʱ\n%60s5.����һվ��ͨ��ʱ\n%60s6.����һ��վ�����\n\n%60s��ѡ����Ҫ�޸ĵ�����:",space,space,space,space,space,space,space);
	} else {
	    printf("%60s1.վ����\n%60s2.վ������\n%60s3.������վ��Ĺ̶�·�߱��\n%60s4.ͣ����ʱ\n%60s5.����һվ��ͨ��ʱ\n\n%60s��ѡ����Ҫ�޸ĵ�����:",space,space,space,space,space,space);
	}
	int choose = 0;
	scanf("%d%*c", &choose);
	char input[50];//auto free
	printSomeSpace(60);
	switch (choose) {
	case 1:
		printf("�������µ�վ����:");
		char * oldID = (char *)malloc(sizeof(char) * 30);
		strcpy(oldID, siteSpecific->siteID);
		noNfgets(input, 50, stdin);
		strcpy(siteSpecific->siteID, input);//�������ڲ������µı��
		changeSaveName(oldID, siteSpecific->siteID);//�ı����Ŷ�Ӧ�Ĵ浵�ļ����������ı�����
		free(oldID);
        return 1;
	case 2:
		printf("�������µ�վ������:");
		noNfgets(input, 50, stdin);
		strcpy(siteSpecific->siteName, input);
		return 2;
	case 3:
		printf("�������µľ�����վ��Ĺ̶�·�߱��:");
		noNfgets(input, 50, stdin);
		strcpy(siteSpecific->routeIDArray, input);
		return 3;
	case 4:
		printf("�������µ�ͣ����ʱ:");
		float newPeriod = 0;
		scanf("%f%*c", &newPeriod);
		siteSpecific->waitTime = newPeriod;
		return 4;
    case 5:
		printf("�������µ�����һվ��ʱ:");
		newPeriod = 0;
		scanf("%f%*c", &newPeriod);
		siteSpecific->time2Last = newPeriod;
		return 5;
	case 6:
	    if (!notFirst){
	        printSomeSpace(60);printf("��������!\n");
            return 0;
	    }
		printf("�������µ�����һ��վ�����:");
		float d2LastNew = 0;
		scanf("%f%*c", &d2LastNew);
		siteSpecific->d2Last = d2LastNew;

        site * siteCorrectP = siteHeadP;
        while (siteCorrectP->next != siteSpecific){
            siteCorrectP = siteCorrectP->next;
        }
		updateAlld2S(siteCorrectP);

		return 6;
	default:
		printSomeSpace(60);printf("��������!\n");
		return 0;
	}
}
int changeCar(car * carSpecific) {
	printSomeSpace(60);printf("-------------------------------------------------\n");
	char space[] = " ";
	printf("%60s1.��������\n%60s2.˾������\n%60s3.˾���ƶ��绰\n%60s4.�ػ���������\n%60s5.�ػ���������\n%60s6.ж����������\n%60s7.ж����������\n\n%60s��ѡ����Ҫ�޸ĵ�����:",space,space,space,space,space,space,space,space);
	int choose = 0;
	scanf("%d%*c", &choose);
	char input[50];//auto free
	printSomeSpace(60);
	switch (choose) {
	case 1:
		printf("�������µĳ�������:");
		char * oldID = (char *)malloc(sizeof(char) * 30);
		strcpy(oldID, carSpecific->carID);
		noNfgets(input, 50, stdin);
		strcpy(carSpecific->carID, input);//�������ڲ������µı��
		changeSaveName(oldID, carSpecific->carID);//�ı����Ŷ�Ӧ�Ĵ浵�ļ����������ı�����
		free(oldID);
		break;
	case 2:
		printf("�������µ�˾������:");
		noNfgets(input, 50, stdin);
		strcpy(carSpecific->driverName, input);
		break;
	case 3:
		printf("�������µ�˾���ƶ��绰:");
		noNfgets(input, 50, stdin);
		strcpy(carSpecific->driverTel, input);
		break;
	case 4:
		printf("�������µ��ػ���������:");
		noNfgets(input, 50, stdin);
		strcpy(carSpecific->good->uploadType, input);
		break;
	case 5:
		printf("�������µ��ػ���������:");
		float newUpV = 0;
		scanf("%f%*c", &newUpV);
		carSpecific->good->upVolume = newUpV;
		break;
	case 6:
		printf("�������µ�ж����������:");
		noNfgets(input, 50, stdin);
		strcpy(carSpecific->good->downloadType, input);
		break;
	case 7:
		printf("�������µ�ж����������:");
		float newDownV = 0;
		scanf("%f%*c", &newDownV);
		carSpecific->good->downVolume = newDownV;
		break;
	default:
		printf("��������!\n");
		return 0;
	}
	return 1;
}

//���վ����Ϣ�߼�
void printSitePage(route *routeP, route * routeHeadP) {
	int inSitePage = 1;
	site* siteHeadP = routeP->firstSite;
	while (inSitePage) {
		system("cls");
		site* siteP = siteHeadP;
		system("date /T");
		printSomeG(71);printf("·�߱�ţ�%6s ������վ����Ϣ", routeP->routeID);printSomeG(71);printf("\n");//title

		char second[] = "���";
		char third[] = "վ����";
		char fourth[] = "վ������";
		char fifth[] = "����ʼվ����";
		char sixth[] = "����һ��վ����";
		char seventh[] = "����һվ��ͨ��ʱ";
		char eighth[] = "ͣ����ʱ";
		char ninth[] = "������վ���·�߱��";
		printf("|%-4s %-10s %-50s %-12s %-14s %-16s %-8s %-50s|\n", second, third, fourth, fifth, sixth, seventh, eighth, ninth);
        printf("|");printSomeSpace(171);printf("|\n");
		while (siteP != NULL) {
			printf("|%-4d %-10s %-50s %-12.3f %-14.3f %-16.3f %-8.3f %-50s|\n", siteP->siteSID, siteP->siteID, siteP->siteName, siteP->d2Start, siteP->d2Last, siteP->time2Last, siteP->waitTime, siteP->routeIDArray);
			siteP = siteP->next;
		}

		printSomeG(173);printf("\n");
		printSomeSpace(60);printf("|\t1.�鿴վ�������Ϣ\t\t\t|\n");
		printSomeSpace(60);printf("|\t2.�����޸�\t\t\t\t|\n");
		printSomeSpace(60);printf("|\t3.����ɾ��\t\t\t\t|\n");
		printSomeSpace(60);printf("|\t4.��������\t\t\t\t|\n");
		printSomeSpace(60);printf("|\t5.�����ϼ��˵�\t\t\t\t|\n");
		printSomeSpace(60);printf("--------------������ѡ����-----------------\n");

		int seq = 0;
		printSomeSpace(60);scanf("%d%*c", &seq);

        printSomeSpace(60);
		switch (seq) {
		case 1:
			printf("��鿴�ڼ���վ�����ϸ������Ϣ��");
			scanf("%d%*c", &seq);
			printCarPage(getSitePointer(siteHeadP, seq - 1));//��ȥ�ú���
			break;
		case 2:
			printf("���޸ĵڼ���վ�����Ϣ:");
			scanf("%d%*c", &seq);
			int changeWhich = changeSite(getSitePointer(siteHeadP, seq - 1), seq-1, siteHeadP);
			updateSitesFILE(siteHeadP);

			MessageBox(NULL, TEXT("�ɹ��޸�վ����Ϣ"), TEXT("�����ɹ�"), MB_OK);
            if (changeWhich == 6){//�����˾��룬Ӧ����·���ڵ�����̺����б��޸�վ���Ժ󣨰�������������ʼվ��ľ���
                routeP->miles = totalMile(routeP);
            } else if (changeWhich == 4 || changeWhich == 5){//������ʱ�����
                routeP->period = totalTime(routeP);
            } else {
                break;
            }
			updateRoutesFILE(routeHeadP);//update save file

			break;
		case 3:
			printf("��ɾ���ڼ���վ�����Ϣ:");
			scanf("%d%*c", &seq);
			siteHeadP = DelSitePos(siteHeadP, seq - 1);//get the new site head pointer
			routeP->firstSite = siteHeadP;
			//�Զ��ı�����
			if (seq == 1) {//ɾ���˵�һ��
				strcpy(routeP->startSite, siteHeadP->siteID);//������һ���洢�ĵ�һվ����������
			} else if (seq == (sizeSiteList(siteHeadP)-2)) {//ɾ�������һ��
				strcpy(routeP->endSite, getSitePointer(siteHeadP, sizeSiteList(siteHeadP) - 1)->siteID);//������һ���洢���յ�վ����������
			}
			//�Զ��������
			site * stepSite = getSitePointer(siteHeadP, seq - 1);
			while (stepSite != NULL) {
				stepSite->siteSID = stepSite->siteSID - 1;
				stepSite = stepSite->next;
			}
			updateSitesFILE(siteHeadP);

			//����·��վ������Ϣ��������浵
			updateSitesCount(routeP);
            routeP->period = totalTime(routeP);

            //����·�߾���
            routeP->miles = totalMile(routeP);

            //����D2S
            updateAlld2S(siteHeadP);

            updateRoutesFILE(routeHeadP);//update save file
			//TODO: ������ɾ��վ�����ݣ�Ӧɸѡ�Ƿ��б�����·��ռ��
			MessageBox(NULL, TEXT("�ɹ�ɾ��վ��"), TEXT("�����ɹ�"), MB_OK);

			break;
		case 4:
			//�����߼�
			siteHeadP = addSite(siteHeadP, routeP->routeID, routeHeadP);
			routeP->firstSite = siteHeadP;
			updateSitesFILE(siteHeadP);

			//����·��վ������Ϣ��������浵
			updateSitesCount(routeP);
            routeP->period = totalTime(routeP);

            //����·�߾���
            routeP->miles = totalMile(routeP);
            //�����ϼ�·�ߵ���ʼվ��ĩβվ����Ϣ
            site * siteTempP = siteHeadP;
            strcpy(routeP->startSite, siteHeadP->siteID);
            while(siteTempP->next != NULL){
                siteTempP = siteTempP->next;
            }
            strcpy(routeP->endSite, siteTempP->routeID);

            updateRoutesFILE(routeHeadP);
			MessageBox(NULL, TEXT("�ɹ�����վ��"), TEXT("�����ɹ�"), MB_OK);

			break;
		case 5:
			inSitePage = 0;
			break;
		default:
			printf("�������");//���������ѡ�����
			break;
		}
		system("cls");
	}
}

//���������Ϣ
void printCarPage(site * siteP) {
	car * carHeadP = siteP->carHeadP;
	int inCarPage = 1;
	while (inCarPage) {
		system("cls");
		car * carP = carHeadP;
		system("date /T");
		printSomeG(65);printf("վ���ţ�%6s �����г�����Ϣ", siteP->siteID);printSomeG(50);printf("\n");
		char first[] = "��������";
		char second[] = "ִ��·�߱��";
		char third[] = "˾������";
		char fourth[] = "˾���ƶ��绰";
		char fifth[] = "�ػ�����";
		char sixth[] = "�ػ�����";
		char seventh[] = "ж������";
		char eighth[] = "ж������";
		printf("|%-8s %-12s %-8s %-12s %-10s %-10s %-10s %-10s", first, second, third, fourth, fifth, sixth, seventh, eighth);printSomeSpace(57);
		printf("|\n|");printSomeSpace(144);printf("|\n");
		while (carP != NULL) {
			printf("|%-8s %-12s %-8s %-12s ", carP->carID, carP->routeID, carP->driverName, carP->driverTel);
            if (carP->good != NULL){
                printf("%-10s %-10.3f %-10s %-10.3f", carP->good->uploadType, carP->good->upVolume, carP->good->downloadType, carP->good->downVolume);
            }
            printSomeSpace(57);
            printf("|\n");
			carP = carP->next;
		}//now carP == NULL
		printSomeG(146);printf("\n");
		printSomeSpace(60);printf("|\t1.�����޸�\t\t\t\t|\n");
		printSomeSpace(60);printf("|\t2.����ɾ��\t\t\t\t|\n");
		printSomeSpace(60);printf("|\t3.��������\t\t\t\t|\n");
		printSomeSpace(60);printf("|\t4.�����ϼ��˵�\t\t\t\t|\n");
		printSomeSpace(60);printf("--------------������ѡ����-----------------\n");
		printSomeSpace(60);
		int seq = 0; scanf("%d%*c", &seq);
		printSomeSpace(60);
		switch (seq) {
		case 1:
			printf("���޸ĵڼ�̨��������Ϣ:");
			scanf("%d%*c", &seq);
			changeCar(getCarPointer(carHeadP, seq - 1));
			updateCarsFILE(carHeadP, siteP->siteID);
			MessageBox(NULL, TEXT("�ɹ��޸ĳ�����Ϣ"), TEXT("�����ɹ�"), MB_OK);
			break;
		case 2:
			printf("��ɾ���ڼ�̨��������Ϣ:");
			scanf("%d%*c", &seq);
			//ɾ����Ӧ�Ĵ浵�ļ�
			char *url = (char *)malloc(sizeof(char) * 20);
			strcpy(url, "save/");
			car * carDel = getCarPointer(carHeadP, seq - 1);
			if (carDel != NULL){
                strcat(url, getCarPointer(carHeadP, seq - 1)->carID);
                strcat(url, ".txt");
                remove(url);
			} else {
                printf("����ָ�����\n");
			}

			free(url);

			carHeadP = DelCarPos(carHeadP, seq - 1);
			updateCarsFILE(carHeadP, siteP->siteID);
			MessageBox(NULL, TEXT("�ɹ�ɾ������"), TEXT("�����ɹ�"), MB_OK);
			break;
		case 3:
			carHeadP = addCar(carHeadP);
			siteP->carHeadP = carHeadP;
			updateCarsFILE(carHeadP, siteP->siteID);
			MessageBox(NULL, TEXT("�ɹ�������"), TEXT("�����ɹ�"), MB_OK);
			break;
		case 4:
			inCarPage = 0;
			break;
		default:
			break;
		}
	}
}

//change the save file's name
int changeSaveName(char* old, char* new) {
	char * oldUrl = (char*)malloc(20 * sizeof(char));
	char * newUrl = (char*)malloc(20 * sizeof(char));

	strcpy(oldUrl, "save/");
	strcat(oldUrl, old);
	strcat(oldUrl, ".txt");

	strcpy(newUrl, "save/");
	strcat(newUrl, new);
	strcat(newUrl, ".txt");
	int result = 0;
	if (rename(oldUrl, newUrl) == 0) {
		result = 1;
	} else {
		result = 0;
	}
	free(oldUrl);
	free(newUrl);
	return result;
}

//�����ı�洢ĳ·������վ��Ĵ浵�е�routeID
void changeOldRouteID(route * routeSpecific) {
    site * siteP = routeSpecific->firstSite;
	while (siteP != NULL) {
		strcpy(siteP->routeID, routeSpecific->routeID);
		siteP = siteP->next;
	}
	updateSitesFILE(routeSpecific->firstSite);
}

//�Զ�վ�������£����ݶ���ָ��ĵķ���ֵ��Ϊһ���ĳ�Ա���ݡ�վ���������и�ֵ��
void updateSitesCount(route * routeSpecific){
    int count = 0;
    site * siteHeadP = routeSpecific->firstSite;
    count = sizeSiteList(siteHeadP);
    routeSpecific->siteNums = count;
}
//����ͳ�Ʊ���
void makeCsv(route * routeHeadP){
    system("cls");
    FILE * saveF = fopen("������Ϣͳ�Ʊ���.csv","w");
    fprintf(saveF, "����·����Ϣ��\n");
    fprintf(saveF, "��,���,����,��վ����,�ܹ�����,�ܺ�ʱ,��ʼվ����,��ֹվ����,����������,�����˰칫�ҵ绰,�������ƶ��绰,�����˵�������\n");

    route * routeP = routeHeadP;
    while (routeP != NULL){
        fprintf(saveF,"��,%s,%s,%d,%f,%f,%s,%s,%s,%s,%s,%s\n",routeP->routeID, routeP->name, routeP->siteNums, routeP->miles, routeP->period, routeP->startSite, routeP->endSite, routeP->adminName, routeP->tel, routeP->mTel, routeP->email);
        routeP = routeP->next;
    }

    fprintf(saveF, "\n\n����վ����Ϣ��\n");
    routeP = routeHeadP;
    while (routeP != NULL){
        site * siteP = routeP->firstSite;
        fprintf(saveF, "\n��,·��%s ��վ����Ϣ��\n", routeP->routeID);
        fprintf(saveF, "��,�̶�����·�߱��,���,���,����,����ʼվ�����,����һ��վ�����,����һ��վ�㽻ͨ��ʱ,ͣ����ʱ,������վ��̶�·�߱��\n");
        while (siteP != NULL){
            fprintf(saveF, "��,%s,%d,%s,%s,%f,%f,%f,%f,%s\n",siteP->routeID,siteP->siteSID, siteP->siteID, siteP->siteName, siteP->d2Start, siteP->d2Last, siteP->time2Last, siteP->waitTime, siteP->routeIDArray);
            siteP = siteP->next;
        }
        routeP = routeP->next;
    }

    fprintf(saveF, "\n\n���г�����Ϣ��\n");
    routeP = routeHeadP;
    while (routeP != NULL){
        site * siteP = routeP->firstSite;
        while (siteP != NULL){
            car * carP = siteP->carHeadP;
            fprintf(saveF, "\n��,վ��%s �ĳ�����Ϣ��\n", siteP->siteID);
            fprintf(saveF, "��,��������,ִ������·�߱��,˾������,˾���ƶ��绰,�ػ�����,�ػ�����,ж������,ж������\n");
            while (carP != NULL){
                fprintf(saveF, "��,%s,%s,%s,%s", carP->carID, carP->routeID, carP->driverName, carP->driverTel);
                good * goodP = carP->good;
                if (goodP != NULL){
                    fprintf(saveF, "��,%s,%f,%s,%f", goodP->uploadType, goodP->upVolume, goodP->downloadType, goodP->downVolume);
                }
                fprintf(saveF, "\n");
                carP = carP->next;
            }
            siteP = siteP->next;
        }
        routeP = routeP->next;
    }

    fprintf(saveF, "\n\nͳ����Ϣ��\n\n");

    fprintf(saveF, "��,·��������,%d\n",sizeRouteList(routeHeadP));

    int sitesCount = 0;routeP = routeHeadP;
    while(routeP != NULL){
        sitesCount = sitesCount + sizeSiteList(routeP->firstSite);
        routeP = routeP->next;
    }
    fprintf(saveF, "��,վ��������,%d\n", sitesCount);

    int carsCount = 0;routeP = routeHeadP;
    while (routeP != NULL){
        site * siteP = routeP->firstSite;
        while (siteP != NULL){
            carsCount = carsCount + sizeCarList(siteP->carHeadP);
            siteP = siteP->next;
        }
        routeP = routeP->next;
    }
    fprintf(saveF, "��,����������,%d\n\n", carsCount);

    //��������߼�
    float mileSum = 0;routeP = routeHeadP;
    while (routeP != NULL){
        mileSum = mileSum + routeP->miles;
        routeP = routeP->next;
    }
    fprintf(saveF, "��,·������̣�,%.4f\n", mileSum);
    fprintf(saveF, "��,·��ƽ����̣�,%.4f\n", mileSum/sizeRouteList(routeHeadP));

    char StringTemp[50];
    float tempFloat = -1;
    routeP = routeHeadP;//�Ƚ�֮ǰ�ĳ�ʼ��
    while (routeP != NULL){
        if (routeP->period > tempFloat){
            tempFloat = routeP->miles;
            strcpy(StringTemp, routeP->routeID);
        }
        routeP = routeP->next;
    }
    fprintf(saveF, "��,��������,%.4f,·��%s\n", tempFloat, StringTemp);

    tempFloat = 99999;routeP = routeHeadP;
    while (routeP != NULL){
        if (routeP->period < tempFloat){
            tempFloat = routeP->miles;
            strcpy(StringTemp, routeP->routeID);
        }
        routeP = routeP->next;
    }
    fprintf(saveF, "��,����������,%.4f,·��%s\n\n", tempFloat, StringTemp);

    //�����ʱ�߼�
    tempFloat = -1;routeP = routeHeadP;
    while (routeP != NULL){
        float timeThis = totalTime(routeP);
        if (timeThis > tempFloat){
            tempFloat = timeThis;
            strcpy(StringTemp, routeP->routeID);
        }
        routeP = routeP->next;
    }
    fprintf(saveF, "��,���ʱ��,%.4f,·��%s\n", tempFloat, StringTemp);

    tempFloat = 99999;routeP = routeHeadP;
    while (routeP != NULL){
        float timeThis = totalTime(routeP);
        if (timeThis < tempFloat){
            tempFloat = timeThis;
            strcpy(StringTemp, routeP->routeID);
        }
        routeP = routeP->next;
    }
    fprintf(saveF, "��,��̺�ʱ��,%.4f,·��%s\n", tempFloat, StringTemp);

    tempFloat = 0;routeP = routeHeadP;
    while (routeP != NULL){
        tempFloat = tempFloat + totalTime(routeP);
        routeP = routeP->next;
    }
    fprintf(saveF, "��,ƽ����ʱ��,%.4f\n\n", tempFloat/sizeRouteList(routeHeadP));


    //ͳ���ػ����߼�
    tempFloat = 0;routeP = routeHeadP;
    float minCarry = 9999;float maxCarry = -1;
    float minEfficiency = 999;float maxEfficiency = -1;
    char maxCarID[10];char minCarID[10];
    char maxCarID2[10];char minCarID2 [10];
    while (routeP != NULL){
        site * siteP = routeP->firstSite;
        while (siteP != NULL){
            car * carP = siteP->carHeadP;
            while (carP != NULL){
                if (carP->good != NULL){
                    float carryVolume = carP->good->upVolume;
                    tempFloat = tempFloat + carryVolume;
                    //���������С�ػ�������
                    if (carryVolume > maxCarry){
                        maxCarry = carryVolume;
                        strcpy(maxCarID, carP->carID);
                    } else if (carryVolume < minCarry){
                        minCarry = carryVolume;
                        strcpy(minCarID, carP->carID);
                    }
                    //����������Ч������
                    float efficiencyThis = carryVolume/getMile(carP->routeID, routeHeadP);
                    if (efficiencyThis > maxEfficiency){
                        maxEfficiency = efficiencyThis;
                        strcpy(maxCarID2, carP->carID);
                    } else if (efficiencyThis < minEfficiency){
                        minEfficiency = efficiencyThis;
                        strcpy(minCarID2, carP->carID);
                    }
                }
                carP = carP->next;
            }
            siteP = siteP->next;
        }
        routeP = routeP->next;
    }
    fprintf(saveF, "��,���ػ�����,%.4f\n", tempFloat);
    fprintf(saveF, "��,ƽ���ػ�����,%.4f\n", tempFloat/carsCount);
    fprintf(saveF, "��,����ػ�����,%.4f,%s\n", maxCarry, maxCarID);
    fprintf(saveF, "��,��С�ػ�����,%.4f,%s\n\n", minCarry, minCarID);

    //��������Ч���߼�
    fprintf(saveF, "��,ƽ������Ч�ʣ�,%.4f\n", tempFloat/mileSum);
    fprintf(saveF, "��,�������Ч�ʣ�,%.4f,%s\n", maxEfficiency, maxCarID2);
    fprintf(saveF, "��,�������Ч�ʣ�,%.4f,%s\n", minEfficiency, minCarID2);
    fprintf(saveF, "��,PS:����Ч��ָ�ػ���������ʱ��֮��\n");

    fclose(saveF);
    MessageBox(NULL, TEXT("�����Ѿ������ڳ���ĸ�Ŀ¼��"), TEXT("�����ɹ�"), MB_OK);
}

//�Ӵ���Ĳ�����Ӧ��·���У�����վ��������ȥ����׼ȷ�ĺ�ʱ����
float totalTime(route *routeP){
    site * siteP = routeP->firstSite;
    float time = 0;
    while (siteP != NULL){
        time = siteP->d2Last + siteP->waitTime + time;
        siteP = siteP->next;
    }
    return time;
}
//�Ӵ���Ĳ�����Ӧ��·���У�����վ��������ȥ����ܳ���
float totalMile(route *routeP){
    site * siteTempP = routeP->firstSite;
    while (siteTempP->next != NULL){
        siteTempP = siteTempP->next;
    }
    return siteTempP->d2Start;
}

//�Ӵ����·��������Ѱ�Ҷ�Ӧ�ַ������������ݵ����
float getMile(char *routeIDThis, route * routeHeadP){
    route *routeP = routeHeadP;
    while (routeP != NULL){
        if (strcmp(routeP->routeID, routeIDThis) == 0){
            return routeP->miles;
        }
        routeP = routeP->next;
    }
    return 0;
}
//��������ո�
void printSomeSpace(int num){
    int i = 0;
    for (i = 0; i < num; i++){
        printf(" ");
    }
}
//�������Gang �ܺ�
void printSomeG(int num){
    int i = 0;
    for (i = 0; i < num; i++){
        printf("-");
    }
}


/**
* ����·�ߵ�d2S
* �����վ��ָ��Ϊ������ȷ�����һ��·�ߣ����������·�߶���Ҫ���и���
*/
void updateAlld2S(site * siteP){//
    site * sitePre = siteP;
    site * siteNext = siteP->next;
    while (siteNext != NULL){
        siteNext->d2Start = sitePre->d2Start + siteNext->d2Last;
        sitePre = siteNext;
        siteNext = siteNext->next;
    }
}
