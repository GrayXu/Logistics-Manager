#include <stdio.h>
#include <ListTool.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

route * initData();
void printFronPage();
void printPowerBy();
void printRoutePage(route * routeHeadP);
void updateRoutesFILE(route* routeHeadP);
void addRoute(route * routeHeadP);
char* noNfgets(char * Buffer, int MaxConut, FILE* Stream);
int changeRoute(route * routeSpecial);
void printSitePage(route *routeP);
int changeSaveName(char* old, char* new);
int changeSite(site * siteSpecific);
void changeOldRouteID(route * routeSpecific);
void printCarPage(site * siteP);

int main() {
	route* routeHeadP;
	routeHeadP = initData();//初始化数据入链表
	char *url = malloc(sizeof(char) * 20);//开辟空间待使用
	//int isFrontPage = 1;
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
					printf("想详细查看第几条路线：");
					seq = 0; scanf("%d%*c", &seq);
					printSitePage(getRoutePointer(routeHeadP, seq - 1));//进入该函数内部

				} else if (input2 == 2) {
					printf("想修改第几条路线：");
					seq = 0; scanf("%d%*c", &seq);
					changeRoute(getRoutePointer(routeHeadP, seq-1));
					updateRoutesFILE(routeHeadP);
					MessageBox(NULL, TEXT("成功修改路线"), TEXT("操作成功"), MB_OK);
					system("cls");
				} else if (input2 == 3) {
					printf("想删除第几条路线：");
					seq = 0; scanf("%d%*c", &seq);
					routeHeadP = DelRoutePos(routeHeadP, seq-1);
					updateRoutesFILE(routeHeadP);
					//删除对应的存档文件 TODO：深层筛选未重复站点删除
					strcpy(url, "save/");
					strcat(url, getRoutePointer(routeHeadP, sizeRouteList(routeHeadP) - 1)->routeID);
					strcat(url, ".txt");
					remove(url);
					MessageBox(NULL, TEXT("成功删除路线"), TEXT("操作成功"), MB_OK);
					system("cls");
				} else if (input2 == 4) {
					addRoute(routeHeadP);
					updateRoutesFILE(routeHeadP);
					MessageBox(NULL, TEXT("成功增添路线\n建议继续进入该路线详细信息界面添加站点信息"), TEXT("操作成功"), MB_OK);
					//创建对应的路线存档文件，但仍然是空文件。
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
			printf("输入错误数字");
		}
	}
	free(url);
	
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
	MessageBox(NULL, TEXT("华中科技大学\nIOT1601 徐光磊\nC语言程序设计_课程设计作品\n物流信息查询系统"), TEXT("制作者信息"), MB_OK);
}

void printRoutePage(route * routeHeadP) {
	route * routeP = routeHeadP;
	system("cls");
	printf("------------------所有路线信息-------------------\n");
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
	printf("|  %-6s %-20s %-6s %-10s %-10s %-10s %-10s %-8s %-8s %-11s %-50s|\n\n", first, second, third, fourth, fifth, sixth, seventh, eighth, ninth, tenth, eleventh);

	register int i = 1;
	while (routeP != NULL) {
		printf("|%d:",i);
		printf("%-6s %-20s %-6d %-10.3f %-10.3f %-10s %-10s %-8s %-8s %-11s %-50s|\n", routeP->routeID, routeP->name, routeP->siteNums, routeP->miles, routeP->period, routeP->startSite, routeP->endSite, routeP->adminName, routeP->tel, routeP->mTel, routeP->email);
		routeP = routeP->next;
		i++;
	}
	printf("-------------------------------------------------\n");
	printf("|\t1.查看路线具体信息\t\t\t|\n");
	printf("|\t2.进行修改\t\t\t\t|\n");
	printf("|\t3.进行删除\t\t\t\t|\n");
	printf("|\t4.进行增添\t\t\t\t|\n");
	printf("|\t5.返回上级菜单\t\t\t\t|\n");
	printf("----------------按数字选择功能-------------------\n");
}

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
	free(siteP);
}

