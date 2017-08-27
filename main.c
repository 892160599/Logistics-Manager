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

int main() {
	route* routeHeadP;
	routeHeadP = initData();//��ʼ������������
	//int isFrontPage = 1;
	while (1) {
	    printFronPage();

		int input1 = 0; 
		scanf("%d", &input1);//����û�������ֵ

		if (input1 == 1) {
			int isRoutePage = 1;
			while (isRoutePage) {
				printRoutePage(routeHeadP);//���·��ҳ����Ϣ
				int input2 = 0; scanf("%d", &input2);//����û�������ֵ
				int seq = 0;

				if (input2 == 1) {
					printf("����ϸ�鿴�ڼ���·�ߣ�");
					seq = 0; scanf("%d", &seq);//����û�������ֵ
					//TODO:��ϸ����
					system("cls");
				} else if (input2 == 2) {
					printf("���޸ĵڼ���·�ߣ�");
					seq = 0; scanf("%d", &seq);//����û�������ֵ
					//TODO:�޸��߼�
					MessageBox(NULL, TEXT("�ɹ��޸�·��"), TEXT("�����ɹ�"), MB_OK);
					system("cls");
				} else if (input2 == 3) {
					printf("��ɾ���ڼ���·�ߣ�");
					seq = 0; scanf("%d", &seq);//����û�������ֵ
					routeHeadP = DelRoutePos(routeHeadP, seq);
					updateRoutesFILE(routeHeadP);
					MessageBox(NULL, TEXT("�ɹ�ɾ��·��"), TEXT("�����ɹ�"), MB_OK);
					system("cls");
					//TODO:����ɾ����IO����
				} else if (input2 == 4) {
					//����·���߼�
					MessageBox(NULL, TEXT("�ɹ�����·��"), TEXT("�����ɹ�"), MB_OK);
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
	/*printf("------------------��������Ϣ��-------------------\n");
	printf("|\t ���пƼ���ѧ\t\t\t\t|\n");
	printf("|\t IOT1601 �����\t\t\t\t|\n");
	printf("|\t C���Գ������_�γ������Ʒ\t\t|\n");
	printf("|\t ������Ϣ��ѯϵͳ\t\t\t|\n");
	printf("-------------------------------------------------\n");*/
	MessageBox(NULL, TEXT("���пƼ���ѧ\nIOT1601 �����\nC���Գ������_�γ������Ʒ\n������Ϣ��ѯϵͳ"), TEXT("��������Ϣ"), MB_OK);
}

void printRoutePage(route * routeHeadP) {
	route * routeP = routeHeadP;
	system("cls");
	printf("-------------------�ѽ���ϵͳ--------------------\n");
	printf("| ����·����Ϣ���£�\n\n");
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
	printf("|   %-5s %-20s %-6s %-10s %-10s %-10s %-10s %-8s %-8s %-11s %-50s|\n", first, second, third, fourth, fifth, sixth, seventh, eighth, ninth, tenth, eleventh);

	register int i = 1;
	while (routeP != NULL) {
		/*char * sitesCount = (char *)malloc(sizeof(char) * 5);
		char * miles = (char *)malloc(sizeof(char) * 31);
		char * times = (char *)malloc(sizeof(char) * 31);
		itoa(routeP->siteNums, sitesCount, 10);
		sprintf(miles, "%f", routeP->miles);
		sprintf(times, "%f", routeP->period);*/
		printf("|%d:",i);
		printf("%-5s %-20s %-6d %-10f %-10f %-10s %-10s %-8s %-8s %-11s %-50s|\n", routeP->routeID, routeP->name, routeP->siteNums, routeP->miles, routeP->period, routeP->startSite, routeP->endSite, routeP->adminName, routeP->tel, routeP->mTel, routeP->email);
	/*	free(sitesCount);
		free(miles);
		free(times);*/
		routeP = routeP->next;
		i++;
	}
	printf("-------------------------------------------------\n");
	printf("|\t1.�鿴��·�߾�����Ϣ\t\t\t|\n");
	printf("|\t2.�����޸�\t\t\t\t|\n");
	printf("|\t3.����ɾ��\t\t\t\t|\n");
	printf("|\t4.��������\t\t\t\t|\n");
	printf("|\t5.�����ϼ��˵�\t\t\t\t|\n");
	printf("-------------------------------------------------\n");
}

//void addRouteNode() {
//
//}

void updateRoutesFILE(route* routeHeadP) {
	route * routeP = routeHeadP;
	FILE *fRouteP = fopen("save/routes.txt", "w");//��ͷ��д�ı�
	while (routeP != NULL) {
		fprintf("%s;%s;%d;%f;%f;%s;%s;%s;%s;%s;%s\n",routeP->routeID, routeP->name, routeP->routeID, routeP->name, routeP->siteNums, routeP->miles, routeP->period, routeP->startSite, routeP->endSite, routeP->adminName, routeP->tel, routeP->mTel, routeP->email);
		routeP = routeP->next;
	}
}
