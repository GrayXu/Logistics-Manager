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
	routeHeadP = initData();//初始化数据入链表
	//int isFrontPage = 1;
	while (1) {
	    printFronPage();

		int input1 = 0; 
		scanf("%d", &input1);//获得用户的输入值

		if (input1 == 1) {
			int isRoutePage = 1;
			while (isRoutePage) {
				printRoutePage(routeHeadP);//输出路线页的信息
				int input2 = 0; scanf("%d", &input2);//获得用户的输入值
				int seq = 0;

				if (input2 == 1) {
					printf("想详细查看第几条路线：");
					seq = 0; scanf("%d", &seq);//获得用户的输入值
					//TODO:详细界面
					system("cls");
				} else if (input2 == 2) {
					printf("想修改第几条路线：");
					seq = 0; scanf("%d", &seq);//获得用户的输入值
					//TODO:修改逻辑
					MessageBox(NULL, TEXT("成功修改路线"), TEXT("操作成功"), MB_OK);
					system("cls");
				} else if (input2 == 3) {
					printf("想删除第几条路线：");
					seq = 0; scanf("%d", &seq);//获得用户的输入值
					routeHeadP = DelRoutePos(routeHeadP, seq);
					updateRoutesFILE(routeHeadP);
					MessageBox(NULL, TEXT("成功删除路线"), TEXT("操作成功"), MB_OK);
					system("cls");
					//TODO:更新删除的IO操作
				} else if (input2 == 4) {
					//增添路线逻辑
					MessageBox(NULL, TEXT("成功增添路线"), TEXT("操作成功"), MB_OK);
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
			printf("输入错误数字");
		}
	}
	
	
	return 0;
}


/*初始化数据*/
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
	printf("|欢迎来到物流信息管理系统，按对应数字进入功能\t|\n");
	printf("|\t1.进入系统\t\t\t\t|\n");
	printf("|\t2.制作者信息\t\t\t\t|\n");
	printf("-------------------------------------------------\n");
}

void printPowerBy() {
	system("cls");
	/*printf("------------------制作者信息：-------------------\n");
	printf("|\t 华中科技大学\t\t\t\t|\n");
	printf("|\t IOT1601 徐光磊\t\t\t\t|\n");
	printf("|\t C语言程序设计_课程设计作品\t\t|\n");
	printf("|\t 物流信息查询系统\t\t\t|\n");
	printf("-------------------------------------------------\n");*/
	MessageBox(NULL, TEXT("华中科技大学\nIOT1601 徐光磊\nC语言程序设计_课程设计作品\n物流信息查询系统"), TEXT("制作者信息"), MB_OK);
}

void printRoutePage(route * routeHeadP) {
	route * routeP = routeHeadP;
	system("cls");
	printf("-------------------已进入系统--------------------\n");
	printf("| 所有路线信息如下：\n\n");
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
	printf("|\t1.查看该路线具体信息\t\t\t|\n");
	printf("|\t2.进行修改\t\t\t\t|\n");
	printf("|\t3.进行删除\t\t\t\t|\n");
	printf("|\t4.进行增添\t\t\t\t|\n");
	printf("|\t5.返回上级菜单\t\t\t\t|\n");
	printf("-------------------------------------------------\n");
}

//void addRouteNode() {
//
//}

void updateRoutesFILE(route* routeHeadP) {
	route * routeP = routeHeadP;
	FILE *fRouteP = fopen("save/routes.txt", "w");//从头改写文本
	while (routeP != NULL) {
		fprintf("%s;%s;%d;%f;%f;%s;%s;%s;%s;%s;%s\n",routeP->routeID, routeP->name, routeP->routeID, routeP->name, routeP->siteNums, routeP->miles, routeP->period, routeP->startSite, routeP->endSite, routeP->adminName, routeP->tel, routeP->mTel, routeP->email);
		routeP = routeP->next;
	}
}
