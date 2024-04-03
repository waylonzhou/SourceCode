package com.waylon.myapplication;

public class MyNativeLibrary {
    static {
        System.loadLibrary("myapplication");
    }

    public static native void myNativeMethod();
    public static native int get_add_result(int a,int b);
}
