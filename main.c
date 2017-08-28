#include <stdio.h>
#include <ListTool.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//TODO: update files

route * initData();
void printFronPage();
void printPowerBy();
void printRoutePage(route * routeHeadP);
void updateRoutesFILE(route* routeHeadP);
void addRoute(route * routeHeadP);
char* noNfgets(char * Buffer, int MaxConut, FILE* Stream);
int changeRoute(route * routeSpecial);
void printfSitePage(route *routeP);

int main() {
	route* routeHeadP;
	routeHeadP = initData();//��ʼ������������
	char *url = malloc(sizeof(char) * 20);//���ٿռ��ʹ��
	//int isFrontPage = 1;
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
					printf("����ϸ�鿴�ڼ���·�ߣ�");
					seq = 0; scanf("%d%*c", &seq);
					printfSitePage(getRoutePointer(routeHeadP, seq - 1));

				} else if (input2 == 2) {
					printf("���޸ĵڼ���·�ߣ�");
					seq = 0; scanf("%d%*c", &seq);
					changeRoute(getRoutePointer(routeHeadP, seq-1));
					updateRoutesFILE(routeHeadP);
					MessageBox(NULL, TEXT("�ɹ��޸�·��"), TEXT("�����ɹ�"), MB_OK);
					//TODO����һ�޸��˱�ŵĴ����߼�
					system("cls");
				} else if (input2 == 3) {
					printf("��ɾ���ڼ���·�ߣ�");
					seq = 0; scanf("%d%*c", &seq);
					routeHeadP = DelRoutePos(routeHeadP, seq-1);
					updateRoutesFILE(routeHeadP);
					//ɾ����Ӧ�Ĵ浵�ļ�
					strcpy(url, "save/");
					strcat(url, getRoutePointer(routeHeadP, sizeRouteList(routeHeadP) - 1)->routeID);
					strcat(url, ".txt");
					remove(url);
					MessageBox(NULL, TEXT("�ɹ�ɾ��·��"), TEXT("�����ɹ�"), MB_OK);
					system("cls");
				} else if (input2 == 4) {
					addRoute(routeHeadP);
					updateRoutesFILE(routeHeadP);
					MessageBox(NULL, TEXT("�ɹ�����·��\n��������·����ϸ��Ϣ�������վ����Ϣ"), TEXT("�����ɹ�"), MB_OK);
					//������Ӧ��·�ߴ浵�ļ�������Ȼ�ǿ��ļ���
					char *url = malloc(sizeof(char) * 20);
					strcpy(url, "save/");
					strcat(url, getRoutePointer(routeHeadP, sizeRouteList(routeHeadP)-1)->routeID);
					strcat(url, ".txt");
					FILE * newF = fopen(url, "w");
					fclose(newF);

					system("cls");
				} else if (input2 == 5) {
					isRoutePage = 0;
					system("cls");
				}

			}
		} else if (input1 == 2) {
			printPowerBy();
			continue;
		} else {
			system("cls");
			printf("�����������");
		}
	}
	free(url);
	
	
	return 0;
}


