/**
* 货物的基本信息：*Type : 装货、卸货的货物的种类
*                  *Volume	: 货物所占容量，（单位立方米）
*/
typedef struct Good {
	char uploadType[10];
	float upVolume;
	char downloadType[10];
	float downVolume;
} good;

/**
* 配送车辆的基本信息：	carID： 车辆牌照
* 					    routeID：执行配送路线编号
* 					    driverName： 司机姓名
* 					    driverTel： 司机移动电话
*						carID: 车辆编号
* 					    goodList： 运货清单
*/
typedef struct Car {
	char carID[9];
	char routeID[7];
	char driverName[9];
	char driverTel[12];
	char siteID[11];
	good * good;
	struct Car * next;
} car;

/**
* 经停站点详细信息:	routeNums: 固定配送路线数量
*					    routeIDArray: 固定配送路线编号的数组
*				    	siteSID: 站点序号
*					    siteID: 站点编号
*					    siteNames: 站点名称
*					    d2Start: 与初始站点距离
*					    d2Last: 与上一个站点距离
*					    t2Last: 与上一个站点交通耗时
*					    tWait: 停留耗时
*					    next: 指向下一个站点的指针
*/
typedef struct Site {
	char routeID[7];
	int siteSID;
	char siteID[11];
	char siteName[51];
	float d2Start;
	float d2Last;
	float time2Last;
	float waitTime;
	char routeIDArray[50];
	struct Car * carHeadP;
	struct Site * next;

} site;

/**
* 配送路线详细信息:	routeID: 固定配送路线编号
*				    	name: 固定配送路线编号名称
*				    	siteNums: 固定配送路线总站点数
*				    	miles: 固定配送路线总公里数
*				    	period: 全站点配送总耗时
*				    	startSite: 起始站点编号
*				    	endSite: 终止站点编号
*				    	adminName: 负责人姓名
*				    	tel: 负责人办公室电话
*				    	mTel: 负责人移动电话
*				    	email: 负责人电子邮箱
*				    	firstSite: 指向站点（即第一个站点）的指针
*				    	next: 指向下一个路线的指针
*/
typedef struct Route {
	char routeID[7];
	char name[21];
	short siteNums;
	float miles;
	float period;
	char startSite[11];
	char endSite[11];
	char adminName[9];
	char tel[9];
	char mTel[12];
	char email[51];
	struct Site * firstSite;//指向该路线的第一个站点，并形成路线链表
	struct Route * next;
} route;

