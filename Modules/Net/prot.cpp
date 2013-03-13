/*=============================================================================
#     FileName: prot.cpp
#         Desc: 实现协议的序列化和反序列化
#       Author: hanxi
#        Email: hanxi.com@gmail.com
#     HomePage: http://hanxi.cnblogs.com
#      Version: 0.0.1
#   LastChange: 2013-03-10 16:32:46
#      History:
=============================================================================*/

#include "prot.h"

#include "log.h"

I2M Prot::sm_protDic;      //协议词典 

void Prot::s_init()
{
    S2A s2a;
    AutoType a1("hanxi");
    AutoType a2("911203");
    s2a.insert(S2A::value_type("name",a1));
    s2a.insert(S2A::value_type("passwd",a2));
    sm_protDic.insert(I2M::value_type(1,s2a));
    s2a.clear();
    a1 = 256;
    s2a.insert(S2A::value_type("count",a1));
    sm_protDic.insert(I2M::value_type(2,s2a));
}


// 用第一个字节保存整数的位数以及是正还是负
// 前4位区分正负,0表示负，F表是正
// 后4为区分位数,1表示8位，2表示16位，4表示32位
static const char T1 = 0xF1; // 正,8位
static const char t1 = 0x01; // 负,8位
static const char T2 = 0xF2; // 正,16位
static const char t2 = 0x02; // 负,16位
static const char T3 = 0xF4; // 正,32位
static const char t3 = 0x04; // 负,32位

int unSerializeIntValue(long &value, char* buffer, int bufferlen){
    Log log(__LOGARG__,5);
	try{
		if(bufferlen<=1) return 0;
		
		char T = 0;               //取第1个字节
		
		memcpy(&T,buffer,1);
		int totellen = 1;
		
		log << std::hex << "0x" << (int)T << std::dec;
		
		bool positive = ((T&0xF0)==0xF0)?true:false; // 判断前4位是F表示正数
        bool positive2 = ((T&0xF0)==0x00)?false:true;// 复查前4位是0表示负数
        if (positive!=positive2) {
            log << "wrong int type, unknow sign" << Log::endl;
            return 0;
        }
		if ( positive ) {
            log << "[+]" << Log::endl;
		}else {
            log << "[-]" << Log::endl;
		}
		bool isInt8  = T&0x01;
		bool isInt16 = T&0x02;
		bool isInt32 = T&0x04;
		
        if( isInt8 ){
			assert(sizeof(char)==1);
			if((bufferlen-totellen)<sizeof(char)) return -1;
			char v8 = 0;
			memcpy((char*)&v8,buffer+totellen,sizeof(char));
			value = positive?(unsigned char)v8:(signed char)-v8;
			totellen+=sizeof(char);
			
            log << value << "是8bit的整型" << Log::endl;
			if( isInt32 || isInt16 ){
				log << "[32bit]" << (isInt32?"YES":"NO") << Log::endl;
				log << "[16bit]" << (isInt16?"YES":"NO") << Log::endl;
				log << "(**wrong int type**)" << Log::endl;
				return 0;
			}
			return totellen;
		}
		else if( isInt16 ){
			assert(sizeof(short)==2);
			if((bufferlen-totellen)<sizeof(short)) return -1;
			short v16 = 0;
			memcpy((char*)&v16,buffer+totellen,sizeof(short));
			value = positive?(unsigned short)v16:(signed short)-v16;
			totellen+=sizeof(short);
			
            log << value << "是16bit的整型" << Log::endl;
			if( isInt32 || isInt8 ){
				log << "[32bit]" << (isInt32?"YES":"NO") << Log::endl;
				log << "[8bit]" << (isInt8?"YES":"NO") << Log::endl;
				log << "(**wrong int type**)" << Log::endl;
				return 0;
			}
			return totellen;
		}
        else if( isInt32 ){
			assert(sizeof(int)==4);
			if((bufferlen-totellen)<sizeof(int)) return -1;
			int v32 = 0;
			memcpy((char*)&v32,buffer+totellen,sizeof(int));
			value = positive?(unsigned int)v32:(signed int)-v32;
			totellen+=sizeof(int);
			
            log << value << "是32bit的整型" << Log::endl;
			if( isInt16 || isInt8 ){
				log << "[16bit]" << (isInt16?"YES":"NO") << Log::endl;
				log << "[8bit]" << (isInt8?"YES":"NO") << Log::endl;
				log << "(**wrong int type**)" << Log::endl;
				return 0;
			}
			return totellen;
		}
		else{
			log << "(invalid int type)" << Log::endl;
			
			return 0;
		}
		
	}catch(...){
		log << "(mem error)" << Log::endl;
		
		return 0;
	}
	
	return 0;
}

