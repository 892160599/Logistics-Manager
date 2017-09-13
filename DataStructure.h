/**
* ����Ļ�����Ϣ��*Type : װ����ж���Ļ��������
*                  *Volume	: ������ռ����������λ�����ף�
*/
typedef struct Good {
	char uploadType[10];
	float upVolume;
	char downloadType[10];
	float downVolume;
} good;

/**
* ���ͳ����Ļ�����Ϣ��	carID�� ��������
* 					    routeID��ִ������·�߱��
* 					    driverName�� ˾������
* 					    driverTel�� ˾���ƶ��绰
*						carID: �������
* 					    goodList�� �˻��嵥
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
* ��ͣվ����ϸ��Ϣ:	routeNums: �̶�����·������
*					    routeIDArray: �̶�����·�߱�ŵ�����
*				    	siteSID: վ�����
*					    siteID: վ����
*					    siteNames: վ������
*					    d2Start: ���ʼվ�����
*					    d2Last: ����һ��վ�����
*					    t2Last: ����һ��վ�㽻ͨ��ʱ
*					    tWait: ͣ����ʱ
*					    next: ָ����һ��վ���ָ��
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
* ����·����ϸ��Ϣ:	routeID: �̶�����·�߱��
*				    	name: �̶�����·�߱������
*				    	siteNums: �̶�����·����վ����
*				    	miles: �̶�����·���ܹ�����
*				    	period: ȫվ�������ܺ�ʱ
*				    	startSite: ��ʼվ����
*				    	endSite: ��ֹվ����
*				    	adminName: ����������
*				    	tel: �����˰칫�ҵ绰
*				    	mTel: �������ƶ��绰
*				    	email: �����˵�������
*				    	firstSite: ָ��վ�㣨����һ��վ�㣩��ָ��
*				    	next: ָ����һ��·�ߵ�ָ��
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
	struct Site * firstSite;//ָ���·�ߵĵ�һ��վ�㣬���γ�·������
	struct Route * next;
} route;

