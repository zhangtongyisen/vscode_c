#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
 
//����ʹ��ħ���ַ���
#define NORMAL 0  			//����
#define TIME_OUT 1			//��ʱ
#define THREE_DUP_ACK 2		//3���ظ�ACK
 
 
//ȫ�ֲ���
const int MSS=100;//�������Ķγ��� �涨Ϊ100B
int ssthresh=3*MSS;//���������� ��ֵΪ16
int cwnd=1*MSS;//ӵ�����ڣ���MSSΪ��λ����ֵΪ1  
int index=1;//�����ִ�
int transData=0;//��ֹ��������ֹ����ѭ�� �����ܴ��ݵ��ֽ�  �Ҳ��Լ򵥶�Ϊÿ��ֻ����ɹ����͵ģ�һ��ӵ���ͼ���ȫ����ʧ
int sumData;//����Ҫ���ݵ� ����������С ��λ�ֽ�
 
/**������ʲ���ӵ��
	����ֵ:
		0:δ��������������
		1:�ش���ʱ����ʱ   				��Ӧ����:������
		2:3���ظ�ACK Ҳ���ǿ����ش�		��Ӧ����:���ٻָ�
*/
int isCrowd(int cwnd){
	int p=cwnd/MSS*2;//����ӵ������Ϊp% Ҳ���� ���ڴ�С/50*100%
	if(rand()%101<p){//p%�ĸ��ʷ���ӵ��
		if(rand()%101<50){//50%���ʳ�ʱ
			return TIME_OUT;
		}else{//50%���ʷ���3���ظ�ACK Ҳ���ǿ����ش�
			return THREE_DUP_ACK;
		}
	}else{
		return NORMAL;
	}
}
 
 
//��ʼ����
void StartTrans(){
	bool isSlowStart=true;
 
	//��������
	transData+=cwnd;
	if(cwnd<ssthresh){//������
		cout<<"***********************��"<<index++<<"�ִ���***********************"<<endl;
		cout<<"������:ӵ������cwnd="<<cwnd/MSS<<",����������ssthresh="<<ssthresh/MSS<<endl;
	}else{//cwnd>=ssthresh  ӵ������
		cout<<"***********************��"<<index++<<"�ִ���***********************"<<endl;
		cout<<"ӵ������:ӵ������cwnd="<<cwnd/MSS<<",����������ssthresh="<<ssthresh/MSS<<endl;
		isSlowStart=false;
	}
 
	//�������ݴ�����ϣ���ʼ�ж��Ƿ�ӵ��
	int crow=isCrowd(cwnd);
	if(!crow){//û��ӵ��
		if(isSlowStart){//������
			cout<<"��⵽��������,�����ڼӱ�!"<<endl;
			cwnd*=2;//���ڼӱ�
		}else{//ӵ������
			cout<<"��⵽��������,��������������!"<<endl;
			cwnd+=MSS*(1.0*MSS/cwnd)*cwnd/MSS;
		}
	}else if(crow==TIME_OUT){//��ʱ (���۴�ʱ����������ӵ������ ����һ��!)
		transData-=cwnd;
		//������
		cout<<"�ش���ʱ����ʱ,����������!�����õ�ǰ���ڼ��룬������1!"<<endl;
		ssthresh=cwnd/2;
		cwnd=1*MSS;
	}else if(crow==THREE_DUP_ACK){//3���ظ�ACK
		cout<<"�յ�3���ظ�ACK����ȡ��ָ�����!�����õ�ǰ���ڼ���,������������!"<<endl;
		ssthresh=cwnd/2;
		cwnd=ssthresh;
	}else{
		cout<<"�ж�ӵ���쳣!�쳣����ֵ:"<<crow<<endl;
		exit(1);
	}
 
	if(transData<sumData)
		cout<<"�Ѿ�����"<<transData<<"B,��ʣ"<<sumData-transData<<"B"<<endl;
	else{
		cout<<"�������!"<<endl;
		return;
	}
	cout<<endl;
	Sleep(1000*(cwnd%3)+1);//���ͣ1~3��
	StartTrans();//���ϵݹ�ѭ�� ֱ���������
}
 
 
int main(){
	srand(time(0));
	// freopen("in.txt","r",stdin);
	// freopen("���н��.txt","w",stdout);
	cout<<"���뱾�δ����������Ĵ�С(��λ�ֽ�B):";
	cin>>sumData;
	cout<<"*********************************��ʼ����**********************************\n"<<endl;
	StartTrans();
	return 0;
}