int serializeIntValue(long value,char *buffer,int bufferlen){
    Log log(__LOGARG__,5);
	try{
		bool positive = true;
		if(value<0) {
			positive = false;
			value = -value;
            log << "-" << value << Log::endl;
		}else{
            log << "+" << value << Log::endl;
		}
		
		//assert((0xFFFFFFFF00000000&value)==0); // 保证兼容32位的机器
		
		unsigned int value32 = (int)value; //先截断
        bool isInt8  = (value32<=0xFF)?true:false;
        bool isInt16 = (value32<=0xFFFF)?true:false;
        bool isInt32 = (value32<=0xFFFFFFFF)?true:false;
		void *value32address = &value32;
		if (isInt8) { // 8bit
			// 1个字节足够了
			assert(1==sizeof(char));
			if(bufferlen<2) return 0;
			if( positive>0 ){
				memcpy(buffer,&T1,1);
                int t = T1;
                log << std::hex << "[8bit]0x" << t << std::dec << Log::endl;
			}else{
                int t = t1;
                log << std::hex << "[8bit]0x" << t << std::dec << Log::endl;
			}
			
			value = value<<24;
			memcpy(buffer+1,value32address,sizeof(char));
			log << "[8bit]YES" << Log::endl;

			return 2;
		}
        else if(isInt16){ //16bit
			assert(2==sizeof(short)); // 同理
			if(bufferlen<3) return 0;
			if( positive>0 ){
				memcpy(buffer,&T2,1);
                int t = T2;
                log << std::hex << "[8bit]0x" << t << std::dec << Log::endl;
			}else{
				memcpy(buffer,&t2,1);
                int t = t2;
                log << std::hex << "[8bit]0x" << t << std::dec << Log::endl;
			}
			value = value<<16;
			memcpy(buffer+1,value32address,sizeof(short));
			log << "[16bit]YES" << Log::endl;
			return 3;
		}
        else if(isInt32){ //32bit
			assert(4==sizeof(int)); // 保证int是32位的
			if(bufferlen<5) return 0;
			if( positive>0 ){
				memcpy(buffer,&T3,1);
                int t=T3;
                log << std::hex << "[8bit]0x" << t << std::dec << Log::endl;
			}else{
				memcpy(buffer,&t3,1);
                int t=t3;
                log << std::hex << "[8bit]0x" << t << std::dec << Log::endl;
			}
			memcpy(buffer+1,value32address,sizeof(int));
			log << "[32bit]YES" << Log::endl;
			return 5;
		}
        else {
			log << "(invalid int type). maybe is a long long type" << Log::endl;

            return 0;
        }
    }
	catch(...){
		log << "(mem error)" << Log::endl;

        return 0;
	}

	return 0;
}

void testSerializeIntValueUnserializeIntValue()
{
    Log log(__LOGARG__,1);
    char buf[1024] = {0};
    long value;
    serializeIntValue(0xff,buf,1024);
    unSerializeIntValue(value,buf,1024);
    log << "value1=" << value << Log::endl;
    serializeIntValue(0xffff,buf,1024);
    unSerializeIntValue(value,buf,1024);
    log << "value2=" << value << Log::endl;
    serializeIntValue(0xffffffff,buf,1024);
    unSerializeIntValue(value,buf,1024);
    log << "value3=" << value << Log::endl;
}

int serializeStringValue(const char* value,char *buffer,int bufferlen){
	try{
		int length = (int)strlen(value);
		int totellen = 0;
		int ret = 0;
		ret = serializeIntValue(length,buffer,bufferlen);
		totellen+=ret;
		if( totellen>0 ){
			if((bufferlen-totellen)<length) return 0;
			memcpy(buffer+totellen,value,length);
			totellen+=length;
			return totellen;
		}else{
			return 0;
		}
	}
	catch(...){
		return 0;
	}
	return 0;
}