/*��ʼ������*/
route * initData() {
	FILE *fRouteP = fopen("save/routes.txt", "r+");
	route * routeHeadP = NULL;
	if (fRouteP == NULL) {
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
					continue;
				}
				car * carHeadP = creatCarList(fCar);
				siteHeadP->carHeadP = carHeadP;
				fclose(fCar);//finish reading cars' info
				
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

void printFronPage() {
	printf("-------------------------------------------------\n");
	printf("|��ӭ����������Ϣ����ϵͳ������Ӧ���ֽ��빦��\t|\n");
	printf("|\t1.����ϵͳ\t\t\t\t|\n");
	printf("|\t2.��������Ϣ\t\t\t\t|\n");
	printf("-------------------------------------------------\n");
}

void printPowerBy() {
	system("cls");
	MessageBox(NULL, TEXT("���пƼ���ѧ\nIOT1601 �����\nC���Գ������_�γ������Ʒ\n������Ϣ��ѯϵͳ"), TEXT("��������Ϣ"), MB_OK);
}

void printRoutePage(route * routeHeadP) {
	route * routeP = routeHeadP;
	system("cls");
	printf("------------------����·����Ϣ-------------------\n");
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
	printf("|  %-6s %-20s %-6s %-10s %-10s %-10s %-10s %-8s %-8s %-11s %-50s|\n\n", first, second, third, fourth, fifth, sixth, seventh, eighth, ninth, tenth, eleventh);

	register int i = 1;
	while (routeP != NULL) {
		printf("|%d:",i);
		printf("%-6s %-20s %-6d %-10.3f %-10.3f %-10s %-10s %-8s %-8s %-11s %-50s|\n", routeP->routeID, routeP->name, routeP->siteNums, routeP->miles, routeP->period, routeP->startSite, routeP->endSite, routeP->adminName, routeP->tel, routeP->mTel, routeP->email);
		routeP = routeP->next;
		i++;
	}
	printf("-------------------------------------------------\n");
	printf("|\t1.�鿴·�߾�����Ϣ\t\t\t|\n");
	printf("|\t2.�����޸�\t\t\t\t|\n");
	printf("|\t3.����ɾ��\t\t\t\t|\n");
	printf("|\t4.��������\t\t\t\t|\n");
	printf("|\t5.�����ϼ��˵�\t\t\t\t|\n");
	printf("----------------������ѡ����-------------------\n");
}

void updateRoutesFILE(route* routeHeadP) {
	route * routeP = routeHeadP;
	FILE *fRouteP = fopen("save/routes.txt", "w+");//��ͷ��д�ı�
	while (routeP != NULL) {
		fprintf(fRouteP,"%s;%s;%d;%f;%f;%s;%s;%s;%s;%s;%s\n",routeP->routeID, routeP->name, routeP->siteNums, routeP->miles, routeP->period, routeP->startSite, routeP->endSite, routeP->adminName, routeP->tel, routeP->mTel, routeP->email);
		routeP = routeP->next;
	}
	fclose(fRouteP);
}

//The new route would be the last node in this list.
void addRoute(route * routeHeadP) {
	//fflush(stdin);
	route * newRouteP = AddRouteNode(routeHeadP, sizeRouteList(routeHeadP));
	if (newRouteP != NULL) {
		char inputTemp[51];
		printf("---------------��������·�ߵ���Ϣ----------------\n");
		printf("��������:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->routeID, inputTemp);
		printf("����������:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->name, inputTemp);
		printf("��������վ����:");
		short sitesCount = 0;
		scanf("%d%*c", &sitesCount);
		newRouteP->siteNums = sitesCount;
		printf("�������ܹ�����:");
		float fMiles = 0;
		scanf("%f%*c", &fMiles);
		newRouteP->miles = fMiles;
		printf("�������ܺ�ʱ:");
		float fPeriod = 0;
		scanf("%f%*c", &fPeriod);
		newRouteP->period = fPeriod;
		printf("��������ʼվ����:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->startSite, inputTemp);
		printf("��������ֹվ����:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->endSite, inputTemp);
		printf("�����븺��������:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->adminName, inputTemp);
		printf("�����븺���˰칫�ҵ绰:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->tel, inputTemp);
		printf("�����븺�����ƶ��绰:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->mTel, inputTemp);
		printf("�����븺���˵�������:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->email, inputTemp);
	} else {
		system("cls");
		printf("error\n");
	}
}

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

int changeRoute(route * routeSpecial) {
	printf("-------------------------------------------------\n");
	printf("1.���\n2.����\n3.��վ����\n4.�ܹ�����\n5.�ܺ�ʱ\n6.��ʼվ����\n7.��ֹվ����\n8.����������\n9.�����˰칫�ҵ绰\n10.�������ƶ��绰\n11.�����˵�������\n��ѡ����Ҫ�޸ĵ�����:");
	int choose = 0;
	scanf("%d%*c", &choose);
	char input[51];
	switch (choose) {
	case 1:
		printf("�������µı��:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecial->routeID, input);
		break;
	case 2:
		printf("�������µ�����:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecial->name, input);
		break;
	case 3:
		printf("�������µ���վ����:");
		int sitesCount = 0;
		scanf("%d%*c", &sitesCount);
		routeSpecial->siteNums = sitesCount;
		//TODO: auto ask if user want to set those sites infomation at the same time OR JUST NOTIFTY HIM OR HER
		break;
	case 4:
		printf("�������µ��ܹ�����:");
		float newMiles = 0;
		scanf("%f%*c", newMiles);
		routeSpecial->miles = newMiles;
		break;
	case 5:
		printf("�������µ��ܺ�ʱ:");
		float newPeriod = 0;
		scanf("%f%*c", newPeriod);
		routeSpecial->period = newPeriod;
		break;
	case 6:
		printf("�������µ���ʼվ����:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecial->startSite, input);
		break;
	case 7:
		printf("�������µ���ֹվ����:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecial->endSite, input);
		break;
	case 8:
		printf("�������µĸ���������:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecial->adminName, input);
		break;
	case 9:
		printf("�������µĸ����˰칫�ҵ绰:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecial->tel, input);
		break;
	case 10:
		printf("�������µĸ������ƶ��绰:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecial->mTel, input);
		break;
	case 11:
		printf("�������µĸ����˵�������:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecial->email, input);
		break;
	default:
		printf("��������\n");
		return 0;
	}
	return 1;
}

void printfSitePage(route *routeP) {
	int inSitePage = 1;
	site* siteHeadP = routeP->firstSite;
	while (inSitePage) {
		system("cls");
		site* siteP = siteHeadP;
		printf("----------------·�߱�ţ�%6s ������վ����Ϣ---------------\n", siteHeadP->routeID);
		char second[] = "���";
		char third[] = "վ����";
		char fourth[] = "վ������";
		char fifth[] = "����ʼվ����";
		char sixth[] = "����һ��վ����";
		char seventh[] = "����һվ��ͨ��ʱ";
		char eighth[] = "ͣ����ʱ";
		char ninth[] = "������վ���·�߱��";
		printf("|%-4s %-10s %-50s %-12s %-14s %-16s %-8s %-50s|\n\n", second, third, fourth, fifth, sixth, seventh, eighth, ninth);

		while (siteP != NULL) {
			printf("|%-4d %-10s %-50s %-12.3f %-14.3f %-16.3f %-8.3f %-50s|\n", siteP->siteSID, siteP->siteID, siteP->siteName, siteP->d2Start, siteP->d2Last, siteP->time2Last, siteP->waitTime, siteP->routeIDArray);
			siteP = siteP->next;
		}
		printf("---------------------------------------------------------\n");
		printf("|\t1.�鿴վ�������Ϣ\t\t\t|\n");
		printf("|\t2.�����޸�\t\t\t\t|\n");
		printf("|\t3.����ɾ��\t\t\t\t|\n");
		printf("|\t4.��������\t\t\t\t|\n");
		printf("|\t5.�����ϼ��˵�\t\t\t\t|\n");
		printf("--------------------������ѡ����-----------------------\n");

		int seq = 0;
		scanf("%d%*c", &seq);

		switch (seq) {
		case 1:
			printf("��鿴�ڼ���վ�����ϸ��Ϣ��");
			//�鿴��Ϣ�߼���һ����ȥ��
			break;
		case 2:
			printf("���޸ĵڼ���վ�����Ϣ:");
			break;
		case 3:
			printf("��ɾ���ڼ���վ�����Ϣ:");
			scanf("%d%*c", &seq);
			siteHeadP = DelCarPos(siteHeadP, seq - 1);//get the new site head
			if(siteHeadP)
			break;
		case 4:
			//�����߼�
			break;
		case 5:
			inSitePage = 0;
			break;
		default:
			printf("�������");//���������ѡ�����
			break;
		}
	}
}