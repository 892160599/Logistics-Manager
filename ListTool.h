#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<DataStructure.h>

/* CURD for routes */

/* ��������·�����ݵ����Ա�*/
route *creatRouteList(FILE* fText) {
	if (feof(fText)) {
		return NULL;
	}
	route *routeP, *pReturn;

	//set the first node (of course this is not an elagent way to realize
	routeP = (route *)malloc(sizeof(route));
	char StrLine[200];
	fgets(StrLine, 200, fText);
	char ** info = readRoute(StrLine);
	strcpy(routeP->routeID, info[0]);
	strcpy(routeP->name, info[1]);
	routeP->siteNums = atoi(info[2]);
	routeP->miles = (float)atof(info[3]);
	routeP->period = (float)atof(info[4]);
	strcpy(routeP->startSite, info[5]);
	strcpy(routeP->endSite, info[6]);
	strcpy(routeP->adminName, info[7]);
	strcpy(routeP->tel, info[8]);
	strcpy(routeP->mTel, info[9]);
	strcpy(routeP->email, info[10]);
	freeDoubleCharArray(11, info);//deeply free
	routeP->next = NULL;
	pReturn = routeP;

	//read other route info from text
	while (1) {
		route * tempP = (route *)malloc(sizeof(route));
		char StrLine[200];
		fgets(StrLine, 200, fText);
		if (feof(fText)) {
			free(tempP);
			break;
		}
		char ** info = readRoute(StrLine);

		strcpy(tempP->routeID, info[0]);
		strcpy(tempP->name, info[1]);
		tempP->siteNums = atoi(info[2]);
		tempP->miles = (float) atof(info[3]);
		tempP->period = (float)atof(info[4]);
		strcpy(tempP->startSite, info[5]);
		strcpy(tempP->endSite, info[6]);
		strcpy(tempP->adminName, info[7]);
		strcpy(tempP->tel, info[8]);
		strcpy(tempP->mTel, info[9]);
		strcpy(tempP->email, info[10]);
		freeDoubleCharArray(11, info);//deeply free

		routeP->next = tempP;
		routeP = tempP;
		routeP->next = NULL;
	}
	return pReturn;
}

//·�ߵ�վ����Ϣ�������� ����ָ���·�ߵĵ�һ��վ���ָ�룬
//�Ӷ��ⲿ���Խ�վ��������·�߽��
site * creatSiteList(FILE* fText) {

	site *siteP, *pReturn;

	//set the first node (of course this is not an elagent way to realize this method
	siteP = (site *)malloc(sizeof(site));
	char StrLine[200];
	fgets(StrLine, 200, fText);
	char ** info = readRoute(StrLine);
	strcpy(siteP->routeID, info[0]);
	siteP->siteSID = atoi(info[1]);
	strcpy(siteP->siteID, info[2]);
	strcpy(siteP->siteName, info[3]);
	siteP->d2Start = atof(info[4]);
	siteP->d2Last = atof(info[5]);
	siteP->time2Last = atof(info[6]);
	siteP->waitTime = atof(info[7]);
	strcpy(siteP->routeIDArray, info[8]);
	freeDoubleCharArray(9, info);
	siteP->next = NULL;
	pReturn = siteP;

	//read other site info from text
	while (1) {
		site * tempP = (site *)malloc(sizeof(site));

		char StrLine[200];
		fgets(StrLine, 200, fText);
		if (feof(fText)) {
			free(tempP);
			break;
		}
		char ** info = readRoute(StrLine);//�����ַ����зֲ���

		strcpy(tempP->routeID, info[0]);
		tempP->siteSID = atoi(info[1]);
		strcpy(tempP->siteID, info[2]);
		strcpy(tempP->siteName, info[3]);
		tempP->d2Start = atof(info[4]);
		tempP->d2Last = atof(info[5]);
		tempP->time2Last = atof(info[6]);
		tempP->waitTime = atof(info[7]);
		strcpy(tempP->routeIDArray, info[8]);
		freeDoubleCharArray(9, info);

		siteP->next = tempP;
		siteP = tempP;
		siteP->next = NULL;
	}
	return pReturn;
}

//������Ϣ�������ص�һ��������ָ��
car * creatCarList(FILE * fText) {

	car *carP, *pReturn;

	//set the first node (of course this is not an elagent way to realize this method
	carP = (car *)malloc(sizeof(car));
	char StrLine[200];
	fgets(StrLine, 200, fText);
	char ** info = readCar(StrLine);

	strcpy(carP->carID, info[0]);
	strcpy(carP->routeID, info[1]);
	strcpy(carP->driverName, info[2]);
	strcpy(carP->driverTel, info[3]);
	freeDoubleCharArray(4, info);

	carP->next = NULL;
	pReturn = carP;

	//read other site info from text
	while (1) {
		car * tempP = (car *)malloc(sizeof(car));

		char StrLine[200];
		fgets(StrLine, 200, fText);
		if (feof(fText)) {
			free(tempP);
			break;
		}
		char ** info = readCar(StrLine);//�����ַ����зֲ���

		strcpy(tempP->carID, info[0]);
		strcpy(tempP->routeID, info[1]);
		strcpy(tempP->driverName, info[2]);
		strcpy(tempP->driverTel, info[3]);
		freeDoubleCharArray(4, info);

		carP->next = tempP;
		carP = tempP;
		carP->next = NULL;
	}
	return pReturn;
}

