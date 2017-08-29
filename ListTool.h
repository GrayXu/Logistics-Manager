#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<DataStructure.h>

/* CURD for routes */

/* 创建储存路线数据的线性表*/
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

//创建信息链表，返回指向该路线的第一个站点的指针，
//从而外部可以将站点连接上路线结点
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
		char ** info = readRoute(StrLine);//进行字符串切分操作

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
		char ** info = readCar(StrLine);//进行字符串切分操作

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
good* creatGood(FILE * fText) {
	good* goodP = (good *)malloc(sizeof(good));
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

/* 打印链表，链表的遍历，TODO：需要做格式化，需要深度遍历(报表？？)*/
void printList(route *pHead) {
	// TODO
}

/* 清空单链表，TODO:   WARNING：需要下层释放后再调用(十字链表) or 深度遍历！！*/
void clearList(route *pHead) {
	route *pNext;

	while (pHead->next != NULL) {
		pNext = pHead->next;
		free(pHead);
		pHead = pNext;
	}
}

/* 返回链表的长度*/
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

/* 获得某位置结点的地址，让外部进行修改, 失败则返回空指针*/
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
car *getCarPointer(car *pHead, int pos) {

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

/* 向单链表中第pos个结点位置插入元素为x的结点(把该位置的往后挤)，若插入成功返回新结点的指针，否则返回NULL*/
route* AddRouteNode(route *HEAD, int pos) {
	route *pHead = HEAD;
	route *pPre = HEAD;//both set to the first( init)
	route *pNew = NULL;
	int i = 0;
	pNew = (route *)malloc(sizeof(route));

	if (pPre == NULL) {
		return NULL;//error
	}
	if (NULL == pHead) {
		return NULL;//error
	}

	if (pos == 0) {//add to be the first one
		pNew->next = HEAD;
	} else if (pos == sizeRouteList(HEAD)) {//add to be the last one
		route * lastRouteP = getRoutePointer(HEAD, pos - 1);
		lastRouteP->next = pNew;
		pNew->next = NULL;
	} else {
		while (pHead != NULL) {
			if (i == pos)
				break;
			pPre = pHead;
			pHead = pHead->next;
			++i;
		}
		pPre->next = pNew;
		pNew->next = pHead;

	}
	return pNew;
}
site * AddSiteNode(site *HEAD, int pos) {
	site *pHead = HEAD;
	site *pPre = HEAD;//both set to the first( init)
	site *pNew = NULL;
	int i = 0;
	pNew = (site *)malloc(sizeof(site));

	if (pPre == NULL) {
		return NULL;//error
	}
	if (NULL == pHead) {
		return NULL;//error
	}

	if (pos == 0) {//add to be the first one
		pNew->next = HEAD;
	} else if (pos == sizeSiteList(HEAD)) {//add to be the last one
		site * lastSiteP = getSitePointer(HEAD, pos - 1);
		lastSiteP->next = pNew;
		pNew->next = NULL;
	} else {
		while (pHead != NULL) {
			if (i == pos)
				break;
			pPre = pHead;
			pHead = pHead->next;
			++i;
		}
		pPre->next = pNew;
		pNew->next = pHead;

	}
	return pNew;
}
car * AddCarNode(car *HEAD, int pos) {
	car *pHead = HEAD;
	car *pPre = HEAD;//both set to the first( init)
	car *pNew = NULL;
	int i = 0;
	pNew = (car *)malloc(sizeof(car));

	if (pPre == NULL) {
		return NULL;//error
	}
	if (NULL == pHead) {
		return NULL;//error
	}

	if (pos == 0) {//add to be the first one
		pNew->next = HEAD;
	} else if (pos == sizeCarList(HEAD)) {//add to be the last one
		car * lastSiteP = getCarPointer(HEAD, pos - 1);
		lastSiteP->next = pNew;
		pNew->next = NULL;
	} else {
		while (pHead != NULL) {
			if (i == pos)
				break;
			pPre = pHead;
			pHead = pHead->next;
			++i;
		}
		pPre->next = pNew;
		pNew->next = pHead;
	}
	return pNew;
}

/* 从单链表中删除第pos个结点(兼容头尾), @return: the new head pointer.*/
route* DelRoutePos(route *HeadP, int pos) {
	route *pHead = HeadP;
	route *pTmp = HeadP;//pTmep即为被删除结点的前一个结点
	//防空指针
	if (NULL == pHead) {
		printf("DelPos函数执行，链表为空\n");
		return NULL;
	}
	register int i = 0;
	while (pHead != NULL) {
		if (i == pos)
			break;
		pTmp = pHead;
		pHead = pHead->next;
		++i;
	}
	if (i==0) {//即删除头结点
		route * returnP = pHead->next;//返回第二个结点
		free(pHead);
		return returnP;
	}
	pTmp->next = pHead->next;
	free(pHead);
	return HeadP;
}
site* DelSitePos(site *HeadP, int pos) {
	site *pHead = HeadP;
	site *pTmp = HeadP;//pTmep即为被删除结点的前一个结点
						//防空指针
	if (NULL == pHead) {
		printf("DelPos函数执行，链表为空\n");
		return NULL;
	}
	register int i = 0;
	while (pHead != NULL) {
		if (i == pos)
			break;
		pTmp = pHead;
		pHead = pHead->next;
		++i;
	}
	if (i == 0) {//即删除头结点
		route * returnP = pHead->next;//返回第二个结点
		free(pHead);
		return returnP;
	}
	pTmp->next = pHead->next;
	free(pHead);
	return HeadP;
}
car* DelCarPos(car *HeadP, int pos) {
	car *pHead = HeadP;
	car *pTmp = HeadP;//pTmep即为被删除结点的前一个结点
					   //防空指针
	if (NULL == pHead) {
		printf("DelPos函数执行，链表为空\n");
		return NULL;
	}
	register int i = 0;
	while (pHead != NULL) {
		if (i == pos)
			break;
		pTmp = pHead;
		pHead = pHead->next;
		++i;
	}
	if (i == 0) {//即删除头结点
		route * returnP = pHead->next;//返回第二个结点
		free(pHead);
		return returnP;
	}
	pTmp->next = pHead->next;
	free(pHead);
	return HeadP;
}

/* 交换2个元素的位置，记得检测头是否改变 */
void swapRoute(route **ppNode, int posA, int posB) {
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