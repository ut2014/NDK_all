package com.it5.ndk;

import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
public class ExampleUnitTest {
    @Test
    public void addition_isCorrect() throws Exception {
        assertEquals(4, 2 + 2);
        System.out.println("void func() --> " + SignatureGen.getSignature(Void.class));
        System.out.println("boolean func() --> " + SignatureGen.getSignature(Boolean.class));
        System.out.println("int func(boolean a) --> " + SignatureGen.getSignature(Integer.class,Boolean.class));
        System.out.println("int func(boolean a,String b) --> " + SignatureGen.getSignature(Integer.class,Boolean.class,String.class));
        System.out.println("int func(byte[] c) --> " + SignatureGen.getSignature(Integer.class,Byte[].class));
        System.out.println("long func(int n,String str,int arr) -->" + SignatureGen.getSignature(Long.class,Integer.class,String.class,Integer[].class));
    }
}