//����������Ϣ������ָ�뷵�س��ⲿ
good* creatGood(FILE * fText) {
	good* goodP = (good *)malloc(sizeof(good));
	char StrLin[200];
	char StrLine[200];
	fgets(StrLine, 200, fText);
	char ** info = readGood(StrLine);

	strcpy(goodP->uploadType, info[0]);
	goodP->upVolume = atof(info[1]);
	strcpy(goodP->downloadType, info[2]);
	goodP->downVolume = atof(info[3]);
	freeDoubleCharArray(4, info);
	
	return goodP;
}

/* ��ӡ��������ı�����TODO����Ҫ����ʽ������Ҫ��ȱ���(������)*/
void printList(route *pHead) {
	// TODO
}

/* ��յ�����TODO:   WARNING����Ҫ�²��ͷź��ٵ���(ʮ������) or ��ȱ�������*/
void clearList(route *pHead) {
	route *pNext;

	while (pHead->next != NULL) {
		pNext = pHead->next;
		free(pHead);
		pHead = pNext;
	}
}

/* ��������ĳ���*/
int sizeRouteList(route *pHead) {
	int size = 0;
	while (pHead != NULL) {
		size++;
		pHead = pHead->next;
	}
	return size;
}
int sizeSiteList(site *pHead) {
	int size = 0;
	while (pHead != NULL) {
		size++;
		pHead = pHead->next;
	}
	return size;
}
int sizeCarList(car *pHead) {
	int size = 0;
	while (pHead != NULL) {
		size++;
		pHead = pHead->next;
	}
	return size;
}

/* ���ĳλ�ý��ĵ�ַ�����ⲿ�����޸�, ʧ���򷵻ؿ�ָ��*/
route* getRoutePointer(route *pHead, int pos) {

	if (pHead == NULL) {
		return NULL;
	}

	route *pNode = pHead;
	int i = 0;
	while (pNode != NULL) {
		if (i == pos) {
			break;
		}
		pNode = pNode->next;
		i++;
	}
	return pNode;
	
}
site *getSitePointer(site *pHead, int pos) {

	if (pHead == NULL) {
		return NULL;
	}

	site *pNode = pHead;
	int i = 0;
	while (pNode != NULL) {
		if (i == pos) {
			break;
		}
		pNode = pNode->next;
		i++;
	}
	return pNode;
}
site *getCarPointer(car *pHead, int pos) {

	if (pHead == NULL) {
		return NULL;
	}

	car *pNode = pHead;
	int i = 0;
	while (pNode != NULL) {
		if (i == pos) {
			break;
		}
		pNode = pNode->next;
		i++;
	}
	return pNode;
}

/* �������е�pos�����λ�ò���Ԫ��Ϊx�Ľ��(�Ѹ�λ�õ�����)��������ɹ������½���ָ�룬���򷵻�NULL*/
route* AddPos(route *pNode, int pos) {
	route *pHead = pNode;
	route *pPre = pNode;//both set to the first
	route *pNew = NULL;
	int i = 0;

	if (NULL == pHead) {
		printf("AddPos����ִ�У�����Ϊ��\n");
		return NULL;
	}

	while (pHead != NULL) {
		if (i == pos)
			break;
		pPre = pHead;
		pHead = pHead->next;
		++i;
	}

	pNew = (route *)malloc(sizeof(route));
	if (pPre == NULL) {
		printf("heap is full.");
		return NULL;//error
	}
	if (i==0) {//add to the first one
		pNew->next = pNode;
	} else if (pHead->next == NULL) {//add to the last one
		pHead->next = pNew;
		pNew->next = NULL;
	} else {
		pPre->next = pNew;
		pNew->next = pHead;
	}
	return pNew;
}

/* �ӵ�������ɾ����pos�����(����ͷβ), @return: successful is return 1.*/
int DelPos(route *pNode, int pos) {
	route *pHead = pNode;
	route *pTmp = pNode;
	

	//����ָ��
	if (NULL == pHead) {
		printf("DelPos����ִ�У�����Ϊ��\n");
		return 0;
	}

	int i = 0;
	while (pHead != NULL) {
		if (i == pos)
			break;
		pTmp = pHead;
		pHead = pHead->next;
		++i;
	}

	if (i==0) {
		free(pHead);
		return 1;
	}

	pTmp->next = pHead->next;
	free(pHead);
	printf("DelPos����ִ�гɹ���ɾ���Ľڵ�IDΪ��ֵ%s\n", pos, pHead->routeID);
	return 1;
}

/* ����2��Ԫ�ص�λ�ã��ǵü��ͷ�Ƿ�ı� */
void swap(route **ppNode, int posA, int posB) {
	route *node = *ppNode;
	int i;
	route *preAp = NULL;
	route *preBp = NULL;
	route *Ap = NULL;
	route *Bp = NULL;

	for (i = 0; i < sizeRouteList(node); i++) {
		if (i == posA) {
			Ap = node;
		}
		else if (i == posB) {
			Bp = node;
		}
		else if (i == posA - 1) {
			preAp = node;
		}
		else if (i == posB - 1) {
			preBp = node;
		}
		node = node->next; 
	}

	if (preBp != NULL && preAp != NULL) {
		//they are both not the first one
		route *tempP = preAp->next;
		preAp->next = preAp->next;
		preBp->next = tempP->next;
		tempP = Ap->next;
		Ap->next = Bp->next;
		Bp->next = tempP;
	} 
	else if (preAp == NULL) {//A is the first one
		route *tempP = Ap->next;
		Ap->next = Bp->next;
		Bp->next = tempP;
		preBp->next = Ap;
	}
	else {//preBp == NULL
		route *tempP = Ap->next;
		Ap->next = Bp->next;
		Bp->next = tempP;
		preAp->next = Bp;
	}

}