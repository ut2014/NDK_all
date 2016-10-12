package com.it5.ndk;

/**
 * Created by IT5 on 2016/10/11.
 */

public class DataProvider {

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    //将Java中的两个int值 传给C语言, 进行相加后, 返回java语言 shuliang.han.ndkparameterpassing.DataProvider
    public native int add(int x, int y);

    //将Java字符串传递给C语言, C语言处理字符串之后, 将处理结果返回给java
    public native String sayHelloInc(String s);

    //将java中的int数组传递给C语言, C语言为每个元素加10, 返回给Java
    public native int[] intMethod(int[] nums);

}