//The new route would be the last node in this list.
void addRoute(route * routeHeadP) {
	route * newRouteP = AddRouteNode(routeHeadP, sizeRouteList(routeHeadP));
	if (newRouteP != NULL) {
		char inputTemp[51];
		printf("---------------请输入新路线的信息----------------\n");
		printf("请输入编号:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->routeID, inputTemp);
		printf("请输入名称:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->name, inputTemp);
		printf("请输入总站点数:");
		short sitesCount = 0;
		scanf("%d%*c", &sitesCount);
		newRouteP->siteNums = sitesCount;
		printf("请输入总公里数:");
		float fMiles = 0;
		scanf("%f%*c", &fMiles);
		newRouteP->miles = fMiles;
		printf("请输入总耗时:");
		float fPeriod = 0;
		scanf("%f%*c", &fPeriod);
		newRouteP->period = fPeriod;
		printf("请输入起始站点编号:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->startSite, inputTemp);
		printf("请输入终止站点编号:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->endSite, inputTemp);
		printf("请输入负责人姓名:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->adminName, inputTemp);
		printf("请输入负责人办公室电话:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->tel, inputTemp);
		printf("请输入负责人移动电话:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->mTel, inputTemp);
		printf("请输入负责人电子邮箱:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newRouteP->email, inputTemp);
	} else {
		system("cls");
		printf("error\n");
	}
}
void addSite(site * siteHeadP) {
	printf("---------------请输入新站点的信息----------------\n");
	printf("请输入新站点在路线中的序号:");
	int seq = 0; scanf("%d%*c", &seq);
	site * newSiteP = AddSiteRoute(siteHeadP, seq-1);
	if (newSiteP != NULL) {
		char inputTemp[51];
		printf("请输入站点编号:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newSiteP->siteID, inputTemp);
		printf("请输入站点名称:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newSiteP->siteName, inputTemp);
		printf("请输入与起始站点距离:");
		float d2S = 0;
		scanf("%f%*c", &d2S);
		newSiteP->d2Start = d2S;
		printf("请输入与上一个站点距离:");
		float d2L = 0;
		scanf("%f%*c", &d2L);
		newSiteP->d2Last = d2L;
		printf("请输入与上一个站点交通耗时:");
		float fPeriod = 0;
		scanf("%f%*c", &fPeriod);
		newSiteP->time2Last = fPeriod;
		printf("请输入停留耗时:");
		float waitTimeN = 0;
		scanf("%f%*c", &waitTimeN);
		newSiteP->waitTime = waitTimeN;
		printf("请输入经过本站点固定路线编号:");
		noNfgets(inputTemp, 50, stdin);
		strcpy(newSiteP->routeIDArray, inputTemp);
		//自动完成部分
		newSiteP->siteSID = sizeSiteList(siteHeadP);
		strcpy(newSiteP->routeID, siteHeadP->routeID);
		//自动更新SID
		site * siteTemp = getSitePointer(siteHeadP, seq);
		while (siteTemp != NULL) {
			siteTemp->siteSID++;
			siteTemp = siteTemp->next;
		}
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

int changeRoute(route * routeSpecific) {
	printf("-------------------------------------------------\n");
	printf("1.编号\n2.名称\n3.总站点数\n4.总公里数\n5.总耗时\n6.起始站点编号\n7.终止站点编号\n8.负责人姓名\n9.负责人办公室电话\n10.负责人移动电话\n11.负责人电子邮箱\n请选择你要修改的属性:");
	int choose = 0;
	scanf("%d%*c", &choose);
	char input[51];//no free
	switch (choose) {
	case 1:
		printf("请输入新的编号:");
		char * oldID = (char *)malloc(sizeof(char) * 30);
		strcpy(oldID, routeSpecific->routeID);
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->routeID, input);
		//改变其编号对应的存档文件名
		changeSaveName(oldID, routeSpecific->routeID);
		//TODO: 还要改变该文件内所有旧路线编号！！！！！
		changeOldRouteID(routeSpecific);
		free(oldID);
		break;
	case 2:
		printf("请输入新的名称:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->name, input);
		break;
	case 3:
		printf("请输入新的总站点数:");
		int sitesCount = 0;
		scanf("%d%*c", &sitesCount);
		routeSpecific->siteNums = sitesCount;
		break;
	case 4:
		printf("请输入新的总公里数:");
		float newMiles = 0;
		scanf("%f%*c", newMiles);
		routeSpecific->miles = newMiles;
		break;
	case 5:
		printf("请输入新的总耗时:");
		float newPeriod = 0;
		scanf("%f%*c", newPeriod);
		routeSpecific->period = newPeriod;
		break;
	case 6:
		printf("请输入新的起始站点编号:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->startSite, input);
		break;
	case 7:
		printf("请输入新的终止站点编号:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->endSite, input);
		break;
	case 8:
		printf("请输入新的负责人姓名:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->adminName, input);
		break;
	case 9:
		printf("请输入新的负责人办公室电话:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->tel, input);
		break;
	case 10:
		printf("请输入新的负责人移动电话:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->mTel, input);
		break;
	case 11:
		printf("请输入新的负责人电子邮箱:");
		noNfgets(input, 50, stdin);
		strcpy(routeSpecific->email, input);
		break;
	default:
		printf("输入有误\n");
		return 0;
	}
	return 1;
}
int changeSite(site * siteSpecific) {
	printf("-------------------------------------------------\n");
	printf("1.站点编号\n2.站点名称\n3.与起始站点距离\n4.与上一个站点距离\n5.停留耗时\n6.经过本站点的固定路线编号\n\n请选择你要修改的属性:");
	int choose = 0;
	scanf("%d%*c", &choose);
	char input[50];//auto free
	switch (choose) {
	case 1:
		printf("请输入新的站点编号:");
		char * oldID = (char *)malloc(sizeof(char) * 30);
		strcpy(oldID, siteSpecific->siteID);
		noNfgets(input, 50, stdin);
		strcpy(siteSpecific->siteID, input);//向链表内部更新新的编号
		changeSaveName(oldID, siteSpecific->siteID);//改变其编号对应的存档文件名（联动改变下文
		free(oldID);
		break;
	case 2:
		printf("请输入新的站点名称:");
		noNfgets(input, 50, stdin);
		strcpy(siteSpecific->siteName, input);
		break;
	case 3:
		printf("请输入新的与起始站点距离:");
		float d2StartNew = 0;
		scanf("%f%*c", &d2StartNew);
		siteSpecific->d2Start = d2StartNew;
		break;
	case 4:
		printf("请输入新的与上一个站点距离:");
		float d2LastNew = 0;
		scanf("%f%*c", &d2LastNew);
		siteSpecific->d2Last = d2LastNew;
		break;
	case 5:
		printf("请输入新的停留耗时:");
		float newPeriod = 0;
		scanf("%f%*c", &newPeriod);
		siteSpecific->waitTime = newPeriod;
		break;
	case 6:
		printf("请输入新的经过本站点的固定路线编号:");
		noNfgets(input, 50, stdin);
		strcpy(siteSpecific->routeIDArray, input);
		break;
	default:
		printf("输入有误!\n");
		return 0;
	}
	return 1;
}

void printSitePage(route *routeP) {
	int inSitePage = 1;
	site* siteHeadP = routeP->firstSite;
	while (inSitePage) {
		system("cls");
		site* siteP = siteHeadP;
		printf("----------------路线编号：%6s 的所有站点信息---------------\n", siteHeadP->routeID);
		char second[] = "序号";
		char third[] = "站点编号";
		char fourth[] = "站点名称";
		char fifth[] = "与起始站距离";
		char sixth[] = "与上一个站距离";
		char seventh[] = "与上一站交通耗时";
		char eighth[] = "停留耗时";
		char ninth[] = "经过本站点的路线编号";
		printf("|%-4s %-10s %-50s %-12s %-14s %-16s %-8s %-50s|\n\n", second, third, fourth, fifth, sixth, seventh, eighth, ninth);

		while (siteP != NULL) {
			printf("|%-4d %-10s %-50s %-12.3f %-14.3f %-16.3f %-8.3f %-50s|\n", siteP->siteSID, siteP->siteID, siteP->siteName, siteP->d2Start, siteP->d2Last, siteP->time2Last, siteP->waitTime, siteP->routeIDArray);
			siteP = siteP->next;
		}
		printf("---------------------------------------------------------\n");
		printf("|\t1.查看站点具体信息\t\t\t|\n");
		printf("|\t2.进行修改\t\t\t\t|\n");
		printf("|\t3.进行删除\t\t\t\t|\n");
		printf("|\t4.进行增添\t\t\t\t|\n");
		printf("|\t5.返回上级菜单\t\t\t\t|\n");
		printf("--------------------按数字选择功能-----------------------\n");

		int seq = 0;
		scanf("%d%*c", &seq);

		switch (seq) {
		case 1:
			printf("想查看第几个站点的详细信息：");
			scanf("%d%*c", &seq);
			printCarPage(getSitePointer(siteHeadP, seq - 1));//进去该函数
			break;
		case 2:
			printf("想修改第几个站点的信息:");
			scanf("%d%*c", &seq);
			changeSite(getSitePointer(siteHeadP, seq - 1));
			MessageBox(NULL, TEXT("成功修改站点"), TEXT("操作成功"), MB_OK);
			break;
		case 3:
			printf("想删除第几个站点的信息:");
			scanf("%d%*c", &seq);
			siteHeadP = DelCarPos(siteHeadP, seq - 1);//get the new site head pointer
			//自动改变上文
			if (seq == 1) {//删除了第一个
				strcpy(routeP->startSite, siteHeadP->siteID);//更新上一级存储的第一站点名称数据
				updateRoutesFILE(routeP);
			} else if (seq == (sizeSiteList(siteHeadP)-2)) {//删除了最后一个
				strcpy(routeP->endSite, getSitePointer(siteHeadP, sizeSiteList(siteHeadP) - 1)->siteID);//更新上一级存储的终点站点名称数据
				updateRoutesFILE(routeP);
			}
			//自动更新序号
			site * stepSite = getSitePointer(siteHeadP, seq - 1);
			while (stepSite != NULL) {
				stepSite->siteSID = stepSite->siteSID - 1;
				stepSite = stepSite->next;
			}
			updateSitesFILE(siteHeadP);
			//TODO：不方便删除站点数据，应筛选是否有被其他路线占用
			MessageBox(NULL, TEXT("成功删除站点"), TEXT("操作成功"), MB_OK);
			break;
		case 4:
			//增添逻辑
			addSite(siteHeadP);
			updateSitesFILE(siteHeadP);
			MessageBox(NULL, TEXT("成功增添站点\n建议继续进入该站点详细信息界面添加站点信息"), TEXT("操作成功"), MB_OK);
			//创建对应的站点存档文件，但仍然是空文件。
			char *url = malloc(sizeof(char) * 20);
			strcpy(url, "save/");
			strcat(url, getSitePointer(siteHeadP, sizeSiteList(siteHeadP) - 1)->siteID);
			strcat(url, ".txt");
			FILE * newF = fopen(url, "w");
			fclose(newF);
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
void printCarPage(site * siteP) {
	system("cls");
	car * carHeadP = siteP->carHeadP;
	int inCarPage = 1;
	/*while (inCarPage) {

	}*/
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

void changeOldRouteID(route * routeSpecific) {
	site* siteP = routeSpecific->firstSite;
	while (siteP != NULL) {
		strcpy(siteP->routeID, routeSpecific->routeID);
		siteP = siteP->next;
	}
	updateSitesFILE(routeSpecific->firstSite);
}


