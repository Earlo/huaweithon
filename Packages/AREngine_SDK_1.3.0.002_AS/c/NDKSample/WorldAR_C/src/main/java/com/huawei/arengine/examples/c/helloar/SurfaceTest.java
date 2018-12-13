package com.huawei.arengine.examples.c.helloar;

import android.app.Activity;
import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLUtils;
import android.util.Log;
import android.view.Surface;

import java.io.IOException;
import java.util.List;

public class SurfaceTest {
  static {
    System.loadLibrary("hello_ar_native");
  }

  private static final String TAG = "SurfaceTest";
  static AssetManager assetManager;

  public static native long getSurface(long val);

  public static native Surface createPreviewSurface(long val);

  public static native Surface[] createPreviewSurfaces(long val);

}
