#include <stdio.h>
#include <ListTool.h>
#include <stdlib.h>
#include <conio.h>

route * initData();
void printFronPage();

int main() {
	route* routeHeadP = initData();//初始化数据入链表
	while (1) {
		printFronPage();
		char in = getchar();//获得用户的输入值
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


/*初始化数据*/
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
	printf("|欢迎进入物流信息管理系统，按对应数字进入功能\t|\n");
	printf("|\t1.进入系统\t\t\t\t|\n");
	printf("|\t2.制作者信息\t\t\t\t|\n");
	printf("-------------------------------------------------\n");
}

void printPowerBy() {
	system("cls");
	printf("-------------------------------------------------\n");
	printf("|制作者信息：\t|\n");
	printf("|\t 华中科技大学\t\t\t\t|\n");
	printf("|\t IOT1601 徐光磊\t\t\t\t|\n");
	printf("|\t C语言程序设计_课程设计作品\t\t\t\t|\n");
	printf("|\t 物流信息查询系统\t\t\t\t|\n");
	printf("-------------------------------------------------\n");
	system("pause");
}