void testSerializeStringValue()
{
    Log log(__LOGARG__,1);
    char buf[1024] = {0};
    const char* str = "hello";
    serializeStringValue(str,buf,1204);
    long len=0;
    int ret = unSerializeIntValue(len,buf,1024);
    std::cout << ret << std::endl;
    if (len>0) {
        const char *pstr = buf+ret;
        static char tmp[1024]={0};
        strncpy(tmp,pstr,len);
        tmp[len]='\0';
        log << tmp << Log::endl;
    }

}

// @return: totellen -> 序列化该prot消耗的buf长度
int Prot::serialize(char* bufferAddr, int bufferLength)
{
    // 协议buffer格式
    // ----------
    // |protId  |
    // |--------|
    // |protLen |
    // |--------|
    // |prot    |
    // |--------|
    Log log(__LOGARG__,1);
    int lenlimit = bufferLength;
    int protId = m_prot->first;
    int totellen = 0;
    
    log << "protId=" << protId << Log::endl;
    log << "lenlimit=" << lenlimit << Log::endl;

    memcpy(bufferAddr+totellen, (void*)&protId, sizeof(int));
    totellen += sizeof(int);
    char *ptotellen = bufferAddr+totellen;
    totellen += sizeof(int);


    S2A &prot = m_prot->second;
    int ret = 0;
    for (S2AIter iter=prot.begin(); iter!=prot.end(); ++iter) {
        ret = 0;
        AutoType &value = iter->second;
        char type = value.getType();
        if (type==VALUE_TYPE_NUMBER) {
            ret = serializeIntValue(value.getNum(),bufferAddr+totellen,lenlimit-totellen);
            if (ret==0) break;
        }
        else if (type==VALUE_TYPE_STRING) {
            ret = serializeStringValue(value.getStr(),bufferAddr+totellen,lenlimit-totellen);
            if (ret==0) break;
        }
        totellen += ret;
    }
    if (ret==0) return 0;
    memcpy(ptotellen, (void*)&totellen, sizeof(int));
    log << "totellen=" << totellen << Log::endl;
    return totellen;
}

bool Prot::pickBufferInfo(char* bufferAddr, int bufferLength, int& o_protId, int& o_protLen)
{
    if (bufferLength>=8) {
        int protId=-1;
        int protLen=0;
        memcpy((char*)&protId,bufferAddr,sizeof(int));
        memcpy((char*)&protLen,bufferAddr+sizeof(int),sizeof(int));
        o_protId = protId;
        o_protLen = protLen;
        return true;
    }
    return false;
}

int Prot::unSerialize(char* bufferAddr, int bufferLength)
{
    //进入本函数,默认调用者已经使用了CFGPickBufferInfo检查了length,在这里不在头检查,在运算中检查
    Log log(__LOGARG__,1);
    int lenlimit = bufferLength;
    log << "lenlimit=" << lenlimit << Log::endl;

    if (lenlimit<8) return 0;
    // 直接跳过protId
    int totellen = 4;
    int pkglen = 0;
    memcpy((char*)&pkglen,bufferAddr+totellen,sizeof(int));
    totellen += sizeof(int);
    
    S2A &prot = m_prot->second;
    int ret = 0;
    for (S2AIter iter=prot.begin(); iter!=prot.end(); ++iter) {
        ret=0;
        AutoType &value = iter->second;
        char type = value.getType();
        if (type==VALUE_TYPE_NUMBER) {
            long num = 0;
            ret = unSerializeIntValue(num,bufferAddr+totellen,lenlimit-totellen);
            if (ret==0) break;
            value = num;
            totellen += ret;
        }
        else if (type==VALUE_TYPE_STRING) {
            long strLen = 0;
            ret = unSerializeIntValue(strLen,bufferAddr+totellen,lenlimit-totellen);
            if (ret==0) break;
            totellen += ret;
            const char *pstr = bufferAddr+totellen;
            value = AutoType(pstr,strLen);
            totellen += strLen;
        }
    }
    if (ret==0) return 0;
    return totellen;
}

void testSerializeUnserialize()
{
    Log log(__LOGARG__,1);
    Prot prot(1);
    prot.setField("name","hanxi2");
    char bufferAddr[10240] = {0};
    prot.serialize(bufferAddr, 10240);
    for (int i=0; i<1024; i++)
    {
        log << bufferAddr[i] << ",";
    }
    log << Log::endl;
    prot.setField("name","hanxixi");
    prot.unSerialize(bufferAddr, 10240);
    log << (prot.getField("name")).getStr() << Log::endl;
}

