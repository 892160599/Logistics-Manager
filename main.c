#include <stdio.h>
#include <ListTool.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <wincon.h>
#include <windef.h>
#include "shlobj.h"
#include <wingdi.h>

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

//主函数，同时展示主界面
int main() {

	route* routeHeadP;
	routeHeadP = initData();//初始化数据入链表
	char *url = malloc(sizeof(char) * 20);//开辟空间待使用
    int space = 60;

	initConsole();

    //主函数里包含了第一层信息展示
	while (1) {
	    printFronPage();

		int input1 = 0;
		scanf("%d%*c", &input1);

		if (input1 == 1) {
			int isRoutePage = 1;
			while (isRoutePage) {
				printRoutePage(routeHeadP);//输出路线页的信息
				int input2 = 0; scanf("%d%*c", &input2);
				int seq = 0;

				if (input2 == 1) {
					printSomeSpace(space);printf("想详细查看第几条路线的站点信息：");
					seq = 0; scanf("%d%*c", &seq);
					route * routeSpecific = getRoutePointer(routeHeadP, seq - 1);
					if (routeSpecific != NULL){
					    printSitePage(getRoutePointer(routeHeadP, seq - 1), routeHeadP);//进入该函数内部
					} else {
                        printSomeSpace(space);printf("错误输入\n");
					}

				} else if (input2 == 2) {
					printSomeSpace(space);printf("想修改第几条路线：");
					seq = 0; scanf("%d%*c", &seq);
					changeRoute(getRoutePointer(routeHeadP, seq-1));
					updateRoutesFILE(routeHeadP);
					MessageBox(NULL, TEXT("成功修改路线"), TEXT("操作成功"), MB_OK);
					system("cls");
				} else if (input2 == 3) {
					printSomeSpace(space);printf("想删除第几条路线：");
					seq = 0; scanf("%d%*c", &seq);
					//删除对应的存档文件 TODO：深层筛选未重复站点删除
					strcpy(url, "save/");
					strcat(url, getRoutePointer(routeHeadP, seq - 1)->routeID);
					strcat(url, ".txt");
					remove(url);
					//再更新路线合集存档
					routeHeadP = DelRoutePos(routeHeadP, seq-1);
					updateRoutesFILE(routeHeadP);
					MessageBox(NULL, TEXT("成功删除路线"), TEXT("操作成功"), MB_OK);
					system("cls");
				} else if (input2 == 4) {
					addRoute(routeHeadP);
					updateRoutesFILE(routeHeadP);
					MessageBox(NULL, TEXT("成功增添路线\n建议继续进入该路线详细信息界面添加站点信息"), TEXT("操作成功"), MB_OK);
					system("cls");
				} else if (input2 == 5) {
                    //快速查询命令
                    quickQuery(routeHeadP);
					system("cls");
				} else if (input2 == 6){
                    makeCsv(routeHeadP);//生成统计报表
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
			printSomeSpace(space);printf("输入错误指令\n");
		}
	}
	free(url);

	return 0;
}

//快速查询实现逻辑
void quickQuery(route * routeHeadP){
    route * routeP = routeHeadP;
    system("cls");
    printSomeSpace(60);system("date /T");
	printSomeSpace(60);printf("-------------------快速查询----------------------\n");
	printSomeSpace(60);printf("|\t1.查询指定司机的载货卸货情况\t\t|\n");
	printSomeSpace(60);printf("|\t2.查询指定车辆的司机联系方式\t\t|\n");
	printSomeSpace(60);printf("|\t3.查询指定车辆的配送路线\t\t|\n");
	printSomeSpace(60);printf("|\t4.查询经停某站点的所有路线\t\t|\n");
	printSomeSpace(60);printf("|\t5.查询耗时最长的路线\t\t\t|\n");
	printSomeSpace(60);printf("|\t6.查询耗时最短的路线\t\t\t|\n");
	printSomeSpace(60);printf("|\t7.查询公里数最长的路线\t\t\t|\n");
	printSomeSpace(60);printf("|\t8.查询公里数最短的路线\t\t\t|\n");
	printSomeSpace(60);printf("-------------------------------------------------\n");
	int seq = 0;printSomeSpace(60);scanf("%d%*c",&seq);
	char input[21];
	float tempFloat = 0;
	int isSuccessful = 0;
	printf("\n");
	printSomeSpace(60);
	switch (seq){
	case 1:
	    printf("请输入司机姓名：");
	    noNfgets(input, 20, stdin);
	    l4:while (routeP != NULL){
            site* siteP = routeP->firstSite;
            while (siteP != NULL){
                car* carP = siteP->carHeadP;
                while (carP != NULL){
                    if(strcmp(input, carP->driverName) == 0){
                        printSomeSpace(60);
                        if (carP->good != NULL){
                            printf("司机 %s载货了容量为%.3f的%s，卸货了容量为%.3f的%s\n", input, carP->good->upVolume, carP->good->uploadType, carP->good->downVolume, carP->good->downloadType);
                        } else {
                            printf("该司机无货物信息\n");
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
        printf("请输入车辆牌照：");
        noNfgets(input, 20, stdin);
        l3:while (routeP != NULL){
            site* siteP = routeP->firstSite;
            while (siteP != NULL){
                car* carP = siteP->carHeadP;
                while (carP != NULL){
                    if (strcmp(carP->carID, input) == 0){
                        printSomeSpace(60);printf("车辆%s的司机%s的联系方式为%s\n", input, carP->driverName, carP->driverTel);
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
        printf("请输入车辆牌照：");
        noNfgets(input, 20, stdin);
        l2:while (routeP != NULL){
            site* siteP = routeP->firstSite;
            while (siteP != NULL){
                car* carP = siteP->carHeadP;
                while (carP != NULL){
                    if (strcmp(carP->carID, input) == 0){
                        printSomeSpace(60);printf("车辆%s的配送路线为%s\n", input, carP->routeID);
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
        printf("请输入站点编号：");
        noNfgets(input, 20, stdin);
        l1:while (routeP != NULL){
            site * siteP = routeP->firstSite;
            while (siteP != NULL){
                if (strcmp(siteP->siteID, input) == 0){
                    printSomeSpace(60);printf("经停站点%s的所有路线:%s\n", input, siteP->routeIDArray);
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
        printf("耗时最长的路线是%s，总耗时为%.3f\n", input, tempFloat);
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
        printf("耗时最短的路线是%s，总耗时为%.3f\n", input, tempFloat);
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
        printf("最长的路线是%s，总公里数为%.3f\n", input, tempFloat);
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
        printf("最短的路线是%s，总公里数为%.3f\n", input, tempFloat);
	    break;
	default:
	    break;
	}
    if (!isSuccessful){
        printSomeSpace(60);printf("找不到相关信息\n");
    }
    printSomeSpace(60);system("pause");
}

//初始化控制台，进行一些个性化设置
void initConsole(){
//    HWND hwnd=GetForegroundWindow();
    system("mode con:cols=175 lines=30");
    system("color 3B");
    SetConsoleTitle("物流信息管理系统");
}

/*初始化数据，读取存档*/
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
			routeP->firstSite = siteHeadP;//将站点链表的头结点指针传递给对应的路线

			//set infomation about those cars in this site
			for (j = 0; j < sizeSiteList(siteHeadP); j++) {
				site * siteP = getSitePointer(siteHeadP, j);
				strcpy(url, "save/");
				strcat(url, siteP->siteID);
				strcat(url, ".txt");
				FILE * fCar = fopen(url, "r+");
				if (fCar == NULL) {
					siteP->carHeadP = NULL;
					continue;//连车的存档都没有，更别说货物了
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

//输出首页
void printFronPage() {
	printSomeSpace(60);
    system("date /T");printSomeSpace(60);
	printf("----------------------------------------------------\n");printSomeSpace(60);
	printf("|欢迎来到物流信息管理系统，按对应数字进入功能\t|\n");printSomeSpace(60);
	printf("|\t1.进入系统\t\t\t\t\t|\n");printSomeSpace(60);
	printf("|\t2.制作者信息\t\t\t\t\t|\n");printSomeSpace(60);
	printf("----------------------------------------------------\n");printSomeSpace(60);

}

//查看制作者信息逻辑
void printPowerBy() {
	MessageBox(NULL, TEXT("华中科技大学\nIOT1601 徐光磊\nC语言程序设计_课程设计作品\n物流信息查询系统"), TEXT("制作者信息"), MB_OK);
	system("cls");
}

//输出路线信息
void printRoutePage(route * routeHeadP) {
	route * routeP = routeHeadP;
	system("cls");
	system("date /T");

	printSomeG(75);printf("所有路线信息");printSomeG(76);printf("\n");//title

	char first[] = "编号";
	char second[] = "名称";
	char third[] = "站点数";
	char fourth[] = "公里数";
	char fifth[] = "耗时";
	char sixth[] = "起始站点";
	char seventh[] = "终止站点";
	char eighth[] = "负责人";
	char ninth[] = "固定电话";
	char tenth[] = "移动电话";
	char eleventh[] = "电子邮箱";
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
	printf("|\t1.查看路线具体信息\t\t\t|\n");printSomeSpace(space);
	printf("|\t2.进行修改\t\t\t\t|\n");printSomeSpace(space);
	printf("|\t3.进行删除\t\t\t\t|\n");printSomeSpace(space);
	printf("|\t4.进行增添\t\t\t\t|\n");printSomeSpace(space);
	printf("|\t5.快速查询\t\t\t\t|\n");printSomeSpace(space);
	printf("|\t6.生成统计报表\t\t\t\t|\n");printSomeSpace(space);
	printf("|\t7.返回上级菜单\t\t\t\t|\n");printSomeSpace(space);
	printf("--------------按数字选择功能-----------------\n");printSomeSpace(space);
}

//rewrite file from list
void updateRoutesFILE(route* routeHeadP) {
	route * routeP = routeHeadP;
	FILE *fRouteP = fopen("save/routes.txt", "w+");//从头改写文本
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
	FILE *fSiteP = fopen(url, "w+");//从头改写文本
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
	FILE *fCarP = fopen(url, "w+");//从头改写文本
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
		printf("---------------请输入新路线的信息----------------\n");
		printSomeSpace(60);printf("请输入编号:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->routeID, inputTemp);
		printSomeSpace(60);printf("请输入名称:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->name, inputTemp);

        newRouteP->firstSite = NULL;//因为是新的路线，故将指向的站点内容指针置空

		newRouteP->siteNums = 0;//auto complete siteConut. default -> 0;

		newRouteP->miles = 0;
		newRouteP->period = 0;

		printSomeSpace(60);printf("请输入起始站点编号:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->startSite, inputTemp);
		printSomeSpace(60);printf("请输入终止站点编号:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->endSite, inputTemp);
		printSomeSpace(60);printf("请输入负责人姓名:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->adminName, inputTemp);
		printSomeSpace(60);printf("请输入负责人办公室电话:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->tel, inputTemp);
		printSomeSpace(60);printf("请输入负责人移动电话:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->mTel, inputTemp);
		printSomeSpace(60);printf("请输入负责人电子邮箱:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->email, inputTemp);
	} else {
		system("cls");
		printf("addRoute error\n");
	}
}
site* addSite(site * siteHeadP, char* routeIDIN, route * routeHeadP){
    printf("---------------请输入新站点的信息----------------\n");
	printSomeSpace(60);printf("请输入新站点在路线中的序号:");//新站点的位置
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
		printSomeSpace(60);printf("请输入站点编号:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newSiteP->siteID, inputTemp);

        //检测是否站点重复
        route * routeP = routeHeadP;
        while(routeP != NULL){
            site * siteP = routeP->firstSite;
            while(siteP != NULL){
                if(!strcmp(siteP->siteID, newSiteP->siteID)){//一样
                    newSiteP->carHeadP = siteP->carHeadP;
                }
                siteP = siteP->next;
            }
            routeP = routeP->next;
        }

		printSomeSpace(60);printf("请输入站点名称:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newSiteP->siteName, inputTemp);

		printSomeSpace(60);printf("请输入与上一个站点交通耗时:");
		float fPeriod = 0;
		scanf("%f%*c", &fPeriod);
		newSiteP->time2Last = fPeriod;

		printSomeSpace(60);printf("请输入停留耗时:");
		float waitTimeN = 0;
		scanf("%f%*c", &waitTimeN);
		newSiteP->waitTime = waitTimeN;

		printSomeSpace(60);printf("请输入经过本站点固定路线编号:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newSiteP->routeIDArray, inputTemp);

        //总距离
        if (seq == 1){
            newSiteP->d2Start = 0;
            newSiteP->d2Last = 0;
        } else {
            printSomeSpace(60);printf("请输入与上一个站点距离:");
            float d2L = 0;
            scanf("%f%*c", &d2L);
            newSiteP->d2Last = d2L;
            site * siteTempP = siteHeadP;
            while(siteTempP->next != newSiteP){
                siteTempP = siteTempP->next;
            }
            newSiteP->d2Start = siteTempP->d2Start + d2L;
        }
        //自动更新其他站点的离起始站点距离
        updateAlld2S(newSiteP);


        //自动补全序号
        newSiteP->siteSID = seq;
		strcpy(newSiteP->routeID, routeIDIN);
        if (flag == 1){//the first one in new save file
            newSiteP->next = NULL;
            return newSiteP;
        } else {
            //自动更新被挤到后面的SID
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
    printf("---------------请输入新路线的信息----------------\n");
    printSomeSpace(60);printf("请输入车辆牌照:");
    noNfgets(inputTemp, 50, stdin);
    strcpy(newCarP->carID, inputTemp);
    printSomeSpace(60);printf("请输入执行配送路线编号:");
    noNfgets(inputTemp, 50, stdin);
    strcpy(newCarP->routeID, inputTemp);
    printSomeSpace(60);printf("请输入司机姓名:");
    noNfgets(inputTemp, 50, stdin);
    strcpy(newCarP->driverName, inputTemp);
    printSomeSpace(60);printf("请输入司机移动电话:");
    noNfgets(inputTemp, 50, stdin);
    strcpy(newCarP->driverTel, inputTemp);

    printSomeSpace(60);printf("请输入载货货物种类:");
    noNfgets(inputTemp, 50, stdin);
    strcpy(newCarP->good->uploadType, inputTemp);
    printSomeSpace(60);printf("请输入载货货物容量:");
    float upV = 0; scanf("%f%*c", &upV);
    newCarP->good->upVolume = upV;
    printSomeSpace(60);printf("请输入卸货货物种类:");
    noNfgets(inputTemp, 50, stdin);
    strcpy(newCarP->good->downloadType, inputTemp);
    printSomeSpace(60);printf("请输入卸货货物容量:");
    float downV = 0; scanf("%f%*c", &downV);
    newCarP->good->downVolume = downV;
    if (flag == 0){
        return carHeadP;
    } else {//flag == 1
        newCarP->next = NULL;
        return newCarP;
    }
}

//不读取换行符的fgets，升级版
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
//修改信息逻辑
int changeRoute(route * routeSpecific) {
    printSomeSpace(60);
	printf("-------------------------------------------------\n");
	char temp[] = " ";
	printf("%60s1.编号\n%60s2.名称\n%60s3.总公里数\n%60s4.起始站点编号\n%60s5.终止站点编号\n%60s6.负责人姓名\n%60s7.负责人办公室电话\n%60s8.负责人移动电话\n%60s8.负责人电子邮箱\n\n%60s请选择你要修改的属性:",temp,temp,temp,temp,temp,temp,temp,temp,temp,temp,temp);
	int choose = 0;
	scanf("%d%*c", &choose);
	char input[51];//no free
	switch (choose) {
	case 1:
		printSomeSpace(60);printf("请输入新的编号:");
		char * oldID = (char *)malloc(sizeof(char) * 30);
		strcpy(oldID, routeSpecific->routeID);
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->routeID, input);
		//改变其编号对应的存档文件名
		changeSaveName(oldID, routeSpecific->routeID);
		changeOldRouteID(routeSpecific);
		free(oldID);
		break;
	case 2:
		printSomeSpace(60);printf("请输入新的名称:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->name, input);
		break;
	case 3:
		printSomeSpace(60);printf("请输入新的总公里数:");
		float newMiles = 0;
		scanf("%f%*c", &newMiles);
		routeSpecific->miles = newMiles;
		break;
    routeSpecific->period = 0;
	case 4:
		printSomeSpace(60);printf("请输入新的起始站点编号:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->startSite, input);
		break;
	case 5:
		printSomeSpace(60);printf("请输入新的终止站点编号:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->endSite, input);
		break;
	case 6:
		printSomeSpace(60);printf("请输入新的负责人姓名:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->adminName, input);
		break;
	case 7:
		printSomeSpace(60);printf("请输入新的负责人办公室电话:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->tel, input);
		break;
	case 8:
		printSomeSpace(60);printf("请输入新的负责人移动电话:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->mTel, input);
		break;
	case 9:
		printSomeSpace(60);printf("请输入新的负责人电子邮箱:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->email, input);
		break;
	default:
		printf("输入有误\n");
		return 0;
	}
	return 1;
}
int changeSite(site * siteSpecific, int notFirst, site * siteHeadP) {
    printSomeSpace(60);
	printf("----------------------------------------------\n");
	char space[] = " ";
	if (notFirst){
        printf("%60s1.站点编号\n%60s2.站点名称\n%60s3.经过本站点的固定路线编号\n%60s4.停留耗时\n%60s5.与上一站交通耗时\n%60s6.与上一个站点距离\n\n%60s请选择你要修改的属性:",space,space,space,space,space,space,space);
	} else {
	    printf("%60s1.站点编号\n%60s2.站点名称\n%60s3.经过本站点的固定路线编号\n%60s4.停留耗时\n%60s5.与上一站交通耗时\n\n%60s请选择你要修改的属性:",space,space,space,space,space,space);
	}
	int choose = 0;
	scanf("%d%*c", &choose);
	char input[50];//auto free
	printSomeSpace(60);
	switch (choose) {
	case 1:
		printf("请输入新的站点编号:");
		char * oldID = (char *)malloc(sizeof(char) * 30);
		strcpy(oldID, siteSpecific->siteID);
		noNfgets(input, 50, stdin);
		strcpy(siteSpecific->siteID, input);//向链表内部更新新的编号
		changeSaveName(oldID, siteSpecific->siteID);//改变其编号对应的存档文件名（联动改变下文
		free(oldID);
        return 1;
	case 2:
		printf("请输入新的站点名称:");
		noNfgets(input, 50, stdin);
		strcpy(siteSpecific->siteName, input);
		return 2;
	case 3:
		printf("请输入新的经过本站点的固定路线编号:");
		noNfgets(input, 50, stdin);
		strcpy(siteSpecific->routeIDArray, input);
		return 3;
	case 4:
		printf("请输入新的停留耗时:");
		float newPeriod = 0;
		scanf("%f%*c", &newPeriod);
		siteSpecific->waitTime = newPeriod;
		return 4;
    case 5:
		printf("请输入新的与上一站耗时:");
		newPeriod = 0;
		scanf("%f%*c", &newPeriod);
		siteSpecific->time2Last = newPeriod;
		return 5;
	case 6:
	    if (!notFirst){
	        printSomeSpace(60);printf("输入有误!\n");
            return 0;
	    }
		printf("请输入新的与上一个站点距离:");
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
		printSomeSpace(60);printf("输入有误!\n");
		return 0;
	}
}
int changeCar(car * carSpecific) {
	printSomeSpace(60);printf("-------------------------------------------------\n");
	char space[] = " ";
	printf("%60s1.车辆牌照\n%60s2.司机姓名\n%60s3.司机移动电话\n%60s4.载货货物种类\n%60s5.载货货物容量\n%60s6.卸货货物种类\n%60s7.卸货货物容量\n\n%60s请选择你要修改的属性:",space,space,space,space,space,space,space,space);
	int choose = 0;
	scanf("%d%*c", &choose);
	char input[50];//auto free
	printSomeSpace(60);
	switch (choose) {
	case 1:
		printf("请输入新的车辆牌照:");
		char * oldID = (char *)malloc(sizeof(char) * 30);
		strcpy(oldID, carSpecific->carID);
		noNfgets(input, 50, stdin);
		strcpy(carSpecific->carID, input);//向链表内部更新新的编号
		changeSaveName(oldID, carSpecific->carID);//改变其编号对应的存档文件名（联动改变下文
		free(oldID);
		break;
	case 2:
		printf("请输入新的司机姓名:");
		noNfgets(input, 50, stdin);
		strcpy(carSpecific->driverName, input);
		break;
	case 3:
		printf("请输入新的司机移动电话:");
		noNfgets(input, 50, stdin);
		strcpy(carSpecific->driverTel, input);
		break;
	case 4:
		printf("请输入新的载货货物种类:");
		noNfgets(input, 50, stdin);
		strcpy(carSpecific->good->uploadType, input);
		break;
	case 5:
		printf("请输入新的载货货物容量:");
		float newUpV = 0;
		scanf("%f%*c", &newUpV);
		carSpecific->good->upVolume = newUpV;
		break;
	case 6:
		printf("请输入新的卸货货物种类:");
		noNfgets(input, 50, stdin);
		strcpy(carSpecific->good->downloadType, input);
		break;
	case 7:
		printf("请输入新的卸货货物容量:");
		float newDownV = 0;
		scanf("%f%*c", &newDownV);
		carSpecific->good->downVolume = newDownV;
		break;
	default:
		printf("输入有误!\n");
		return 0;
	}
	return 1;
}

//输出站点信息逻辑
void printSitePage(route *routeP, route * routeHeadP) {
	int inSitePage = 1;
	site* siteHeadP = routeP->firstSite;
	while (inSitePage) {
		system("cls");
		site* siteP = siteHeadP;
		system("date /T");
		printSomeG(71);printf("路线编号：%6s 的所有站点信息", routeP->routeID);printSomeG(71);printf("\n");//title

		char second[] = "序号";
		char third[] = "站点编号";
		char fourth[] = "站点名称";
		char fifth[] = "与起始站距离";
		char sixth[] = "与上一个站距离";
		char seventh[] = "与上一站交通耗时";
		char eighth[] = "停留耗时";
		char ninth[] = "经过本站点的路线编号";
		printf("|%-4s %-10s %-50s %-12s %-14s %-16s %-8s %-50s|\n", second, third, fourth, fifth, sixth, seventh, eighth, ninth);
        printf("|");printSomeSpace(171);printf("|\n");
		while (siteP != NULL) {
			printf("|%-4d %-10s %-50s %-12.3f %-14.3f %-16.3f %-8.3f %-50s|\n", siteP->siteSID, siteP->siteID, siteP->siteName, siteP->d2Start, siteP->d2Last, siteP->time2Last, siteP->waitTime, siteP->routeIDArray);
			siteP = siteP->next;
		}

		printSomeG(173);printf("\n");
		printSomeSpace(60);printf("|\t1.查看站点具体信息\t\t\t|\n");
		printSomeSpace(60);printf("|\t2.进行修改\t\t\t\t|\n");
		printSomeSpace(60);printf("|\t3.进行删除\t\t\t\t|\n");
		printSomeSpace(60);printf("|\t4.进行增添\t\t\t\t|\n");
		printSomeSpace(60);printf("|\t5.返回上级菜单\t\t\t\t|\n");
		printSomeSpace(60);printf("--------------按数字选择功能-----------------\n");

		int seq = 0;
		printSomeSpace(60);scanf("%d%*c", &seq);

        printSomeSpace(60);
		switch (seq) {
		case 1:
			printf("想查看第几个站点的详细车辆信息：");
			scanf("%d%*c", &seq);
			printCarPage(getSitePointer(siteHeadP, seq - 1));//进去该函数
			break;
		case 2:
			printf("想修改第几个站点的信息:");
			scanf("%d%*c", &seq);
			int changeWhich = changeSite(getSitePointer(siteHeadP, seq - 1), seq-1, siteHeadP);
			updateSitesFILE(siteHeadP);

			MessageBox(NULL, TEXT("成功修改站点信息"), TEXT("操作成功"), MB_OK);
            if (changeWhich == 6){//更改了距离，应更改路线内的总里程和所有被修改站点以后（包括自身）的与起始站点的距离
                routeP->miles = totalMile(routeP);
            } else if (changeWhich == 4 || changeWhich == 5){//更改了时间相关
                routeP->period = totalTime(routeP);
            } else {
                break;
            }
			updateRoutesFILE(routeHeadP);//update save file

			break;
		case 3:
			printf("想删除第几个站点的信息:");
			scanf("%d%*c", &seq);
			siteHeadP = DelSitePos(siteHeadP, seq - 1);//get the new site head pointer
			routeP->firstSite = siteHeadP;
			//自动改变上文
			if (seq == 1) {//删除了第一个
				strcpy(routeP->startSite, siteHeadP->siteID);//更新上一级存储的第一站点名称数据
			} else if (seq == (sizeSiteList(siteHeadP)-2)) {//删除了最后一个
				strcpy(routeP->endSite, getSitePointer(siteHeadP, sizeSiteList(siteHeadP) - 1)->siteID);//更新上一级存储的终点站点名称数据
			}
			//自动更新序号
			site * stepSite = getSitePointer(siteHeadP, seq - 1);
			while (stepSite != NULL) {
				stepSite->siteSID = stepSite->siteSID - 1;
				stepSite = stepSite->next;
			}
			updateSitesFILE(siteHeadP);

			//更新路线站点数信息至链表与存档
			updateSitesCount(routeP);
            routeP->period = totalTime(routeP);

            //更新路线距离
            routeP->miles = totalMile(routeP);

            //更新D2S
            updateAlld2S(siteHeadP);

            updateRoutesFILE(routeHeadP);//update save file
			//TODO: 不方便删除站点数据，应筛选是否有被其他路线占用
			MessageBox(NULL, TEXT("成功删除站点"), TEXT("操作成功"), MB_OK);

			break;
		case 4:
			//增添逻辑
			siteHeadP = addSite(siteHeadP, routeP->routeID, routeHeadP);
			routeP->firstSite = siteHeadP;
			updateSitesFILE(siteHeadP);

			//更新路线站点数信息至链表与存档
			updateSitesCount(routeP);
            routeP->period = totalTime(routeP);

            //更新路线距离
            routeP->miles = totalMile(routeP);
            //更新上级路线的起始站点末尾站点信息
            site * siteTempP = siteHeadP;
            strcpy(routeP->startSite, siteHeadP->siteID);
            while(siteTempP->next != NULL){
                siteTempP = siteTempP->next;
            }
            strcpy(routeP->endSite, siteTempP->routeID);

            updateRoutesFILE(routeHeadP);
			MessageBox(NULL, TEXT("成功增添站点"), TEXT("操作成功"), MB_OK);

			break;
		case 5:
			inSitePage = 0;
			break;
		default:
			printf("输入错误！");//输入的数字选项错误
			break;
		}
		system("cls");
	}
}

//输出车辆信息
void printCarPage(site * siteP) {
	car * carHeadP = siteP->carHeadP;
	int inCarPage = 1;
	while (inCarPage) {
		system("cls");
		car * carP = carHeadP;
		system("date /T");
		printSomeG(65);printf("站点编号：%6s 的所有车辆信息", siteP->siteID);printSomeG(50);printf("\n");
		char first[] = "车辆牌照";
		char second[] = "执行路线编号";
		char third[] = "司机姓名";
		char fourth[] = "司机移动电话";
		char fifth[] = "载货种类";
		char sixth[] = "载货容量";
		char seventh[] = "卸货种类";
		char eighth[] = "卸货容量";
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
		printSomeSpace(60);printf("|\t1.进行修改\t\t\t\t|\n");
		printSomeSpace(60);printf("|\t2.进行删除\t\t\t\t|\n");
		printSomeSpace(60);printf("|\t3.进行增添\t\t\t\t|\n");
		printSomeSpace(60);printf("|\t4.返回上级菜单\t\t\t\t|\n");
		printSomeSpace(60);printf("--------------按数字选择功能-----------------\n");
		printSomeSpace(60);
		int seq = 0; scanf("%d%*c", &seq);
		printSomeSpace(60);
		switch (seq) {
		case 1:
			printf("想修改第几台车辆的信息:");
			scanf("%d%*c", &seq);
			changeCar(getCarPointer(carHeadP, seq - 1));
			updateCarsFILE(carHeadP, siteP->siteID);
			MessageBox(NULL, TEXT("成功修改车辆信息"), TEXT("操作成功"), MB_OK);
			break;
		case 2:
			printf("想删除第几台车辆的信息:");
			scanf("%d%*c", &seq);
			//删除对应的存档文件
			char *url = (char *)malloc(sizeof(char) * 20);
			strcpy(url, "save/");
			car * carDel = getCarPointer(carHeadP, seq - 1);
			if (carDel != NULL){
                strcat(url, getCarPointer(carHeadP, seq - 1)->carID);
                strcat(url, ".txt");
                remove(url);
			} else {
                printf("输入指令错误\n");
			}

			free(url);

			carHeadP = DelCarPos(carHeadP, seq - 1);
			updateCarsFILE(carHeadP, siteP->siteID);
			MessageBox(NULL, TEXT("成功删除车辆"), TEXT("操作成功"), MB_OK);
			break;
		case 3:
			carHeadP = addCar(carHeadP);
			siteP->carHeadP = carHeadP;
			updateCarsFILE(carHeadP, siteP->siteID);
			MessageBox(NULL, TEXT("成功增添车辆"), TEXT("操作成功"), MB_OK);
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

//用来改变存储某路线所有站点的存档中的routeID
void changeOldRouteID(route * routeSpecific) {
    site * siteP = routeSpecific->firstSite;
	while (siteP != NULL) {
		strcpy(siteP->routeID, routeSpecific->routeID);
		siteP = siteP->next;
	}
	updateSitesFILE(routeSpecific->firstSite);
}

//自动站点数更新（根据二级指针的的返回值，为一级的成员数据“站点数”进行赋值）
void updateSitesCount(route * routeSpecific){
    int count = 0;
    site * siteHeadP = routeSpecific->firstSite;
    count = sizeSiteList(siteHeadP);
    routeSpecific->siteNums = count;
}
//生成统计报表
void makeCsv(route * routeHeadP){
    system("cls");
    FILE * saveF = fopen("物流信息统计报表.csv","w");
    fprintf(saveF, "所有路线信息：\n");
    fprintf(saveF, "·,编号,名称,总站点数,总公里数,总耗时,起始站点编号,终止站点编号,负责人姓名,负责人办公室电话,负责人移动电话,负责人电子邮箱\n");

    route * routeP = routeHeadP;
    while (routeP != NULL){
        fprintf(saveF,"·,%s,%s,%d,%f,%f,%s,%s,%s,%s,%s,%s\n",routeP->routeID, routeP->name, routeP->siteNums, routeP->miles, routeP->period, routeP->startSite, routeP->endSite, routeP->adminName, routeP->tel, routeP->mTel, routeP->email);
        routeP = routeP->next;
    }

    fprintf(saveF, "\n\n所有站点信息：\n");
    routeP = routeHeadP;
    while (routeP != NULL){
        site * siteP = routeP->firstSite;
        fprintf(saveF, "\n·,路线%s 的站点信息：\n", routeP->routeID);
        fprintf(saveF, "·,固定配送路线编号,序号,编号,名称,与起始站点距离,与上一个站点距离,与上一个站点交通耗时,停留耗时,经过本站点固定路线编号\n");
        while (siteP != NULL){
            fprintf(saveF, "·,%s,%d,%s,%s,%f,%f,%f,%f,%s\n",siteP->routeID,siteP->siteSID, siteP->siteID, siteP->siteName, siteP->d2Start, siteP->d2Last, siteP->time2Last, siteP->waitTime, siteP->routeIDArray);
            siteP = siteP->next;
        }
        routeP = routeP->next;
    }

    fprintf(saveF, "\n\n所有车辆信息：\n");
    routeP = routeHeadP;
    while (routeP != NULL){
        site * siteP = routeP->firstSite;
        while (siteP != NULL){
            car * carP = siteP->carHeadP;
            fprintf(saveF, "\n·,站点%s 的车辆信息：\n", siteP->siteID);
            fprintf(saveF, "·,车辆牌照,执行配送路线编号,司机姓名,司机移动电话,载货种类,载货容量,卸货种类,卸货容量\n");
            while (carP != NULL){
                fprintf(saveF, "·,%s,%s,%s,%s", carP->carID, carP->routeID, carP->driverName, carP->driverTel);
                good * goodP = carP->good;
                if (goodP != NULL){
                    fprintf(saveF, "·,%s,%f,%s,%f", goodP->uploadType, goodP->upVolume, goodP->downloadType, goodP->downVolume);
                }
                fprintf(saveF, "\n");
                carP = carP->next;
            }
            siteP = siteP->next;
        }
        routeP = routeP->next;
    }

    fprintf(saveF, "\n\n统计信息：\n\n");

    fprintf(saveF, "·,路线总数：,%d\n",sizeRouteList(routeHeadP));

    int sitesCount = 0;routeP = routeHeadP;
    while(routeP != NULL){
        sitesCount = sitesCount + sizeSiteList(routeP->firstSite);
        routeP = routeP->next;
    }
    fprintf(saveF, "·,站点总数：,%d\n", sitesCount);

    int carsCount = 0;routeP = routeHeadP;
    while (routeP != NULL){
        site * siteP = routeP->firstSite;
        while (siteP != NULL){
            carsCount = carsCount + sizeCarList(siteP->carHeadP);
            siteP = siteP->next;
        }
        routeP = routeP->next;
    }
    fprintf(saveF, "·,车辆总数：,%d\n\n", carsCount);

    //计算里程逻辑
    float mileSum = 0;routeP = routeHeadP;
    while (routeP != NULL){
        mileSum = mileSum + routeP->miles;
        routeP = routeP->next;
    }
    fprintf(saveF, "·,路线总里程：,%.4f\n", mileSum);
    fprintf(saveF, "·,路线平均里程：,%.4f\n", mileSum/sizeRouteList(routeHeadP));

    char StringTemp[50];
    float tempFloat = -1;
    routeP = routeHeadP;//比较之前的初始化
    while (routeP != NULL){
        if (routeP->period > tempFloat){
            tempFloat = routeP->miles;
            strcpy(StringTemp, routeP->routeID);
        }
        routeP = routeP->next;
    }
    fprintf(saveF, "·,最长里程数：,%.4f,路线%s\n", tempFloat, StringTemp);

    tempFloat = 99999;routeP = routeHeadP;
    while (routeP != NULL){
        if (routeP->period < tempFloat){
            tempFloat = routeP->miles;
            strcpy(StringTemp, routeP->routeID);
        }
        routeP = routeP->next;
    }
    fprintf(saveF, "·,最短里程数：,%.4f,路线%s\n\n", tempFloat, StringTemp);

    //计算耗时逻辑
    tempFloat = -1;routeP = routeHeadP;
    while (routeP != NULL){
        float timeThis = totalTime(routeP);
        if (timeThis > tempFloat){
            tempFloat = timeThis;
            strcpy(StringTemp, routeP->routeID);
        }
        routeP = routeP->next;
    }
    fprintf(saveF, "·,最长耗时：,%.4f,路线%s\n", tempFloat, StringTemp);

    tempFloat = 99999;routeP = routeHeadP;
    while (routeP != NULL){
        float timeThis = totalTime(routeP);
        if (timeThis < tempFloat){
            tempFloat = timeThis;
            strcpy(StringTemp, routeP->routeID);
        }
        routeP = routeP->next;
    }
    fprintf(saveF, "·,最短耗时：,%.4f,路线%s\n", tempFloat, StringTemp);

    tempFloat = 0;routeP = routeHeadP;
    while (routeP != NULL){
        tempFloat = tempFloat + totalTime(routeP);
        routeP = routeP->next;
    }
    fprintf(saveF, "·,平均耗时：,%.4f\n\n", tempFloat/sizeRouteList(routeHeadP));


    //统计载货量逻辑
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
                    //更新最大最小载货量数据
                    if (carryVolume > maxCarry){
                        maxCarry = carryVolume;
                        strcpy(maxCarID, carP->carID);
                    } else if (carryVolume < minCarry){
                        minCarry = carryVolume;
                        strcpy(minCarID, carP->carID);
                    }
                    //更新最高最低效率数据
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
    fprintf(saveF, "·,总载货量：,%.4f\n", tempFloat);
    fprintf(saveF, "·,平均载货量：,%.4f\n", tempFloat/carsCount);
    fprintf(saveF, "·,最大载货量：,%.4f,%s\n", maxCarry, maxCarID);
    fprintf(saveF, "·,最小载货量：,%.4f,%s\n\n", minCarry, minCarID);

    //计算配送效率逻辑
    fprintf(saveF, "·,平均配送效率：,%.4f\n", tempFloat/mileSum);
    fprintf(saveF, "·,最高配送效率：,%.4f,%s\n", maxEfficiency, maxCarID2);
    fprintf(saveF, "·,最低配送效率：,%.4f,%s\n", minEfficiency, minCarID2);
    fprintf(saveF, "·,PS:配送效率指载货量与配送时间之比\n");

    fclose(saveF);
    MessageBox(NULL, TEXT("报表已经保存在程序的根目录。"), TEXT("操作成功"), MB_OK);
}

//从传入的参数对应的路线中，进入站点数据中去计算准确的耗时数据
float totalTime(route *routeP){
    site * siteP = routeP->firstSite;
    float time = 0;
    while (siteP != NULL){
        time = siteP->d2Last + siteP->waitTime + time;
        siteP = siteP->next;
    }
    return time;
}
//从传入的参数对应的路线中，进入站点数据中去获得总长度
float totalMile(route *routeP){
    site * siteTempP = routeP->firstSite;
    while (siteTempP->next != NULL){
        siteTempP = siteTempP->next;
    }
    return siteTempP->d2Start;
}

//从传入的路线链表中寻找对应字符串参数的数据的里程
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
//批量输出空格
void printSomeSpace(int num){
    int i = 0;
    for (i = 0; i < num; i++){
        printf(" ");
    }
}
//批量输出Gang 杠号
void printSomeG(int num){
    int i = 0;
    for (i = 0; i < num; i++){
        printf("-");
    }
}


/**
* 更新路线的d2S
* 传入的站点指针为数据正确的最后一个路线，往后的所有路线都需要进行更新
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
