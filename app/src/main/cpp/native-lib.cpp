#include <jni.h>
#include <string>
#include <android/log.h>

#define LOG_TAG "System.out"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
char* Jstring2str(JNIEnv *nv, jstring str);
extern "C"
{
jstring
Java_com_it5_ndk_DataProvider_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
};
jstring
Java_com_it5_ndk_DataProvider_sayHelloInc(JNIEnv *env,jobject obj,jstring str){
    char *p=(char *)Jstring2str(env,str);
    //打印Java传递过来的数据
    LOGI("java JNI string parameter is :%S",p);
    char *append ="append";
    //strcat(dest, source) 函数可以将source字符串 添加到dest字符串后面

    return env->NewStringUTF(strcat(p,append));
};
jintArray
Java_com_it5_ndk_DataProvider_intMethod(JNIEnv *env,jobject obj,jintArray arr){
    //获取arr大小
    int len =env->GetArrayLength(arr);
    //在logCat中打印arr的大小
    LOGI("the length of array is %d",len);
    //如果长度为0, 返回arr
    if (len==0) {
        return arr;
    }
    //如果长度大于0, 那么获取数组中的每个元素
    jint* p = env->GetIntArrayElements(arr, 0);
    //打印出数组中每个元素的值
    int i=0;
    for (; i <len; i++) {
        LOGI("arr[%d]=%d",i,*(p+i));
    }
    return arr;
};
//方法签名, Java环境 和 调用native方法的类 必不可少, 后面的参数就是native方法的参数
jint
Java_com_it5_ndk_DataProvider_add(JNIEnv *env,jobject obj,jint x,jint y){
    //Java中的int对应的是C语言中的long类型, 对应JNI中的jint类型, C语言中
    LOGI("JNI_log : x=%d , y=%d",x,y);
    return x+y;
};

//C调用java方法得到结果
jint
Java_com_it5_ndk_DataProvider_c2java(JNIEnv *env,jobject obj){
    //Java中的int对应的是C语言中的long类型, 对应JNI中的jint类型, C语言中
//    LOGI("JNI_log : x=%d , y=%d",x,y);
    char* classname="com/it5/ndk/DataProvider";
    //得到类的返回值
    jclass dpclazz=env->FindClass(classname);
    //通过类，找方法的id
    jmethodID  mid=env->GetMethodID(dpclazz,"javaAdd","(II)I");

    jint bint=env->CallIntMethod(obj, mid,3,4);
    return bint;
};
}
//java中的jstring, 转化为c的一个字符数组
char* Jstring2str(JNIEnv *env, jstring str) {
    //声明了一个字符串变量 rtn
    char* rtn=NULL;
    //找到Java中的String的Class对象
    jclass clsstring=env->FindClass("java/lang/String");
    //创建一个Java中的字符串 "GB2312"
    jstring strencode=env->NewStringUTF("GB2312");
    /*
    * 获取String中定义的方法 getBytes(), 该方法的参数是 String类型的, 返回值是 byte[]数组
    * "(Ljava/lang/String;)[B" 方法前面解析 :
    * -- Ljava/lang/String; 表示参数是String字符串
    * -- [B : 中括号表示这是一个数组, B代表byte类型, 返回值是一个byte数组
    */
    jmethodID  mid=env->GetMethodID(clsstring,"getBytes","(Ljava/lang/String;)[B");
    //调用Java中的getBytes方法, 传入参数介绍 参数②表示调用该方法的对象, 参数③表示方法id , 参数④表示方法参数
    jbyteArray  barr=(jbyteArray)env->CallObjectMethod(str, mid,
                                              strencode); // String .getByte("GB2312");
    //获取数组的长度
    jsize  alen=env->GetArrayLength(barr);
    //获取数组中的所有的元素 , 存放在 jbyte*数组中
    jbyte* ba=env->GetByteArrayElements(barr,JNI_FALSE);
    //将Java数组中所有元素拷贝到C的char*数组中, 注意C语言数组结尾要加一个 '\0'
    if (alen>0) {
        rtn=(char*)malloc(alen+1);//new   char[alen+1]; "\0"
        memcpy(rtn,ba,alen);
        rtn[alen]='\0';
    }
    env->ReleaseByteArrayElements(barr,ba,0);//释放内存
    return rtn;
}
