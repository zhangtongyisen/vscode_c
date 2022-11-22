#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
 
//避免使用魔法字符串
#define NORMAL 0  			//正常
#define TIME_OUT 1			//超时
#define THREE_DUP_ACK 2		//3个重复ACK
 
 
//全局参数
const int MSS=100;//单个报文段长度 规定为100B
int ssthresh=3*MSS;//慢启动门限 初值为16
int cwnd=1*MSS;//拥塞窗口，以MSS为单位。初值为1  
int index=1;//传播轮次
int transData=0;//防止程序无休止的死循环 设置总传递的字节  且策略简单定为每次只计算成功传送的，一旦拥塞就假设全部丢失
int sumData;//本次要传递的 总数据量大小 单位字节
 
/**随机概率产生拥塞
	返回值:
		0:未丢包，网络正常
		1:重传计时器超时   				对应策略:慢启动
		2:3个重复ACK 也即是快速重传		对应策略:快速恢复
*/
int isCrowd(int cwnd){
	int p=cwnd/MSS*2;//产生拥塞概率为p% 也即是 窗口大小/50*100%
	if(rand()%101<p){//p%的概率发生拥塞
		if(rand()%101<50){//50%概率超时
			return TIME_OUT;
		}else{//50%概率返回3个重复ACK 也即是快速重传
			return THREE_DUP_ACK;
		}
	}else{
		return NORMAL;
	}
}
 
 
//开始传输
void StartTrans(){
	bool isSlowStart=true;
 
	//传输数据
	transData+=cwnd;
	if(cwnd<ssthresh){//慢启动
		cout<<"***********************第"<<index++<<"轮传输***********************"<<endl;
		cout<<"慢启动:拥塞窗口cwnd="<<cwnd/MSS<<",慢启动门限ssthresh="<<ssthresh/MSS<<endl;
	}else{//cwnd>=ssthresh  拥塞避免
		cout<<"***********************第"<<index++<<"轮传输***********************"<<endl;
		cout<<"拥塞避免:拥塞窗口cwnd="<<cwnd/MSS<<",慢启动门限ssthresh="<<ssthresh/MSS<<endl;
		isSlowStart=false;
	}
 
	//本轮数据传输完毕，开始判断是否拥塞
	int crow=isCrowd(cwnd);
	if(!crow){//没有拥塞
		if(isSlowStart){//慢启动
			cout<<"检测到网络正常,将窗口加倍!"<<endl;
			cwnd*=2;//窗口加倍
		}else{//拥塞避免
			cout<<"检测到网络正常,将窗口线性增加!"<<endl;
			cwnd+=MSS*(1.0*MSS/cwnd)*cwnd/MSS;
		}
	}else if(crow==TIME_OUT){//超时 (不论此时慢启动还是拥塞避免 策略一样!)
		transData-=cwnd;
		//慢启动
		cout<<"重传计时器超时,回退慢启动!门限置当前窗口减半，窗口置1!"<<endl;
		ssthresh=cwnd/2;
		cwnd=1*MSS;
	}else if(crow==THREE_DUP_ACK){//3个重复ACK
		cout<<"收到3个重复ACK，采取快恢复策略!门限置当前窗口减半,窗口置新门限!"<<endl;
		ssthresh=cwnd/2;
		cwnd=ssthresh;
	}else{
		cout<<"判断拥塞异常!异常返回值:"<<crow<<endl;
		exit(1);
	}
 
	if(transData<sumData)
		cout<<"已经传输"<<transData<<"B,还剩"<<sumData-transData<<"B"<<endl;
	else{
		cout<<"传输完毕!"<<endl;
		return;
	}
	cout<<endl;
	Sleep(1000*(cwnd%3)+1);//随机停1~3秒
	StartTrans();//不断递归循环 直到发送完毕
}
 
 
int main(){
	srand(time(0));
	// freopen("in.txt","r",stdin);
	// freopen("运行结果.txt","w",stdout);
	cout<<"输入本次传送数据量的大小(单位字节B):";
	cin>>sumData;
	cout<<"*********************************开始传输**********************************\n"<<endl;
	StartTrans();
	return 0;
}
