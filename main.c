#include <stdio.h>
#include <ListTool.h>
#include <stdlib.h>
#include <conio.h>

route * initData();
void printFronPage();

int main() {
	route* routeHeadP = initData();//��ʼ������������
	while (1) {
		printFronPage();
		char in = getchar();//����û�������ֵ
		getchar();
		if (in == '1') {
			break;
		} else if (in == '2') {
			printPowerBy();
			continue;
		}
	}
	
	return 0;
}


/*��ʼ������*/
route * initData() {
	FILE *fRouteP = fopen("save/routes.txt", "r+");
	route * routeHeadP;
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
	printf("-------------------------------------------------\n");
	printf("|��������Ϣ��\t|\n");
	printf("|\t ���пƼ���ѧ\t\t\t\t|\n");
	printf("|\t IOT1601 �����\t\t\t\t|\n");
	printf("|\t C���Գ������_�γ������Ʒ\t\t\t\t|\n");
	printf("|\t ������Ϣ��ѯϵͳ\t\t\t\t|\n");
	printf("-------------------------------------------------\n");
	system("pause");
}
